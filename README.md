# University Mark Estimation | c-marks-estimation
> Created by Nicholas Ramsay

This project stores marks attained and marks estimated for university subjects in a binary file and provides utilities for interacting with said file. This project is designed to help me predict marks before the end of my university semesters. It has been written in C for three primary reasons: 
1. In order to practice builing software in C, which is different from most other development experiences; 
2. C is suitable for binary file interaction; and
3. C is suitable for memory management, thus leaving a small memory footprint in the running of the program.

## Building and Execution
```
make all
cd dist
./main
```

## Todo
* remove stdio.h includes in files that don't need it for non-debugging use
* handle arg options
* change name from array to char pointer in other files
* check for memory leaks
* print table formatted subject details
* subject of name "list" should be disallowed
* estimation of name "default" should be disallowed


