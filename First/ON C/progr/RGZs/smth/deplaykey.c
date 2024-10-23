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

void playKeyDecrypt(char *ciphertext, char *plaintext) {
  int index = 0;
  for (int i = 0; i < strlen(ciphertext); i += 2) {
    char c1 = ciphertext[i];
    char c2 = ciphertext[i + 1];

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
      plaintext[index++] = grid[r1][(c1 - 1 + 5) % 5];
      plaintext[index++] = grid[r2][(c2 - 1 + 5) % 5];
    } else if (c1 == c2) {
      plaintext[index++] = grid[(r1 - 1 + 5) % 5][c1];
      plaintext[index++] = grid[(r2 - 1 + 5) % 5][c2];
    } else {
      plaintext[index++] = grid[r1][c2];
      plaintext[index++] = grid[r2][c1];
    }
  }
  plaintext[index] = '\0';
}

int main() {
  char ciphertext[100];
  char plaintext[100];

  // Считать зашифрованный текст из файла
  FILE *file = fopen("ciphertext.txt", "r");
  fscanf(file, "%s", ciphertext);
  fclose(file);

  // Дешифровать текст
  playKeyDecrypt(ciphertext, plaintext);

  printf("Расшифрованный текст: %s\n", plaintext);

  return 0;
}
