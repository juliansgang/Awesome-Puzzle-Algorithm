#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListLibrary.c"
#include "basicAndInitSpaceFunctions.c"
#include "spaceCheckingFunctions.c"
#include "createPermeatations.c"


int main(){
	
	/*
	int*** bla = makeSpace();
	bla = setBlock(bla, 0, 0, 0, 1);
	printSpace(bla);
	printf("done");*/
	
	
	
	//make array to hold all pieces	
	Pieces* pieces = calloc(1, sizeof(Pieces*)*NUMPIECES);
	
	//this is for inputting the pieces
	
	//loop through pieces 
	for(int i = 0; i<NUMPIECES; i++){
		
		/*
		
		//make a piece and put in array of pieces
		(*pieces)[i] = makePiece(); 
		
		//loop thorugh orientations 
		for(int j = 0; j<NUMORI; j++){
			//input
			printf("Input P:%d, Or:%d\n__________________________|\n",i, j);
			char input[31];
			fgets(input, 30, stdin);
			char* c = malloc(sizeof(char)*27);
			memcpy(c, input, 27*sizeof(char));
			//use string to populate each orientation of piece
			populateSpace(getOrientation((*pieces)[i], j), c);
		}
		
		*/
		
		(*pieces)[i] = getPieceFromUser(i);
		
	}
	
	printf("PRINT OUT OF INPUTS\n");
	
	//loop through pieces 
	for(int x = 0; x<NUMPIECES; x++){
		//loop thorugh orientations 
		for(int i = 0; i<NUMORI; i++){
			printSpace(getOrientation((*pieces)[x], i));	
		}
		
	}
	
	//our puzzle space to store completed puzzle
	int*** puzzleSpace = makeSpace();
	
	//flag for when fitting piece is found and if there is no solution
	int next = 0;
	
	//list to store backtracking data
	List* currentStatus = makeList();
	add(currentStatus, 0, 0, 0);
	
	//piece loop
	while(1){
		if(getCurrentPieceNum(currentStatus)==(NUMPIECES)){break;}
		printf("Piece started: %d\n", getCurrentPieceNum(currentStatus));
		
		//orientaion loop
		while(1){
			
			printf("\tOrientation started: %d\n", getCurrentOrientationNum(currentStatus));
			
			
			if(getCurrentOrientationNum(currentStatus)>=NUMORI){
				//if all orientations tried back track
				printf("Tried all Orientations\n");
				break;
			}else{
				
				//do the next orientation.
				
				//possition loop
				while(1){
					if(getCurrentPositionNum(currentStatus)==27){
						//if all positions tried move to next orientation.
						updateHeadListItem(currentStatus, getCurrentPieceNum(currentStatus), getCurrentOrientationNum(currentStatus)+1, 0);
						break;
					}else{
						//try next position
						printf("\t\tTest Position: %d\n", getCurrentPositionNum(currentStatus));
						//if it fits in place. ie doesn't fall off end or overlap other pieces
						if(doesItFit(puzzleSpace, (*(*pieces)[getCurrentPieceNum(currentStatus)])[getCurrentOrientationNum(currentStatus)], getCurrentPositionNum(currentStatus))){
							printf("\t\t\tSuccess on position %d\n", getCurrentPositionNum(currentStatus));
							addPieceToPuzzle(puzzleSpace,(*(*pieces)[getCurrentPieceNum(currentStatus)])[getCurrentOrientationNum(currentStatus)], getCurrentPositionNum(currentStatus));
							//move on to placing next piece
							add(currentStatus, getCurrentPieceNum(currentStatus)+1, 0, 0);
							//set flag to move to next piece
							next = 1;
							break;
						}
						printf("\t\t\tFailure: position %d does not work\n", getCurrentPositionNum(currentStatus));
						updateHeadListItem(currentStatus, getCurrentPieceNum(currentStatus), getCurrentOrientationNum(currentStatus), getCurrentPositionNum(currentStatus)+1);
					}
				}
				if(next){break;}				
			}
			
		}
		if(next){
			next=0;
			continue;
		}
		
		//else: need to back track
		
		//if has finished searching all orienations and positions of the 0th piece
		if(getCurrentPieceNum(currentStatus)==0){
			//Finish
			printf("Sorry there is no solution!! :-(\n");
			return 0;
		}
		
		//remove current block that has failed to be placed
		deleteHeadListItem(currentStatus);
		//move back to the previous block but in the next position
		updateHeadListItem(currentStatus, getCurrentPieceNum(currentStatus), getCurrentOrientationNum(currentStatus), getCurrentPositionNum(currentStatus)+1);
		//remove the problem piece from the puzzle space
		removePieceFromPuzzle(puzzleSpace,(*(*pieces)[getCurrentPieceNum(currentStatus)])[getCurrentOrientationNum(currentStatus)]);
	}
	
	
	
	//hack:delete last listItem
	deleteHeadListItem(currentStatus);
	
	printf("Completed Puzzle:\n");
	printSpace(puzzleSpace);
	
	ListItem* currentItem = currentStatus->first;
	
	//printing a list of pieces in place
	printf("Instructions:\n");
	printf("Piece\tOrientaion\tPosition\n");
	while(currentItem!=NULL){
		printf("%d\t%d\t\t%d\n",currentItem->piece, currentItem->orientation, currentItem->position);
		currentItem = currentItem->nextItem;
	}
	
	return 0;
}
