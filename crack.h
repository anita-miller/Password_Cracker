#ifndef CRACK_H_
#define CRACK_H_

void crack_noargument();

void crack_oneargument(int number_guesses);

void crack_twoargument(char *guesses_file, char *hashes_file);

#endif