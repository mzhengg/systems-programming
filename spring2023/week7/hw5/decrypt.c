#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define MAX 10240
#define MAX_WORD_COUNT 60000                //we have less than 60000 words
#define MAX_WORD_LENGTH 80                //each word is less than 80 letters

//Using these two global variables can be justified :)
char words[MAX_WORD_COUNT][MAX_WORD_LENGTH];        //2-d array to hold all the words
int word_count = 0;                    //number of words, initilized to 0

//Note the words in the dictionary file are sorted
//This fact could be useful
void read_file_to_array(char *filename)
{
    FILE *fp;

    //open the file for reading
    fp = fopen(filename, "r");
    if(fp==NULL)
    {
        printf("Cannot open file %s.\n", filename);
        exit(-1);
    }
    //make sure when each word is saved in the array words,
    //it does not ends with a '\n'
    //see how this is done using fscanf 
    while(!feof(fp))
        fscanf(fp, "%s\n", words[word_count++]);
    fclose(fp);
}

//TODO (DONE)
//Test wether a string word is in the dictionary
//Return 1 if word is in the dictionary
//Return 0 otherwise
//Be efficient in implementing this function
//Efficiency is needed to pass test cases in limited time
int in_dict(char *word) {
    int left = 0;
    int right = word_count - 1;

    while (left <= right) {
        // calculate mid point
        int mid = (left + right) / 2;

        // compares two strings character by character
        int cmp = strcmp(words[mid], word);

        if (cmp == 0) { // if the strings are equal, strcmp returns
            return 1;
        } else if (cmp < 0) { // if the first non-matching character in str1 is lower (in ASCII) than that of str2, then cmp < 0
            left = mid + 1;
        } else { // if the first non-matching character in str1 is greater (in ASCII) than that of str2, then cmp > 0;
            right = mid - 1;
        }
    }

    return 0;
}

//TODO (DONE)
//Use key and shift to decrypt the encrypted message
//len is the length of the encrypted message
//Note the encrypted message is stored as an array of integers (not chars)
//The result is in decrypted
void decryption(unsigned char key, unsigned char shift, const int *encrypted, int len, char *decrypted)
{
    // for each integer in the encrypted message, apply the reverse operations
    for (int i = 0; i < len; i++) {
        decrypted[i] = (encrypted[i] ^ key) >> shift;
    }

    // last element in the string is null byte
    decrypted[len] = '\0';
}

//TODO (DONE)
//calculate a score for a message msg
//the score is used to determine whether msg is the original message
int message_score(const char *msg)
{
    // the number of words in the message that are present in the dictionary
    int score = 0;

    char *word, *str;

    // duplicate the message
    str = strdup(msg);

    // keep looping through the words in the message
    while ((word = strsep(&str, " \t\n\r")) != NULL) {
        // loop through each character in the word
        for (int i = 0; i < strlen(word); i++) {
            // verify that the character is a valid alphabet letter
            if (!isalpha(word[i])) {
                // if not a valid alphabet letter, continue on with the next letter
                continue;
            }

            // otherwise, it's a valid alphabet letter; convert it to lowercase
            word[i] = tolower(word[i]);
        }

        // check if the given word is in the dictionary; if so, then increment score
        if (in_dict(word)) {
            score++;
        }
    }

    return score;
}

//search using all the (key, shift) combinations
//to find the original message
//result is saved in message
void search(const int *encrypted, int len, char *message)
{
	char decrypted[MAX];

    int max_score = 0;
    strcpy(message, "");
    for(unsigned char k = 0; k < 255; k++)
    {
        for(unsigned char shift = 0; shift <= 24; shift++)
        {
            decryption(k, shift, encrypted, len, decrypted);
			int score = message_score(decrypted);
			if(score > max_score)
			{	
				max_score = score;
				strcpy(message, decrypted);
			}
        }
    }
}

//TODO (DONE)
//read the encrypted message from the file to encrypted
//return number of bytes read
int read_encrypted(char *filename, int *encrypted)
{
    // open encrypted file
    FILE *fp = fopen(filename, "rb");

    // if there is an error with opening the file, let the user know
    if(fp == NULL) {
        printf("Can't open file %s.\n", filename);
        exit(-1);
    }

    // get the size of the encrypted file in bytes
    int bytes = fread(encrypted, sizeof(int), MAX, fp);

    // close the file
    fclose(fp);

    // return the number of bytes
    return bytes;
}

//Do not change the main() function
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("%s encrypted-message\n", argv[0]);
		return 0;
	}

	read_file_to_array("dict.txt");

	int encrypted[MAX];
	int len = read_encrypted(argv[1], encrypted);
	
	char message[MAX];
	strcpy(message, "");
	search(encrypted, len, message);
	printf("%s\n", message);
	return 0;
}