#include <iostream>

using namespace std;
const int s = 100001;

int binarySearch(int arr[], int l, int r, int temp){
    if (r >= l){
        int mid = l + (r - l)/2;

        if (arr[mid] == temp)  return mid;
        if (arr[mid] > temp) return binarySearch(arr, l, mid - 1, temp);
        return binarySearch(arr, mid + 1, r, temp);
    }
    return s - 1;
}

int main() {
    freopen("binsearch.in", "r", stdin);
    freopen("binsearch.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a[s], first[s], last[s];
    int j, temp, n, m;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    first[s - 1] = -1;
    last[s - 1] = -1;
    first[0] = 1;
    last[n - 1] = n;
    for (int i = 1; i < n; i++)
        if (a[i] == a[i - 1])
            first[i] = first[i - 1];
        else
            first[i] = i+1;
    for (int i = n-2; i >= 0; i--)
        if (a[i] == a[i + 1])
            last[i] = last[i + 1];
        else
            last[i] = i + 1;

    cin >> m;
    for (int i = 0; i < m; i++){
        cin >> temp;
        j = binarySearch(a, 0, n - 1, temp);
        cout << first[j] << ' ' << last[j] << '\n';
    }
}