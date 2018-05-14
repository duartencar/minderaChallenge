# Mindera Graduate Program 

## Challenge B - Adjacent Cells

### Challenge info
https://minderacraft.workable.com/jobs/490096
https://docs.google.com/document/d/1voZP8HOmUMy19CKTOq8mZcZRW8bF2lfAT8uqIouZ400/edit

### Compile

```
cd ./src
make 
```

### Run

```
./minderaChallenge.out [fileToTest]
```

#### fileToTest must be in ../resources/ directory

### Run options

The program will ask you if you want to print groups at the end of execution. if you select this option performance is very good, but it consumes a lot of memory. Otherwise, it will consume much less memory, because the groups will be printed has they are found and memory is cleaned immediately, but performance is much worse. this is show in the next table:

|| Execution time (s) | Memory Consumed (Gb) |
| ------------- | ------------- | ------------- |
| Print at end  | 29 | 5.3 |
| Print as it finds  | 77 | 1,1 |

The 20000x20000.json test file was used to get this numbers, results will be different in other machines.
