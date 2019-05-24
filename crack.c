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
#include "helper_functions/crack_zero_argument_helper_functions.h"
#include "helper_functions/crack_one_argument_helper_functions.h"

#define SHA256_BLOCK_SIZE 32
#define MAX_WORD_LEN 10000
#define NUM_FOUR_LETTERS_PASSWORDS 10
#define NUM_SIX_LETTERS_PASSWORDS 20
#define PASSWORD_LEN_FOUR_LETTER 4
#define PASSWORD_LEN_SIX_LETTER 6

#define START_FIRST_GROUP_SYMBOLS 32
#define START_SECOND_GROUP_SYMBOLS 58
#define START_THIRD_GROUP_SYMBOLS 91
#define START_FOURTH_GROUP_SYMBOLS 123
#define START_POS_UPPERCASE 65
#define START_POS_LOWERRCASE 97
#define START_POS_NUMBERS 48

#define PASSWORD_FILE_FOURWORDS "pwd4sha256"
#define PASSWORD_FILE_SIXWORDS "pwd6sha256"
#define COMMON_PASSWORDS "6_letters/common_passwords.txt"
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
	six_letter_pwd_creator(curr_guess, six_letter_hashed_passwords);
}



void crack_oneargument(int number_guesses)
{
	//int number_guesses = atoi(num_guesses);
	char curr_word[MAX_WORD_LEN];
	int flag = 1;
	
	// Dictionary Attack 
	// First thing first is a dictionary of common passwords
	FILE *dictionary_common_passwords = fopen(DB_COMMON_PASSWORDS, "r");
	while (fgets(curr_word, MAX_WORD_LEN, dictionary_common_passwords))
	{
		// Because fgets also gets the newline character, so we search for length 7 and cut the final \n char.
		curr_word[PASSWORD_LEN_SIX_LETTER] = '\0';
		printf("%s\n", curr_word);

		// if reached the number specified then break;
		number_guesses--;
		if (number_guesses == 0)
		{
			//if all the guesses are found set flag as 0
			flag = 0;
			fclose(dictionary_common_passwords);
		}
	}
	
	// if flag value is 0 means all the guesses are found, if its 1 it means we need to make more
	if(flag == 1){
		//Dictionary Attack
		FILE *files[10];

		files[0] = fopen(DB_NAMES_MALE_LOWER, "r");
		files[1] = fopen(DB_NAMES_MALE_UPPER, "r");
		files[2] = fopen(DB_NAMES_FEMALE_LOWER, "r");
		files[3] = fopen(DB_NAMES_FEMALE_UPPER, "r");
		files[4] = fopen(DB_1000_NOUNS_LOWER, "r");
		files[5] = fopen(DB_1000_NOUNS_UPPER, "r");
		files[6] = fopen(DB_1000_VERBS_LOWER, "r");
		files[7] = fopen(DB_1000_VERBS_UPPER, "r");
		files[8] = fopen(DB_1000_ADJEC_LOWER, "r");
		files[9] = fopen(DB_1000_ADJEC_UPPER, "r");

		time_t seed_of_seed;
		srand((unsigned)time(&seed_of_seed));
		int seed = rand();
		srand((unsigned)seed);

		// giving each type of password explained in README a weight based on how popular they are
		for (int i = 0; i < number_guesses; i++)
		{
			// craeting random value
			int rateOfOccurance = rand() % 100;

			if (rateOfOccurance < 80)
			{
				dictionaryAttack(rateOfOccurance, files);
				
			}
			else
			{
				//after dicionary attack we try mix of letteres and num using brute force
				mixOfNumLettersBruteForce(rateOfOccurance);
				
			}
		}
		printf("%d\n", number_guesses);
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

