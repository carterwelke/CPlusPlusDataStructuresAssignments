//
//  main.cpp
//  Sorting Algorithms
//
//  Created by Howard Miller on 4/22/19.
//  Copyright © 2019 Howard Miller. All rights reserved.
//

//Carter Welke CIST 004B Spring 2020

#include <iostream>
#include <iomanip>
#include <cmath>  // Used for log10()
#include <thread>  // Used for Multi-Threaded solution
#include <cstdlib>  // Used for bult-in q-sort routine
#include <chrono>  // used for timing functions
#include <ctime>   // Used to display time

#include <algorithm>
#include <vector>

using namespace std;
using namespace std::chrono;

/************************
 ** STRUCT TO DEFINE A TEST PLUS NAME
 *************************/
struct sortRoutine {
	void (*function)( int *, size_t );
	const char * name;
};

/************************
 ** Utility Functions
 *************************/
int *getRandomNumbers (size_t num, int seed);
void printArray (int *array, size_t count);
bool checkSort  (int *array, size_t count);
duration<double> sortAndTime (int* testArray, size_t theSize, sortRoutine theTest, bool print =false);

/************************
 ** Sample Sort Functions Provided
 *************************/
void shakerSort (int *array, size_t count);
void cQuickSort (int *array, size_t count);
void quickSortBook  (int *array, size_t count);


/************************
 ** Student Created Sort Function
 *************************/
void bubbleSort (int *array, size_t count);             // REQUIRED
void selectionSort(int *data, size_t n);                // REQUIRED
void insertionSort(int *data, size_t n);                // REQUIRED

void bubbleSortOptimized (int *array, size_t count);    	// EXTRA CREDIT (EASY, So I recommend you do this)

void quickSort  (int *array, size_t count);             // REQUIRED / Extra Credit if you do the non-recursive verison
void mergeSort  (int *array, size_t count);             // REQUIRED / Extra Credit if you do the non-recursive verison
void heapSort  (int *array, size_t count);     			// REQUIRED / Extra Credit if you do the non-recursive verison

void heapSortNonRecursive(int *, size_t);

void quickSortNonRecursive (int *array, size_t count);  // Extra Credit
void nonRecursiveMergeSort  (int *array, size_t count); // Extra Credit

void quickSortBookOptimized  (int *array, size_t count); 	// EXTRA CREDIT

void radixSort  (int *array, size_t count);     			// EXTRA CREDIT


void quickSortThreaded  (int *array, size_t count);     	// EXTRA CREDIT
void quickSortHybrid  (int *array, size_t count);       	// EXTRA CREDIT
void quickSortThreadedHybrid (int *array, size_t count);  	//Just Crazy stuff!




/************************
 ** Sort Functions
 ** Add your function to this table
 *************************/

sortRoutine yourSortRoutines[] = {
	//{shakerSort, "a sample Shaker Sort"},
	//{quickSortBook, "the Quick Sort from the Book"},
	//{bubbleSort, "the Bubble Sort"},
	//{bubbleSortOptimized, "your Optimized Bubble Sort"},
	{selectionSort, "your Selection Sort"},
	{insertionSort, "your Insertion Sort"},
	
	//    {radixSort, "your Radix Sort"}
	//{cQuickSort, "the C++ Built-in Quick Sort"},
	//    {quickSort, "your Quick Sort"},
	{heapSort, "your Heap Sort"},
	    {heapSortNonRecursive, "your Heap Sort no recursion"},
	//    {quickSortNonRecursive, "your Non-Recursive Quick Sort"},
	//    {quickSortHybrid, "your Hybrid Quick Sort"},  // Not worth it
	//    {quickSortThreaded, "your Multi-Threaded Quick Sort"},
	//    {quickSortThreadedHybrid, "your Hybrid Multi-Threaded Quick Sort"},
	    {mergeSort, "your Merge Sort"},
	//    {nonRecursiveMergeSort, "your Non-Recursive Merge Sort"},
	
	{nullptr , nullptr }  // Terminates the list
};

long long checkSum;  // Used to double check the sorted list


////My Utility Functions
void printCurrentArray(int* arr, size_t n) {
	std::cout << "Printing Array:" << endl;
	for (int i = 0; i < n; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << endl;
	return;
}

//merge sort helper function
void merge(int data[], size_t n1, size_t n2) {
	int* temp; // Points to dynamic array to hold the sorted elements
	size_t copied = 0; // Number of elements copied from data to temp
	size_t copied1 = 0; // Number copied from the first half of data
	size_t copied2 = 0; // Number copied from the second half of data
	size_t i; // Array index to copy from temp back into data
	// Allocate memory for the temporary dynamic array.
	temp = new int[n1 + n2];
	// Merge elements, copying from two halves of data to the temporary array.
	while ((copied1 < n1) && (copied2 < n2))
	{
		if (data[copied1] < (data + n1)[copied2])
			temp[copied++] = data[copied1++]; // Copy from first half
		else
			temp[copied++] = (data + n1)[copied2++]; // Copy from second half
	}
	// Copy any remaining entries in the left and right subarrays.
	while (copied1 < n1)
		temp[copied++] = data[copied1++];
	while (copied2 < n2)
		temp[copied++] = (data + n1)[copied2++];
	// Copy from temp back to the data array, and release temp’s memory.
	for (i = 0; i < n1 + n2; ++i)
		data[i] = temp[i];
	delete[] temp;
}

//recursive heap sort helper functions
inline size_t lChild(size_t k) {
	return 2 * k + 1;
}
inline size_t rChild(size_t k) {
	return 2 * k + 2;
}
void heapify(int* data, size_t n, size_t i) {
	size_t largest = i;
	size_t l = lChild(i);
	size_t r = rChild(i);

	// If left child is larger than root 
	if (l < n && data[l] > data[largest])
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && data[r] > data[largest])
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(data[i], data[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(data, n, largest);
	}

}

//nonrecursive heap sort helper functions
inline size_t parent(size_t k) {
	return (k - 1) / 2;
}
void make_heap(int* data, size_t n) {
	size_t i;
	size_t k;
	for (i = 1; i < n; ++i) {
		k = i;
		while (k > 0 && data[k] > data[parent(k)]) {
			swap(data[k], data[parent(k)]);
			k = parent(k);
		}
	}
}
void reheapify_down(int data[], size_t n) {
	// Reheapification downward (for a heap where the root is out of place)
	size_t current; // Index of the node that’s moving down
	size_t big_child_index; // Index of current’s larger child
	bool heap_ok; // Will become true when heap is correct
	current = 0;
	heap_ok = false;
	while ((!heap_ok) && (lChild(current) < n))
	{
		/*Set big_child_index to be the index of the larger child of the current
			node. (If there is only one child, then big_child_index will be set to
				the index of this one child.)*/
		if (rChild(current) >= n) {
			big_child_index = lChild(current);
		}
		else if (data[lChild(current)] >= data[rChild(current)]) {
			big_child_index = lChild(current);
		}
		else {
			big_child_index = rChild(current);
		}

		if (data[current] < data[big_child_index])
		{
			swap(data[current], data[big_child_index]);
			current = big_child_index;
		}
		else
			heap_ok = true;
	}
	//printCurrentArray(data, n);
}



/************************
 ** main()
 ** Do not change this
 *************************/
int main(int argc, const char * argv[]) {
	size_t inputSize{0};
	char inputChar;
	
	do {
		cout << "Enter the size of Array you wish to sort (not more than 100,000,000): ";
		cin >> inputSize;
		if (inputSize > 100000000)
			cout << "Please try again!\n" << endl;
	} while (inputSize > 100000000 );
	
	do {
		cout << "Do you wish a single run (Y/N): ";
		cin >> inputChar;
		inputChar = toupper (inputChar);
	} while (inputChar != 'Y' && inputChar != 'N');
	
	if (inputChar == 'Y'){
		for ( size_t i{0} ;yourSortRoutines[i].function != nullptr ; ++ i  ){
			cout << fixed << setprecision(6);
			int* testArray = getRandomNumbers (inputSize, 0);
			
			cout<< "\nNow executing " << yourSortRoutines[i].name << " of "<< inputSize <<" items." << endl;
			duration<double> time_span_r = sortAndTime(testArray, inputSize, yourSortRoutines[i], true);
			cout << static_cast<char>(toupper(yourSortRoutines[i].name[0])) << &yourSortRoutines[i].name[1]
			<< " took " << setw(7) << time_span_r.count() << " Seconds." << endl;
			
			cout<< "Now Executing " << yourSortRoutines[i].name << " of "<< inputSize <<" pre-sorted items." << endl;
			duration<double> time_span_r2 = sortAndTime(testArray, inputSize, yourSortRoutines[i], true);
			
			cout << static_cast<char>(toupper(yourSortRoutines[i].name[0])) << &yourSortRoutines[i].name[1]
			<< " took " << setw(8) << time_span_r2.count() << " Seconds." << endl;
			delete[] testArray;
		}
		cout << endl;
	} else {
		size_t ArraySize{0};
		time_t rawtime;
		cout << "\nTesting every Sort Routine with array sizes of from 0 to " << inputSize << " numbers."<< endl;;
		do {
			if (ArraySize % 100 == 1 ) {
				if (ArraySize == 1)
					cout << "Starting at:\t\t\t";
				time (&rawtime);
				//cout  << '\t' << ctime(&rawtime) << setw(log10(inputSize)+1)<< ArraySize-1; // Note: ctime has built-in '\n'
				// MS USERS       
				char str[26];
				ctime_s(str,sizeof str,&rawtime);
				cout  << '\t' << str << setw(log10(inputSize)+1)<< ArraySize-1; // Note: ctime has built-in '\n'
			}
			if (ArraySize % 10 == 9 )
				cout <<" .";
			for ( size_t i{0} ;yourSortRoutines[i].function != nullptr ; ++ i  ){
				int* testArray = getRandomNumbers (ArraySize, 0);
				sortAndTime(testArray, ArraySize, yourSortRoutines[i], true);      // Run sort and print array if an error
				delete[] testArray;
			}
		}  while(ArraySize++ < inputSize);
		cout <<endl;
		time (&rawtime);
		//cout  << "Finished at:\t\t\t\t" << ctime(&rawtime)<<endl; // Note: ctime has built-in '\n'
		// MS USERS  
		char str[26];
		ctime_s(str,sizeof str,&rawtime);
		cout  << "Finished at:\t\t\t\t" << str <<endl; // Note: ctime has built-in '\n'
	}
	return 0;
}

/************************
 ** Sample SHAKER SORT
 *************************/
void shakerSort (int *array, size_t count) {
	if (count <= 1)
		return; // No work for an empty or 1 element array.
	
	size_t p, i;
	for (p = 1; p <= count / 2; p++) {
		bool doneEarlyOptimization {true};
		for (i = p - 1; i < count - p; i++){  // Up Pass
			if (array[i] > array[i+1]) {
				int temp = array[i+1];
				array[i+1] = array[i];
				array[i] = temp;
				doneEarlyOptimization = false;
			}
		}
		for (i = count - p - 1; i >= p; i--) {  // Down Pass
			if (array[i] < array[i-1]) {
				int temp = array[i-1];
				array[i-1] = array[i];
				array[i] = temp;
				doneEarlyOptimization = false;
			}
		}
		if (doneEarlyOptimization)
			break;
	}
	return;
}

/************************
 ** BUILT-IN C-QUICK SORT
 *************************/
int cQuickSortCompare (const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );
}

void cQuickSort (int *array, size_t count) {
	qsort (array, count, sizeof(int), cQuickSortCompare);
	return;
}


/************************
 ** BUBBLE SORT
 *************************/
void bubbleSort (int *array, size_t count) {
	for (int i = 0; i < count; ++i) {
		for (int j = 0; j < count - i; ++j) {
			if (array[j] > array[j + 1]) {
				swap(array[j], array[j + 1]);
			}
		}
	}
	return;
}

/************************
 ** Optimized BUBBLE SORT
 *************************/
void bubbleSortOptimized(int* array, size_t count) {
	for (int i = 0; i < count; ++i) {
		bool more = false;
		for (int j = 0; j < count - i; ++j) {
			if (array[j] > array[j + 1]) {
				swap(array[j], array[j + 1]);
				more = true;
			}
		}
		if (!more) {
			return;
		}
	}
	return;
}

/************************
 ** SELECTION SORT
 *************************/
void selectionSort(int* data, size_t n) {
	size_t i, j, index_of_biggest;
	int biggest;
	if (n == 0)
		return;
	for (i = n - 1; i > 0; --i)
	{
		biggest = data[0];
		index_of_biggest = 0;
		for (j = 1; j <= i; ++j)
		{
			if (data[j] > biggest)
			{
				biggest = data[j];
				index_of_biggest = j;
			}
		}
		swap(data[i], data[index_of_biggest]);
	}
}

/************************
 ** INSERTION SORT
 *************************/
//insert element into sorted side
//move to next element
void insertionSort(int* data, size_t n) {
	size_t i, j, index_of_insertion;
	int savedCopy;
	if (n == 0)
		return;
	//printCurrentArray(data,n);
	for (i = 0; i < n; ++i) {
		savedCopy = data[i];
		for (j = i; j > 0; --j) {
			if (savedCopy < data[j-1]) {
				data[j] = data[j-1];
			}
			else {
				data[j] = savedCopy;
				break;
			}
		}
		if (j == 0) {
			data[0] = savedCopy;
		}
	}
	//printCurrentArray(data, n);
	return;
}

/************************
 ** RADIX SORT
 *************************/
void radixSort(int* data, size_t n) {
	const int MAX_ITERATIONS = sizeof(int) * 8;
	int divisor = 1;
	vector<int> list1;
	for (size_t i = 0; i < MAX_ITERATIONS; ++i) {
		
	}
}

/************************
 ** MERGE SORT
 *************************/
void mergeSort(int* data, size_t n) {
	size_t n1;
	size_t n2;

	if (n > 1) {
		n1 = n / 2;
		n2 = n - n1;
		mergeSort(data, n1);
		mergeSort((data+n1),n2);

		merge(data, n1, n2);
	}
}

/************************
 ** Non-recursive MERGE SORT
 *************************/

/************************
 ** HEAP SORT
 *************************/
void heapSortNonRecursive(int* data, size_t n) {
	if (n <= 1) {
		return;
	}
	size_t unsorted;
	make_heap(data, n);
	//printCurrentArray(data, n);
	unsorted = n;
	while (unsorted > 1)
	{
		--unsorted;
		swap(data[0], data[unsorted]);
		reheapify_down(data, unsorted);
	}
	//printCurrentArray(data, n);
}


/***************************
Recursive Heap Sort
***************************/
void heapSort(int* data, size_t n) {
	for (int i = (n / 2) - 1; i >= 0; --i) {
		heapify(data, n, i);
	}
	for (int i = n - 1; i > 0; --i)
	{
		swap(data[0], data[i]);
		heapify(data, i, 0);
	}
}


/************************
 ** QUICK SORT
 *************************/


/************************
 ** Multi-Threaded QUICK SORT
 *************************/

/************************
 ** Hybrid QUICK SORT
 *************************/


/************************
 ** Threaded Hybrid QUICK SORT
 *************************/


/************************
 ** QUICK SORT FROM BOOK
 *************************/
void partitionBook(int data[ ], size_t n, size_t& pivot_index)
// Library facilities used: itemtool.h, stdlib.h
//
// NOTES FROM THE IMPLEMENTOR:
// How the partition works on small arrays:
//
// Notice that n=0 is not permitted by the precondition.
//
// If n=1, then too_big_index is initialized as 1, and too_small_index is
// initialized as 0. Therefore, the body of the loop is never executed,
// and after the loop pivot_index is set to zero.
//
// If n=2, then both too_big_index and too_small_index are initialized as 1.
// The loop is entered, and there are two cases to consider:
// -- if data[1] <= pivot, then too_big_index increases to 2, and
//    too_small_index stays at 1. The if-statement at the bottom of the loop
//    is then skipped, and after the loop we copy data[1] down to data[0],
//    and copy the pivot into data[0]. Thus, the smaller element is in
//    data[0], and the larger element (the pivot) is in data[1].
// -- if data[1] > pivot, then too_big_index stays at 1, and too_small_index
//    decreases to 0. The if-statement at the bottom of the loop is then
//    skipped, and after the loop we end up copying the pivot onto data[0]
//    (leaving data[1] alone). Thus, the smaller element (the pivot) remains
//    at data[0], leaving the larger element at data[1].
{
	int pivot = data[0];
	size_t too_big_index = 1;     // Index of first item after pivot
	size_t too_small_index = n-1; // Index of last item
	
	// Partition the array, using pivot as the pivot element
	while (too_big_index <= too_small_index)
	{
		while ((too_big_index < n) && (data[too_big_index] <= pivot))
			too_big_index++;
		while (data[too_small_index] > pivot)
			too_small_index--;
		if (too_big_index < too_small_index){
			int temp = data[too_small_index];
			data[too_small_index] = data[too_big_index];
			data[too_big_index] = temp;
			// Too Slow            swap(data[too_small_index], data[too_big_index]);
		}
	}
	// Move the pivot element to its correct position
	pivot_index = too_small_index;
	data[0] = data[pivot_index];
	data[pivot_index] = pivot;
}

void quickSortBook(int data[ ], size_t n) {
	size_t pivot_index; // Array index for the pivot element
	size_t n1;          // Number of elements before the pivot element
	size_t n2;          // Number of elements after the pivot element
	
	if (n > 1)
	{
		// Partition the array, and set the pivot index
		partitionBook(data, n, pivot_index);
		
		// Compute the sizes of the subarrays
		n1 = pivot_index;
		n2 = n - n1 - 1;
		
		// Recursive calls to sort the subarrays
		quickSortBook(data, n1);
		quickSortBook((data + pivot_index + 1), n2);
	}
}




/************************
 ** Utility Functions
 ** Do not change these
 *************************/
duration<double> sortAndTime (int* testArray, size_t theSize, sortRoutine theTest, bool print){
	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	theTest.function (testArray, theSize);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	
	if ( !checkSort  (testArray, theSize) && print){
		cout<< "Array size of: "<< theSize << " contents after " << theTest.name << " completed." << endl;
		printArray (testArray, theSize);
	}
	
	return t2 - t1;
}


int* getRandomNumbers(size_t num, int seed =0) {
	int *arr = nullptr;
	checkSum = 0;
	if (num > 0) {
		arr = new int[num+2];    // Array to hold the numbers
		srand(seed);
		int rnum = static_cast<int>(num);
		for (int count = 0; count < num; count++){
			arr[count] = rand() % (rnum*11) - rnum*11/2;
			checkSum += static_cast <long long>(arr[count]);
		}
		arr[num+1] = arr [num] = 999999;  // catch array overrun
	}
	return arr;
}

bool checkSort( int *a, size_t count) {
	if (count < 1)
		return true; // No work for an empty array.
	bool sorted = true;
	long long testCheckSum =0;
	for ( size_t i{0} ; i < count-1 ; ++i){
		testCheckSum += static_cast<long long>(a[i]);
		if ( a[i] > a[i+1] ) {
			sorted = false;
			cout << "Error Encountered!"<< endl;
			cout << "\tArray ["<< setw(log10(count)+1) <<i   << "] = " << a[i]   << endl;
			cout << "\tArray ["<< setw(log10(count)+1) <<i+1 << "] = " << a[i+1] << endl;
			break;
		}
	}
	if (testCheckSum+ static_cast<long long>(a[count-1]) != checkSum ) {
		cout <<"\nChecksum of Array does not match.  Orginal: " << checkSum;
		cout <<" New: " << testCheckSum+ static_cast<long long>(a[count-1]);
		cout <<"\nNot All numbers not present in the resulting array!\n";
		printArray(a, count);
		sorted = false;
	}
	return sorted;
}

void printArray (int* array, size_t count){
	for ( size_t i{0} ; i < count ; ++i){
		cout << "Array [" << setw(log10(count)+1) <<i<< "] = " << array[i] << endl;
	}
}
