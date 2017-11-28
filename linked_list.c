#include <stdio.h>
#include <stdlib.h>

#define MIN_INT (-2147483648)



typedef struct _node {
	struct _node *prev;
	struct _node *next;
	int val;
} node_t;

typedef struct _list {
	node_t *items;
} list_t;




int max(list_t *list) {
	int current_max = MIN_INT;
	node_t *node =  list->items;
	while (node) {
		if (node->val > current_max) {
			current_max = node->val;
		}
		node = node->next;
	}
	return current_max;
}

// if index is greater than the length of the list this returns last element
node_t* get(list_t *list, int index) {
	if (!(list->items)) {
		return NULL;
	}
	node_t *node =  list->items;
	for (int i = 0; i < index; i++) {
		if (node->next == NULL) {
			return node;
		}
		node = node->next;
	}
	return node;
}

void insert_here(list_t *list, node_t *node, int elem) {
	// if the list is empty
	if (!node) {
		node = (node_t*) malloc(sizeof(*node));
		node->val = elem;
		node->next = list->items;
		node->prev = NULL;
		list->items = node;
		return;
	}
	node_t *new = (node_t*) malloc(sizeof(*node));
	new->prev = node->prev;
	new->next = node;
	new->val = elem;
	if (node->prev == NULL) {
		list->items = new;
	} else {
		node->prev->next = new;
	}
	node->prev = new;
}

void insert_sorted(list_t *list, int elem) {
	node_t *node =  list->items;
	while (node->val <= elem && node->next) {
		node = node->next;
	}
	insert_here(list, node, elem);
}

void delete_here(list_t *list, node_t *node) {
	// if the list is empty
	if (!(list->items)) {
		return;
	}
	if (node->next) {
		node->next->prev = node->prev;
	}
	if (node->prev) {
		node->prev->next = node->next;
		free(node);
		return;
	}
	list->items = node->next;
	free(node);

	
}

void print_array(list_t *list) {
	node_t *node =  list->items;
	while (node) {
		printf("%d ", node->val);
		node = node->next;
	}
	printf("\n\n");
}

void setup(list_t *list){
	list->items = NULL;
}

/*
int main(){
	list_t list;
	setup(&list);
	print_array(&list);
	for (int i = 0; i < 10; i++) {
		printf("loc =");
		int loc;
		scanf("%d", &loc);
		int elem;
		printf("elem =");
		scanf("%d", &elem);
		node_t *node = get(&list, loc);
		insert_here(&list, node, elem);
		print_array(&list);
	}
	for (int i = 0; i < 10; i++) {
		printf("loc =");
		int loc;
		scanf("%d", &loc);
		node_t *node = get(&list, loc);
		delete_here(&list, node);
		print_array(&list);
	}

}
*/
