#ifndef TURING_MACHINE
#define TURING_MACHINE

// structure of turing machine
struct Turing_Machine
{
	char *tape;
	int size;
	int pt;
};

// func. declaration of TM operations.
struct Turing_Machine* inittialize_TM(int);
void copyInput(struct Turing_Machine*, char*);
int checkSymbol(struct Turing_Machine*, char);
void moveRight(struct Turing_Machine*, char, int);
void moveLeft(struct Turing_Machine*, char, int);
void displayTM(struct Turing_Machine*);
int shiftRightUntilSymbolIsNotSeen(struct Turing_Machine*, char, int);
int shiftLeftUntilSymbolIsNotSeen(struct Turing_Machine*, char, int);
int shiftRightUntilSymbolIsSeen(struct Turing_Machine*, char, int);
int shiftLeftUntilSymbolIsSeen(struct Turing_Machine*, char, int);
int convertUnaryToBinary(struct Turing_Machine* , int);

#endif