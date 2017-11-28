#include "linked_list.c"
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

// Inserted items in reverse order, should come out as the correct order in the end
void testInsertSortedReverse(list_t* list, int size){
	printf("Testing Insert Sorted with Reverse Values: \n");

	clock_t start, end;
    double cpu_time_used = 0;
	list_t list;
	setup(&list);

	// populate list with items
	for(int i=size-1; i>=0; i--){

		start = clock();
		insert_sorted(&list, i);
		end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;		
	}

	node_t cur = list->items;
	for(int i=0; i<size-1; i++){
		int val = cur->val;
		int next_val = cur->next->val;
		if(next_val<val){
			printf("Insert Sorted does not work!")
			break;
		}
		cur = cur->next;
	}
	printf("%d reverse sequential insertions into an ordered list of size:%d, time: %f \n", size/2, size, cpu_time_used);

}

// Inserted items in reverse order, should come out as the correct order in the end
void testInsertSortedRandom(list_t* list, int size){

	printf("Testing Insert Sorted with Random Values: \n");
	clock_t start, end;
    double cpu_time_used = 0;
	list_t list;
	setup(&list);

	// populate list with items
	for(int i=0; i<size-1; i++){
		int item = rand()%100; // keep it to in between 1-100
		start = clock();
		insert_sorted(&list, item);
		end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;		
	}

	node_t cur = list->items;
	for(int i=0; i<size-1; i++){
		int val = cur->val;
		int next_val = cur->next->val;
		if(next_val<val){
			printf("Insert Sorted does not work!")
		}
		cur = cur->next;
	}
	printf("%d reverse sequential insertions into an ordered list of size:%d, time: %f \n", size/2, size, cpu_time_used);

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
		node_t *node = get(&list, i);
		//start = clock();
		insert_here(&list, node, i);
		//end = clock();
		//cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;

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
	
	//start = clock();

	for(int i=0; i<size; i++){
		int index = rand()%size;
		node_t *node = get(&list, index);
		//start = clock();
		insert_here(&list, node, i);
		//end = clock();
		//cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;

	}
		//print_array(&list);
	printf("%d random insertions, time: %f \n", size, cpu_time_used);
	return list;
}


int main(){
	int size=100000;
	// printf("Beginning Testing Suite for Linked List. N is: %d\n", size);
	// testSequentialInsert(size);
	// list_t list = testRandomInsert(size);	
	// testFindMax(&list, size);
	testInsertSortedReverse(size);
	testInsertSortedRandom(size);

}
