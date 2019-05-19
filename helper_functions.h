/*
* Anita Naseri 
* Assignment 2, May 2019
*/
#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

#include <stdio.h>
#include "sha256.h"
//create hash representation for BYTE array
void create_hash(BYTE text[], BYTE hash[SHA256_BLOCK_SIZE], int lenght);

//read hashes of passwords into a char** from a file
//unsigned char (*)[32] read_passwords_hashes(char *filename, int lenght);

void four_letter_pwd_creator(char *curr_guess, unsigned char **four_letter_hashed_passwords);

void six_letter_pwd_creator(char *curr_guess, unsigned char **six_letter_hashed_passwords);


#endif