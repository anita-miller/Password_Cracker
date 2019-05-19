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

#include "crack.h"
#include "sha256.h"
#include "helper_functions.h"

#define SHA256_BLOCK_SIZE 32
#define MAX_WORD_LEN 10000
#define NUM_FOUR_LETTERS_PASSWORDS 10
#define NUM_SIX_LETTERS_PASSWORDS 20
#define PASSWORD_LEN_FOUR_LETTER 4
#define PASSWORD_LEN_SIX_LETTER 6

#define PASSWORD_FILE_FOURWORDS "pwd4sha256"
#define PASSWORD_FILE_SIXWORDS "pwd6sha256"
#define COMMON_PASSWORDS "common_passwords.txt"
#define NUM_4_LETTERS_PASSWORDS 10

void crack_noargument()
{

	char curr_guess[MAX_WORD_LEN];
	unsigned char four_letter_hashed_passwords[NUM_FOUR_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE];
	unsigned char six_letter_hashed_passwords[NUM_SIX_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE];

	FILE *pwd4sha256 = fopen(PASSWORD_FILE_FOURWORDS, "rb");
	for (int i = 0; i < NUM_FOUR_LETTERS_PASSWORDS; i++)
	{
		fread(four_letter_hashed_passwords[i], sizeof(four_letter_hashed_passwords[i]), 1, pwd4sha256);
	}
	// Store the binary file as an array of hex values (for 6-chars passwords)
	FILE *pwd6sha256 = fopen(PASSWORD_FILE_SIXWORDS, "rb");
	for (int i = 0; i < NUM_SIX_LETTERS_PASSWORDS; i++)
	{
		fread(six_letter_hashed_passwords[i], sizeof(six_letter_hashed_passwords[i]), 1, pwd6sha256);
	}

	four_letter_pwd_creator(curr_guess, four_letter_hashed_passwords);
	//six_letter_pwd_creator(curr_guess, six_letter_hashed_passwords);
}
/*
void crack_oneargument(int number_guesses)
{
	char curr_guess[MAX_WORD_LEN];
	int guesses_made = 0;
	char correct_guesses[NUM_FOUR_LETTERS_PASSWORDS][PASSWORD_LEN_FOUR_LETTER];
	int correct_guesses_num = 0;
	// First go through the common_passwords if n is small
	FILE *common_passwords = fopen(COMMON_PASSWORDS, "r");
	if (!common_passwords)
	{
		return 1;
	}

	// Store the binary file as an array of hex values
	unsigned char passwords[NUM_FOUR_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE];
	FILE *pwd4sha256 = fopen(PASSWORD_FILE_FOURWORDS, "rb");
	for (int i = 0; i < NUM_FOUR_LETTERS_PASSWORDS; i++)
	{
		fread(passwords[i], sizeof(passwords[i]), 1, pwd4sha256);
	}

	// for each word in the common_passwords file
	while (fgets(curr_guess, MAX_WORD_LEN, common_passwords))
	{
		// Filter 4-letters passwords
		if (strlen(curr_guess) == PASSWORD_LEN_FOUR_LETTER + 1)
		{
			guesses_made++;
			// Because fgets also gets the newline character, so we search for length 5 and cut the final \n char.
			curr_guess[PASSWORD_LEN_FOUR_LETTER] = '\0';
			// Hash the 4-letter password

			BYTE result[SHA256_BLOCK_SIZE];
			create_hash((BYTE *)curr_guess, result);

			// Compare the hash to the array of hash (result is an 1d array of hex and hashed_passwords is a 2d array of hashes)
			int count_matched_hash = 0;
			for (int i = 0; i < NUM_FOUR_LETTERS_PASSWORDS; i++)
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
					for (int k = 0; k < PASSWORD_LEN_FOUR_LETTER; k++)
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
		if (guesses_made == n)
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

	for (word_count = 0; word_count < number_guesses - guesses_made; word_count++)
	{
		// generate each digit
		for (letter_count = 0; letter_count < PASSWORD_LEN_FOUR_LETTER; letter_count++)
		{
			curr_guess[letter_count] = 32 + rand() % 95;
		}
		curr_guess[PASSWORD_LEN_FOUR_LETTER] = '\0';
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
		for (int i = 0; i < NUM_FOUR_LETTERS_PASSWORDS; i++)
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
	fclose(COMMON_PASSWORDS);
}
*/
void crack_twoargument(char *guesses_file, char *hashes_file)
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
		create_hash((BYTE *)curr_guess, result, strlen(curr_guess));

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
