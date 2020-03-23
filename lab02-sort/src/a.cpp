#include <iostream>

using namespace std;

void quickSort(int arr[], int left, int right) {
    int l = left, r = right;
    int temp;
    int pivot = arr[(l + r) / 2];

    /* partition */
    while (l <= r) {
        while (arr[l] < pivot)
            l++;
        while (arr[r] > pivot)
            r--;
        if (l <= r) {
            temp = arr[l];
            arr[l] = arr[r];
            arr[r] = temp;
            l++;
            r--;
        }
    };

    /* recursion */
    if (left < r)
        quickSort(arr, left, r);
    if (l < right)
        quickSort(arr, l, right);
}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a[300001];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    quickSort(a, 0, n-1);
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}