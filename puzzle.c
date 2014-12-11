#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---LinkedList---*/
struct ListItem {
	int piece;
	int orientation;
	int position;
	struct ListItem* nextItem;
	
};

typedef struct ListItem ListItem;

struct List {
	ListItem* first;
};

typedef struct List List;

void add(List* list, int piece, int orientation, int position){
	
	ListItem* newListItem = malloc(sizeof(ListItem));
	//new Item
	newListItem->orientation = orientation;
	newListItem->position = position;
	newListItem->piece = piece;
	newListItem->nextItem = list->first;
	list->first = newListItem;
}

void updateHeadListItem(List* list, int piece, int orientation, int position){
	list->first->orientation = orientation;
	list->first->position = position;
	list->first->piece = piece;
}

void deleteHeadListItem(List* list){
	void * p = list->first;
	list->first = list->first->nextItem;
	free(p);
}

List* makeList(){
	List* list = malloc(sizeof(List));
	list->first = NULL;
	return list;
}

int getCurrentPieceNum(List* list){
	return list->first->piece;
}

int getCurrentPositionNum(List* list){
	return list->first->position;
}

int getCurrentOrientationNum(List* list){
	return list->first->orientation;
}

/*-------space functions------*/

enum{SIZE=sizeof(int)*3*3*3, NUMPIECES = 5, NUMORI = 6};

typedef int* Piece[6];
typedef Piece* Pieces[NUMPIECES];



int* makeSpace(){
	int* temp = calloc(1, sizeof(int)*3*3*3);
	return temp;
}

int getBlock(int* s, int x, int y, int z){
	if(x<3&&y<3&&z<3){
		return s[(y*9+x*3+z)];
	}
	return 0;
}

int* setBlock(int* s, int x, int y, int z, int set){
	s[(y*9+x*3+z)] = set;
	return s;
}

Piece* makePiece(){
	Piece* piece = calloc(1, sizeof(Piece));
	for(int x = 0; x<NUMORI; x++){
		(*piece)[x] = makeSpace();
	}
	return piece;

}

int* getOrientation(Piece* p, int i){
	return (*p)[i];
}

int* populateSpace(int* s, char* in){
	for(int i = 0; i<3*3*3;i++){
		if(in[i]=='1'){
			int x = ((i%9)/3);
			int y = (i/9);
			int z = (i%3);
			setBlock(s, x, y, z, 1);
		}
	}
	return s;
}

int height(int* s){
	for(int x = 0; x<9; x++){
		if(s[18+x] == 1){return 2;}
	}
	for(int x = 0; x<9; x++){
		if(s[9+x] == 1){return 1;}
	}
	return 0;
}

int width(int* s){
	for(int x = 6; x<25; x=x+9){
		for(int y = 0; y<3; y++){
			if(s[y+x] == 1){return 2;}
		}
	}
	for(int x = 3; x<22; x=x+9){
		for(int y = 0; y<3; y++){
			if(s[y+x] == 1){return 1;}
		}
	}
	return 0;
}

int depth(int* s){
	for(int x = 2; x<27; x=x+3){
		if(s[x] == 1){return 2;}
	}
	for(int x = 1; x<26; x=x+3){
		if(s[x] == 1){return 1;}
	}
	return 0;
}

int doesItFit(int* puzzleSpace, int* in, int i){
	int x = ((i%9)/3);
	int y = (i/9);
	int z = (i%3);
	if( (height(in)+y)>2 || (width(in)+x)>2 || (depth(in)+z)>2 ){return 0;}
	for(int j = 0; j<27; j++){
		int xj = ((j%9)/3);
		int yj = (j/9);
		int zj = (j%3);
		if(getBlock(puzzleSpace, xj+x, yj+y, zj+z)==1 && getBlock(in, xj, yj, zj)==1){
			return 0;
		}
	}
	return 1;
	
}

void removePieceFromPuzzle(int* puz, int* piece){
	for(int y = 0; y<3; y++){
		for(int x = 0; x<3; x++){
			for(int z = 0; z<3; z++){
				if(getBlock(piece, x, y, z) == 1){
					setBlock(puz, x, y, z, 0);
				}
			}
		}
	}
}

void addPieceToPuzzle(int* puz, int* piece, int i){
	
	int xo = ((i%9)/3);
	int yo = (i/9);
	int zo = (i%3);
	
	
	for(int y = 0; y<3; y++){
		for(int x = 0; x<3; x++){
			for(int z = 0; z<3; z++){
				if(getBlock(piece, x, y, z) == 1){
					setBlock(puz, x+xo, y+yo, z+zo, 1);
				}
			}
		}
	}
}


void printSpace(int* in){
	printf("{\n");
	for(int y = 0; y<3; y++){
		printf("{\n");
		for(int x = 0; x<3; x++){
			printf("{");
			for(int z = 0; z<3; z++){
				
				printf(" %d ", getBlock(in, x,y,z));
			}
			printf("}\n");
		}
		printf("}\n");
	}
	printf("}\n");
	
}

int main(){
	
	//make array to hold all pieces	
	Pieces* pieces = calloc(1, sizeof(Pieces*)*NUMPIECES);
	
	//this is for inputting the pieces
	
	//loop through pieces 
	for(int i = 0; i<NUMPIECES; i++){
		
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
	int* puzzleSpace = makeSpace();
	
	//flag for when fitting piece is found
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
			//possition loop
			while(1){
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
				if(getCurrentPositionNum(currentStatus)<26){
					//try next position
					updateHeadListItem(currentStatus, getCurrentPieceNum(currentStatus), getCurrentOrientationNum(currentStatus), getCurrentPositionNum(currentStatus)+1);
				}else{
					//if all positions tried move to next orientation.
					updateHeadListItem(currentStatus, getCurrentPieceNum(currentStatus), getCurrentOrientationNum(currentStatus)+1, 0);
					break;
				}	
			
			}
			if(next){break;}
			
			if(getCurrentOrientationNum(currentStatus)<6){
				//move to next orientation.
				updateHeadListItem(currentStatus, getCurrentPieceNum(currentStatus), getCurrentOrientationNum(currentStatus)+1, 0);
			}else{
				//if all orientations tried back track
				break;
			}
		}
		if(next){continue;}
		//else: need to back track
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
