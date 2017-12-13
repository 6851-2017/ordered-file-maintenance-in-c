#include <vector>
#include <time.h>
#include <set>
// TODO: insert sorted
// TODO: gtime -v run it with add it to all the test cases
// once for each structure

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
  printf("%d, %f\n", size, cpu_time_used);
  //printf("%f for %d inserts\n", cpu_time_used, size);
}

// inserting elements near each other
void testInsertNear(int size){
  std::vector<int> vec (10 , size); 
  std::vector<int>::iterator it;
  int last_index = 0;
  for(int i=0; i<size; i++){
    // random comput stuff to make sure our inserts are close to eachother
    int vecSize = vec.size();
    int index = last_index  + (rand() % 5);
    if(index%2==1){
      index = last_index - (rand() % 5);
      if(index<0){
        index = -index; // don't want to insert negative index
      }
    }
    it = (vec.begin()+index);

    vec.insert(it, i);
  }
}



void testInsertVarious(){

  printf("Tests Vector Inserts for sizes 10, 100, 1,000, 10,000, 100,000 \n\n");
  testInsertRandom(10, 10);
  testInsertRandom(10, 100);
  testInsertRandom(10, 1000);
  testInsertRandom(10, 10000);
  testInsertRandom(10, 100000);
  testInsertRandom(10, 1000000);

}

void testInsertSet(int beginSize, int size){
  clock_t start, end;
  double cpu_time_used = 0;
  

  int currentSize = beginSize;
  std::set<int> myset;
  start = clock();
  for(int i=0; i<size; i++){
    myset.insert(i);
  }
  end = clock();
  cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("%d, %f\n", size, cpu_time_used);
}

// insert random elements into set
// set should order it for us
void testInsertSortedRandomSet(int beginSize, int size){
  clock_t start, end;
  double cpu_time_used = 0;
  

  int currentSize = beginSize;
  std::set<int> myset;
  start = clock();
  for(int i=0; i<size; i++){
    //int elem = rand()%100;
    myset.insert(i);
  }
  end = clock();
  cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("%d, %f\n", size, cpu_time_used);
}

void testMaxVector(int size){
  clock_t start, end;
  double cpu_time_used = 0;
  std::vector<int> vec(10, size);
  std::vector<int>::iterator it;

  for(int i=0; i<size; i++){
    int vecSize = vec.size();
    int index = rand() % vecSize;
    it = (vec.begin()+index);
    vec.insert(it, i);
  }
  printf("inserted");
  int max_elem = -1;
  start = clock();
  for(int i=0; i<size; i++){
    if(vec[i]>max_elem){
      max_elem = vec[i];
    }
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("size:%d, time:%f, max:%d, \n", size, cpu_time_used, max_elem);

}

void testScanSet(int size){
  clock_t start, end;
  double cpu_time_used = 0;
  std::set<int> myset;
  std::set<int>::iterator it;
  for(int i=0; i<size; i++){
    myset.insert(i);
  }
  int max_elem = -1;
  start = clock();
  for (it = myset.begin(); it != myset.end(); ++it){
    int elem = *it; // Note the "*" here
    if(*it>max_elem){
      max_elem=*it;
    }
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("size:%d, time:%f, max_elem:%d\n", size, cpu_time_used, max_elem);

}

int main(){
  //testInsertVarious();
//   printf("set\n");
//   testScanSet(1000);
//   testScanSet(10000);
//   testScanSet(100000);
//   testScanSet(1000000);
//   printf("vector\n");
//   testMaxVector(1000);
//   testMaxVector(10000);
//   testMaxVector(100000);
// //   testMaxVector(1000000);
//     testInsertSortedRandomSet(10, 10);
//     testInsertSortedRandomSet(10, 100);
  // testInsertSortedRandomSet(10, 1000);
  // testInsertSortedRandomSet(10, 10000);
  testInsertSortedRandomSet(10, 1000);
  // testInsertNear(1000000);
 }