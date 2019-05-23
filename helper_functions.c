/*
* Anita Naseri 
* Assignment 2, May 2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdbool.h>
#include <time.h>

#include <stddef.h>
#include "sha256.h"
#include "helper_functions.h"

#define SHA256_BLOCK_SIZE 32
#define NUM_SIX_LETTERS_PASSWORDS 20
#define NUM_FOUR_LETTERS_PASSWORDS 10
#define PASSWORD_LEN_SIX_LETTER 6
#define PASSWORD_LEN_FOUR_LETTER 4
#define PASSWORD_LEN_SIX_LETTER 6
#define MAX_WORD_LEN 10000
//create hash representation for BYTE array
void create_hash(BYTE text[], BYTE hash[SHA256_BLOCK_SIZE], int lenght)
{
	SHA256_CTX ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, text, lenght);
	sha256_final(&ctx, hash);
}

void four_letter_pwd_creator(char *curr_guess, unsigned char four_letter_hashed_passwords[NUM_FOUR_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE])
{
	int flag = 1;
	int countPasswords = 0;
	// 4-letters passwords: Brute Force
	for (int i = 32; i <= 126 && flag == 1; i++)
	{
		for (int j = 32; j <= 126 && flag == 1; j++)
		{
			for (int n = 32; n <= 126 && flag == 1; n++)
			{
				for (int m = 32; m <= 126 && flag == 1; m++)
				{
					curr_guess[0] = i;
					curr_guess[1] = j;
					curr_guess[2] = n;
					curr_guess[3] = m;
					curr_guess[4] = '\0';

					//create hash for guess
					BYTE curr_guessHash[SHA256_BLOCK_SIZE];
					create_hash((BYTE *)curr_guess, curr_guessHash, PASSWORD_LEN_FOUR_LETTER);

					// Compare the hash to the array of hash (result is an 1d array of hex and hashed_passwords is a 2d array of hashes)
					for (int i = 0; i < NUM_FOUR_LETTERS_PASSWORDS; i++)
					{
						int matchedHashes = 0;
						// for every hex
						for (int j = 0; j < SHA256_BLOCK_SIZE; j++)
						{
							if (four_letter_hashed_passwords[i][j] == curr_guessHash[j])
							{
								matchedHashes++;
							}
						}
						// password found
						if (matchedHashes == SHA256_BLOCK_SIZE)
						{
							printf("%s %d\n", curr_guess, i + 1);
							countPasswords++;
							break;
						}
					}
					if (countPasswords == NUM_FOUR_LETTERS_PASSWORDS)
					{
						flag = 0;
					}
				}
			}
		}
	}
}

void six_letter_pwd_creator(char *curr_guess, unsigned char six_letter_hashed_passwords[NUM_SIX_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE])
{
	int flag = 1;
	int countPasswords = 0;
	// 6-letters passwords: Brute Force
	
	for (int i = 48; i <= 122 && flag == 1; i++)
	{
		//48-57 are number 0-9
		//91-96 are [ / ] ^ _ '
		if ((i >= 58 && i <= 64) || (i >= 91 && i <= 96) || (i >= 123 && i <= 126))
		{
			continue;
		}
		for (int j = 48; j <= 122 && flag == 1; j++)
		{
			if ((j >= 58 && j <= 64) || (j >= 91 && j <= 96) || (j >= 123 && j <= 126))
			{
				continue;
			}
			for (int k = 48; k <= 122 && flag == 1; k++)
			{
				if ((k >= 58 && k <= 64) || (k >= 91 && k <= 96) || (k >= 123 && k <= 126))
				{
					continue;
				}
				for (int m = 48; m <= 122 && flag == 1 ; m++)
				{
					if ((m >= 58 && m <= 64) || (m >= 91 && m <= 96) || (m >= 123 && m <= 126))
					{
						continue;
					}
					for (int a = 48; a <= 122 && flag == 1; a++)
					{
						if ((a >= 58 && a <= 64) || (a >= 91 && a <= 96) || (a >= 123 && a <= 126))
						{
							continue;
						}
						for (int b = 48; b <= 122 && flag == 1 ; b++)
						{
							if ((b >= 58 && b <= 64) || (b >= 91 && b <= 96) || (b >= 123 && b <= 126))
							{
								continue;
							}
							curr_guess[0] = i;
							curr_guess[1] = j;
							curr_guess[2] = k;
							curr_guess[3] = m;
							curr_guess[4] = a;
							curr_guess[5] = b;
							curr_guess[6] = '\0';

							//create hash for guess
							BYTE result[SHA256_BLOCK_SIZE];
							create_hash((BYTE *)curr_guess, result, PASSWORD_LEN_SIX_LETTER);

							// Compare the hash to the array of hash (result is an 1d array of hex and hashed_passwords is a 2d array of hashes)
							for (int c = 0; c < NUM_SIX_LETTERS_PASSWORDS; c++)
							{
								int num_matched_hash = 0;
								// for every hex
								for (int d = 0; d < SHA256_BLOCK_SIZE; d++)
								{
									if (six_letter_hashed_passwords[c][d] == result[d])
									{
										num_matched_hash++;
									}
								}
								// password found
								if (num_matched_hash == SHA256_BLOCK_SIZE)
								{
									printf("%s %d\n", curr_guess, c + 1);
									countPasswords++;
									break;
								}
							}
							if (countPasswords == NUM_SIX_LETTERS_PASSWORDS)
							{
								flag = 0;
							}
							//printf("%s\n", curr_guess);
						}
					}
				}
			}
		}
	}
}

char *create_rand_num()
{
	char *word = malloc(sizeof(char) * MAX_WORD_LEN);
	// We will generate a random 6 digit number
	for (int i = 0; i < PASSWORD_LEN_SIX_LETTER; i++)
	{
		word[i] = 48 + rand() % 10;
	}
	word[PASSWORD_LEN_SIX_LETTER] = '\0';
	return word;
	
}

void read_word_dict(FILE *db, char *word, int count)
{
	fgets(word, MAX_WORD_LEN, db);

	printf("%s\n", word);

}