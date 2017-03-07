/**
 *  @file heap_sort.cpp
 *  @author Sheng-Hao Ma (aaaddress1, aka adr)
 *  @date 03/07/2017
 *  @brief implementat heap sorting algoprithms
 **/

void maxHeapify(/* input array */int * a, /* parent */int p, /* count */int n) {
    int curParent = a[p];
    int child = 2 * p + 1;
    while(child < n) {
        if(child + 1 < n && a[child] < a[child + 1])
            child++;

        if(curParent < a[child]) {
            a[p] = a[child];
            p = child;
            child= 2 * p + 1;
        }
        else break;
    }
    a[p] = curParent;
}

void heapSort(/* input array */int * a, /* count */int n) {
	#define swap(x, y) ({ int t = x; x = y; y = t; })
    for(int i = n/2; i--> 0;)
        maxHeapify(a, i, n);

    for(int i = n; i--> 0;) {
        swap(a[0], a[i]);
        maxHeapify(a, 0, i);
    }
}