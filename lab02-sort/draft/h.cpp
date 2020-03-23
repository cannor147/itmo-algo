#include <iostream>

using namespace std;
const int sz = 1000000;

int inv = 0;
unsigned int cur = 0;
unsigned int c, d;
unsigned int nextRand24() {
    cur = cur * c + d;
    return cur >> 8;
}

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
            inv += n1 - i;
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
    freopen("invcnt.in", "r", stdin);
    freopen("invcnt.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int  a[sz];
    int n;
    unsigned int m;
    cin >> n >> m;
    cin >> c >> d;
    for (int i = 0; i < n; i++){
        a[i] = (int) nextRand24() % m;
    }
    mergeSort(a, 0, n-1);
    cout << inv;
}