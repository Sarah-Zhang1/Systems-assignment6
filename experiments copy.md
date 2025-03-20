# Threaded Merge Sort Experiments


## Host 1: Macbook Pro

- CPU: 12 Core
- Cores: 12
- Cache size (if known):
- RAM: 32 GB
- Storage (if known): 1 TB
- OS: MacOS

### Input data
The dataset that I created is 101 million random integers. This data was created via running this command in terminal: `shuf -i1-101000000 > hundred-one-million.txt`. It took `msort` 11.016879 seconds to read the dataset and 26.042496 seconds to sort the dataset. 

### Experiments

#### 1 Thread

Command used to run experiment: `MSORT_THREADS=1 ./tmsort 101000000 < hundred-one-million.txt > /dev/null`

Sorting portion timings:

1. 25.709322 seconds
2. 26.117240 seconds
3. 26.403984 seconds
4. 26.491595 seconds

#### 2 Threads

Command used to run experiment: `MSORT_THREADS=2 ./tmsort 101000000 < hundred-one-million.txt > /dev/null`

Sorting portion timings:

1. 14.053977 seconds
2. 13.383095 seconds
3. 14.370194 seconds
4. 13.769796 seconds

#### 12 Threads

Command used to run experiment: `MSORT_THREADS=12 ./tmsort 101000000 < hundred-one-million.txt > /dev/null`

Sorting portion timings:

1. 5.122719 seconds
2. 5.676841 seconds
3. 5.498719 seconds
4. 5.320842 seconds


#### 24 Threads

Command used to run experiment: `MSORT_THREADS=24 ./tmsort 101000000 < hundred-one-million.txt > /dev/null`

Sorting portion timings:

1. 5.881560 seconds
2. 5.361372 seconds
3. 6.995410 seconds
4. 8.378426 seconds



## Host 2: VMware Fusion

- CPU: 2 Core 
- Cores: 2
- Cache size (if known):
- RAM: 3.8 GiB
- Storage (if known): 
- OS: Linux Ubuntu

### Input data

The dataset that I created is 101 million random integers. This data was created via running this command in terminal: `shuf -i1-101000000 > hundred-one-million.txt`. It took `msort` 11.016879 seconds to read the dataset and 26.042496 seconds to sort the dataset. 

### Experiments

#### X Threads

Command used to run experiment: ``

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

#### Y Threads

Command used to run experiment: ``

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

#### Z Threads

Command used to run experiment: ``

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds


## Observations and Conclusions

*Reflect on the experiment results and the optimal number of threads for your concurrent merge sort implementation on different hosts or platforms. Try to explain why the performance stops improving or even starts deteriorating at certain thread counts.*



