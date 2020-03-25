/*
    * runtime: O(n.log(n)) average, O(n^2) worst case
    * Memory: O(n.log(n))
*/

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

class QuickSort {
    private:
        static int partition(int a[], int left, int right) {
            int a0 = a[left];
            int i = left + 1, j = right;

            do {
                while (i <= j && a[i] <= a0) i++;
                while (i <= j && a[j] > a0) j--;
                if (i < j) {
                    int temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;

                    i++;
                    j--;
                }
            } while (i <= j);

            int temp = a[left];
            a[left] = a[j];
            a[j] = temp;

            return j;
        }

    public:
        static void quickSort(int a[], int left, int right) {
            if (left < right) {
                int mid = partition(a, left, right);
                quickSort(a, left, mid - 1);
                quickSort(a, mid + 1, right);
            }
        }
};

int main(int argc, char const *argv[]) {
    int a[] = {9,1,8,2,7,3,6,4,5,0};
    int left = 0, right = sizeof(a)/sizeof(int) - 1;
    QuickSort::quickSort(a, left, right);

    for (int i = 0; i <= right; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
