
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
