#include "array_doubling.c"
#include <time.h>


void testFindMax(list_t* list , int size){

	clock_t start, end;
    double cpu_time_used = 0;
	//start = clock();
	int x = max(list);
	//end = clock();
	//cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Max:%d of %d items, time: %f \n",x, size, cpu_time_used);

}

// inserts N elements sequentially into ofm.
// prints out time it takes for N operations
list_t testSequentialInsert(int size){
	list_t list;
	setup(&list);
	//print_array(&list);

	clock_t start, end;
    double cpu_time_used = 0;
	
	
	for(int i=0; i<size; i++){
		//start = clock();
		insert(&list, i,i);
		//end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
	}

	//print_array(&list);
	printf("%d sequential insertions, time: %f \n", size, cpu_time_used);
	return list;
}

// inserts N elements at random locations into OFM. 
// prints out time it takes for N operations
list_t testRandomInsert(int size){

	list_t list;

	setup(&list);
	//print_array(&list);

	clock_t start, end;
    double cpu_time_used = 0;
	

	for(int i=0; i<size; i++){
		int index = rand()%size;
		//start = clock();
		insert(&list,index,i);
		//end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;

	}
	

	//print_array(&list);
	printf("%d random insertions, time: %f \n", size, cpu_time_used);
	return list;
}


int main(){
	int size=100000;
	printf("Beginning Testing Suite for Array Doubling. N is: %d\n", size);
	testSequentialInsert(size);
	list_t list = testRandomInsert(size);	
	testFindMax(&list, size);
}


