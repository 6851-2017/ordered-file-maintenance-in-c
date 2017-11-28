#include <time.h>
#include "OrderedFileMaintenance.c"

// inserts N elements sequentially into ofm.
// prints out time it takes for N operations
void testSequentialInsertOFM(list_t* list, int size){

	printf("Initial List: \n");
	print_array(list);

	clock_t start, end;
    double cpu_time_used = 0;
	
	insert_first(list, 0);
	int* item = get_first(list);
	for(int i=0; i<size-1; i++){
		start = clock();
		item = insert_after(list, i+1, item);
		end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
	}

	print_array(list);
	printf("%d sequential insertions, time: %f \n", size, cpu_time_used);
}

void testInsertSortedRandom(list_t* list, int size){

	clock_t start, end;
    double cpu_time_used = 0;
	list_t list;
	setup(&list);

	insert_first(list, 0);
	for(int i=0; i<size; i++){
		int item = rand()%100;
		start = clock();
		//insert_sorted(list, i+1, item);
		end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;		
	}

	// verify correctness

	for(int i=0; i<size-1; i++){

		int cur_val = list->items[i];
		int next_val = list->items[i+1];
		if(next_val<cur_val){
			printf("Insert Sorted Is not working!");
			break;
		}

	}
	printf("%d random insertions into an ordered list of size:%d, time: %f \n", size, size, cpu_time_used);

}


// to be called after sequential insert, delete some of the elements.
void testSequentialDelete(list_t *list, int size){
	printf("Before deletion: \n");
	print_array(list);
	clock_t start, end;
    double cpu_time_used = 0;
	int* item = get_first(list);
    for(int i=0; i<size; i++){
    	int* next_item = get_first(list);
    	start = clock();
    	delete_here(list, item);
    	end = clock();
    	cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
    	item = next_item;
    }
    print_array(list);
	printf("%d sequential deletions, time: %f \n", size, cpu_time_used);
}

// inserts N elements at random locations into OFM. 
// prints out itme it takes for N operations
void testRandomInsertOFM(list_t* list, int size){
	/*
	int randomInsert[N_0] = {0};
	int index;
	for(int i=0; i< size; i++){
		index = rand()%(size-1);
		randomInsert[i] = index;
	}

	setup(list);
	print_array(list);

	clock_t start, end;
    double cpu_time_used = 0;
	

	for(int i=0; i<size; i++){
		start = clock();
		insert(list, randomInsert[i],i);
		end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
	}
	print_array(list);
	printf("%d random insertions, time: %f \n", size, cpu_time_used);
	*/
}


//sorting -> insert a bunch of elts, and maintain the fact that they're always sorted. 



int main(){
	list_t list;
	setup(&list);
	printf("Beginning Testing Suite. N is: %d\n", list.N);
	testSequentialInsertOFM(&list, 82);
	testSequentialDelete(&list, 40);
	//testRandomInsertOFM(N/4);	

}


