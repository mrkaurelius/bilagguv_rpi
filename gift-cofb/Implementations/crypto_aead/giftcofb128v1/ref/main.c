#include "api.h"
#include "crypto_aead.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CRYPTO_BYTES 64

void string2hexString(unsigned char *input, int clen, char *output);
void *hextobyte(char *hexstring, unsigned char *bytearray);

int main(int argc, char *argv[])
{

    unsigned long long mlen;
    unsigned long long clen;

    unsigned char plaintext[CRYPTO_BYTES];
    unsigned char cipher[CRYPTO_BYTES];
    unsigned char npub[CRYPTO_NPUBBYTES] = "";
    unsigned char ad[CRYPTO_ABYTES] = "";
    unsigned char nsec[CRYPTO_ABYTES] = "";

    unsigned char key[CRYPTO_KEYBYTES];

    char pl[CRYPTO_BYTES] = "DEADBEEF29";
    char chex[CRYPTO_BYTES] = "";
    char keyhex[2 * CRYPTO_KEYBYTES + 1] = "0123456789ABCDEF0123456789ABCDEF";
    char nonce[2 * CRYPTO_NPUBBYTES + 1] = "000000000000111111111111";
    char add[CRYPTO_ABYTES] = "";

    if (argc > 1)
    {
        strcpy(pl, argv[1]);
    }
    if (argc > 2)
    {
        strcpy(keyhex, argv[2]);
    }
    if (argc > 3)
    {
        strcpy(nonce, argv[3]);
    }
    if (argc > 4)
    {
        strcpy(add, argv[4]);
    }

    if (strlen(keyhex) != 32)
    {
        printf("Key length needs to be 16 bytes");
        return (0);
    }

    strcpy(plaintext, pl);
    strcpy(ad, add);
    hextobyte(keyhex, key);
    hextobyte(nonce, npub);

    // printf("Elephant light-weight cipher\n");
    // printf("Plaintext: %s\n", plaintext);
    // printf("Key: %s\n", keyhex);
    // printf("Nonce: %s\n", nonce);
    // printf("Additional Information: %s\n\n", ad);

    // printf("Plaintext: %s\n", plaintext);

    clock_t begin_crypt = clock();

    int ret = crypto_aead_encrypt(cipher, &clen, plaintext, strlen(plaintext), ad, strlen(ad), nsec, npub, key);

    clock_t end_crypt = clock();

    string2hexString(cipher, clen, chex);
    // hextobyte(chex, cipher);

    printf("cipher_text:\t%s\n", chex, clen);

    clock_t begin_dec = clock();

    ret = crypto_aead_decrypt(plaintext, &mlen, nsec, cipher, clen, ad, strlen(ad), npub, key);

    clock_t end_dec = clock();

    plaintext[mlen] = '\0';
    printf("plain_text:\t%s\n", plaintext);
    // printf("%s\n", plaintext);

    if (ret == 0)
    {
        // printf("Success!\n");
    }
    else
    {
        exit(1);
    }

    double time_spent_crypt = (double)(end_crypt - begin_crypt) / CLOCKS_PER_SEC;
    double time_spent_dec = (double)(end_dec - begin_dec) / CLOCKS_PER_SEC;

    printf("et_crypt:\t%lf\n", time_spent_crypt);
    printf("et_crypt_clok:\t%lf\n", time_spent_crypt * 1200000000);

    printf("et_dec:\t%lf\n", time_spent_dec);
    printf("et_dec_clok:\t%lf\n", time_spent_dec * 1200000000);

    sleep(1);

    return 0;
}
void string2hexString(unsigned char *input, int clen, char *output)
{
    int loop;
    int i;

    i = 0;
    loop = 0;

    for (i = 0; i < clen; i += 2)
    {
        sprintf((char *)(output + i), "%02X", input[loop]);
        loop += 1;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}
void *hextobyte(char *hexstring, unsigned char *bytearray)
{

    int i;

    int str_len = strlen(hexstring);

    for (i = 0; i < (str_len / 2); i++)
    {
        sscanf(hexstring + 2 * i, "%02x", &bytearray[i]);
    }
}
