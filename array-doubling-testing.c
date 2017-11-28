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

void testInsertSortedReverse(int size){
	printf("Testing Reverse Insert Sort:\n");
	list_t list;
	setup(&list);

	clock_t start, end;
    double cpu_time_used = 0;
	
	// insert item elements in reverse order
	for(int i=size-1; i>=0; i--){
		start = clock();
		insert_sorted(&list, i);
		end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;		
	}

	// for correction
	for(int i=0; i<size-1; i++){
		int cur_val = list.items[i];
		int next_val = list.items[i+1];
		if(next_val<cur_val){
			printf("insert ordered not working!");
			break;
		}
	}

	printf("%d reverse sequential insertions for insert-ordered, time: %f \n", size, cpu_time_used);

}

void testInsertSortedRandom(int size){

	printf("Testing Random Insert Sort:\n");
	list_t list;
	setup(&list);

	clock_t start, end;
    double cpu_time_used = 0;
	
	for(int i=0; i<size; i++){
		int val = rand()%100;
		start = clock();
		insert_sorted(&list, val);
		end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;		
	}

	// for correction
	for(int i=0; i<size-1; i++){
		int cur_val = list.items[i];
		int next_val = list.items[i+1];
		if(next_val<cur_val){
			printf("insert ordered not working!");
			break;
		}
	}

	printf("%d random insertions for insert-ordered, time: %f \n", size, cpu_time_used);

}


int main(){
	int size=100;
	//printf("Beginning Testing Suite for Array Doubling. N is: %d\n", size);
	//testSequentialInsert(size);
	//list_t list = testRandomInsert(size);	
	//testFindMax(&list, size);
	testInsertSortedReverse(size);
	testInsertSortedRandom(size);

}


