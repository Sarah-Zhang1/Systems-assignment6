/** 
 * Threaded Merge Sort
 *
 * Modify this file to implement your multi-threaded version of merge sort. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <unistd.h>

#include <assert.h> 
#include <pthread.h>

#define tty_printf(...) (isatty(1) && isatty(0) ? printf(__VA_ARGS__) : 0)

#ifndef SHUSH
#define log(...) (fprintf(stderr, __VA_ARGS__))
#else 
#define log(...)
#endif

/** The number of threads to be used for sorting. Default: 1 */
int thread_count = 1;

/* Counter for active threads */
int active_threads = 1;  // Start with 1 for the main thread

/**
 * Compute the delta between the given timevals in seconds.
 */
double time_in_secs(const struct timeval *begin, const struct timeval *end) {
  long s = end->tv_sec - begin->tv_sec;
  long ms = end->tv_usec - begin->tv_usec;
  return s + ms * 1e-6;
}

/**
 * Print the given array of longs, an element per line.
 */
void print_long_array(const long *array, int count) {
  for (int i = 0; i < count; ++i) {
    printf("%ld\n", array[i]);
  }
}

/**
 * Merge two slices of nums into the corresponding portion of target.
 */
void merge(long nums[], int from, int mid, int to, long target[]) {
  int left = from;
  int right = mid;

  int i = from;
  for (; i < to && left < mid && right < to; i++) {
    if (nums[left] <= nums[right]) {
      target[i] = nums[left];
      left++;
    }
    else {
      target[i] = nums[right];
      right++;
    }
  }
  if (left < mid) {
    memmove(&target[i], &nums[left], (mid - left) * sizeof(long));
  }
  else if (right < to) {
    memmove(&target[i], &nums[right], (to - right) * sizeof(long));
  }

}

// struct to hold all information needed for sorting 
typedef struct {
  long *nums; // array to be sorted
  int from; // starting index of the sub array
  int to; // ending index (exclusive)
  long *end; //where sorted result is stored
} sort_args;

//declaration of merge_sort_aux
void merge_sort_aux(long nums[], int from, int to, long target[]);


/*
 * Thread function for parallel merge sort
 */
void *thread_merge_sort(void *arg) {
  sort_args *args = (sort_args*)arg;
  merge_sort_aux(args->nums, args->from, args->to, args->end);
  
  free(args);
  return NULL;
}


/**
 * Sort the given slice of nums into target.
 *
 * Warning: nums gets overwritten.
 */
void merge_sort_aux(long nums[], int from, int to, long target[]) {
  if (to - from <= 1) {
    return;
  }

  int mid = (from + to) / 2;

  if (active_threads < thread_count) { 
    //if haven't reached the thread limit then divide the work and create a new thread for one half
    pthread_t thread; 
    sort_args *args = (sort_args*)malloc(sizeof(sort_args));
    assert(args != NULL);
 
    args->nums = target;
    args->from = from;
    args->to = mid;
    args->end = nums;
    
    // increment active_threads
    __sync_fetch_and_add(&active_threads, 1);
    
    // Create thread for left side
    pthread_create(&thread, NULL, thread_merge_sort, args);
    
    // Process right side in current thread
    merge_sort_aux(target, mid, to, nums);
    
    // wait until the left is finished 
    pthread_join(thread, NULL);
    
    // decrement active_threads
    __sync_fetch_and_sub(&active_threads, 1);
  } else {
    // process both halves sequentially in the current thread
    merge_sort_aux(target, from, mid, nums);
    merge_sort_aux(target, mid, to, nums);
  }
  
  merge(nums, from, mid, to, target);
}





/**
 * Sort the given array and return the sorted version.
 *
 * The result is malloc'd so it is the caller's responsibility to free it.
 *
 * Warning: The source array gets overwritten.
 */
long *merge_sort(long nums[], int count) {
  long *result = calloc(count, sizeof(long));
  assert(result != NULL);

  memmove(result, nums, count * sizeof(long));

  merge_sort_aux(nums, 0, count, result);

  return result;
}

/**
 * Based on command line arguments, allocate and populate an input and a 
 * helper array.
 *
 * Returns the number of elements in the array.
 */
int allocate_load_array(int argc, char **argv, long **array) {
  assert(argc > 1);
  int count = atoi(argv[1]);

  *array = calloc(count, sizeof(long));
  assert(*array != NULL);

  long element;
  tty_printf("Enter %d elements, separated by whitespace\n", count);
  int i = 0;
  while (i < count && scanf("%ld", &element) != EOF)  {
    (*array)[i++] = element;
  }

  return count;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <n>\n", argv[0]);
    return 1;
  }

  struct timeval begin, end;

  // get the number of threads from the environment variable SORT_THREADS
  if (getenv("MSORT_THREADS") != NULL)
    thread_count = atoi(getenv("MSORT_THREADS"));

  log("Running with %d thread(s). Reading input.\n", thread_count);

  // Read the input
  gettimeofday(&begin, 0);
  long *array = NULL;
  int count = allocate_load_array(argc, argv, &array);
  gettimeofday(&end, 0);

  log("Array read in %f seconds, beginning sort.\n", 
      time_in_secs(&begin, &end));
 
  // Sort the array
  gettimeofday(&begin, 0);
  long *result = merge_sort(array, count);
  gettimeofday(&end, 0);
  
  log("Sorting completed in %f seconds.\n", time_in_secs(&begin, &end));

  // Print the result
  gettimeofday(&begin, 0);
  print_long_array(result, count);
  gettimeofday(&end, 0);
  
  log("Array printed in %f seconds.\n", time_in_secs(&begin, &end));

  free(array);
  free(result);

  return 0;
}
