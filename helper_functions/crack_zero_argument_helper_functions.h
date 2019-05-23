/*
* Anita Naseri 
* Assignment 2, May 2019
*/
#ifndef CRACK_ZERO_ARGUMENT_HELPER_FUNCTIONS_H_
#define CRACK_ZERO_ARGUMENT_HELPER_FUNCTIONS_H_

#include <stdio.h>
#include "sha256.h"

#define SHA256_BLOCK_SIZE 32
#define NUM_SIX_LETTERS_PASSWORDS 20
#define NUM_FOUR_LETTERS_PASSWORDS 10

//create hash representation for BYTE array
void create_hash(BYTE text[], BYTE hash[SHA256_BLOCK_SIZE], int lenght);

void four_letter_pwd_creator(char *curr_guess, unsigned char four_letter_hashed_passwords[NUM_FOUR_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE]);

void six_letter_pwd_creator(char *curr_guess, unsigned char six_letter_hashed_passwords[NUM_SIX_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE]);


#endif