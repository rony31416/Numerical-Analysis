
#include <stdio.h>
#include <stdlib.h>

// Function to perform matrix multiplication
void matrixMultiply(int key[][3], int plaintext[], int result[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        result[i] = 0;
        for (j = 0; j < n; j++)
        {
            result[i] += key[i][j] * plaintext[j];
        }
        result[i] %= 26; // Modulo 26 for alphabets
    }
}

// Function to encrypt using Hill cipher
void hillCipherEncrypt(int key[][3], int plaintext[], int n)
{
    int i;
    int result[3];

    printf("Ciphertext: ");
    for (i = 0; i < n; i++)
    {
        printf("%c", plaintext[i] + 'A');
    }

    // Padding with 'X' if the plaintext size is not a multiple of n
    int padding = n - (n % 3);
    for (i = 0; i < padding; i++)
    {
        printf("X");
    }

    printf("\n");

    printf("Plaintext blocks: ");
    for (i = 0; i < n; i++)
    {
        printf("%c", plaintext[i] + 'A');
    }

    printf("\n");

    printf("Ciphertext blocks: ");
    for (i = 0; i < n; i += 3)
    {
        matrixMultiply(key, plaintext + i, result, 3);
        printf("%c%c%c", result[0] + 'A', result[1] + 'A', result[2] + 'A');
    }

    printf("\n");
}

int main()
{
    int key[3][3] = { {6, 24, 1}, {13, 16, 10}, {20, 17, 15} }; // Example key matrix
    int plaintext[9] = {0}; // Plaintext array

    printf("Enter 9 plaintext characters (A-Z): ");
    for (int i = 0; i < 9; i++)
    {
        char ch;
        scanf(" %c", &ch);
        plaintext[i] = ch - 'A';
    }

    hillCipherEncrypt(key, plaintext, 9);

    return 0;
}
/*Enter 9 plaintext characters (A-Z): hellorony
Ciphertext: helloronyXXXXXXXXX
Plaintext blocks: hellorony
Ciphertext blocks: XFJHRLIGD
*/
