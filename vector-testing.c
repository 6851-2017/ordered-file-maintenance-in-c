#include <vector>


// given a starting size, and a total number of elements to insert
// create a vector that will take all of these elements
// inserts in random places
void testInsertRandom(int beginSize, int size){

  printf("Insert %d elements randomly into vector, begin size: %d \n", size, beginSize);
  int currentSize = beginSize;
  std::vector<int> vec (beginSize , size);  
  for(int i=0; i<size; i++){
  	int randInd = rand()%vec.size();
  	it = (myvector.begin()+randInt)% randInd;

  	vec.insert(it, index);
  }

}

void testInsertVarious(){

	printf("Tests Vector Inserts for sizes 10, 100, 1,000, 10,000, 100,000 \n");
	testInsertRandom(10, 10);
	testInsertRandom(10, 100);
	testInsertRandom(10, 1000);
	testInsertRandom(10, 10000);
	testInsertRandom(10, 100000);

}