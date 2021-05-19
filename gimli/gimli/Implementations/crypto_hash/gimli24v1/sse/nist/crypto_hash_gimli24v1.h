#ifndef crypto_hash_gimli24v1_H
#define crypto_hash_gimli24v1_H

#define crypto_hash_gimli24v1_sse_BYTES 32
 
#ifdef __cplusplus
extern "C" {
#endif
extern int crypto_hash_gimli24v1_sse(unsigned char *,const unsigned char *,unsigned long long);
#ifdef __cplusplus
}
#endif

#define crypto_hash_gimli24v1 crypto_hash_gimli24v1_sse
#define crypto_hash_gimli24v1_BYTES crypto_hash_gimli24v1_sse_BYTES

#endif
