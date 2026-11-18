#include <stdio.h>
#include <pthread.h>
int arr[] = {7,12,19,3,18,4,2,6,15,8};
int sorted_arr[10];
int SIZE=10;
int mid=5;

struct sort_args {
    int start;
    int end;
};
struct merge_args {
    int start;
    int mid;
    int end;
};
void insertionSort(int *a, int n) {
    for(int i=1; i<n; i++) {
        int key=a[i], j=i-1;
        while(j>=0 && a[j]>key) a[j+1]=a[j],j--;
        a[j+1]=key;
    }
}
void* threadSort(void *arg) {
    struct sort_args *a= (struct sort_args*)arg;
    insertionSort(&arr[a->start], a->end - a->start);
    pthread_exit(NULL);
}

void mergeArr(int *a, int size_a, int *b, int size_b, int *result) {
    int i=0, j=0, k=0;
    while(i<size_a && j<size_b) {
        if(a[i]<b[j])
            result[k++]=a[i++];
        else
            result[k++]=b[j++];
    }
    while(i<size_a) {
        result[k++] = a[i++];
    }
    while(j<size_b) {
        result[k++] = b[j++];
    }
}

void* thread_Merge(void *arg) {
    struct merge_args *a= (struct merge_args*)arg;
    mergeArr(&arr[a->start], (a->mid )-(a->start), &arr[a->mid], (a->end )-(a->mid), sorted_arr);
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2, t3;
    struct sort_args s1={0, mid};
    struct sort_args s2={mid, SIZE};
    pthread_create(&t1,NULL, threadSort, &s1);
    pthread_create(&t2,NULL, threadSort, &s2);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    struct merge_args m={0,mid,SIZE};
    pthread_create(&t3,NULL, thread_Merge, &m);
    pthread_join(t3,NULL);
    for(int i=0; i<SIZE; i++) printf("%d ", sorted_arr[i]);
    return 0;
}