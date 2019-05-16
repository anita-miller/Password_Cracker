/*
* Anita Naseri 
* Assignment 2, May 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "crack_noargument.h"

#define SHA256_BLOCK_SIZE 32
#define MAX_WORD_LEN 10000
#define NUM_4_LETTERS_PASSWORDS 10

void crack_noargument()
{
	int countPasswords = 0;
	char curr_guess[MAX_WORD_LEN];
	int flag = 1;
	// Store the binary file as an array of hex values
	unsigned char passwords[NUM_4_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE];
	FILE *pwd4sha256 = fopen(PASSWORD_FILE, "rb");
	for (int i = 0; i < NUM_4_LETTERS_PASSWORDS; i++)
	{
		fread(passwords[i], sizeof(passwords[i]), 1, pwd4sha256);
	}

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
					create_hash((BYTE *)curr_guess, curr_guessHash);

					// Compare the hash to the array of hash (result is an 1d array of hex and hashed_passwords is a 2d array of hashes)
					for (int i = 0; i < NUM_4_LETTERS_PASSWORDS; i++)
					{
						int matchedHashes = 0;
						// for every hex
						for (int j = 0; j < SHA256_BLOCK_SIZE; j++)
						{
							if (passwords[i][j] == curr_guessHash[j])
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
					if (countPasswords == NUM_4_LETTERS_PASSWORDS)
					{
						flag = 0;
					}
				}
			}
		}
	}
}
