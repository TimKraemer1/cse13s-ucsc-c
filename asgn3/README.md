# Assignment 3 - Sorting - Putting your Affairs in Order
  
## Function
The purpose of this program is to test out different sorting algorithms, and compare them with different parameters such as size of array to be sorted, seed for randomness of array values, etc to see which sorting algorithms fare better than the others depending on these set parameters. This program also is a way to improve our understanding and implementation of pointers, structures, and ADTs. When running the program, a variety of inputs ara available to choose from to specify what you want printed. Options include: which sort(s) you want run, what seed you want for the randomness of the unsorted lost, how many elements you want printed after it was sorted, how many elements you want included in your unsorted list, and also you have the option to print a help output, which tells the person running the program which inputs are available, what each do and what arguements are needed for the inputs if necessary.

# How To Compile
To compile with the Makefile, first run:

        $ make clean
to remove any extraneous executables.
Then run:

        $ make
# How to Run
Run the code line:

        $ ./sorting
with which test(s) and settings you want to run after that in the manner shown below:

-a   Runs all of the sorts.\
-e   Runs the Heap sort.\
-i   Runs the Insertion sort.\
-s   Runs the Shell sort.\
-q   Runs the Quick sort.\
-r   Sets the seed to be used for the random array. Default: 13371453.\
-n   Sets the length of the array. Default: 100.\
-p   Sets the number of printed elements. Default: 100. (If number specified larger than length of array, all elements in array will be printed.\
-h   Display help message.\

To print any new tests or change any of the settings, run the command again with the preferred test and/or settings.
