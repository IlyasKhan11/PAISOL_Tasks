#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int start, int end) {
    int pivot = arr[end];
    int i = start - 1; 

    for (int j = start; j < end; j++) {
        if (arr[j] <= pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[end]);
    return i + 1;
}

int useQuickSelect(int arr[], int start, int end, int k) {
    
    if (k > end) {
        cout << "Invalid Kth position, exceeds the array limit, no element at position ";
        return -1;
    }

    if (start > end) {
        cout << "Empty array.";
        return -2;
    }

    if (start == end) {
        return arr[start]; // Only one element in the array
    }

    int pivot = partition(arr, start, end);

    if (k == pivot) {
        return arr[pivot];
    } else if (k < pivot) {
        return useQuickSelect(arr, start, pivot - 1, k);
    } else {
        return useQuickSelect(arr, pivot + 1, end, k);
    }
}

void useTestCases() {
  int testCases[][6] = {
    {1, 2, 3, 4, 5, 6},
    {6, 5, 4, 3, 2, 1},
    {5, 1, 3, 6, 2, 4},
    {1, 1, 1, 1, 1, 1},
    {9, 7, 5, 3, 1, 2},
    {10, 20, 30, 40, 50, 60},
  };

  int ks[] = {1, 2, 3, 4, 5, 10}; // 1-based indexing

  int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

  for (int i = 0; i < numTestCases; ++i) {
    int n = sizeof(testCases[i]) / sizeof(testCases[i][0]);

    if (n == 0) {
      cout << "Empty list." << endl;
      continue; 
    }

    cout << "Original array: ";
    for (int j = 0; j < n; ++j) {
      cout << testCases[i][j] << " ";
    }
    cout << endl;

    for (int j = 0; j < sizeof(ks) / sizeof(ks[0]); ++j) {
      int k = ks[j];
      int result = -1;

      if (n > 0) {
        result = useQuickSelect(testCases[i], 0, n - 1, k - 1); 
      }

      if (result != -1) {
        cout << "The " << k << "th smallest element is: " << result << endl;
      }else if(result ==-2){
        cout<<"empty array"<<endl;
      } else {
        cout << "k (" << k << ") is greater than the number of elements in the array." << endl;
      }
    }

    cout << endl; 
  }
}



void useUserDefinedCases() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int *arr = new int[size];

    if(size==0){
        cout<<"empty array,"<<endl;
        return;
    }
    cout << "Enter " << size << " elements separated by space: ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }


    int k;
    cout << "Enter the value of k (1-based indexing): ";
    cin >> k;

    int result = useQuickSelect(arr, 0, size - 1, k - 1); 
    cout << "The " << k << "th smallest element is: " << result << endl;

    delete[] arr;
}

int main() {
    int choice;
    cout << "Please select what you want to do next:\n 1) Use pre-defined test cases\n 2) Use your own defined test case\n Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            useTestCases();
            break;
        case 2:
            useUserDefinedCases();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
