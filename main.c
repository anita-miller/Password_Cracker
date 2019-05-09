/*
* 
* Anita Naseri 
* Assignment 2, May 2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define listlength 10000
#define wordslength 6
#define SHA256_BLOCK_SIZE 32

#include "sha256.h"

int main(int argc, char **argv)
{

	int i, nwords = 0;
	char **words = NULL; /* file given as argv[1] (default dictionary.txt) */
	char *fname = argc > 1 ? argv[0] : "common_passwords.txt";
	FILE *dictionary = fopen(fname, "r");

	if (!dictionary)
	{ /* validate file open */
		fprintf(stderr, "error: file open failed.\n");
		return 1;
	}

	if (!(words = getwords(dictionary, &nwords)))
	{
		fprintf(stderr, "error: getwords returned NULL.\n");
		return 1;
	}
	fclose(dictionary);

	printf("\n '%d' words read from '%s'\n\n", nwords, fname);

	for (i = 0; i < nwords; i++)
	{
		//printf("%s\n", words[i]);
		if (argc < 1)
		{
			crack_noargument(words[i]);
		}
		else if (argc == 1)
		{
			crack_oneargument(argc[0]);
		}

		else if (argc == 2)
		{
			crack_oneargument(argc[0], argc[1]);
		}
		else
		{
			perror("can not accept 3 inputs");
			exit(EXIT_FAILURE);
		}
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


void crack_noargument(char *word)
{
	BYTE text[] = {word};
	SHA256_CTX ctx;
	int idx;
	int pass = 1;
}

void crack_oneargument()
{

}

void crack_twoargument()
{

}
}

void crack_oneargument()
{

}

void crack_twoargument()
{

}
/*

if (argc < 2)
	{
		
	}
	else if (argc == 2)
	{

	}
	else{
		perror("can not accept 3 inputs");
		exit(EXIT_FAILURE);
	}
	*/