#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct ListItem {
	int **piece;
	int orientation;
	int position;
	struct ListItem* nextItem;
	
} ListItem;

// Will create a 2d Array to play with
int** createArray()
{
    int* values = calloc(3*3, sizeof(int));
    int** rows = malloc(3*sizeof(int*));
    for (int i=0; i<3; ++i)
    {
        rows[i] = values + i*3;
    }
    return rows;
}
// Will rotate a piece by 90degrees clockwise
int** rotatePiece(int **rotateMatrix){
	int** newMatrix = createArray();
	int n = 3;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            newMatrix[i][j] = rotateMatrix[n - j - 1][i];
        }
    }
    return newMatrix;

}
// Will print out a 2D matrix
int printMatrix2D(int **arr){
	for (int i = 0; i < 3; i++) {
		printf("{ %d,%d,%d },\n", arr[i][0],arr[i][1],arr[i][2]);
	}
	printf("\n");
	return 0;
}
 
int main() {
	ListItem *allPieces = NULL;

	int cube[3][3][3];
	int blocksInPuzzle = 0;
	int piecesInPuzzle = 0;
	int shouldAskForPiece = 1;
	int shouldAskForBlock = 1;
	char input[100];
	

	printf("Currently only works for a 2D face, will implement third dimention soon \n \n");
    
	
	// Get input from the user
	while (shouldAskForPiece == 1){
		printf("Please Insert a piece--\n");
		printf("Insert a block of the piece as type (x,y)(type F to finish):");
		// Create a new piece
		ListItem *newPiece = malloc(sizeof(ListItem));
		int** newPieceArr = createArray();

		while (shouldAskForBlock == 1){
			printf("Insert a Piece:\n");
			scanf("%s",input);
			if(input[0] == 'F') {
				shouldAskForBlock = 0;
			} else {
				newPieceArr[input[1] - '0'][input[3] - '0'] = 1;
				
			}
		}
		// Temporary - will stop while loop after first piece is inputted
		shouldAskForPiece = 0;

		// Add the piece to out list
		newPiece->piece = newPieceArr;
		newPiece->nextItem = allPieces;
		allPieces = newPiece;
		piecesInPuzzle++;

		// Future proof - check if too many blocks have been inputted - does not work right now
		if (blocksInPuzzle > 27){
			printf("Error: too many blocks\n");
		} else if (blocksInPuzzle == 27){
			printf("Input complete \n");
			shouldAskForPiece = 0;
		}
	}
	// Now show first piece in each rotation
	ListItem *printPieces = malloc(sizeof(ListItem));
	printPieces = allPieces;
	while(printPieces){
		int **tempPiece = createArray();
		tempPiece = printPieces->piece;
		printMatrix2D(tempPiece);
		tempPiece = rotatePiece(tempPiece);
		printMatrix2D(tempPiece);
		tempPiece = rotatePiece(tempPiece);
		printMatrix2D(tempPiece);
		tempPiece = rotatePiece(tempPiece);
		printMatrix2D(tempPiece);
		
		printPieces = printPieces->nextItem;
	}
	

	return 0;

}