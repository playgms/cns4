#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toUpperCase(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    unsigned int encryptionMatrix[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};
    unsigned int decryptionMatrix[3][3] = {{8, 5, 10}, {21, 8, 21}, {21, 12, 8}};
    
    unsigned int plaintextVector[3], ciphertextVector[3];
    char plaintext[20];
    int i, j, temp;
    
    printf("Enter the plaintext (3 characters): \n");
    scanf("%s", plaintext);

    toUpperCase(plaintext);
    
    if (strlen(plaintext) != 3) {
        printf("Error: Plaintext must be exactly 3 characters long.\n");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        plaintextVector[i] = plaintext[i] - 'A';
    }

    for (i = 0; i < 3; i++) {
        temp = 0;
        for (j = 0; j < 3; j++) {
            temp += encryptionMatrix[i][j] * plaintextVector[j];
        }
        ciphertextVector[i] = temp % 26;
    }

    printf("\nEncrypted ciphertext: ");
    for (i = 0; i < 3; i++) {
        printf("%c", ciphertextVector[i] + 'A');
    }

    for (i = 0; i < 3; i++) {
        temp = 0;
        for (j = 0; j < 3; j++) {
            temp += decryptionMatrix[i][j] * ciphertextVector[j];
        }
        plaintextVector[i] = temp % 26;
    }

    printf("\nDecrypted plaintext: ");
    for (i = 0; i < 3; i++) {
        printf("%c", plaintextVector[i] + 'A');
    }

    return 0;
}
