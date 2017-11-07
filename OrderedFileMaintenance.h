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

double get_density(int index, int len);

// find index of first 1-bit (least significant bit)
static inline int bsf_word(int word);

int get_depth(int len);


pair_int get_parent(int index, int len);
pair_double density_bound(int depth);

// Evenly redistribute elements in the ofm, given a range to look into
// index: starting position in ofm structure
// len: area to redistribute
void redistribute(int index, int len);
void scan(int index, int len);

void slide_right(int index);

// given index, return the starting index of the leaf it is in
int find_leaf(int index);

// same as find_leaf, but does it for any level in the tree
// index: index in array
// len: length of sub-level. 
int find_node(int index, int len);

void insert(int index, int elem);

void print_array();
void setup();

