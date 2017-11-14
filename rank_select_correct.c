#include <stdio.h>
#include <stdlib.h>

#define logK 4
#define K (1 << logK)
#define N (2 << K)
#define logN (K+1)
#define logSqN (logN*logN)
#define loglogN (logK+1)

static int table [K][logK];


void fill_table(){
	for (int i=0; i<K; i++){
		for (int j=0; j < logK; j++){
			int value = i >> j;
			int count = __builtin_popcount(value);
			table[i][logK-j-1] =  count; 
		}
	}
}

// return how many one bits are left of this position 
int rank(int pos, int vector){

}

int main(){

	int bitString [N/32] = {0};

	// these chunks can be smaller
	int chunks [(N/logSqN)+1]; 

	int subchunks[(N/logSqN)+1][K];
	int count = 0;

	// filling chunks
	for(int i=0; i<N; i+=logSqN){
		int j = i;
		if(j%32 !=0){
			int partial = bitString[j/32];
			partial = partial << (j%32);
			count += __builtin_popcount(partial);
			j += ((j/32) + 1) * 32;
		}

		while(j+32 <(i+logSqN) && (j<N)){
			count+=__builtin_popcount(bitString[j/32]);
		}
		if(j%32 !=0){
			int partial = bitString[j/32];
			partial = partial >> (32-(j%32));
			count += __builtin_popcount(partial);
		}
		chunks[i/logSqN] = count;
	}

	for(int x=0; x<(N/logSqN)+1; x++){

		for(int y=0; y<K; y+=loglogN){
			int z = j;

		}
	}
}


