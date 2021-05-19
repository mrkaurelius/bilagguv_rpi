#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#include "crypto_hash.h"
#include "api.h"

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

#define MAX_FILE_NAME				256
#define MAX_MESSAGE_LENGTH			1024

void init_buffer(unsigned char *buffer, unsigned long long numbytes);

void fprint_bstr(FILE *fp, const char *label, const unsigned char *data, unsigned long long length);

int generate_test_vectors();


int main()
{
	int ret = generate_test_vectors();

	if (ret != KAT_SUCCESS) {
		fprintf(stderr, "test vector generation failed with code %d\n", ret);
	}

	return ret;
}

int generate_test_vectors()
{
	FILE                *fp;
	char                fileName[MAX_FILE_NAME];
	unsigned char       msg[MAX_MESSAGE_LENGTH];
	unsigned char		digest[CRYPTO_BYTES];
	int                 ret_val = KAT_SUCCESS;
	int					count = 1;

	init_buffer(msg, sizeof(msg));

	sprintf(fileName, "LWC_HASH_KAT_%d.txt", (CRYPTO_BYTES * 8));

	if ((fp = fopen(fileName, "w")) == NULL) {
		fprintf(stderr, "Couldn't open <%s> for write\n", fileName);
		return KAT_FILE_OPEN_ERROR;
	}

	for (unsigned long long mlen = 0; mlen <= MAX_MESSAGE_LENGTH; mlen++) {

		fprintf(fp, "Count = %d\n", count++);

		fprint_bstr(fp, "Msg = ", msg, mlen);

		ret_val = crypto_hash(digest, msg, mlen);
		
		if(ret_val != 0) {
			fprintf(fp, "crypto_hash returned <%d>\n", ret_val);
			ret_val = KAT_CRYPTO_FAILURE;
			break;
		}

		fprint_bstr(fp, "MD = ", digest, CRYPTO_BYTES);

		fprintf(fp, "\n");
	}

	fclose(fp);

	return ret_val;
}

void fprint_bstr(FILE *fp, const char *label, const unsigned char *data, unsigned long long length)
{    
    fprintf(fp, "%s", label);
        
	for (unsigned long long i = 0; i < length; i++)
		fprintf(fp, "%02X", data[i]);
	    
    fprintf(fp, "\n");
}

void init_buffer(unsigned char *buffer, unsigned long long numbytes)
{
	for (unsigned long long i = 0; i < numbytes; i++)
		buffer[i] = (unsigned char)i;
}
