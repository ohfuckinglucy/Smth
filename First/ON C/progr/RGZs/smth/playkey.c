#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char grid[5][5] = {
  {'P', 'L', 'A', 'Y', 'F'},
  {'I', 'R', 'E', 'X', 'M'},
  {'B', 'C', 'D', 'G', 'H'},
  {'J', 'K', 'N', 'O', 'S'},
  {'T', 'U', 'V', 'W', 'Z'}
};

void playKeyEncrypt(char *plaintext, char *ciphertext) {
  int index = 0;
  for (int i = 0; i < strlen(plaintext); i += 2) {
    char c1 = plaintext[i];
    char c2 = plaintext[i + 1];

    // Найти координаты в решетке
    int r1, c1, r2, c2;
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        if (grid[j][k] == c1) {
          r1 = j;
          c1 = k;
        }
        if (grid[j][k] == c2) {
          r2 = j;
          c2 = k;
        }
      }
    }

    // Заменить символы
    if (r1 == r2) {
      ciphertext[index++] = grid[r1][(c1 + 1) % 5];
      ciphertext[index++] = grid[r2][(c2 + 1) % 5];
    } else if (c1 == c2) {
      ciphertext[index++] = grid[(r1 + 1) % 5][c1];
      ciphertext[index++] = grid[(r2 + 1) % 5][c2];
    } else {
      ciphertext[index++] = grid[r1][c2];
      ciphertext[index++] = grid[r2][c1];
    }
  }
  ciphertext[index] = '\0';
}

int main() {
  char plaintext[100];
  char ciphertext[100];

  // Ввести текст
  printf("Введите текст для шифрования: ");
  scanf(" %[^\n]%*c", plaintext);

  // Зашифровать текст
  playKeyEncrypt(plaintext, ciphertext);

  // Сохранить зашифрованный текст в файл
  FILE *file = fopen("ciphertext.txt", "w");
  fprintf(file, "%s", ciphertext);
  fclose(file);

  printf("Зашифрованный текст: %s\n", ciphertext);

  return 0;
}
