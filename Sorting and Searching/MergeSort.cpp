/*
    * runtime: O(n.log(n)) average & worst case
    * memory: depends on size of array :>
*/

#include "stdio.h"
#include "stdlib.h"

#include "iostream"
using namespace std;

class MergeSort {
    public:
        static void mergeSort(int a[], int left, int right) {
            if (left < right) {
                int mid = (left + right) / 2;
                mergeSort(a, left, mid);
                mergeSort(a, mid + 1, right);
                merge(a, left, mid, right);
            }
        }

    private:
        static void merge(int a[], int left, int mid, int right) {
            int i = left, j = mid + 1, k = 0;
            int *helper = new int[right - left + 1];

            while (i <= mid && j <= right) {
                if (a[i] > a[j]) {
                    helper[k] = a[j];
                    j++;
                }
                else {
                    helper[k] = a[i];
                    i++;
                }
                k++;
            }

            // nếu 1 trong 2 phần còn dư phần tử và phần còn lại đã hết 
            while (i <= mid) {
                helper[k] = a[i];
                i++;
                k++;
            }
            while (j <= right) {
                helper[k] = a[j];
                j++;
                k++;
            }

            // gán các giá trị đã sort vào mảng chính 
            i = left;
            k = 0;
            for (; k < right - left + 1; k++) {
                a[i] = helper[k];
                i++;
            }
            delete[] helper;
        }
};

int main(int argc, char const *argv[]) {
    int a[] = {9,1,8,2,7,3,6,4,5,0};
    int left = 0, right = sizeof(a)/sizeof(int) - 1;
    MergeSort::mergeSort(a, left, right);

    for (int i = 0; i <= right; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
