#include "linked_list.c"
#include <time.h>


// inserts N elements sequentially into ofm.
// prints out time it takes for N operations
void testSequentialInsert(int size){
	list_t list;

	setup(&list);
	//print_array(&list);

	clock_t start, end;
    double cpu_time_used;
	
	start = clock();
	
	for(int i=0; i<size; i++){
		node_t *node = get(&list, i);
		insert_here(&list, node, i);
	}
	end = clock();

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//print_array(&list);
	printf("%d sequential insertions, time: %f \n", size, cpu_time_used);
}

// inserts N elements at random locations into OFM. 
// prints out time it takes for N operations
void testRandomInsert(int size){

	list_t list;

	setup(&list);
	//print_array(&list);

	clock_t start, end;
    double cpu_time_used = 0;
	
	start = clock();

	for(int i=0; i<size; i++){
		int index = rand()%size;
		node_t *node = get(&list, index);
		start = clock();
		insert_here(&list, node, i);
		end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;

	}
		//print_array(&list);
	printf("%d random insertions, time: %f \n", size, cpu_time_used);
}


int main(){
	int size=10000;
	printf("Beginning Testing Suite for Linked List. N is: %d\n", size);
	testSequentialInsert(size);
	testRandomInsert(size);	

}
