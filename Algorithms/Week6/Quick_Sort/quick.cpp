#include<iostream>
using namespace std; 

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
 
int partition (int arr[], int low, int high) {
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    for (int j = low; j <= high- 1; j++) {
        if (arr[j] <= pivot) {
            i++;                 // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
/* Function to print an array */
 
// Driver program to test above functions
int main() {
    int n;
    cout<<"\nEnter the number of data element to be sorted: ";
    cin>>n;
    int arr[n];
    for(int i = 0; i < n; i++) {
        cout<<"Enter element "<<i+1<<": ";
        cin>>arr[i];
    }
    quickSort(arr, 0, n-1);
    cout<<" Sorted Array -> " ; 
    for (int i = 0; i < n; i++)
        cout<<"->"<<arr[i];
    return 0;
}