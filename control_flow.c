#include <stdio.h>
#define arr_size 1000000

int binsearch(int x, int v[], int n);

int main()
{
    int nums[arr_size], i;
    for(i = 0; i < arr_size; i++)
    {
        nums[i] = i;
    }

    binsearch(33333, nums, arr_size);
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, mid, high;

    low = 0;
    high = n - 1;
    while( low <= high) 
    {
        mid = (low + high) / 2;
        if(x < v[mid])
            high = mid - 1;
        else if(x > v[mid])
            low = mid + 1;
        else
            return v[mid];
    }
    return -1;
}
