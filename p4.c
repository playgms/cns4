#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod26(int a) {
    return (a % 26 + 26) % 26;
}

void matrixMultiply(int a[3][3], int b[3], int result[3]) {
    for (int i = 0; i < 3; i++) {
        result[i] = 0;
        for (int j = 0; j < 3; j++) {
            result[i] += a[i][j] * b[j];
        }
        result[i] = mod26(result[i]);
    }
}

void getCofactor(int matrix[3][3], int temp[3][3], int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(int matrix[3][3], int n) {
    int D = 0;
    if (n == 1) {
        return matrix[0][0];
    }
    int temp[3][3];
    int sign = 1;
    for (int f = 0; f < n; f++) {
        getCofactor(matrix, temp, 0, f, n);
        D += sign * matrix[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return D;
}

void adjoint(int matrix[3][3], int adj[3][3]) {
    if (3 == 1) {
        adj[0][0] = 1;
        return;
    }
    int sign = 1, temp[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            getCofactor(matrix, temp, i, j, 3);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, 3 - 1));
        }
    }
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void findInverse(int matrix[3][3], int inverse[3][3]) {
    int det = determinant(matrix, 3);
    det = mod26(det);
    if (gcd(det, 26) != 1) {
        printf("Error: Key matrix is not invertible.\n");
        return;
    }
    int adj[3][3];
    adjoint(matrix, adj);
    int invDet = modInverse(det, 26);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverse[i][j] = mod26(adj[i][j] * invDet);
        }
    }
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int key[3][3];
    char message[100], encryptedMessage[100], decryptedMessage[100];
    int i, j, t;
    unsigned int c[3], d[3];

    printf("Enter the 3x3 key matrix (9 integers between 0-25):\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    printf("Enter the plain text (in capitals): ");
    scanf("%s", message);

    int messageLength = strlen(message);
    while (messageLength % 3 != 0) {
        message[messageLength++] = 'X';
    }
    message[messageLength] = '\0';

    printf("Original Message: %s\n", message);

    // Encrypt the message
    for (i = 0; i < messageLength; i += 3) {
        for (j = 0; j < 3; j++) {
            c[j] = toupper(message[i + j]) - 65;
        }
        matrixMultiply(key, c, d);
        for (j = 0; j < 3; j++) {
            encryptedMessage[i + j] = d[j] + 65;
        }
    }
    encryptedMessage[messageLength] = '\0';
    printf("Encrypted Message: %s\n", encryptedMessage);

    // Calculate the inverse key matrix
    int inverseKey[3][3];
    findInverse(key, inverseKey);

    // Decrypt the message
    for (i = 0; i < messageLength; i += 3) {
        for (j = 0; j < 3; j++) {
            d[j] = encryptedMessage[i + j] - 65;
        }
        matrixMultiply(inverseKey, d, c);
        for (j = 0; j < 3; j++) {
            decryptedMessage[i + j] = c[j] + 65;
        }
    }
    decryptedMessage[messageLength] = '\0';
    printf("Decrypted Message: %s\n", decryptedMessage);

    return 0;
}
