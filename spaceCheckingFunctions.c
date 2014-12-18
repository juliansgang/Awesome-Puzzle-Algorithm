
int height(int*** s){
	for(int x = 0; x<9; x++){
		if(s[2][x/3][x%3] == 1){return 2;}
	}
	for(int x = 0; x<9; x++){
		if(s[1][x/3][x%3] == 1){return 1;}
	}
	return 0;
}

int width(int*** s){
	for(int x = 0; x<9; x++){
		if(s[x/3][2][x%3] == 1){return 2;}
	}
	for(int x = 0; x<9; x++){
		if(s[x/3][1][x%3] == 1){return 1;}
	}
	return 0;
}

int depth(int*** s){
	for(int x = 0; x<9; x++){
		if(s[x/3][x%3][2] == 1){return 2;}
	}
	for(int x = 0; x<9; x++){
		if(s[x/3][x%3][1] == 1){return 1;}
	}
	return 0;
}

int doesItFit(int*** puzzleSpace, int*** in, int i){
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

void removePieceFromPuzzle(int*** puz, int*** piece){
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

void addPieceToPuzzle(int*** puz, int*** piece, int i){
	
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

