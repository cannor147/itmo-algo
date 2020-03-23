#include <iostream>

using namespace std;
const int sz = 3000000;


void merge(int arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 =  r - m;
    int* left;
    int* right;
    left = new int[n1];
    right = new int[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        right[i] = arr[m + i + 1];

    int i = 0, j = 0, k = l;
    while ((i < n1) && (j < n2)){
        if (left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = right[j];
        j++;
        k++;
    }
    delete [] left;
    delete [] right;
}

void mergeSort(int arr[], int l, int r){
    if (l < r){
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

int main() {
//    freopen("sort.in", "r", stdin);
//    freopen("sort.out", "w", stdout);
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);

    int a[sz];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    mergeSort(a, 0, n-1);
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
}