#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#include <ctype.h>
#include "hangman.h"

int check = 0;
int get_word(char secret[]) {
	FILE *fp;
	fp = fopen("words.txt", "r");
	char letter = NULL;
	int count = 0, k=0;
	while (letter != EOF) {
		letter = fgetc(fp);
		if (letter == ' ')count++;
	}
	fclose(fp);
	srand(time(NULL));
	int guessed = (rand() % count) + 1;
	fp = fopen("words.txt", "r");
	int count2 = 0;
	while (count2 < guessed) {
		letter = fgetc(fp);
		if (letter == ' ')count2++;
	}
	letter = fgetc(fp);
	while(letter!=EOF){
		secret[k] = letter;
		letter = fgetc(fp);
		if (letter == ' ')break;
		k++;
	}

	fclose(fp);
	return 0;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
	int result = 0;


	for (int i = 0; i < strlen(secret); i++) {
		for (int j = 0; j < strlen(letters_guessed); j++) {
			if (secret[i] == letters_guessed[j]) {
				guessed_word[i] = letters_guessed[j];
				result = 1;
				check++;
			}
		}
		if (!result && isalpha(guessed_word[i]) != 2) 
			guessed_word[i] = '_';
	}

	
}

void get_available_letters(const char letters_guessed[], char available_letters[]){
	char letters[] = "abcdefghijklmnopqrstuvwxyz";
	if (strlen(letters_guessed) == 0) {
		strcpy(available_letters, letters);
	}
	else {
		for (int i = 0; i < strlen(available_letters); i++) {
			for (int j = 0; j < strlen(letters_guessed); j++) {
				if (available_letters[i] == letters_guessed[j]){
					for (int k = i; k < strlen(available_letters); k++) {
						available_letters[k] = available_letters[k + 1];
					}
					available_letters[strlen(available_letters)] = '\0';
					break;
				}
			}
		}
	}

}

int is_word_guessed(const char secret[], const char letters_guessed[]) {
	int counter = 0;
	for (int i = 0; i < strlen(letters_guessed); i++) {
		if (letters_guessed[i] == secret[i]) counter++;
		else return 0;
	}
	if (counter != strlen(secret))return 0;
	return 1;
}





void hangman(const char secret[]) {
	printf("Hello, my friend!\n");
	printf("Let's play the 'HANGMAN'\n");
	printf("You need to unravel the word!\n");
	char letters_guessed[15] = "";
	char guessed_word[15] = "";
	char available_letters[30] = "";
	int l = 5, g = 0;;

	printf("my guessed word is %s\n", secret);
	do{
		int p = 0;

		int f = check;
		get_guessed_word(secret, letters_guessed, guessed_word);

		if (check == f && g != 0) {
			printf("ops, you make mistake!\n");
			l--;
		}
		g++;
		
		printf("Our attempts is %d\n", l);

		for (int k = 0; k < strlen(guessed_word); k++)
			printf("%c ", guessed_word[k]);
		printf("\n");

		for (int i = 0; i < strlen(secret); i++) {
			if (secret[i] == guessed_word[i])p++;
		}
		if (p == strlen(secret)) {
			l = -2;
			break;
		}

		get_available_letters(letters_guessed, available_letters);
		for (int i = 0; i < strlen(available_letters); i++) {
			printf("%c", available_letters[i]);
		}
		printf("\n");
		scanf("%s", &letters_guessed);
		for (int i = 0; i < strlen(letters_guessed); i++)
			letters_guessed[i] = tolower(letters_guessed[i]);


		if (isalpha(letters_guessed[1]) > 1) {
			if (is_word_guessed(secret, letters_guessed) == 0)l = 0;
			else l = -2;
		}
		
	}while(l>0);


	if (l == -2) {
		printf("Congratulations!\n");
		printf("You win!\n");
	}
	else {
		printf("You lose!\n");
		for (int i = 0; i < strlen(secret); i++)
			printf("%c", secret[i]);
	}

}