This project's aim was to find the shortest path between 2 airports and find the most important airport

VIDEO PRESENTATION included on github as an .mp4 file.

PDF LINK: https://docs.google.com/document/d/1h8fJJY22mGeHiCUCbYTy9_dzX1fS910ljpvTT_hoMr0/edit

Note: All development commits have been made on the temp_dan branch. Only our proposal and final commits are made to the main branch.

The project has the main files:

main.cpp - This is where we will output our desired data in sentences
test.cpp - This is our test suite
readFromFile.cpp - This file contains code that helps parse the data 
graph.cpp - This file cointains code that creates nodes and edges to form a graph
DFS.cpp - This file contains code that traverses the graph to find the distance between 2 desired airports
Dijkstra's - This file contains code that find the shortest path between 2 desired airports
Tarjan's - This file contains the code the loop detection for the paths

How to run files
To run the full project:
1. Compile using "make" in terminal
2. ./finalproj
3. User will be prompted to input 2 airport IDs (start and end)
4. The terminal will output information (if error due to routes not existing)

Notes: 
This code is used with the openflights data: (https://openflights.org/data.html (but dataset has been edited to remove quotations marks)
If you want to use your own dataset please put your dataset (quotation marks removed) and go to main.cpp to change the filename in lines 29 and 30.


To run the test suite:
1. Compile using "make test" in terminal
2. ./tests

Notes: 
There are unit tests for some individual functions
We use both the datasets from the file data (data/filename.dat) and tests(tests/filename.dat).
data contains the full dataset from openflights with removed "" (quotation marks)
tests contains small unit tests to test for exceptions or if basic functionality works (you can copy paste desired lines from data)
You can refer to the tests.cpp file in test to view individual tests (each has comments on what is exactly being tested)



