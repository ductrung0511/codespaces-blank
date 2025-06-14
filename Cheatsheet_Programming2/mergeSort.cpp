#include<iostream>
void Merge(int arr[],int left, int mid, int right){
    int range = right - left+1;
    int tempArr[range];
    int i = left;
    int j = mid + 1 ;
    int index =0;
    
    while(i <= mid && j <= right ){
        if(arr[i] < arr[j]){
            tempArr[index++] = arr[i];
            i++;
        }
        else{
            tempArr[index++] = arr[j];
            j++;
        }

    }
    while (i<= mid){
        tempArr[index++] = arr[i];
        i++;
    }
    while ( j <= right){
        tempArr[index++] = arr[j];
        j++;
    }
    for(int k = 0; k< range; k++){
        arr[k+left] = tempArr[k];
    }
}

void MergeSort(int arr[],int left, int right){
    if (left >= right) return;
    int mid = left + (right - left )/2 ;
    MergeSort(arr, left, mid);
    MergeSort(arr, mid + 1, right);
    Merge(arr, left, mid, right);
}


using namespace std;
int main(){
    int arr[] = {1,4,3,2,5};
    int size = sizeof(arr) /sizeof(arr[0]);
    MergeSort(arr, 0, size -1 );
    
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}