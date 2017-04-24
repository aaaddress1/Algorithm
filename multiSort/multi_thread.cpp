/***
 * @file multi_thread.cpp
 * @author Sheng-Hao Ma (aaaddress1, aka adr)
 * @date 2017/04/24
 ***/
#include <stdio.h>
#include <pthread.h>
#include <algorithm>

typedef struct {
	int thread_id;
	int begin_index;
	int end_index;
	int *array;
	int array_length;
} sort_param;

typedef struct {
	int sort_div_length;
	int *array;
	int array_length;
} multi_div_sort_param;

void *sort_arr(void *ptr) {
	sort_param *param = (sort_param *)ptr;
	int *arr = param->array;
	std::sort((arr + param->begin_index), (arr + param->end_index + 1));
	pthread_exit(0);
}

void *multi_div_sort(void *ptr) {
	multi_div_sort_param *param = (multi_div_sort_param *)ptr;
	int heap_count = 0;
	int each_inc_count = param->array_length / param->sort_div_length;
	pthread_t *t = new pthread_t[param->sort_div_length];
	sort_param *p = new sort_param[param->sort_div_length];

	/* create child thread for each array range */
	for (int i = 0; i < param->sort_div_length; heap_count = p[i].end_index + 1, i++) {
		p[i].thread_id = i;
		p[i].array = param->array;
		p[i].array_length = param->array_length;
		p[i].begin_index = heap_count;
		p[i].end_index = p[i].begin_index + each_inc_count;
		p[i].end_index = p[i].end_index < p[i].array_length - 1 ? p[i].end_index : p[i].array_length - 1;
		pthread_create(&t[i], NULL, sort_arr, (void *)&p[i]);
		pthread_join(t[i], NULL);
	}

	/* wait for all array range sorted */
	for (int i = 0; i < param->sort_div_length; i++)
		pthread_join(t[i], NULL);
	std::sort(param->array, param->array + param->array_length);
	pthread_exit(0);
}

int main(void) {
	int arr[] = { 7, 1, 3, 5, 4, 1 };
	pthread_t thread;
	multi_div_sort_param p;

	p.array = arr;
	p.array_length = sizeof(arr) / sizeof(int);
	p.sort_div_length = 2; /* div sort range into two pieces, or more */
	pthread_create(&thread, NULL, multi_div_sort, (void *)&p);
	pthread_join(thread, NULL);

	for(int i = 0; i < p.array_length; i++) printf("%i ", arr[i]);
	puts("");
	return 0;
}
