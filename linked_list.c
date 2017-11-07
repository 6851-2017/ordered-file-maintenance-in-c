#include <stdio.h>
#include <stdlib.h>

#define MIN_INT (-2147483648)



typedef struct _node {
	_node *prev;
	_node *next;
	int val;
} list_t;


int max(list_t *list) {
	int current_max = MIN_INT;
	while (list) {
		if (list->val > current_max) {
			current_max = list->val;
		}
		list = list->next;
	}
	return current_max;
}


void insert(list_t *list, int index, int elem) {
	// if the list is empty
	if (!list) {
		list = (*list_t) malloc(sizeof(*list));
		list->val = elem;
		list->next = null;
		return;
	}
	for (int i = 0; i < index; i++) {
		if (list->next == null) {
			list->next = (*list_t) malloc(sizeof(*list));
			list->next->val = elem;
			list->next->prev = list;
			list->next->next = null;
			return;
		}
		list = list->next;
	}
	list_t *new = (*list_t) malloc(sizeof(*list));
	new->prev = list->prev;
	new->next = list;
	new->val = elem;
	list->prev->next = new;

}

void print_array(list_t *list) {
	while (list) {
		printf("%d ", list->val);
		list = list->next;
	}
	printf("\n\n");
}

void setup(list_t *list){
}

int main(){
	list_t list;
	setup(&list);
	print_array(&list);
	while (1) {
		printf("loc =");
		int loc;
		scanf("%d", &loc);
		int elem;
		printf("elem =");
		scanf("%d", &elem);
		insert(&list, loc, elem);
		print_array(&list);
	}


}

