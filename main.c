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

    frequencias_idioma = frequencias_portugues;

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
    mensagem[strcspn(mensagem, "\n")] = '\0';

    for (int i = 0; mensagem[i]; i++) {
        mensagem[i] = tolower(mensagem[i]);
    }

    decifrar_mensagem(mensagem, idioma);

    return 0;
}
