# Advanced Programming Techniques Assignment 2

## Team Name: Advanced Programming Technicians


### Team Structure:

| Name               | Student Number |
|--------------------|----------------|
|Benjamin Speelmeyer |s3729184        |
|Finn Gurry          |s3431331        |
|Matthew Cole        |s3489649        |
|Sarthak Rungta      |s3816605        |

### Note on tests

All tests are written with a specific format in mind. In particular, there are
4 types of input files related to tests:

|File naming convention|Description                                               |
|----------------------|----------------------------------------------------------|
|{TestName}.input      |Main test file to be redirected into standard input       |
|{TestName}.output     |Expected test output                                      |
|{TestName}.expsave    |If test involves saving, this is the file to check against|
|{TestName}_save       |File to load if test loads file                           |

In addition, due to the indeterministic nature of the program, we have altered the
program to take a command line argument, "static", which will cause qwirkle to use
a non-random set of tiles. Tests 5, 7 and 8 are written with this in mind, and will
fail the standard `diff` test unless generated with a static command:

```bash
$./qwirkle "static" < test_5_newgame.input > test_5_newgame.gameout
```

To make this process simpler, we created two bash scripts to automate the testing:

 * run_tests
 * run_tests_static

The first runs the tests and performs the diff check as usual, the second will
run qwirkle with the static command line argument. We hope they are useful.

***run_tests***:
```bash
#!/bin/bash
for f in *.input ; do ./qwirkle < "${f%%.*}.input" > "${f%%.*}.gameout" ; done
for f in *.input ; do echo "${f%%.*} diff:" & diff -w "${f%%.*}.output" "${f%%.*}.gameout" ; done
for f in *.input ; do if [ -e "${f%%.*}.expsave" ] ; then echo "${f%%.*} save diff:" & diff -w "${f%%.*}.expsave" "${f%%.*}.save" ; fi ; done
```

***run_tests_static***:
```bash
#!/bin/bash
for f in *.input ; do if [[ ${f%%.*} == *"new"* ]] ; then ./qwirkle "static" < "${f%%.*}.input" > "${f%%.*}.gameout" ; else ./qwirkle < "${f%%.*}.input" > "${f%%.*}.gameout" ; fi ; done
for f in *.input ; do if [[ ${f%%.*} == *"new"* ]] ; then echo "${f%%.*} diff:" & diff -w "${f%%.*}_static.output" "${f%%.*}.gameout" ; else echo "${f%%.*} diff:" & diff -w "${f%%.*}.output" "${f%%.*}.gameout" ; fi ; done
for f in *.input ; do if [ -e "${f%%.*}.expsave" ] ; then echo "${f%%.*} save diff:" & if [[ ${f%%.*} == *"new"* ]] ; then diff -w "${f%%.*}_static.expsave" "${f%%.*}.save" ; else diff -w "${f%%.*}.expsave" "${f%%.*}.save" ; fi ; fi ; done
```