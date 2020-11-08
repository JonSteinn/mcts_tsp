# mcts_tsp

## Build
```sh
make -C src
```

## Run and arguments
There are 3 arguments available,
  * `-a <value>` for algorithm
  * `-f <value>` for file
  * `-t <value>` for time
Below is an example.
```sh
./src/main.exe -a 0 -t 5 -f data/tour001.txt
```
The algorithms available are
  0. MCTS
  1. Greedy (shortest next)

## Test data
The data is from http://www.math.uwaterloo.ca/tsp/data/index.html. It is in the following format.
```
<length of optimal tour>
<number of data points>
<space seperator coordinates for data point 1>
<space seperator coordinates for data point 2>
<space seperator coordinates for data point 3>
...
```
