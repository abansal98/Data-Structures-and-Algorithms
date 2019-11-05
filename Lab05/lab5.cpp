#include <cstdlib>
#include <iostream>
#include <fstream>
#include <array>
#include "timer.h"

using namespace std;

void insertionSort(int arr[],int left,int right){
    int curr;
    int i, j;
    for(i=left+1;i<=right;i++){
        curr=arr[i];
        for(j=i;j>0 && arr[j-1] > curr;j--){
            arr[j]=arr[j-1];
        }
        arr[j]=curr;
    }
}

//quicksort has been slightly modified to take threshold as an argument
//when size of partition is at or below threshold, insertion sort is done
void quickSort(int arr[], int left, int right, int threshold){
    if(right-left <= threshold){
        insertionSort(arr,left,right);
    }
    else{
        int i=left;
        int j=right-1;

        /* whatever you do to choose pivot, put the code here
           ensure pivot is at end of array.  For example if 
           you choose middle of array as pivot then swap it 
           with arr[right]*/

        //Picking right most element as the pivot
        //int pivot=arr[right];   //set pivot

        //Picking the middle value as the pivot
        int pivot = arr[right/2];
        swap(arr[right], arr[right/2]);
        int pivotpt=right;   //NOTE: don't change this, pivot needs
                             //to be at end of array to be out of the way
                             //regardless of pivot picking method

        while(i<j){
            while(i< right-1 && arr[i]<pivot) i++;
            while(j > 0 && arr[j]>pivot) j--;
            if(i<j)
                swap(arr[i++],arr[j--]);
        }
        if(i==j && arr[i] < arr[pivotpt])
        i++;
        swap(arr[i],arr[pivotpt]);
        quickSort(arr,left,i-1,threshold);
        quickSort(arr,i+1,right,threshold);
    }
}

void quickSort_rightPivot(int arr[], int left, int right, int threshold){
    if(right-left <= threshold){
        insertionSort(arr,left,right);
    }
    else{
        int i=left;
        int j=right-1;

        /* whatever you do to choose pivot, put the code here
           ensure pivot is at end of array.  For example if 
           you choose middle of array as pivot then swap it 
           with arr[right]*/

        //Picking right most element as the pivot
        int pivot=arr[right];   //set pivot

        int pivotpt=right;   //NOTE: don't change this, pivot needs
                             //to be at end of array to be out of the way
                             //regardless of pivot picking method

        while(i<j){
            while(i< right-1 && arr[i]<pivot) i++;
            while(j > 0 && arr[j]>pivot) j--;
            if(i<j)
                swap(arr[i++],arr[j--]);
        }
        if(i==j && arr[i] < arr[pivotpt])
        i++;
        swap(arr[i],arr[pivotpt]);
        quickSort(arr,left,i-1,threshold);
        quickSort(arr,i+1,right,threshold);
    }
}

void quickSort_middlePivot(int arr[], int left, int right, int threshold){
    if(right-left <= threshold){
        insertionSort(arr,left,right);
    }
    else{
        int i=left;
        int j=right-1;

        /* whatever you do to choose pivot, put the code here
           ensure pivot is at end of array.  For example if 
           you choose middle of array as pivot then swap it 
           with arr[right]*/

        //Picking the middle value as the pivot
        swap(arr[right], arr[right/2]);

        int pivot = arr[right];   //set pivot
        int pivotpt=right;   //NOTE: don't change this, pivot needs
                             //to be at end of array to be out of the way
                             //regardless of pivot picking method

        while(i<j){
            while(i< right-1 && arr[i]<pivot) i++;
            while(j > 0 && arr[j]>pivot) j--;
            if(i<j)
                swap(arr[i++],arr[j--]);
        }
        if(i==j && arr[i] < arr[pivotpt])
        i++;
        swap(arr[i],arr[pivotpt]);
        quickSort(arr,left,i-1,threshold);
        quickSort(arr,i+1,right,threshold);
    }
}

void quickSort_medianPivot(int arr[], int left, int right, int threshold){
    if(right-left <= threshold){
        insertionSort(arr,left,right);
    }
    else{
        int i=left;
        int j=right-1;

        /* whatever you do to choose pivot, put the code here
           ensure pivot is at end of array.  For example if 
           you choose middle of array as pivot then swap it 
           with arr[right]*/

        //Median as the pivot
        int tempArray[3] = {arr[0], arr[right], arr[right/2]};
        quickSort(tempArray, 0, 2, 3);
        arr[0] = tempArray[0];
        arr[right] = tempArray[1];
        arr[right/2] = tempArray[2];

        int pivot = arr[right];     //set pivot
        int pivotpt=right;   //NOTE: don't change this, pivot needs
                             //to be at end of array to be out of the way
                             //regardless of pivot picking method

        while(i<j){
            while(i< right-1 && arr[i]<pivot) i++;
            while(j > 0 && arr[j]>pivot) j--;
            if(i<j)
                swap(arr[i++],arr[j--]);
        }
        if(i==j && arr[i] < arr[pivotpt])
        i++;
        swap(arr[i],arr[pivotpt]);
        quickSort(arr,left,i-1,threshold);
        quickSort(arr,i+1,right,threshold);
    }
}

//non-recursive interface to quicksort, real work
//done in recursive version.
void quickSort(int arr[],int size,int threshold=3){
    quickSort(arr,0,size-1,threshold);
}

/*This function is passed an empty array of size elements
it will fill the array with random numbers*/
void generateRandom(int array[],int size){
    for(int i=0;i<size;i++){
        array[i]=rand();
    }
}

/*This function is passed an empty array with sz elements. It will 
fill this array with numbers where the numbers are ordered is ordered 
from big to small. Note that the values in here need not be random 
only that it goes from biggest to smallest*/
void generateReverse(int array[],int size){
	array[0] = rand();
	for(int i = 1; i < size; i++){
		array[i] = array[i-1] - 20;
	}
}


/*This function is passed an empty array with size elements. 
This function generate 20 random numbers. Each element of the
array will get one of these 20 numbers.*/
void generateManyDuplicates(int array[],int size){
	int arr[size];
	for(int i = 0; i < size; i++){
		arr[i] = rand();
	}

	for(int i = 0; i < size; i++){
		array[i] = arr[rand()%size];
	}	
}

/*This function is passed an empty array with size elements. 
This function generates a nearly sorted array (small to big). 
This can be done by creating a sorted array(doesn't have to be
random numbers...just small to big) and then randomly
performing a small number of swaps on the array. The small
number can be based on percentage of size around 5%. Thus if
 sz was 100, you would do 5 swaps (making around 10 numbers 
 out of place, leaving 90 sorted)*/

void generateNearlySorted(int array[],int size){
	array[0] = (rand()%20);
	for(int i = 1; i < size; i++){
		array[i] = array[i-1] + (rand()%size);
	}
    
    int swaps = 5;
    int index = 0;

    if(size >= 100){
        swaps = size * 0.05;
    }

    for(int i = 0; i < swaps; i++){
        index = rand()%(size - 1);
        array[index] = array[index] + array[index + 1];
        array[index + 1] = array[index] - array[index + 1];
    }
}

int main(int argc, char* argv[]){

    int size = 0;

    if(argc == 2){
        size = atoi(argv[1]);
    }

    int* myarr = new int[size];
    Timer stopwatch;
    ofstream log("quick.csv");

    //Variable data and algorithm test
    /*
    log << endl << endl << "Starting sorting with random Array" << endl;
    for(int i = 5000; i <= 100000; i+=5000){
        myarr = new int[i];
        generateRandom(myarr, i);

        int* tempArr = new int[i];
        for(int j = 0; j < i; j++){
            tempArr[j] = myarr[j];
        }

        log << i << ',';

        //Right element as the pivot
        stopwatch.start();
        quickSort_rightPivot(tempArr, 0, i-1, 3);
        stopwatch.stop();
        log << stopwatch.currtime() << ',';
        stopwatch.reset();

        //Middle element as the pivot
        stopwatch.start();
        quickSort_middlePivot(tempArr, 0, i-1, 3);
        log << stopwatch.currtime() << ',';
        stopwatch.stop();
        stopwatch.reset();

        //Median element as the pivot
        stopwatch.start();
        quickSort_medianPivot(tempArr, 0, i-1, 3);
        log << stopwatch.currtime() << ',';
        stopwatch.stop();
        stopwatch.reset();

        log << endl;
    }

    log << endl << endl << "Starting sorting with nearly sorted array" << endl;
    for(int i = 5000; i <= 100000; i+=5000){
        myarr = new int[i];
        generateNearlySorted(myarr, i);

        int* tempArr = new int[i];
        for(int j = 0; j < i; j++){
            tempArr[j] = myarr[j];
        }

        log << i << ',';

        //Right element as the pivot
        stopwatch.start();
        quickSort_rightPivot(tempArr, 0, i-1, 3);
        stopwatch.stop();
        log << stopwatch.currtime() << ',';
        stopwatch.reset();

        //Middle element as the pivot
        stopwatch.start();
        quickSort_middlePivot(tempArr, 0, i-1, 3);
        log << stopwatch.currtime() << ',';
        stopwatch.stop();
        stopwatch.reset();

        //Median element as the pivot
        stopwatch.start();
        quickSort_medianPivot(tempArr, 0, i-1, 3);
        log << stopwatch.currtime() << ',';
        stopwatch.stop();
        stopwatch.reset();

        log << endl;
    }

    log << endl << endl << "Starting sorting with array with many duplicates" << endl;
    for(int i = 5000; i <= 100000; i+=5000){
        myarr = new int[i];
        generateManyDuplicates(myarr, i);

        int* tempArr = new int[i];
        for(int j = 0; j < i; j++){
            tempArr[j] = myarr[j];
        }

        log << i << ',';

        //Right element as the pivot
        stopwatch.start();
        quickSort_rightPivot(tempArr, 0, i-1, 3);
        stopwatch.stop();
        log << stopwatch.currtime() << ',';
        stopwatch.reset();

        //Middle element as the pivot
        stopwatch.start();
        quickSort_middlePivot(tempArr, 0, i-1, 3);
        log << stopwatch.currtime() << ',';
        stopwatch.stop();
        stopwatch.reset();

        //Median element as the pivot
        stopwatch.start();
        quickSort_medianPivot(tempArr, 0, i-1, 3);
        log << stopwatch.currtime() << ',';
        stopwatch.stop();
        stopwatch.reset();

        log << endl;
    }

    log << endl << endl << "Starting sorting with reverse sorted array" << endl;
    for(int i = 5000; i <= 100000; i+=5000){
        cout << "index is: " << i << endl;
        myarr = new int[i];
        generateReverse(myarr, i);

        int* tempArr = new int[i];
        for(int j = 0; j < i; j++){
            tempArr[j] = myarr[j];
        }

        log << i << ',';

        //Right element as the pivot
        stopwatch.start();
        quickSort_rightPivot(tempArr, 0, i-1, 3);
        stopwatch.stop();
        log << stopwatch.currtime() << ',';
        stopwatch.reset();

        //Middle element as the pivot
        stopwatch.start();
        quickSort_middlePivot(tempArr, 0, i-1, 3);
        log << stopwatch.currtime() << ',';
        stopwatch.stop();
        stopwatch.reset();

        //Median element as the pivot
        stopwatch.start();
        quickSort_medianPivot(tempArr, 0, i-1, 3);
        log << stopwatch.currtime() << ',';
        stopwatch.stop();
        stopwatch.reset();

        log << endl;
    }
    */

    //The definition of "small" test
    //size of data set for this test is 10,000,000
    int smalls[13] = {5, 10, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    generateRandom(myarr, size);

    //creating 13 copies of the original data for the test with 13 different values of small/threshold
    int* tempArr1 = new int[size];
    int* tempArr2 = new int[size];
    int* tempArr3 = new int[size];
    int* tempArr4 = new int[size];
    int* tempArr5 = new int[size];
    int* tempArr6 = new int[size];
    int* tempArr7 = new int[size];
    int* tempArr8 = new int[size];
    int* tempArr9 = new int[size];
    int* tempArr10 = new int[size];
    int* tempArr11 = new int[size];
    int* tempArr12 = new int[size];
    int* tempArr13 = new int[size];
    for(int i = 0; i < size; i++){
        tempArr1[i] = myarr[i];
        tempArr2[i] = myarr[i];
        tempArr3[i] = myarr[i];
        tempArr4[i] = myarr[i];
        tempArr5[i] = myarr[i];
        tempArr6[i] = myarr[i];
        tempArr7[i] = myarr[i];
        tempArr8[i] = myarr[i];
        tempArr9[i] = myarr[i];
        tempArr10[i] = myarr[i];
        tempArr11[i] = myarr[i];
        tempArr12[i] = myarr[i];
        tempArr13[i] = myarr[i];
    }

    int* tempArrays[13] = {tempArr1, tempArr2, tempArr3, tempArr4, tempArr5, tempArr6, tempArr7, tempArr8, tempArr9,
        tempArr10, tempArr11, tempArr12, tempArr13};

    for(int i = 0; i < 13; i++){
        cout << "Test number: " << i << endl;
        stopwatch.start();
        quickSort_rightPivot(tempArrays[i], 0, size-1, smalls[i]);
        stopwatch.stop();
        log << smalls[i] << ',' << stopwatch.currtime() << endl;
        stopwatch.reset();
    }
    return 0;
}
