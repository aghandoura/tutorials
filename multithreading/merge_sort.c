#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 2 /* # of thread */
/////!!!!!!!threads are created recursively keep this low
#define MAX_ELEM 100  /* # of thread */

int *a;  /* target array */
pthread_mutex_t mutex;

/* structure for array index
 * used to keep low/high end of sub arrays
 */
typedef struct Arr {
    int low;
    int high;
} ArrayIndex;

int uniform_distribution(int rangeLow, int rangeHigh)
{
    int range = rangeHigh - rangeLow + 1; //+1 makes it [rangeLow, rangeHigh], inclusive.
    int copies=RAND_MAX/range; // we can fit n-copies of [0...range-1] into RAND_MAX
    // Use rejection sampling to avoid distribution errors
    int limit=range*copies;
    int myRand=-1;
    while( myRand<0 || myRand>=limit){
        myRand=rand();
    }
    return myRand/copies+rangeLow;    // note that this involves the high-bits
}

void merge(int low, int high)
{
        /*pthread_mutex_lock(&mutex);*/
        int mid = low + (high - low)/2;
        int left = low;
        int right = mid+1;

        int b[high-low+1];
        int i, cur = 0;

        while(left <= mid && right <= high) {
                if (a[left] > a[right])
                        b[cur++] = a[right++];
                else
                        b[cur++] = a[left++];
        }

        while(left <= mid) b[cur++] = a[left++];
        while(right <= high) b[cur++] = a[right++];
        for (i = 0; i < (high-low+1) ; i++) a[low+i] = b[i];

        /*pthread_mutex_unlock(&mutex);*/
}

void * mergesort(void *a)
{
        ArrayIndex *pa = (ArrayIndex *)a;
        int mid = pa->low + (pa->high - pa->low)/2;

        ArrayIndex aIndex[N];
        pthread_t thread[N];

        aIndex[0].low = pa->low;
        aIndex[0].high = mid;

        aIndex[1].low = mid+1;
        aIndex[1].high = pa->high;

        if (pa->low >= pa->high) return NULL;

        int i;
        for(i = 0; i < N; i++) pthread_create(&thread[i], NULL, mergesort, &aIndex[i]);
        for(i = 0; i < N; i++) pthread_join(thread[i], NULL);

        merge(pa->low, pa->high);

        pthread_exit(NULL);
}

int main()
{
        ArrayIndex ai;
        int index = 0;
        int i;
        time_t seconds;

        seconds = time(NULL);

        time(&seconds);

        srand ((unsigned) seconds);

        a = malloc( MAX_ELEM * sizeof(int));
        if (!a)
        {
            printf("malloc failed \n");
            return -1;
        }

        for (index = 0; index < MAX_ELEM; index++)
        {
            a[index] = uniform_distribution(0, index);

        }

        for (i = 0; i < MAX_ELEM; i++) printf ("%d ", a[i]);
        printf("\n");

        ai.low = 0;
        ai.high = MAX_ELEM;
        pthread_t thread;

        pthread_create(&thread, NULL, mergesort, &ai);
        pthread_join(thread, NULL);

        for (i = 0; i < MAX_ELEM; i++) printf ("%d ", a[i]);
        printf("\n");

        pthread_mutex_destroy(&mutex);
        free(a);

        return 0;
}
