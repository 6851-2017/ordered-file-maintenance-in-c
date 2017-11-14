#include <stdio.h>
#include <stdlib.h>

static int bit_vector = 0;
// TODO: Make this space efficient by passing addresses of ints 

// find index of first 1-bit (least significant bit)
static inline int bsf_word(int word) {
  int result;
  __asm__ volatile("bsf %1, %0" : "=r"(result) : "r"(word));
  return result;
}

// given an index, set the bit at the first 1-bit to 0
static inline void zero_bit(int index, int vector){

	vector ^= vector & -vector;
}

// find the ith one bit. returns 0 if there is no ith one bit
int select(int pos, int vector){
	int result = vector;
	for(int x=0; x < pos-1; x++){
		int index = bsf_word(result);
		result = zero_bits(index, result);
	}	
	return bsf_word(result);
}

// return how many one bits are left of this position 
int rank(int pos, int vector){
	int total_bits = 0;
	int temp = vector;
	pos++;

	// zero out anything to the right of this position
	temp = temp >> (pos);
	temp = temp << (pos);

	int next_one = bsf_word(temp);
	while(next_one!=0){
		total_bits+=1;
		temp = temp >> (next_one+1);
		temp = temp << (next_one+1);
		next_one = bsf_word(temp);
	}
	return total_bits;

}

int main(){
	int test = 12;

	printf("should be 3 (%d), \n", select(2, 12));

	printf("should be 2 (%d) \n ", rank(0, 12));

}
