#include <stdio.h>
#include <stdlib.h>


#define loglogN 3
#define logN (1 << loglogN)
#define N (1 << logN)
#define H (logN - loglogN)


static int array[N] = {0};

typedef struct _pair_int {
	int x; // length in array
	int y; // depth 
} pair_int;

typedef struct _pair_double {
	double x;
	double y;
} pair_double;

double get_density(int index, int len) {
	double full = 0;
	for (int i = index; i < index+len; i++) {
		if (array[i] != -1) {
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

int get_depth(int len) {
	return bsf_word(N/len);
}


pair_int get_parent(int index, int len) {
	int parent_len = len*2;
	int depth = get_depth(len);
	pair_int pair;
	pair.x = parent_len;
	pair.y = depth;
	return pair;
}

pair_double density_bound(int depth) {
	pair_double pair;
	pair.x = 1.0/2.0 - (( .25*depth)/H);
	pair.y = 3.0/4.0 + ((.25*depth)/H);
	return pair;
}

// Evenly redistribute elements in the ofm, given a range to look into
// index: starting position in ofm structure
// len: area to redistribute
void redistribute(int index, int len) {
	int space[len];
	int j = 0;

	// move all items in ofm in the range into
	// a temp array
	for (int i = index; i< index+len; i++) {
		if (array[i]!=-1) {
			space[j++] = array[i];
			array[i] = -1;
		}
	}

	// evenly redistribute for a uniform density
	double index_d = index;
	double step = ((double) len)/j;
	for (int i = 0; i < j; i++) {
	  int in = index_d;
	  array[in] = space[i];
	  index_d+=step;
	}
}

void scan(int index, int len) {
	for (int i = index; i < index+len; i++) {
		if (array[i]!=-1) {
			printf("%d ", array[i]);
		}
	}
}


void slide_right(int index) {
	int el = array[index];
	while (array[++index] != -1) {
		int temp = array[index];
		array[index] = el;
		el = temp;
	}
	array[index] = el;
}

// given index, return the starting index of the leaf it is in
int find_leaf(int index) {
	return (index/logN)*logN;
}

// same as find_leaf, but does it for any level in the tree
// index: index in array
// len: length of sub-level. 
int find_node(int index, int len) {
	return (index/len)*len;
}

void insert(int index, int elem) {
	int node_index = find_leaf(index);
	int level = H;
	int len = logN;
	double density = get_density(node_index, len);

	// spill over into next level up, node is completely full.
	if (density == 1) {
	  node_index = find_node(node_index, len*2);
	  redistribute(node_index, len*2);
	} else {
	  redistribute(node_index, logN);
	}

	// always deposit on the left
	if (array[index] == -1) {
		array[index] = elem;
	} else {
		slide_right(index);
		array[index] = elem;
	}

	pair_double density_b = density_bound(level);
	//printf("lower bound = %f, density = %f, upper bound = %f\n",density_b.x, density, density_b.y);
	// DENG: shouldn't you be recalculating density here after insertion?

	while (density >= density_b.y) {
		len*=2;
		level--;
		node_index = find_node(node_index, len);
		pair_double density_b = density_bound(level);
		density = get_density(node_index, len);
	}
	redistribute(node_index, len); 

}

int find_index(int* elem_pointer){
	int* array_start = &array[0];
	int index = (array_start-elem_pointer)/sizeof(int);
	return index;
}

// given an element pointer, find the next element index after it
int get_next_elem_index(int* elem_pointer){
	int index = find_index(elem_pointer);
	index++;
	while(index<N){
		if(array[index]!=-1){
			return index;
		}
		index++;
	}
	return -1;
}

// given an element pointer, find previous element index after it
int get_prev_elem_index(int* elem_pointer){
	int index = find_index(elem_pointer);
	index--;
	while(index>=0){
		if(array[index]!=-1){
			return index;
		}
		index--;
	}
	return -1;
}


// given an element value and pointer to an element,
// insert before it.
void insert_before(int new_elem, int* elem_pointer){
	int elem_index = find_index(elem_pointer);
	if(elem_index!=0){
		insert(elem_index-1, new_elem);
		return;
	}
}

void insert_after(int new_elem, int* elem_pointer){
	int elem_index = find_index(elem_pointer);
	if(elem_index<(N-2) && elem_index >0){
		insert(elem_index+1, new_elem);
		return;
	}

}


void delete(int index){
	int node_index = find_leaf(index);
	int level = H;
	int len = logN;
	pair_double density_b = density_bound(level);
	double low_bound = density_b.x;

	if(array[index]== -1){
		printf("Element does not exist at index: %d \n", index);
		return;
	}
	//deletion
	array[index] = -1;

	// redistribute 'recursively' until we are within density bounds.
	double density = get_density(node_index, len);
	while(density < density_b.x){
		len*=2;
		level--;
		node_index = find_node(node_index, len);
		pair_double density_b = density_bound(level);
		density = get_density(node_index, len);
	}
	redistribute(node_index, len);
}

void delete_before(int* elem_pointer){
	int elem_index = find_index(elem_pointer);
	if(elem_index>0 && elem_index<N){
		delete(elem_index-1);
		return;
	}
}

void delete_after(int* elem_pointer){
	int elem_index = find_index(elem_pointer);
	if(elem_index<(N-2) && elem_index >=0){
		delete(elem_index+1);
		return;
	}
}



void print_array() {
	for (int i = 0; i < N; i++) {
		if (array[i] == -1) {
			printf("/ ");
		} else {
			printf("%d ", array[i]);
		}
	}
	printf("\n\n");
}

void setup(){
	for (int i = 0; i < N; i++) {
		array[i] = -1;
	}
	print_array();
	for (int i = 0; i < N; i+=2) {
		array[i] = 10*i;
	}
}


int main(){
	setup();
	print_array();
	while (1) {
		printf("loc =");
		int loc;
		scanf("%d", &loc);
		int elem;
		printf("elem =");
		scanf("%d", &elem);
		insert(loc, elem);
		print_array();
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


