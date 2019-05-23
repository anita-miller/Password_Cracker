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
#include "crack_zero_argument_helper_functions.h"

#define PASSWORD_LEN_SIX_LETTER 6
#define MAX_WORD_LEN 10000

#define START_FIRST_GROUP_SYMBOLS 32
#define START_SECOND_GROUP_SYMBOLS 58
#define START_THIRD_GROUP_SYMBOLS 91
#define START_FOURTH_GROUP_SYMBOLS 123
#define START_POS_UPPERCASE 65
#define START_POS_LOWERRCASE 97
#define START_POS_NUMBERS 48

void dictionaryAttack(int rateOfOccurance, FILE **files)
{
	char curr_word[MAX_WORD_LEN];
	//opening dicitonary files
	
	// Case 1:  Nouns Lowercase -25%
	if (rateOfOccurance >= 0 && rateOfOccurance < 25)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[4]);
		printf("%s\n", curr_word);
	}

	// Case 2: Number combination - %15
	else if (rateOfOccurance >= 25 && rateOfOccurance < 40)
	{
		// We will generate a random 6 digit number
		for (int position = 0; position < PASSWORD_LEN_SIX_LETTER; position++)
		{
			curr_word[position] = START_POS_NUMBERS + rand() % 10;
		}
		curr_word[PASSWORD_LEN_SIX_LETTER] = '\0';
		printf("%s\n", curr_word);
	}

	// Case 3: Names Lowercase - 15%
	else if (rateOfOccurance >= 40 && rateOfOccurance < 58)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[0]);
		printf("%s\n", curr_word);
	}

	else if (rateOfOccurance >= 48 && rateOfOccurance < 55)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[2]);
		printf("%s\n", curr_word);
	}

	// Case 4: Other dictionary words Lowercase - 10%
	else if (rateOfOccurance >= 55 && rateOfOccurance < 60)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[6]);
		printf("%s\n", curr_word);
	}
	else if (rateOfOccurance >= 60 && rateOfOccurance < 65)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[8]);
		printf("%s\n", curr_word);
	}

	// Case 5: Names Uppercase - 5%
	else if (rateOfOccurance >= 65 && rateOfOccurance < 68)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[1]);
		printf("%s\n", curr_word);
	}

	else if (rateOfOccurance >= 68 && rateOfOccurance < 70)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[3]);
		printf("%s\n", curr_word);
	}

	// Case 6: Nouns Uppercase - 5%
	else if (rateOfOccurance >= 70 && rateOfOccurance < 75)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[5]);
		printf("%s\n", curr_word);
	}

	// Case 7: Other dictionary words Uppercase - 5%
	else if (rateOfOccurance >= 75 && rateOfOccurance < 78)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[7]);
		printf("%s\n", curr_word);
	}
	else if (rateOfOccurance >= 78 && rateOfOccurance < 80)
	{
		// We will go through the dictionary one by one
		fgets(curr_word, MAX_WORD_LEN, files[9]);
		printf("%s\n", curr_word);
	}
}



void mixOfNumLettersBruteForce(int rateOfOccurance)
{
	char curr_word[MAX_WORD_LEN];
	// toss a randomiser to decide this digit is number or letter
	int randomiser = rand() % 2;
	if (rateOfOccurance >= 80 && rateOfOccurance < 90)
	{
		// generating digits
		for (int position = 0; position < PASSWORD_LEN_SIX_LETTER; position++)
		{
			if (randomiser == 0)
			{
				// numebers
				curr_word[position] = START_POS_NUMBERS + rand() % 10;
			}
			else if (randomiser == 1)
			{
				// lowercase letters
				curr_word[position] = START_POS_LOWERRCASE + rand() % 26;
			}
		}
		curr_word[PASSWORD_LEN_SIX_LETTER] = '\0';
		printf("%s\n", curr_word);
	}

	// Case 9: Mix of Uppercase letters and numbers - 5%
	else if (rateOfOccurance >= 90 && rateOfOccurance < 95)
	{
		// generating digits
		for (int position = 0; position < PASSWORD_LEN_SIX_LETTER; position++)
		{
			if (randomiser == 0){
				// numbers
				curr_word[position] = START_POS_NUMBERS + rand() % 10;
			}
			else if (randomiser == 1){
				// uppercase letters
				curr_word[position] = START_POS_UPPERCASE + rand() % 26;
			}
		}
		curr_word[PASSWORD_LEN_SIX_LETTER] = '\0';
		printf("%s\n", curr_word);
	}

	// Mix of lowercase letters and Uppercase letters【3%】
	else if (rateOfOccurance >= 95 && rateOfOccurance < 98)
	{
		// generating characters
		for (int position = 0; position < PASSWORD_LEN_SIX_LETTER; position++)
		{
			if (randomiser == 0){
				// uppercase letter
				curr_word[position] = START_POS_UPPERCASE + rand() % 26;
			}
			else if (randomiser == 1){
				// lowercase letters
				curr_word[position] = START_POS_LOWERRCASE + rand() % 26;
			}
		}
		curr_word[PASSWORD_LEN_SIX_LETTER] = '\0';
		printf("%s\n", curr_word);
	}

	// all possible symbols【1%】
	else if (rateOfOccurance == 98)
	{
		// generating characters
		for (int position = 0; position < PASSWORD_LEN_SIX_LETTER; position++)
		{
			// 33 symbols but since they arent all after each other in the table
			//we need to find them seperately

			int group_of_symbol = rand() % 33;
			int symbol;
			if (group_of_symbol >= 0 && group_of_symbol < 16){
				symbol = START_FIRST_GROUP_SYMBOLS + rand() % 16;
			}

			else if (group_of_symbol >= 16 && group_of_symbol < 23){
				symbol = START_SECOND_GROUP_SYMBOLS + rand() % 7;
			}

			else if (group_of_symbol >= 23 && group_of_symbol < 29){
				symbol = START_THIRD_GROUP_SYMBOLS + rand() % 6;
			}

			else{
				symbol = START_FOURTH_GROUP_SYMBOLS + rand() % 4;
			}

			curr_word[position] = symbol;
		}
		curr_word[PASSWORD_LEN_SIX_LETTER] = '\0';
		printf("%s\n", curr_word);
	}

	// mix of everything[1%]
	else
	{
		// generate each digit
		for (int position = 0; position < PASSWORD_LEN_SIX_LETTER; position++)
		{
			curr_word[position] = START_FIRST_GROUP_SYMBOLS + rand() % 95;
		}
		curr_word[PASSWORD_LEN_SIX_LETTER] = '\0';
		printf("%s\n", curr_word);
	}
}
