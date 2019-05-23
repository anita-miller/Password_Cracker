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

#define DB_COMMON_PASSWORDS "6_letters/common_passwords.txt"
#define DB_NAMES_MALE_LOWER "6_letters/names_m_lower.txt"
#define DB_NAMES_MALE_UPPER "6_letters/names_m_lupper.txt"
#define DB_NAMES_FEMALE_LOWER "6_letters/names_f_lower.txt"
#define DB_NAMES_FEMALE_UPPER "6_letters/names_f_upper.txt"
#define DB_1000_NOUNS_LOWER "6_letters/nouns_1000_lower.csv"
#define DB_1000_NOUNS_UPPER "6_letters/nouns_1000_upper.csv"
#define DB_1000_VERBS_LOWER "6_letters/verbs_1000_lower.csv"
#define DB_1000_VERBS_UPPER "6_letters/verbs_1000_upper.csv"
#define DB_1000_ADJEC_LOWER "6_letters/adj_1000_lower.csv"
#define DB_1000_ADJEC_UPPER "6_letters/adj_1000_upper.csv"

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

void crack_oneargument(int number_guesses)
{
	//int number_guesses = atoi(num_guesses);
	char current_word[MAX_WORD_LEN];

	// Store the binary file as an array of hex values (for 6-chars passwords)
	unsigned char six_letter_hashed_passwords[NUM_SIX_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE];
	
	FILE *pwd6sha256 = fopen(PASSWORD_FILE_SIXWORDS, "rb");
	for (int i = 0; i < NUM_SIX_LETTERS_PASSWORDS; i++)
	{
		fread(six_letter_hashed_passwords[i], sizeof(six_letter_hashed_passwords[i]), 1, pwd6sha256);
	}

	char *fuck = "fucckkk";

	/* Dictionary Attack Part */
	// First thing first is a dictionary of common passwords
	/*FILE *dictionary_common_passwords = fopen(DB_COMMON_PASSWORDS, "r");
	while (fgets(current_word, MAX_WORD_LEN, dictionary_common_passwords))
	{
		// Filter 6-letters passwords
		if (strlen(current_word) == PASSWORD_LEN_SIX_LETTER + 1)
		{
			// Because fgets also gets the newline character, so we search for length 7 and cut the final \n char.
			current_word[PASSWORD_LEN_SIX_LETTER] = '\0';
			printf("%s\n", current_word);
			// if reached the number specified then break;
			number_guesses--;
			if (number_guesses == 0)
			{
				fclose(dictionary_common_passwords);
				fclose(pwd6sha256);
				printf("%s\n", fuck);
				return 0;
			}
		}
	}*/
	// Then it's the Weighted Dictionary Attack
	FILE *dictionary_name_male_lower = fopen(DB_NAMES_MALE_LOWER, "r");
	FILE *dictionary_name_male_upper = fopen(DB_NAMES_MALE_UPPER, "r");
	FILE *dictionary_name_female_lower = fopen(DB_NAMES_FEMALE_LOWER, "r");
	FILE *dictionary_name_female_upper = fopen(DB_NAMES_FEMALE_UPPER, "r");
	FILE *dictionary_nouns_lower = fopen(DB_1000_NOUNS_LOWER, "r");
	FILE *dictionary_nouns_upper = fopen(DB_1000_NOUNS_UPPER, "r");
	FILE *dictionary_verbs_lower = fopen(DB_1000_VERBS_LOWER, "r");
	FILE *dictionary_verbs_upper = fopen(DB_1000_VERBS_UPPER, "r");
	FILE *dictionary_adj_lower = fopen(DB_1000_ADJEC_LOWER, "r");
	FILE *dictionary_adj_upper = fopen(DB_1000_ADJEC_UPPER, "r");
	// Constants
	time_t seed_of_seed;
	srand((unsigned)time(&seed_of_seed));
	int seed = rand();
	srand((unsigned)seed);

	/*
	int name_male_lower_counter = 0;
	int name_female_lower_counter = 0;
	int nouns_lower_counter = 0;
	int verbs_lower_counter = 0;
	int adj_lower_counter = 0;
	int name_male_upper_counter = 0;
	int name_female_upper_counter = 0;
	int nouns_upper_counter = 0;
	int verbs_upper_counter = 0;
	int adj_upper_counter = 0;*/

	// To randomise the order of guesses, we have 12 cases and each case is
	// weighted differently (see Algorithm_plan.txt for detail). Based on passwords in pwd4sha256,
	// combination of lower case nouns are very popular, therefore has a higher weight.
	for (int i = 0; i < number_guesses; i++)
	{
		// This randomisation is achieved by a random number ranging 0-99 (used as percentage)
		int percentage = rand() % 100;

		// Case 1: Number combination - 25%
		if (percentage >= 0 && percentage < 25)
		{
			// We will generate a random 6 digit number
			for (int letter_count = 0; letter_count < PASSWORD_LEN_SIX_LETTER; letter_count++)
			{
				current_word[letter_count] = 48 + rand() % 10;
			}
			current_word[PASSWORD_LEN_SIX_LETTER] = '\0';
			printf("%s\n", current_word);

		}

		// Case 2: Names Lowercase - 15%
		else if (percentage >= 25 && percentage < 32)
		{
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_name_male_lower);
		}

		else if (percentage >= 32 && percentage < 40)
		{	
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_name_female_lower);
		}

		// Case 3: Nouns Lowercase - 15%
		else if (percentage >= 40 && percentage < 55)
		{
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_nouns_lower);
		}

		// Case 4: Other dictionary words Lowercase - 8%
		else if (percentage >= 55 && percentage < 59)
		{
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_verbs_lower);
		}
		else if (percentage >= 59 && percentage < 63)
		{
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_adj_lower);
		}

		// Case 5: Names Uppercase - 8%
		else if (percentage >= 63 && percentage < 67)
		{
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_name_male_upper);
		}

		else if (percentage >= 67 && percentage < 71)
		{
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_name_female_upper);
		}

		// Case 6: Nouns Uppercase - 7%
		else if (percentage >= 71 && percentage < 78)
		{
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_nouns_upper);
		}

		// Case 7: Other dictionary words Uppercase - 7%
		else if (percentage >= 78 && percentage < 81)
		{
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_verbs_upper);
		}
		else if (percentage >= 81 && percentage < 85)
		{
			// We will go through the dictionary one by one
			fgets(current_word, MAX_WORD_LEN, dictionary_adj_upper);
		}

		/* Dictionary Attack finished, try brute force with randomised */
		// Case 8: Mix of lowercase letters and numbers - 5%
		else if (percentage >= 85 && percentage < 90)
		{
			// generate each digit
			for (int letter_count = 0; letter_count < PASSWORD_LEN_SIX_LETTER; letter_count++)
			{
				// toss a coin to decide this digit is number or letter
				int coin = rand() % 2;
				if (coin == 0)
				{
					// numebers
					current_word[letter_count] = 48 + rand() % 10;
				}
				else if (coin == 1)
				{
					// lowercase letters
					current_word[letter_count] = 97 + rand() % 26;
				}
			}
			current_word[PASSWORD_LEN_SIX_LETTER] = '\0';
			printf("%s\n", current_word);
		}

		// Case 9: Mix of Uppercase letters and numbers - 5%
		else if (percentage >= 90 && percentage < 95)
		{
			// generate each digit
			for (int letter_count = 0; letter_count < PASSWORD_LEN_SIX_LETTER; letter_count++)
			{
				// toss a coin to decide this digit is number or letter
				int coin = rand() % 2;
				if (coin == 0)
				{
					// numbers
					current_word[letter_count] = 48 + rand() % 10;
				}
				else if (coin == 1)
				{
					// uppercase letters
					current_word[letter_count] = 65 + rand() % 26;
				}
			}
			current_word[PASSWORD_LEN_SIX_LETTER] = '\0';
			printf("%s\n", current_word);
		}

		// Case 10: Mix of lowercase letters and Uppercase letters【3%】
		else if (percentage >= 95 && percentage < 98)
		{
			// generate each character
			for (int letter_count = 0; letter_count < PASSWORD_LEN_SIX_LETTER; letter_count++)
			{
				// toss a coin to decide this digit is number or letter
				int coin = rand() % 2;
				if (coin == 0)
				{
					// uppercase letter
					current_word[letter_count] = 65 + rand() % 26;
				}
				else if (coin == 1)
				{
					// lowercase letters
					current_word[letter_count] = 97 + rand() % 26;
				}
			}
			current_word[PASSWORD_LEN_SIX_LETTER] = '\0';
			printf("%s\n", current_word);
		}

		// Case 11: All Symbols【1%】
		else if (percentage == 98)
		{
			// generate each character
			for (int letter_count = 0; letter_count < PASSWORD_LEN_SIX_LETTER; letter_count++)
			{
				// In ASCII table the symbols are not all next to each other, they have four groups and 33 symbols in total
				int pick_symbol_group = rand() % 33;
				int symbol;
				if (pick_symbol_group >= 0 && pick_symbol_group < 16)
				{
					symbol = 32 + rand() % 16;
				}
				else if (pick_symbol_group >= 16 && pick_symbol_group < 23)
				{
					symbol = 58 + rand() % 7;
				}
				else if (pick_symbol_group >= 23 && pick_symbol_group < 29)
				{
					symbol = 91 + rand() % 6;
				}
				else
				{
					symbol = 123 + rand() % 4;
				}
				current_word[letter_count] = symbol;
			}
			current_word[PASSWORD_LEN_SIX_LETTER] = '\0';
			printf("%s\n", current_word);
		}

		// Case 12: Mixture of symbols, numbers and letters [1%]
		else
		{
			// generate each digit
			for (int letter_count = 0; letter_count < PASSWORD_LEN_SIX_LETTER; letter_count++)
			{
				current_word[letter_count] = 32 + rand() % 95;
			}
			current_word[PASSWORD_LEN_SIX_LETTER] = '\0';
			printf("%s\n", current_word);
		}
	}
}

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
