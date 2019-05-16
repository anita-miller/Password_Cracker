/*
* Anita Naseri 
* Assignment 2, May 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stddef.h>
#include "sha256.h"
#include "crack_twoargument.h"


#define SHA256_BLOCK_SIZE 32
#define MAX_WORD_LEN 10000
#define NUM_4_LETTERS_PASSWORDS 10


void crack_threeargument(char *guesses_file, char *hashes_file)
{

	FILE *inputFile_guesses;
	FILE *inputFile_hashes;
	unsigned char hashes[MAX_WORD_LEN][SHA256_BLOCK_SIZE];
	int count_input_guesses;
	char curr_guess[MAX_WORD_LEN];
	int count_matched_hash;

	//opening both files
	inputFile_guesses = fopen(guesses_file, "r");
	inputFile_hashes = fopen(hashes_file, "rb");

	/* validate file open */
	if (!inputFile_hashes || !inputFile_guesses)
	{
		fprintf(stderr, "error: file open failed.\n");
		return 1;
	}

	count_input_guesses = 0;
	while (fread(hashes[count_input_guesses], sizeof(hashes[count_input_guesses]), 1, inputFile_hashes) == 1)
	{
		count_input_guesses++;
	}

	// for each word in the guesses file
	while (fgets(curr_guess, MAX_WORD_LEN, inputFile_guesses))
	{
		int wordlen = strlen(curr_guess);

		// strip '\n'
		if (curr_guess[wordlen - 1] == '\n')
			curr_guess[--wordlen] = 0;

		// Hash the guessed password
		BYTE result[SHA256_BLOCK_SIZE];
		create_hash((BYTE *)curr_guess, result);

		// Compare the hash to the array of hash
		for (int i = 0; i < count_input_guesses; i++)
		{
			count_matched_hash = 0;
			// for every value from 0 to 32
			for (int j = 0; j < SHA256_BLOCK_SIZE; j++)
			{
				if (hashes[i][j] == result[j])
				{
					count_matched_hash++;
				}
			}

			// password found
			if (count_matched_hash == SHA256_BLOCK_SIZE)
			{
				printf("%s %d\n", curr_guess, i + 1);
				break;
			}
		}
	}

	//opening both files closing both files
	fclose(inputFile_guesses);
	fclose(inputFile_hashes);
}
