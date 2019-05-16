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
#include "crack_towargument.h"

#define listlength 10000
#define wordslength 6
#define SHA256_BLOCK_SIZE 32
#define PASSWORD_LEN_OPTION_ONE 4
#define PASSWORD_LEN_OPTION_TWO 6
#define MAX_WORD_LEN 10000
#define NUM_4_LETTERS_PASSWORDS 10

// Constants
#define COMMON_PASSWORDS "common_passwords.txt"
#define PASSWORD_FILE "pwd4sha256"
void crack_twoargument(int number_guesses)
{
	char curr_guess[MAX_WORD_LEN];
	int guesses_made = 0;
	char correct_guesses[NUM_4_LETTERS_PASSWORDS][PASSWORD_LEN_OPTION_ONE];
	int correct_guesses_num = 0;
	// First go through the common_passwords if n is small
	FILE *common_passwords = fopen(COMMON_PASSWORDS, "r");
	if (!common_passwords)
	{
		return 1;
	}

	// Store the binary file as an array of hex values
	unsigned char passwords[NUM_4_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE];
	FILE *pwd4sha256 = fopen(PASSWORD_FILE, "rb");
	for (int i = 0; i < NUM_4_LETTERS_PASSWORDS; i++)
	{
		fread(passwords[i], sizeof(passwords[i]), 1, pwd4sha256);
	}
	
	// for each word in the common_passwords file
	while (fgets(curr_guess, MAX_WORD_LEN, common_passwords))
	{
		// Filter 4-letters passwords
		if (strlen(curr_guess) == PASSWORD_LEN_OPTION_ONE + 1)
		{
			num_guesses_made++;
			// Because fgets also gets the newline character, so we search for length 5 and cut the final \n char.
			curr_guess[PASSWORD_LEN_OPTION_ONE] = '\0';
			// Hash the 4-letter password

			BYTE result[SHA256_BLOCK_SIZE];
			create_hash((BYTE *)curr_guess, result);

			// Compare the hash to the array of hash (result is an 1d array of hex and hashed_passwords is a 2d array of hashes)
			int count_matched_hash = 0;
			for (int i = 0; i < NUM_4_LETTERS_PASSWORDS; i++)
			{
				count_matched_hash = 0;
				// for every hex
				for (int j = 0; j < SHA256_BLOCK_SIZE; j++)
				{
					if (passwords[i][j] == result[j])
					{
						count_matched_hash++;
					}
				}
				// password found
				if (count_matched_hash == SHA256_BLOCK_SIZE)
				{
					printf("%s %d\n", curr_guess, i + 1);
					// store the word into an array to avoid repetition of displaying correct guesses
					for (int k = 0; k < PASSWORD_LEN_OPTION_ONE; k++)
					{
						correct_guesses[correct_guesses_num][k] = curr_guess[k];
					}
					correct_guesses_num++;
					break;
				}
			}
			// not found but still print the guess out
			if (count_matched_hash != SHA256_BLOCK_SIZE)
			{
				printf("%s\n", curr_guess);
			}
		}

		// if reached the number specified then break;
		if (num_guesses_made == n)
		{
			fclose(common_passwords);
			fclose(pwd4sha256);
			return 0;
		}
	}

	// Now that the common_passwords file is checked and still wants more guess, then we generate random guesses
	int word_count = 0;
	int letter_count = 0;
	bool repeated = false;

	for (word_count = 0; word_count < number_guesses - num_guesses_made; word_count++)
	{
		// generate each digit
		for (letter_count = 0; letter_count < PASSWORD_LEN_OPTION_ONE; letter_count++)
		{
			curr_guess[letter_count] = 32 + rand() % 95;
		}
		curr_guess[PASSWORD_LEN_OPTION_ONE] = '\0';
		// check if this word is already guessed correct
		for (int i = 0; i < correct_guesses_num; i++)
		{
			if (strcmp(curr_guess, correct_guesses[i]) == 0)
			{
				repeated = true;
				break;
			}
		}
		if (repeated == true)
		{
			continue;
		}

		// Now we know it is not a repeated correct guess, hash and check if it is correct
		// Hash the 4-letter password
		BYTE result[SHA256_HASH_SIZE];
		create_hash((BYTE *)curr_guess, result);

		// Compare the hash to the array of hash (result is an 1d array of hex and hashed_passwords is a 2d array of hashes)
		for (int i = 0; i < NUM_4_LETTERS_PASSWORDS; i++)
		{
			int count_matched_hash = 0;
			// for every hex
			for (int j = 0; j < SHA256_HASH_SIZE; j++)
			{
				if (hashed_passwords[i][j] == result[j])
				{
					count_matched_hash++;
				}
			}
			// password found
			if (count_matched_hash == SHA256_HASH_SIZE)
			{
				printf("%s %d\n", curr_guess, i + 1);
				break;
			}
			else
			{
				printf("%s\n", curr_guess);
				break;
			}
		}
	}
	fclose(common_passwords_file);
}