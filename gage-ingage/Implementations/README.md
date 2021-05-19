Reference Implementation for GAGE and InGAGE
============================================


Release Directory Structure
---------------------------

	.
	├── crypto_aead
	│   ├── ingage2k128n096c224r008
	│   ├── ingage2k128n096c224r016
	│   ├── ingage2k128n096c224r032
	│   ├── ingage2k128n128c256r064
	│   ├── ingage2k256n096c448r064
	│   └── ingage2k256n128c448r064
	└── crypto_hash
	    ├── gage2h256c224r008
	    ├── gage2h256c224r016
	    ├── gage2h256c224r032
	    ├── gage2h256c224r064
	    ├── gage2h256c256r016
	    ├── gage2h256c256r032
	    ├── gage2h256c256r064
	    ├── gage2h256c256r128
	    ├── gage2h256c512r032
	    └── gage2h256c512r064


The directories for the Gage and InGage reference implementations are similarly structured.

The directories are structured in the following way:

1. Level distinguishes between hash functions in `crypto_hash` and AEAD functions in `crypto_aead`
2. Level distinguishes the different members of each family
3. Level directories offer different implementation variants with `ref` being the reference implementation

Each directory name on the second level starts with the families name (`gage` or `ingage`) followed by a version number and several parameters. Each parameter is indicated by a single letter followed by a numeric value.

Parameters for `GAGE`
--------------------

* h<num>: <num> is the number of bits of the resulting message digest
* c<num>: <num> is the value of the capacity parameter
* r<num>: <num> is the value of the rate parameter 


Parameters for `InGAGE`
----------------------

* k<num>: <num> is the size of the key in bits
* n<num>: <num> is the size of the nonce in bits
* c<num>: <num> is the value of the capacity parameter
* r<num>: <num> is the value of the rate parameter 


Structure of the Reference Implementation
-----------------------------------------

	crypto_hash/gage2h256c224r008/
	├── LWC_HASH_KAT_256.txt
	└── ref
	    ├── api.h
	    ├── constants.c
	    ├── constants.h
	    ├── crypto_hash.h
	    ├── genkat_hash.c
	    ├── hash.c
	    └── parameters.h
	crypto_aead/ingage2k128n096c224r008/
	├── LWC_AEAD_KAT_128_96.txt
	└── ref
	    ├── api.h
	    ├── constants.c
	    ├── constants.h
	    ├── crypto_aead.h
	    ├── encrypt.c
	    ├── genkat_aead.c
	    └── parameters.h


All reference implementation of `GAGE` and `InGAGE` family members share a large amount of code.

The members of `GAGE` and `InGAGE` families differ only in their state size
and how this size is split in rate and capacity. Those values are defined
for each implementation in `parameters.h`. 

Since `InGAGE` also offers four different interfaces (k=128,n=96; k=128,n=128; k=256,n=96; k=256,n=128),
there are also four different variations of `api.h` which define those parameters.


All implementations share:

* constants.c : this file defines the `leaders` or round constants and the s-box
* constants.h : provides interfaces to the constants defined in constants.c
                and defines the state structure


All implementations of `GAGE` further share:

* hash.c        : core implementation of `GAGE`
* api.h         : defines the size of the message digest to 32 bytes
* crypto_hash.h : provides a prototype for the `crypto_hash()` function
* genkat_hash.c : provides a main program to generate test vectors


All implementations of `InGAGE` share
* encrypt.c     : core implementation of `InGAGE`
* crypto_aead.h : provides a prototype for the `crypto_aead_encrypt()`
                  and `crypto_aead_decrypt()` functions
* genkat_aead.c : provides a main program to generate test vectors

