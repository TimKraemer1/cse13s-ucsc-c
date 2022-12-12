# Assignment 1 - Pass the Pigs

## Function
This programs simulates a game of pigs. You play with a number of players from 2 to 10, and you pick a seed for the creation of the random numbers. Each player takes turns rolling the weighted die, called the "pig", and based on how it lands the player gets a certain number of points and gets to roll again, or if it lands on its "side", the player does not get any points and loses their turn. First player at or over 100 points wins. 

The implementation of the enumerated Position type and Position array comes from the assignment document. 

# How To Compile
To compile with the Makefile, run:

	$ make

To compile using the clang command, run:

	$ clang -Wall -wextra -Wpedantic -o pig pig.c

# How to Run
Run the code line:

	$ ./pig

When prompted, enter the number of players between 2 and 10. If number of players is out of range, uses default 2 players instead. 

When prompted, enter the seed that you would like to use between 1 and UINT MAX.
If seed is out of range, it uses a default of 2021 instead. 


