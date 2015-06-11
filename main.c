#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "md5.h"

#define MAX_SIZE 256
char *char2binstr(unsigned char i)
{
	/* Convert an int to a binary string */
	size_t bits = sizeof(unsigned int) * CHAR_BIT;
	char * str = malloc(bits + 1);
	if(!str) return NULL;
	str[bits] = 0;

	unsigned u = *(unsigned *)&i;
	for(; bits--; u >>= 1)
		str[bits] = u & 1 ? '1' : '0';

	return str;
}

int count_ones(char* str, size_t len){
    int	count = 0;
	int i = 0;
	for (i = 0; i < len; ++i){
		if (str[i] == '1')
			count++;
	}
	return count;
}
int main(void){
	char string[MAX_SIZE];
	unsigned char digest[16];

	while (1) {
		printf("\nInput string: ");
		fgets(string, MAX_SIZE, stdin);
		strtok(string, "\n");
		int i;
		/*
		printf("Input binary string: \n");
		int count;
		count = 0;
		for (i = 0; i < CHAR_BIT; ++i){
			char* str = char2binstr(string[i]);
			count += count_ones(str, CHAR_BIT);
			printf("%s", str);
		}
		printf("\n");
		printf("Number of ones: %d\n", count);
		*/
		MD5_CTX ctx;
		MD5_Init(&ctx);
		MD5_Update(&ctx, string, strlen(string));
		MD5_Final(digest, &ctx);	

		char mdString[33];
		for (i = 0; i < 16; ++i)
			sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
		printf("MD5 digest:   %s\n\n", mdString);
		/*
		count = 0;
		for (i = 0; i < 33; ++i){
			char* s = char2binstr(mdString[i]);
			count += count_ones(s, CHAR_BIT);
			printf("%s", s);
		}
		printf("\n");
		printf("Number of ones: %d\n", count);
		*/
	}
	return 0;
}
