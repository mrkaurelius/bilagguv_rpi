#ifndef crypto_aead_gimli24v1_H
#define crypto_aead_gimli24v1_H

#define crypto_aead_gimli24v1_ref_KEYBYTES 32
#define crypto_aead_gimli24v1_ref_NSECBYTES 0
#define crypto_aead_gimli24v1_ref_NPUBBYTES 16
#define crypto_aead_gimli24v1_ref_ABYTES 16
#define crypto_aead_gimli24v1_ref_NOOVERLAP 1
 
#ifdef __cplusplus
extern "C" {
#endif
extern int crypto_aead_gimli24v1_ref_encrypt(unsigned char *,unsigned long long *,const unsigned char *,unsigned long long,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *,const unsigned char *);
extern int crypto_aead_gimli24v1_ref_decrypt(unsigned char *,unsigned long long *,unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
#ifdef __cplusplus
}
#endif

#define crypto_aead_gimli24v1_encrypt crypto_aead_gimli24v1_ref_encrypt
#define crypto_aead_gimli24v1_decrypt crypto_aead_gimli24v1_ref_decrypt
#define crypto_aead_gimli24v1_KEYBYTES crypto_aead_gimli24v1_ref_KEYBYTES
#define crypto_aead_gimli24v1_NSECBYTES crypto_aead_gimli24v1_ref_NSECBYTES
#define crypto_aead_gimli24v1_NPUBBYTES crypto_aead_gimli24v1_ref_NPUBBYTES
#define crypto_aead_gimli24v1_ABYTES crypto_aead_gimli24v1_ref_ABYTES
#define crypto_aead_gimli24v1_NOOVERLAP crypto_aead_gimli24v1_ref_NOOVERLAP

#endif
