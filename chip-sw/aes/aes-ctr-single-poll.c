#include "aes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(void)
{
  // 128bit IV
  uint8_t IV[16]         = {0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff};

  // 128bit key
  uint8_t keyone[16]        = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  
  // 256bit key
  uint8_t keytwo[32]        = {0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 
                               0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4};

  // 512bit text
  uint8_t plaintext[64]     = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
                               0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
                               0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
                               0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10};

  // Expected for 128b enc
  uint8_t ciphertextone[64] = {0x87, 0x4d, 0x61, 0x91, 0xb6, 0x20, 0xe3, 0x26, 0x1b, 0xef, 0x68, 0x64, 0x99, 0x0d, 0xb6, 0xce,
                               0x98, 0x06, 0xf6, 0x6b, 0x79, 0x70, 0xfd, 0xff, 0x86, 0x17, 0x18, 0x7b, 0xb9, 0xff, 0xfd, 0xff,
                               0x5a, 0xe4, 0xdf, 0x3e, 0xdb, 0xd5, 0xd3, 0x5e, 0x5b, 0x4f, 0x09, 0x02, 0x0d, 0xb0, 0x3e, 0xab,
                               0x1e, 0x03, 0x1d, 0xda, 0x2f, 0xbe, 0x03, 0xd1, 0x79, 0x21, 0x70, 0xa0, 0xf3, 0x00, 0x9c, 0xee};

  // Expected for 256b enc
  uint8_t ciphertexttwo[64] = {0x60, 0x1e, 0xc3, 0x13, 0x77, 0x57, 0x89, 0xa5, 0xb7, 0xa7, 0xf5, 0x04, 0xbb, 0xf3, 0xd2, 0x28,
                               0xf4, 0x43, 0xe3, 0xca, 0x4d, 0x62, 0xb5, 0x9a, 0xca, 0x84, 0xe9, 0x90, 0xca, 0xca, 0xf5, 0xc5,
                               0x2b, 0x09, 0x30, 0xda, 0xa2, 0x3d, 0xe9, 0x4c, 0xe8, 0x70, 0x17, 0xba, 0x2d, 0x84, 0x98, 0x8d,
                               0xdf, 0xc9, 0xc5, 0x8d, 0xb6, 0x7a, 0xad, 0xa6, 0x13, 0xc2, 0xdd, 0x08, 0x45, 0x79, 0x41, 0xa6};

  // Scratch space for data
  uint8_t fillerspace[64]   = {0x0};

  // ----------------- Single Block 128b Enc/Dec Loop -----------------
  printf("AES CTR E/D Loop, 4 blocks, 128b Key, Polling:\n");

  // Encrypting all four blocks using single function call
  printf("Encrypting plaintext and checking output...\n");
  AES_CTR_XCRYPT_POLL(IV, keyone, 128, plaintext, fillerspace, 64);

  // Comparing actual results to expected
  checkBytes(fillerspace, ciphertextone, 64);

  // Decrypting all four blocks using single function call (using expected as source)
  printf("Decrypting ciphertext and checking output...\n");
  AES_CTR_XCRYPT_POLL(IV, keyone, 128, ciphertextone, fillerspace, 64);

  // Comparing actual results to expected
  checkBytes(fillerspace, plaintext, 64);

  // ----------------- Single Block 256b Enc/Dec Loop -----------------
  printf("\nAES CTR E/D Loop, 4 blocks, 256b Key, Polling:\n");

  // Encrypting all four blocks using single function call
  printf("Encrypting plaintext and checking output...\n");
  AES_CTR_XCRYPT_POLL(IV, keytwo, 256, plaintext, fillerspace, 64);

  // Comparing actual results to expected
  checkBytes(fillerspace, ciphertexttwo, 64);

  // Decrypting all four blocks using single function call (using expected as source)
  printf("Decrypting ciphertext and checking output...\n");
  AES_CTR_XCRYPT_POLL(IV, keytwo, 256, ciphertexttwo, fillerspace, 64);

  // Comparing actual results to expected
  checkBytes(fillerspace, plaintext, 64);

  return 0;
}
