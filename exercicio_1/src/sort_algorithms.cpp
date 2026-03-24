
#include "sort_algorithms.h"
#include <algorithm>



void selectionSort(std::vector<int>& arr, int lentgh){

    for (int i = 0; i < lentgh-1; i++){

        int min = i;

        for (int j = i+1; j < lentgh; j++){

            if (arr[j] < arr[min]){
                min = j;
            };

            if (min != i) {
                std::swap(arr[i], arr[min]);
            }
        }
    }
}

void insertionSort(std::vector<int>& arr, int lentgh){

    for (int i = 0; i < lentgh-1; i++){
        int element = arr[i];
        int j = i;

        while (j > 0 && arr[j-1] > element){
            arr[j] = arr[j-1];
            j = j-1;
        };

        arr[j] = element;
    }
}

