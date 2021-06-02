// C++ program for Merge Sort
#include <iostream>
using namespace std;

void merge(int arr[1000][1000], int l, int hm, int r, int u, int vm, int d)
{
    int m1 = hm - l + 1;
    int m2 = r - hm;
    int n1 = vm - u + 1;
    int n2 = d - vm;

    // temporary matrices for left-right merge (row wise)
    int L[m1 + m2][n1], R[m1 + m2][n2];

    for (int i = 0; i < m1 + m2; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            L[i][j] = arr[l+i][u+j];
        }
        for (int j = 0; j < n2; j++)
        {
            R[i][j] = arr[l+i][vm + 1 + j];
        }
    }

    // merging row elements
    for (int i = 0; i < m1 + m2; i++)
    {
        int j1 = 0, j2 = 0;
        int k1 = u;

        while (j1 < n1 && j2 < n2)
        {
            if (L[i][j1] <= R[i][j2])
            {
                arr[l+i][k1] = L[i][j1];
                j1++;
            }
            else
            {
                arr[l+i][k1] = R[i][j2];
                j2++;
            }
            k1++;
        }

        // leftovers
        while (j1 < n1)
        {
            arr[l+i][k1] = L[i][j1];
            j1++;
            k1++;
        }
        while (j2 < n2)
        {
            arr[l+i][k1] = R[i][j2];
            j2++;
            k1++;
        }
    }
    
    // temporary matrices for up-down merge (coloumn wise)
    int U[m1][n1 + n2], D[m2][n1 + n2];

    for (int j = 0; j < n1 + n2; j++)
    {
        for (int i = 0; i < m1; i++)
        {
            U[i][j] = arr[l+i][u+j];
        }
        for (int i = 0; i < m2; i++)
        {
            D[i][j] = arr[hm + 1 + i][u + j];
        }
    }
    
    // merging column elements
    for (int j = 0; j < n1 + n2; j++)
    {
        int i1 = 0, i2 = 0;
        int k2 = l;
        while (i1 < m1 && i2 < m2)
        {
            if (U[i1][j] <= D[i2][j])
            {
                arr[k2][u+j] = U[i1][j];
                i1++;
            }
            else
            {
                arr[k2][u+j] = D[i2][j];
                i2++;
            }
            k2++;
        }

        // leftovers
        while (i1 < m1)
        {
            arr[k2][u+j] = U[i1][j];
            i1++;
            k2++;
        }

        while (i2 < m2)
        {
            arr[k2][u+j] = D[i2][j];
            i2++;
            k2++;
        }
    }

}

void mergeSort(int arr[1000][1000], int l, int r, int u, int d)
{
    if (l >= r || u >= d)
    {
        return;
    }
    int hm = l + (r - l) / 2; // row middle
    int vm = u + (d - u) / 2; // column middle
    mergeSort(arr, l, hm, u, vm); // 1st quadrant
    mergeSort(arr, hm + 1, r, u, vm); // 2nd quadrant
    mergeSort(arr, l, hm, vm + 1, d); // 3rd quadrant
    mergeSort(arr, hm + 1, r, vm + 1, d); // 4th quadrant
    merge(arr, l, hm, r, u, vm , d);
}

void printMatrix(int A[1000][1000], int m , int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int m, n;
    cin >> m >> n;
    int arr[1000][1000];

    // input array
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }
    
    mergeSort(arr, 0, m-1, 0, n-1);

    cout << "Sorted matrix is \n";
    printMatrix(arr, m, n);
    return 0;
}