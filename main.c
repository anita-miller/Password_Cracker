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

#include "crack.h"
#include "helper_functions.h"

int main(int argc, char **argv)
{
	// Part 1: No arguments to crack.exe
	if (argc == 1)
	{
		crack_noargument();
	}

	// Part 2: one argument to crack.exe
	else if (argc == 2)
	{
		crack_oneargument(argv[1]);
	}

	// Part 3: three arguments to crack.exe	
	else if (argc == 3)
	{
		crack_twoargument(argv[1], argv[2]);
	}
	else
	{
		perror("can not accept 3 inputs");
		exit(EXIT_FAILURE);
	}

	return 0;
}
