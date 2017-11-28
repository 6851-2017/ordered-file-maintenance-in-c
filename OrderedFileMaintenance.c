#include <stdio.h>
#include <stdlib.h>


typedef struct _list {
	int N;
	int H;
	int logN;
	int* items;

} list_t;



typedef struct _pair_int {
	int x; // length in array
	int y; // depth 
} pair_int;

typedef struct _pair_double {
	double x;
	double y;
} pair_double;

double get_density(list_t* list, int index, int len) {

	double full = 0;
	for (int i = index; i < index+len; i++) {
		if (list->items[i] != -1) {
			full++;
		}
	}
	return full/len;
}

// find index of first 1-bit (least significant bit)
static inline int bsf_word(int word) {
  int result;
  __asm__ volatile("bsf %1, %0" : "=r"(result) : "r"(word));
  return result;
}

static inline int bsr_word(int word) {
  int result;
  __asm__ volatile("bsr %1, %0" : "=r"(result) : "r"(word));
  return result;
}

int get_depth(list_t* list, int len) {
	return bsf_word(list->N/len);
}


pair_int get_parent(list_t* list, int index, int len) {
	int parent_len = len*2;
	int depth = get_depth(list, len);
	pair_int pair;
	pair.x = parent_len;
	pair.y = depth;
	return pair;
}

pair_double density_bound(list_t* list, int depth) {
	pair_double pair;

	// between 1/4 and 1/2
	// pair.x = 1.0/2.0 - (( .25*depth)/list->H);
	// between 1/8 and 1/4
	pair.x = 1.0/4.0 - (( .125*depth)/list->H);
	pair.y = 3.0/4.0 + ((.25*depth)/list->H);
	return pair;
}


// Evenly redistribute elements in the ofm, given a range to look into
// index: starting position in ofm structure
// len: area to redistribute
void redistribute(list_t* list, int index, int len) {
	int space[len];
	int j = 0;

	// move all items in ofm in the range into
	// a temp array
	for (int i = index; i< index+len; i++) {
		if (list->items[i]!=-1) {
			space[j++] = list->items[i];
			list->items[i] = -1;
		}
	}

	// evenly redistribute for a uniform density
	double index_d = index;
	double step = ((double) len)/j;
	for (int i = 0; i < j; i++) {
	  int in = index_d;
	  list->items[in] = space[i];
	  index_d+=step;
	}
}

int isPowerOfTwo (int x) {
  return ((x != 0) && !(x & (x - 1)));
}

void double_list(list_t* list) {
	list->N*=2;
	list->logN = (1 << bsr_word(bsr_word(list->N)+1));
	list->H = bsr_word(list->N/list->logN);
	int *new_array = (int*)malloc(list->N*sizeof(*(list->items)));
	for (int i = 0; i < list->N/2; i++) {
		new_array[i] = list->items[i];
	}
	for (int i = list->N/2; i < list->N; i++) {
		new_array[i] = -1;
	}
	free(list->items);
	list->items = new_array;
	redistribute(list, 0, list->N);
}

void half_list(list_t* list) {
	list->N/=2;
	list->logN = (1 << bsr_word(bsr_word(list->N)+1));
	list->H = bsr_word(list->N/list->logN);
	int *new_array = (int*)malloc(list->N*sizeof(*(list->items)));
	int j = 0;
	for (int i = 0; i < list->N*2; i++) {
		if (list->items[i] != -1) {
			new_array[j++] = list->items[i];
		}
	}
	free(list->items);
	list->items = new_array;
	redistribute(list, 0, list->N);
}

void scan(list_t* list, int index, int len) {
	for (int i = index; i < index+len; i++) {
		if (list->items[i]!=-1) {
			printf("%d ", list->items[i]);
		}
	}
}


void slide_right(list_t* list, int index) {
	int el = list->items[index];
	while (list->items[++index] != -1) {
		int temp = list->items[index];
		list->items[index] = el;
		el = temp;
	}
	list->items[index] = el;
}

// given index, return the starting index of the leaf it is in
int find_leaf(list_t* list, int index) {
	return (index/list->logN)*list->logN;
}

// same as find_leaf, but does it for any level in the tree
// index: index in array
// len: length of sub-level. 
int find_node(int index, int len) {
	return (index/len)*len;
}

int* find_elem_pointer(list_t* list, int index, int elem){

	int item = list->items[index];
	while(item!=elem){
		item = list->items[++index];
	}
	return &(list->items[index]);

}

int* insert( list_t* list, int index, int elem) {
	int node_index = find_leaf(list, index);
	int level = list->H;
	int len = list->logN;
	double density = get_density(list, node_index, len);

	// spill over into next level up, node is completely full.
	if (density == 1) {
	  node_index = find_node(node_index, len*2);
	  redistribute(list, node_index, len*2);
	} else {
	  redistribute(list, node_index, len);
	}

	// always deposit on the left
	if (list->items[index] == -1) {
		list->items[index] = elem;
	} else {
		slide_right(list, index);
		list->items[index] = elem;
	}

	pair_double density_b = density_bound(list, level);
	density = get_density(list, node_index, len);
	//printf("density %f, upperbound %f, len = %d, N = %d, logN = %d\n", density, density_b.y, len, list->N, list->logN);
	while (density >= density_b.y) {
		len*=2;
		if (len <= list->N){
			level--;
			node_index = find_node(node_index, len);
			density_b = density_bound(list, level);
			density = get_density(list, node_index, len);
		} else {
			double_list(list);
			return find_elem_pointer(list, 0, elem);
		}
		//printf("density %f, upperbound %f, len = %d, N = %d, logN = %d\n", density, density_b.y, len, list->N, list->logN);
	}
	redistribute(list, node_index, len); 
	return find_elem_pointer(list, node_index, elem);

}

int find_index(list_t* list, int* elem_pointer){
	int* array_start = list->items; 
	int index = (elem_pointer- array_start);
	return index;
}

// given an element pointer, find the next element index after it
int* get_next_elem_index(list_t* list, int* elem_pointer){
	int index = find_index(list, elem_pointer);
	index++;
	while(index<list->N){
		if(list->items[index]!=-1){
			return list->items+index;
		}
		index++;
	}
	return NULL;
}

// given an element pointer, find previous element index after it
int* get_prev_elem_index(list_t* list, int* elem_pointer){
	int index = find_index(list, elem_pointer);
	index--;
	while(index>=0){
		if(list->items[index]!=-1){
			return list->items+index;
		}
		index--;
	}
	return NULL;
}

// given an element value and pointer to an element,
// insert before it.
int* insert_before(list_t* list, int new_elem, int* elem_pointer){
	int elem_index = find_index(list, elem_pointer);
	if(elem_index!=0){
		return insert(list, elem_index-1, new_elem);
	}
	return NULL;
}

// returns pointer to the element we just inserted!
int* insert_after(list_t* list, int new_elem, int* elem_pointer){
	int elem_index = find_index(list, elem_pointer);
	if(elem_index<(list->N-1) && elem_index >=0){
		int* new_elem_pointer =  insert(list, elem_index+1, new_elem);
		return new_elem_pointer;
	}
	else{
		printf("returning null\n");
		return NULL;
	}
}

int* get_first(list_t* list){
	int index = 0;
	int elem = list->items[index];
	while(elem==-1){
		elem = list->items[++index];
	}
	if(index==list->N){
		// return first index location by default
		return list->items;
	}
	return &(list->items[index]);
}

// insert as the first item into the list.
int* insert_first(list_t*list, int elem){
	list->items[0] = elem;
	return list->items;
}

void delete(list_t* list, int index){
	int node_index = find_leaf(list, index);
	int level = list->H;
	int len = list->logN;
	pair_double density_b = density_bound(list, level);
	double low_bound = density_b.x;
	if(list->items[index]== -1){
		printf("Element does not exist at index: %d \n", index);
		return;
	}
	//deletion
	list->items[index] = -1;

	// redistribute 'recursively' until we are within density bounds.
	double density = get_density(list, node_index, len);
	while(density < density_b.x){
		len*=2;
		if (len <= list->N){
			level--;
			node_index = find_node(node_index, len);
			pair_double density_b = density_bound(list, level);
			density = get_density(list, node_index, len);
		} else {
			half_list(list);
			return;
		}
	}
	redistribute(list, node_index, len);
}

void delete_here(list_t* list, int* elem_pointer){
	int elem_index = find_index(list, elem_pointer);
	if(elem_index>=0 && elem_index<list->N){
		delete(list, elem_index);
		return;
	}
}


void print_array(list_t* list) {
	for (int i = 0; i < list->N; i++) {
		if (list->items[i] == -1) {
			printf("/ ");
		} else {
			printf("%d ", list->items[i]);
		}
	}
	printf("\n\n");
}

void setup(list_t* list){

	list->N = 16;
	printf("%d\n", bsf_word(list->N));
	list->logN = (1 << bsr_word(bsr_word(list->N)+1));
	list->H = bsr_word(list->N/list->logN);
	//printf("N = %d, logN = %d, loglogN = %d, H = %d\n", list->N, list->logN, list->loglogN, list->H);
	
	list->items = (int*)malloc(list->N*sizeof(*(list->items)));
	for (int i = 0; i < list->N; i++) {
		list->items[i] = -1;
	}

	print_array(list);
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

	// delete
	// while (1) {
	// 	printf("loc =");
	// 	int loc;
	// 	scanf("%d", &loc);

	// 	delete(loc);
	// 	print_array();
	// }
}


