Week 1 & 2 (11/8 - 11/21) Finalized Proposal and Team Contract. Worked on planning graph structure and work logistics. Designed implementation of graph such that airport IDs would correspond to the adjacency vector node ids as to allow for O(1) node find times. To do this, we studied the dataset for possible methods of seperating and storing the useful data from the less useful data as well as possible ways to arrange the data within the project. 

Week 3 & 4 (11/22 - 12/5) Organized project folder to contain separate folders for testcases, datasets and other files. After noticing irregularities with how our testcases worked with our datasets, we processed our datasets to remove all quotation marks as they interfered with checking for strings. We noticed several inconsistiencies in the dataset and began drafting plans for how to handle these inconsistiences when parsing the data. Finished template of project(MAKEFILE and testing suite working), Finished parsing of data. For the parsing of data, we developed a way to parse each data file line by line until we were able to get a vector of vector strings in order to have every single word be an entry in the veGraphing and edges half done.

Week 5 (12/6-12/12) Graph implementation, DFS, Dijkstra's complete. Testcases for each of these algorithms have been implemented but may not cover all possible edge cases. Realized that Tarjan does not work properly with the DFS implemented.  Might have to change the DFS or abort on the Tarjan's developemnt. 

Week 6 (12/13): Posted video(.mp4), README.md, GOALS.md, RESULTS.pdf. Final edge cases have been fixed for invalid nodes. DFS and Dijkstra's fully functional. Tarjan's algorithm is implemented but does not fully work. Due to the possibility of segmentation faults and endless loops with certain inputs, testcases and main function uses of Tarjan's algorithm have been commented out or deleted. Finalized test cases with complex and edges cases. Code and comments cleaned up. Main file edited to take in user inputs and print out data in human readable way. 
