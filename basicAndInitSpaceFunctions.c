enum{SIZE=sizeof(int)*3*3*3, NUMPIECES = 3, NUMORI = 1};

typedef int*** Piece[6];
typedef Piece* Pieces[NUMPIECES];



int*** makeSpace(){
	int* values = calloc(3*3*3, sizeof(int));
    int** rows = malloc(3*3*sizeof(int*));
	int*** levels = malloc(3*sizeof(int**));
	for (int j=0; j<3; ++j){
		levels[j] = rows + j*3;
		for (int i=0; i<3; ++i){
			rows[j*3+i] = values + j*9 + i*3;
		}
	}
	
    return levels;
}

int getBlock(int*** s, int x, int y, int z){
	if(x<3&&y<3&&z<3){
		return s[y][x][z];
	}
	return 0;
}

int*** setBlock(int*** s, int x, int y, int z, int set){
	s[y][x][z] = set;
	return s;
}

Piece* makePiece(){
	Piece* piece = calloc(1, sizeof(Piece));
	for(int x = 0; x<NUMORI; x++){
		(*piece)[x] = makeSpace();
	}
	return piece;

}

int*** getOrientation(Piece* p, int i){
	return (*p)[i];
}

int*** populateSpace(int*** s, char* in){
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

void printSpace(int*** in){
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
