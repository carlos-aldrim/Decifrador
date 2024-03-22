#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100000

// Função para calcular a pontuação de um texto decifrado com base na frequência de letras em português
int calcularPontuacao(char texto[]) {
    int pontuacao = 0;
    int frequencia[26] = {0}; // Array para contar a frequência de cada letra
    char letras_comuns[] = {'a', 'e', 'o', 's', 'r', 'i', 'n', 'd', 'm'};

    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha(texto[i])) {
            int indice = tolower(texto[i]) - 'a';
            frequencia[indice]++;
        }
    }

    // Atribuir pontuações com base na frequência de letras comuns em português
    for (int i = 0; i < sizeof(letras_comuns) / sizeof(letras_comuns[0]); i++) {
        int indice = letras_comuns[i] - 'a';
        pontuacao += frequencia[indice];
    }

    return pontuacao;
}

// Função para decifrar o texto usando a cifra de Vigenère com força bruta
void decifrarForcaBruta(char texto[], int texto_len) {
    char texto_decifrado[MAX_SIZE];
    char chave[MAX_SIZE];
    char melhor_decifrado[MAX_SIZE];
    char melhor_chave[MAX_SIZE];
    int melhor_pontuacao = 0;

    printf("\n\n\t\t\t===================================================");
    printf("\n\n\t\t\tAGUARDE UM INSTANTE, SEU TEXTO ESTA SENDO DECIFRADO");
    printf("\n\n\t\t\t===================================================");

    for (int k = 1; k <= 4; k++) { // Supondo que a chave tenha no máximo 4 caracteres
        for (int i = 0; i < k; i++) {
            chave[i] = 'A'; // Começando com todas as letras 'A'
        }
        chave[k] = '\0';
        
        do {
            int chave_len = strlen(chave);
            for (int i = 0, j = 0; i < texto_len; i++) {
                char letra = texto[i];
                if (isalpha(letra)) {
                    char base = isupper(letra) ? 'A' : 'a';
                    texto_decifrado[i] = ((toupper(letra) - toupper(chave[j]) + 26) % 26) + base;
                    j = (j + 1) % chave_len;
                } else {
                    texto_decifrado[i] = letra;
                }
            }
            texto_decifrado[texto_len] = '\0';

            // Calcular a pontuação do texto decifrado
            int pontuacao = calcularPontuacao(texto_decifrado);

            // Se a pontuação for maior que a melhor pontuação até agora, atualizar o melhor resultado
            if (pontuacao > melhor_pontuacao) {
                melhor_pontuacao = pontuacao;
                strcpy(melhor_decifrado, texto_decifrado);
                strcpy(melhor_chave, chave);
            }

            // Atualizar a chave para a próxima combinação
            int i = k - 1;
            while (i >= 0 && chave[i] == 'Z') {
                chave[i] = 'A';
                i--;
            }
            if (i < 0) // Todas as combinações foram tentadas
                break;
            chave[i]++;
        } while (1);
    }

    system("cls");

    printf("\t\t\t================================================");
    // Mostrar a chave utilizada
    printf("\n\n\t\tCHAVE UTILIZADA PARA DECIFRAR O TEXTO: %s\n", melhor_chave);
    // Imprimir o melhor resultado encontrado
    printf("\n\n\t\tTEXTO DECIFRADO MAIS PROVAVEL:\n\n%s\n", melhor_decifrado);
    printf("\n\t\t\t================================================"); 
}

// Obtem a mensagem a ser decifrada
void obterMensagem(char texto[]) {
    printf("\t\t\t================================================");
    printf("\n\t\t\t            CRIPTOGRAFIA - TRABALHO I           ");
    printf("\n\t\t\t================================================");
        
    printf("\n\n\t\tINSIRA A MENSAGEM CIFRADA: ");

    fgets(texto, MAX_SIZE, stdin);    

    printf("\n\n\t\t\t================================================");

    system("cls");
}

// Verifica se o usuario ja possui a chave
char obterOpcao() {
    char opc;  

    printf("\n\n\t\t\t================================================");

    printf("\n\n\t\tJA SABE QUAL O VALOR DA CHAVE?");

    printf("\n\n\t\t1 - SIM");
    printf("\n\t\t2 - NAO");
    printf("\n\t\t3 - SAIR");

    printf("\n\n\t\tESCOLHA A OPCAO DESEJADA: ");

    scanf(" %c", &opc); 

    printf("\n\n\t\t\t================================================");

    system("cls");

    return opc;
}

// Função para obter a chave do usuário
void obterChave(char chave[]) {
    printf("\n\n\t\t\t================================================");
    
    printf("\n\n\t\tQUAL O VALOR DA CHAVE? (No máximo 10 caracteres): ");
    scanf(" %[^\n]", chave);
    
    printf("\n\n\t\t\t================================================");
    
    system("cls");
}

// Função para decifrar o texto usando a cifra de Vigenère
void decifrarVigenere(char texto[], char chave[]) {
    int texto_len = strlen(texto);
    int chave_len = strlen(chave);
    char texto_decifrado[MAX_SIZE];
    
    for (int i = 0, j = 0; i < texto_len; i++) {
        char letra = texto[i];
        
        if (isalpha(letra)) {
            char base = isupper(letra) ? 'A' : 'a';
            texto_decifrado[i] = ((toupper(letra) - toupper(chave[j]) + 26) % 26) + base;
            j = (j + 1) % chave_len;
        } else {
            texto_decifrado[i] = letra;
        }
    }
    texto_decifrado[texto_len] = '\0';
    
    system("cls");

    printf("\t\t\t================================================");    
    // Imprimir o resultado encontrado
    printf("\n\n\t\tTEXTO DECIFRADO:\n\n%s\n", texto_decifrado);
    printf("\n\t\t\t================================================"); 
}

int main() {    
    system("cls");
        
    char texto[MAX_SIZE];
    obterMensagem(texto);

    char opc = obterOpcao();

    if (opc == '1') {    
        char chave[11]; // 10 caracteres + '\0'
        obterChave(chave); // Se o usuário conhece a chave, solicitamos a chave
        decifrarVigenere(texto, chave); // e deciframos o texto usando essa chave.
    } else if (opc == '2') {            
        decifrarForcaBruta(texto, strlen(texto)); // Se o usuário não conhece a chave, deciframos por força bruta.
    } else if (opc == '3') {     
        printf("\n\n\t\t\t\t\tATE LOGO" );
        printf("\n\n\t\t\t================================================");   
    } else {
        printf("\n\nOPCAO INVALIDA");
        printf("\n\n\t\t\t================================================");
    }

    return 0;
}

