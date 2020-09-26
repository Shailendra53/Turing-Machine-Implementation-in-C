#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turing_machine.h"


struct Turing_Machine* inittialize_TM(int size){

	struct Turing_Machine* TM;
	// intiializing TM
	TM = (struct Turing_Machine*)malloc(sizeof(struct Turing_Machine));
	// head pointer at 1
	TM->pt = 1;
	// initializing size, tape, head as '>' and empty symbol as 'U'
	TM->size = size;
	TM->tape = (char*)malloc(sizeof(char)*size);
	TM->tape[0] = '>';
	for(int i=1;i<size;i++){
		TM->tape[i] = 'U';
	}
	// return TM instance
	return TM;
}

// copy given input to tuning machine tape.
void copyInput(struct Turing_Machine* TM, char* input){
	int size = strlen(input);
	for(int i=0;i<size;i++){
		TM->tape[i+1] = input[i];
	}
}

// function to check whether pointer symbol matches given symbol c.
int checkSymbol(struct Turing_Machine* TM, char c){
	if(TM == NULL){
		printf("Turing Machine is not Initialised\n");
		exit(1);
	}
	if(*(TM->tape + TM->pt) == c)
		return 1;
	else
		return 0;
}

// move right in TM tape by modifying the tape symbol to given symbol c
// if c == '\0' then move right without changing symbol
void moveRight(struct Turing_Machine* TM, char c, int counter){
	if(TM == NULL){
		printf("Turing Machine is not Initialised\n");
		exit(1);
	}
	if(TM->pt < TM->size-1){
		char prev = TM->tape[TM->pt];
		if(c != 0){
			TM->tape[TM->pt] = c;
		}
		printf("%d : %c %c R\n", counter, prev, TM->tape[TM->pt]);
		TM->pt++;
	}
	else{
		printf("Turing Machine is on last pointer of tape so cannot move right\n");
	}
}

// move left in TM tape by modifying the tape symbol to given symbol c
// if c == '\0' then move left without changing symbol
void moveLeft(struct Turing_Machine* TM, char c, int counter){
	if(TM == NULL){
		printf("Turing Machine is not Initialised\n");
		exit(1);
	}
	if(TM->pt > 0){
		char prev = TM->tape[TM->pt];
		if(c != 0){
			TM->tape[TM->pt] = c;
		}
		printf("%d : %c %c L\n", counter, prev, TM->tape[TM->pt]);
		TM->pt--;
	}
	else{
		printf("Turing Machine is on first pointer of tape so cannot move left\n");
	}	
}

// to print the data of turing machine until first 'U'
void displayTM(struct Turing_Machine* TM){
	printf("==================Printing Turing Machine Data=================\n");
	if(TM == NULL){
		printf("Turing Machine is not Initialised\n");
	}
	else{
		int i = 0;
		printf("%c", TM->tape[i]);
		i++;
		while(TM->tape[i] != 'U'){
			printf("%c", TM->tape[i]);
			i++;
		}
		printf("%c\n", TM->tape[i]);
		for(int i=0;i<TM->pt;i++){
			printf("_");
		}
		printf("^");
		i = TM->pt;
		while(TM->tape[i] != 'U'){
			printf("_");
			i++;
		}
	}
	printf("\n==============================================================\n");
}

// shift right until given symbol c is not seen
int shiftRightUntilSymbolIsNotSeen(struct Turing_Machine* TM, char c, int counter){
	char temp = '\0';
	while(checkSymbol(TM, c) != 1){
		moveRight(TM, temp, counter);
		counter++;
	}
	return counter;
}

// shift left until given symbol c is not seen
int shiftLeftUntilSymbolIsNotSeen(struct Turing_Machine* TM, char c, int counter){
	char temp = '\0';
	while(checkSymbol(TM, c) != 1){
		moveLeft(TM, temp, counter);
		counter++;
	}
	return counter;
}

// shift right until given symbol c is seen
int shiftRightUntilSymbolIsSeen(struct Turing_Machine* TM, char c, int counter){
	char temp = '\0';
	while(checkSymbol(TM, c) == 1){
		moveRight(TM, temp, counter);
		counter++;
	}
	return counter;
}

// shift left until given symbol c is seen
int shiftLeftUntilSymbolIsSeen(struct Turing_Machine* TM, char c, int counter){
	char temp = '\0';
	while(checkSymbol(TM, c) == 1){
		moveLeft(TM, temp, counter);
		counter++;
	}
	return counter;
}

// convert the unary tape symbols to binary representation
// given tape should be of format ">11#U"
// start with head, then unary rep. followed by # and the empty symbol U
int convertUnaryToBinary(struct Turing_Machine* TM, int counter){
	char c = '\0';
	// read one by one each one and after hash 
	// make their binary rep. in reverse manner.
	while(checkSymbol(TM, '#') == 0){
		moveRight(TM, 'Y', counter);
		counter++;
		counter = shiftRightUntilSymbolIsNotSeen(TM, '#', counter);
		moveRight(TM, c, counter);
		counter++;
		while(checkSymbol(TM, '1') == 1){
			moveRight(TM, '0', counter);
			counter++;
		}
		moveLeft(TM, '1', counter);
		counter++;
		counter = shiftLeftUntilSymbolIsNotSeen(TM, 'Y', counter);
		moveRight(TM, c, counter);
		counter++;
	}
	counter = shiftRightUntilSymbolIsNotSeen(TM, 'U', counter);
	moveLeft(TM, c, counter);
	counter++;
	// finally reverse the bianry rep. after hash to array after head of tape
	// in reverse manner
	while(checkSymbol(TM, '#') == 0){
		if(checkSymbol(TM, '0') == 1){
			counter = shiftLeftUntilSymbolIsNotSeen(TM, '#', counter);
			moveLeft(TM, c, counter);
			counter++;
			counter = shiftLeftUntilSymbolIsSeen(TM, 'Y', counter);
			moveRight(TM, c, counter);
			counter++;
			moveRight(TM, '0', counter);
			counter++;
			counter = shiftRightUntilSymbolIsNotSeen(TM, 'U', counter);
			moveLeft(TM, c, counter);
			counter++;
			moveLeft(TM, 'U', counter);
			counter++;
		}
		else if(checkSymbol(TM, '1') == 1){
			counter = shiftLeftUntilSymbolIsNotSeen(TM, '#', counter);
			moveLeft(TM, c, counter);
			counter++;
			counter = shiftLeftUntilSymbolIsSeen(TM, 'Y', counter);
			moveRight(TM, c, counter);
			counter++;
			moveRight(TM, '1', counter);
			counter++;
			counter = shiftRightUntilSymbolIsNotSeen(TM, 'U', counter);
			moveLeft(TM, c, counter);
			counter++;
			moveLeft(TM, 'U', counter);
			counter++;
		}
	}
	moveLeft(TM, '\0', counter);
	counter++;
	while(checkSymbol(TM, 'Y') == 1){
		moveLeft(TM, '#', counter);
		counter++;
	}
	moveRight(TM, '\0', counter);
	counter++;
	moveRight(TM, '\0', counter);
	counter++;
	// remove uncessary symbols
	while(checkSymbol(TM, 'U') == 0){
		moveRight(TM, 'U', counter);
		counter++;
	}
	counter = shiftLeftUntilSymbolIsNotSeen(TM, '>', counter);
	moveRight(TM, c, counter);
	counter++;
}