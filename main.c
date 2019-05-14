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

#define listlength 10000
#define wordslength 6
#define SHA256_BLOCK_SIZE 32
#define PASSWORD_LEN_OPTION_ONE 4
#define PASSWORD_LEN_OPTION_TWO 6
#define MAX_WORD_LEN 20
#define NUM_4_LETTERS_PASSWORDS 10

// Constants
#define FIRST_GUESS_COMMON_PASSWORDS  "common_passwords.txt"
#define PASSWORD_FILE  "pwd4sha256"

char **getwords(FILE *fp, int *n);
void free_array(char **words, int rows);
void create_hash(BYTE text[], BYTE hash[SHA256_BLOCK_SIZE]);
unsigned char** readSHAfilePasswords();
void crack_noargument();
int checkPasswords(BYTE *passwords, char *guess); 

int main(int argc, char **argv)
{

	int i, nwords = 0;
	char **words = NULL; /* file given as argv[1] (default dictionary.txt) */
	char *fname = argc > 1 ? argv[0] : FIRST_GUESS_COMMON_PASSWORDS;
	FILE *dictionary = fopen(fname, "r");

	if (!dictionary)
	{ /* validate file open */
		fprintf(stderr, "error: file open failed.\n");
		return 1;
	}
	words = getwords(dictionary, &nwords); 
	if (!(words))
	{
		fprintf(stderr, "error: getwords returned NULL.\n");
		return 1;
	}
	fclose(dictionary);

	//for (i = 0; i < nwords; i++)

	// Part 1: No arguments to crack.exe
	if (argc == 1)
	{
		crack_noargument();
	}

	// Part 2: one argument to crack.exe
	/*else if (argc == 2)
		{
			crack_twoargument(words[i], argcv0]);
		}

		// Part 3: three arguments to crack.exe
		else if (argc == 3)
		{
			crack_oneargument(words[i], , argv[0], argv[1]);
		}*/
	else
	{
		perror("can not accept 3 inputs");
		exit(EXIT_FAILURE);
	}

	free_array(words, nwords);

	return 0;
}

/* read all words 1 per-line, from 'fp', return
 * pointer-to-pointers of allocated strings on 
 * success, NULL otherwise, 'n' updated with 
 * number of words read.
 */
char **getwords(FILE *fp, int *n)
{

	char **words = NULL;
	char buf[wordslength + 1] = {0};
	int maxlen = listlength > 0 ? listlength : 1;

	if (!(words = calloc(maxlen, sizeof *words)))
	{
		fprintf(stderr, "getwords() error: virtual memory exhausted.\n");
		return NULL;
	}

	while (fgets(buf, wordslength + 1, fp))
	{

		size_t wordlen = strlen(buf); /* get word length */

		if (buf[wordlen - 1] == '\n') /* strip '\n' */
			buf[--wordlen] = 0;

		words[(*n)++] = strdup(buf); /* allocate/copy */

		if (*n == maxlen)
		{ /* realloc as required, update maxlen */
			void *tmp = realloc(words, maxlen * 2 * sizeof *words);
			if (!tmp)
			{
				fprintf(stderr, "getwords() realloc: memory exhausted.\n");
				return words; /* to return existing words before failure */
			}
			words = tmp;
			memset(words + maxlen, 0, maxlen * sizeof *words);
			maxlen *= 2;
		}
	}

	return words;
}


void free_array(char **words, int rows)
{

	int i;
	for (i = 0; i < rows; i++)
	{
		free(words[i]);
	}
	free(words);
}

//create hash representation for BYTE array
void create_hash(BYTE text[], BYTE hash[SHA256_BLOCK_SIZE])
{
	SHA256_CTX ctx;

	sha256_init(&ctx);
	sha256_update(&ctx, text, PASSWORD_LEN_OPTION_ONE);
	sha256_final(&ctx, hash);
}

//read file containing SHA Passwords and returns the bite array
unsigned char** readSHAfilePasswords()
{
	FILE *dictionary;
	// Store the binary file as an array of hex values
	unsigned char listofHashes[NUM_4_LETTERS_PASSWORDS][SHA256_BLOCK_SIZE];

	dictionary = fopen(PASSWORD_FILE, "rb");

	for (int i = 0; i < NUM_4_LETTERS_PASSWORDS; i++)
	{
		fread(listofHashes[i], sizeof(listofHashes[i]), 1, dictionary);
	}

	fclose(dictionary);

	return listofHashes;
}


//checks if guess in passwords and returns the index if it is
int checkPasswords(BYTE *passwords, char *guess)
{
	//create hash for guess
	BYTE guessHash[SHA256_BLOCK_SIZE];
	create_hash((BYTE *) guess, guessHash);

	for (int i = 0; i < 288; i++)
	{
		int sz = SHA256_BLOCK_SIZE; // number of characters to copy

		BYTE check[sz + 1];
		int from = i; // here from is where you start to copy

		strncpy(check, passwords + from, sz);
		if (memcmp(check, guessHash, SHA256_BLOCK_SIZE) == 0)
		{
			return i / 32;
		}
	}

	return -1;
}



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

	// check the list of hash passwrod against word from list of most common words
	//if (checkPasswords(passwords, word) != -1){
	//	printf("%s\n", word);
	//	printf("%d\n", checkPasswords(passwords, word));
	//}

	char* text = "should stop";

	// 4-letters passwords: Brute Force
	for (int i = 32; i <= 126 && flag == 1; i++)
	{
		for (int j = 32; j <= 126 &&flag == 1; j++)
		{
			for (int n = 32; n <= 126 &&flag == 1 ; n++)
			{
				for (int m = 32; m <= 126 &&flag == 1 ; m++)
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
					if (countPasswords == NUM_4_LETTERS_PASSWORDS){
						flag = 0;
					}
				}
			}
		}
	}
}

/*void crack_twoargument()
{

}

void crack_twoargument()
{

}

*/
