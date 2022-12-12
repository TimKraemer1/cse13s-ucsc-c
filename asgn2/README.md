# Assignment 1 - Slice of Pi

## Function
The purpose of this program is to attempt to make our own Math Library, and compare our approximations with the values of pi and e from the standard C math library. We implemented 6 different functions (e.c, euler.c, madhava.c, bbp.c, viete.c, and sqrtnewton.c), and used those to create a test harness to print and compare each of our pi/e approximations, with the corresponding approximation from the library. The test harness will take as input which test you want to run (be it any of the ones listed above), or test all of them at the same time. You can also add an arguement -s, which will print the number of terms each math function calculated to get to its approximation. 

# How To Compile
To compile with the Makefile, first run:

        $ make clean
to remove any extraneous executables. 
Then run:

	$ make
# How to Run
Run the code line:

        $ ./mathlib-test
with which test(s) you want to run after that 

-a   Runs all tests.\
-e   Runs e test.\
-b   Runs BBP pi test.\
-m   Runs Madhava pi test.\
-r   Runs Euler pi test.\
-v   Runs Viete pi test.\
-n   Runs Newton square root tests.\
-s   Print verbose statistics.\
-h   Display program synopsis and usage.\

To print any new tests, run the command again
