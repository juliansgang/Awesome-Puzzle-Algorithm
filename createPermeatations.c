Piece* getPieceFromUser(int i){
	
	//code bellow to be replaced by code ben has made.....
	
	
	//make a piece and put in array of pieces
		Piece* p = makePiece(); 
		
		//loop thorugh orientations 
		for(int j = 0; j<NUMORI; j++){
			//input
			printf("Input P:%d, Or:%d\n__________________________|\n",i, j);
			char input[31];
			fgets(input, 30, stdin);
			char* c = malloc(sizeof(char)*27);
			memcpy(c, input, 27*sizeof(char));
			//use string to populate each orientation of piece
			populateSpace(getOrientation(p, j), c);
		}
		
		return p;
	
}
