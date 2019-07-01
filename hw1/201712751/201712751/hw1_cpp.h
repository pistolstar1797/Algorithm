#include <time.h>
#include <stdlib.h>

//simple swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//select random pivot and make partition
int randomized_partition(int a[], int n){
    srand(time(NULL));    
    int index = rand() % n;
    int pivot = a[index];
    
    swap(a + index, a + n-1);

    int t = -1;
    
    for(int i = 0 ; i < n-1 ; i++) {
        if(a[i] <= pivot) {
            t++;
            swap(a + t, a + i);
        }
    }

    swap(a + t+1, a + n-1);

    return t+1;
}


//find the "k"th smallest element in array "a" with "n" elements by using Randomized-select in CLRS
int randomized_select(int a[], int n, int k){
    if(n == 0) {
        return a[0];
    }
    
    if(n > 0) {
        int m = randomized_partition(a, n);
        if(m == k) {
            return a[m];
        }
        else if (m < k) {
            return randomized_select(a + m+1, n - (m+1), k - (m+1));
        }
        else {
            return randomized_select(a, m, k);
        }
    }
}

//get median of medians recursively divided by 5
int get_index(int c[], int n) {
    if(n == 0) {
        return c[0];
    }

    for(int i = 0 ; i < n ; i += 5) {
        if(i + 5 > n) {
            for(int j = 1 ; j < (n%5) ; j++) {
                int temp = c[i+j];
                int k = j;
                
                while(--k >= 0 && temp < c[i+k]) {
                    c[i + k+1] = c[i + k];
                    c[k] = temp;
                }
            }

            c[i/5] = c[i + (n%5)/2];
        }
        else {
            for(int j = 1 ; j < 5 ; j++) {
                int temp = c[i+j];
                int k = j;
                
                while(--k >= 0 && temp < c[i+k]) {
                    c[i + k+1] = c[i + k];
                    c[k] = temp;
                }
            }

            c[i/5] = c[i + 2];
        }
    }

    return get_index(c, n/5);
}

//select median and make partition 
int deterministic_partition(int a[], int n) {
    int c[n];

    for(int i = 0 ; i < n ; i++) {
        c[i] = a[i];
    }

    int index = 0;
    int pivot = get_index(c, n);

    for(int i = 0 ; i < n ; i++) {
        if(a[i] == pivot) {
            index = i;
            break;
        }
    }
    
    swap(a + index, a + n-1);

    int t = -1;
    
    for(int i = 0 ; i < n-1 ; i++) {
        if(a[i] <= pivot) {
            t++;
            swap(a + t, a + i);
        }
    }

    swap(a + t+1, a + n-1);

    return t+1;
}

//find the "k"th smallest element in array "a" with "n" elements by using the worst-case linear-time algorithm in CLRS
int deterministic_select(int a[], int n, int k){
    if(n == 0) {
        return a[0];
    }
    
    if(n > 0) {
        int m = deterministic_partition(a, n);
        if(m == k) {
            return a[m];
        }
        else if (m < k) {
            return deterministic_select(a + m+1, n - (m+1), k - (m+1));
        }
        else {
            return deterministic_select(a, m, k);
        }
    }
}

//check whether the "k"th smallest element in array "a" with "n" elements is the "ans"
bool checker(int a[], int n, int k, int ans){
    int cnt = 0;

    for(int i = 0 ; i < n ; i++) {
        if(a[i] < ans) {
            cnt++;
        }
    }

    if(cnt == k) {
        return true;
    }
    else {
        return false;
    }
}
