#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_ALFABETO 26

float frequencias_portugues[TAM_ALFABETO] = {
    14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28, 6.18, 0.40, 0.02, 2.78,
    4.74, 5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 4.63, 1.67, 0.01, 0.21,
    0.01, 0.47
};

float frequencias_ingles[TAM_ALFABETO] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15, 0.77, 4.03,
    2.41, 6.75, 7.51, 1.93, 0.10, 5.99, 6.33, 9.06, 2.76, 0.98, 2.36, 0.15,
    1.97, 0.07
};

float frequencias_espanhol[TAM_ALFABETO] = {
    12.02, 0.92, 1.18, 4.29, 13.11, 0.77, 1.42, 1.08, 4.96, 0.13, 0.17, 5.26,
    2.22, 4.41, 4.69, 0.31, 0.90, 6.42, 7.02, 3.87, 4.62, 1.05, 0.06, 0.48,
    0.01, 0.47
};

void calcular_frequencias(const char *texto, float *frequencias, int tamanho) {
    int total = 0;
    memset(frequencias, 0, tamanho * sizeof(float));

    while (*texto) {
        if (isalpha(*texto)) {
            frequencias[tolower(*texto) - 'a']++;
            total++;
        }
        texto++;
    }

    for (int i = 0; i < tamanho; i++) {
        frequencias[i] /= total;
    }
}

float comparar_frequencias(float *frequencias, float *frequencias_idioma, int tamanho) {
    float score = 0.0;
    for (int i = 0; i < tamanho; i++) {
        score += frequencias[i] * frequencias_idioma[i];
    }
    return score;
}

void decifrar_mensagem(const char *mensagem, const char *idioma) {
    float frequencias[TAM_ALFABETO];
    float *frequencias_idioma;

    if (strcmp(idioma, "portugues") == 0)
        frequencias_idioma = frequencias_portugues;
    else if (strcmp(idioma, "ingles") == 0)
        frequencias_idioma = frequencias_ingles;
    else if (strcmp(idioma, "espanhol") == 0)
        frequencias_idioma = frequencias_espanhol;
    else {
        printf("Idioma nao suportado.\n");
        return;
    }

    calcular_frequencias(mensagem, frequencias, TAM_ALFABETO);

    float max_score = 0.0;
    int deslocamento = 0;

    for (int i = 0; i < TAM_ALFABETO; i++) {
        float score = comparar_frequencias(frequencias, frequencias_idioma, TAM_ALFABETO);
        if (score > max_score) {
            max_score = score;
            deslocamento = i;
        }

        float temp = frequencias[0];
        for (int j = 0; j < TAM_ALFABETO - 1; j++) {
            frequencias[j] = frequencias[j + 1];
        }
        frequencias[TAM_ALFABETO - 1] = temp;
    }

    printf("Melhor palpite para o deslocamento: %d\n", deslocamento);
    printf("Mensagem decifrada: ");
    while (*mensagem) {
        if (isalpha(*mensagem)) {
            char caractere_decifrado = (*mensagem - 'a' - deslocamento + TAM_ALFABETO) % TAM_ALFABETO + 'a';
            printf("%c", caractere_decifrado);
        } else {
            printf("%c", *mensagem);
        }
        mensagem++;
    }
    printf("\n");
}

int main() {
    char mensagem[1000];
    char idioma[20];
    printf("Digite a mensagem cifrada: ");
    fgets(mensagem, sizeof(mensagem), stdin);
    mensagem[strcspn(mensagem, "\n")] = '\0'; // Remover a quebra de linha

    printf("Digite o idioma (portugues, ingles ou espanhol): ");
    scanf("%s", idioma);

    decifrar_mensagem(mensagem, idioma);

    return 0;
}
