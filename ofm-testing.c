#include <time.h>
#include "OrderedFileMaintenance.c"

// inserts N elements sequentially into ofm.
// prints out time it takes for N operations
void testSequentialInsertOFM(list_t* list, int size){
	setup(list);

	printf("Initial List: \n");
	print_array(list);

	clock_t start, end;
    double cpu_time_used;
	
	start = clock();
	
	for(int i=0; i<size; i++){
		insert(list, i,i);
	}
	end = clock();

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	print_array(list);
	printf("%d sequential insertions, time: %f \n", size, cpu_time_used);
}

// inserts N elements at random locations into OFM. 
// prints out itme it takes for N operations
void testRandomInsertOFM(list_t* list, int size){

	int randomInsert[N_0] = {0};
	int index;
	for(int i=0; i< size; i++){
		index = rand()%(size-1);
		randomInsert[i] = index;
	}

	setup(list);
	print_array(list);

	clock_t start, end;
    double cpu_time_used;
	
	start = clock();

	for(int i=0; i<size; i++)
		{insert(list, randomInsert[i],i);}
	
	end = clock();

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	print_array(list);
	printf("%d random insertions, time: %f \n", size, cpu_time_used);
}

int main(){
	list_t list;
	printf("Beginning Testing Suite. N is: %d\n", N_0);
	testSequentialInsertOFM(&list, N_0/4);
	//testRandomInsertOFM(N/4);	

}


