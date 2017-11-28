#include <stdio.h>
#include <stdlib.h>

#define MIN_INT (-2147483648)



typedef struct _list {
	int size;
	int capacity;
	int* items;
} list_t;



int max(list_t *list) {
	int current_max = MIN_INT;
	for (int i = 0; i < list->size; i++) {
		if (list->items[i] > current_max) {
			current_max = list->items[i];
		}
	}
	return current_max;
}

void slide_right(list_t *list, int index) {
	int el = list->items[index];
	while (index < list->size) {
		int temp = list->items[index];
		list->items[index++] = el;
		el = temp;
	}
	list->items[index] = el;
}

void slide_left(list_t *list, int index) {
	while (index < list->size-1) {
		list->items[index] = list->items[index+1];
		index++;
	}
}




void insert(list_t *list, int index, int elem) {
	if (index > list->size) {
		index = list->size;
	}
	if (list->size == list->capacity) {
		int * new_items = (int*) malloc(list->capacity*2*sizeof(*(list->items)));
		list->capacity*=2;
		int i = 0;
		for (; i < index; i++) {
			new_items[i] = list->items[i];
		}
		new_items[i] = elem;
		for (; i<list->size; i++) {
			new_items[i+1] = list->items[i];
		}
		free(list->items);
		list->items = new_items;
		list->size+=1;

	} else {
		if (index < list->size) {
			slide_right(list, index);
		}
		list->size++;
		list->items[index] = elem;	
	}

}

int binary_search(list_t *list, int elem) {
	int start = 0;
	int end = list->size;
	while (start < end) {
		int mid = (start + end)/2;
		if (elem < list->items[mid]) {
			end = mid;
		} else {
			start = mid;
		}
	}
	return start;
}

void insert_sorted(list_t *list, int elem) {
	insert(list, binary_search(list, elem), elem);
}

void delete(list_t *list, int index) {
	if (index > list->size) {
		index = list->size;
	}
	if (list->size == list->capacity/4) {
		int * new_items = (int*) malloc((list->capacity/2)*sizeof(*(list->items)));
		list->capacity/=2;
		int i = 0;
		for (; i < index; i++) {
			new_items[i] = list->items[i];
		}
		i++;
		for (; i<list->size; i++) {
			new_items[i-1] = list->items[i];
		}
		free(list->items);
		list->items = new_items;
		list->size--;

	} else {
		if (index < list->size) {
			slide_left(list, index);
		}
		list->size--;
	}


}

void print_array(list_t *list) {

	for (int i = 0; i < list->size; i++) {
		printf("%d ", list->items[i]);
	}
	printf("\n\n");
}



void setup(list_t *list){
	list->size = 0;
	list->capacity = 8;

	// DENG: was this supposed tobe sizeof (list->capacity?)
	list->items = (int*) malloc(8*sizeof(*(list->items)));
	for (int i = 0; i < list->capacity; i++) {
		list->items[i] = 0;
	}
}
/*
int main(){
	list_t list;
	setup(&list);
	print_array(&list);
	for (int i = 0; i < 24; i++) {
		printf("## info size = %d. capacity = %d\n", list.size, list.capacity);
		printf("loc =");
		int loc;
		scanf("%d", &loc);
		int elem;
		printf("elem =");
		scanf("%d", &elem);
		insert(&list, loc, elem);
		print_array(&list);
	}
	for (int i = 0; i < 24; i++) {
		printf("## info size = %d. capacity = %d\n", list.size, list.capacity);
		printf("loc =");
		int loc;
		scanf("%d", &loc);
		delete(&list, loc);
		print_array(&list);
	}

}
*/

