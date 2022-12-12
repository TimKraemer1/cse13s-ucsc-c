# Assignment 4: The Perambulations of Denver Long

## Function
The purpose of this program is to find the shortest path between a set of locations. Given a number of vertices, a list of locations, and a list of relationships between these locations called edges, our task is to use Depth First Search to find the shortest path that is able to return back to the starting vertice, otherwise known as a Hamiltonian Path. Other options are available such as verbose printing which prints out every path found, the help message, and you can even choose which infile and out file to read/print to.

## How to Compile
To compile with the Makefile, first run:

	$ make clean
to remove any extraneous executables.
Then run:

	$make
to compile the code

## How to Run
Run the code line below:

	$./tsp
with which infile, outfile you want, with verbose, specified undirected/directed for the graph, or a helper menu:

-i	Specifies the infile (stdin by default)\
-o	Specifies the outfile (stdout by default)\
-u	Specifies undirected for the Graph (directed by default)\
-v	Turns on verbose printing\
-h	Displays help message\
