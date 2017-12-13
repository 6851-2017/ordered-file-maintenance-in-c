#include "array_doubling.c"
#include <time.h>



void testInsertGtime(int size){
	
	list_t list;
	setup(&list);
	for(int i=0; i< size; i++){
		insert(&list, i,i);
	}
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
	free(list.items);
	printf("%d reverse sequential insertions for insert-ordered, time: %f \n", size, cpu_time_used);

}

void testInsertSortedRandom(int size){

	// printf("Testing Random Insert Sorted:\n");
	list_t list;
	setup(&list);

	clock_t start, end;
    double cpu_time_used = 0;
	start = clock();
	
	for(int i=0; i<size; i++){
		int val = rand()%100;
		insert_sorted(&list, val);
	}
	end = clock();
	cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;		
	
	// for correction
	for(int i=0; i<size-1; i++){
		int cur_val = list.items[i];
		int next_val = list.items[i+1];
		if(next_val<cur_val){
			printf("insert ordered not working!");
			break;
		}
	}

	//printf("%d random insertions for insert-ordered, time: %f \n", size, cpu_time_used);
	printf("%d, %f, \n", size, cpu_time_used);
	free(list.items);
}

// inserting at most 5 away or near at a time
void testInsertSortedNear(int size){

	printf("Testing Random Insert Sorted Near:\n");
	list_t list;
	setup(&list);

	clock_t start, end;
    double cpu_time_used = 0;
	int lastVal = 0;
	//start = clock();
	for(int i=0; i<size; i++){
		int dev = rand()%5;
		int val = lastVal + dev;
		if(dev%2==1){
			val = abs(lastVal - dev);
		}
		insert_sorted(&list, val);
	}
	//end = clock();
	//cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;		
	
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
	free(list.items);
}

void testInsertSortedRandomVarious(){
	//printf("Tests Array Insert Sorted Random  sizes 10, 100, 1,000, 10,000, 100,000 \n\n");	
	testInsertSortedRandom(10);
	testInsertSortedRandom(100);
	testInsertSortedRandom(1000);
	testInsertSortedRandom(10000);
	testInsertSortedRandom(100000);
	 testInsertSortedRandom(1000000);

}

void testInsertSortedNearVarious(){
	printf("Tests Array Insert Sorted Near sizes 10, 100, 1,000, 10,000, 100,000 \n\n");	
	testInsertSortedNear(10);
	testInsertSortedNear(100);
	testInsertSortedNear(1000);
	testInsertSortedNear(10000);
	testInsertSortedNear(100000);
	testInsertSortedNear(1000000);

}

void testMax(int size){
	list_t list;
	clock_t start, end;
	setup(&list);
	for(int i=0; i<size; i++){
		int val = rand()%100;
		insert_sorted(&list, val);
	}
	start = clock();
	int max_elem = max(&list);
	end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;	
	printf("max:%d, %d, time: %f \n",max_elem, size, cpu_time_used);

	free(list.items);

}

int main(){
	int size=100000;
	//printf("Beginning Testing Suite for Array Doubling. N is: %d\n", size);
	//testSequentialInsert(size);
	//list_t list = testRandomInsert(size);	
	//testFindMax(&list, size);
	// testInsertSortedReverse(size);
	// testInsertSortedRandom(size);
	testInsertSortedRandomVarious();
	//testInsertSortedNear(1000000);
	// testMax(1000);
	// testMax(10000);
	// testMax(100000);
	// testMax(1000000);
}


