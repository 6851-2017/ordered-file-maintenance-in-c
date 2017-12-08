#include <vector>
#include <time.h>


// given a starting size, and a total number of elements to insert
// create a vector that will take all of these elements
// inserts in random places
void testInsertRandom(int beginSize, int size){



  //printf("Insert %d elements randomly into vector, begin size: %d \n", size, beginSize);

  clock_t start, end;
  double cpu_time_used = 0;
  

  int currentSize = beginSize;
  std::vector<int> vec (beginSize , size); 
  std::vector<int>::iterator it;
 
  for(int i=0; i<size; i++){
    int vecSize = vec.size();
    int index = rand() % vecSize;
    it = (vec.begin()+index);
    start = clock();
    vec.insert(it, i);
    end = clock();
    cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
  }
  printf("%f for %d inserts\n", cpu_time_used, size);
}

void testInsertVarious(){

  printf("Tests Vector Inserts for sizes 10, 100, 1,000, 10,000, 100,000 \n\n");
  testInsertRandom(10, 10);
  testInsertRandom(10, 100);
  testInsertRandom(10, 1000);
  testInsertRandom(10, 10000);
  testInsertRandom(10, 100000);

}
int main(){
  testInsertVarious();
}