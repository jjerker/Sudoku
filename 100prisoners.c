// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

#define NBOXES 100

void permut(int *arr, int n ) {
    int i,j; 
    int val;
    for (i=0; i<n; i++) {
        val = rand() % NBOXES;
        for (j=0; j<n;j++) {if (val==arr[j]) {val=(++val) % NBOXES; j=0; } }
        arr[i] = val; 
    }
}

int testprisoner (int *arr, int nprisoner, int n) {
    int i;
    int select = rand() % NBOXES;
    //printf("In testprisoner\n");
    for (i=0; i<n; i++) {
        if (arr[select]==nprisoner) return 1;
        //printf("Moving from box %i to box %i\n", select, arr[select]);
        select = arr[select];
    }
    return 0;
}

int teststrat (int *arr, int n){
    int count=0;
    int i;
    //printf("In teststrat n=%i\n",n);

    for (i=0; i<n;i++) {
    //printf("In teststrat2\n");
        if (testprisoner(arr, i, n/2)) count++;
        //printf("Iteration %i, count=%i\n", i, count);
    }
    return count;
}

#define ITER 1000

int main() {
    // Write C code here
    int box[NBOXES];
    int i,j;
    int count=0;
    // Create random numbers in boxes
    permut(box, NBOXES);
    for (i=0; i<ITER; i++) {
        printf("teststrat =%i\n", teststrat(box, NBOXES));
        if (teststrat(box,NBOXES) == NBOXES) count++;
    }
    
    printf("Succesfull cases %i / %i = %f  \n", count, ITER, count/ITER);
    
    return 0;
}
