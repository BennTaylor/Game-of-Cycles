# Game-of-Cycles

This program is used to analyze the game of cycles, a finite impartial combinatorial game. Game boards (which are planar embeddings of connected graphs) can be encoded by the user and then interpreted by the program. The program then computes the complete game tree of that board, and uses it to assess which player holds a winning strategy from each possible game state. Users can also "play" the game through the terminal, inputting moves by each player and having winning strategy moves displayed to them when available.

### Organization

Here is the meaning of each subdirectory and general organization of the code:
- src/ contains the source code for computations related to the game tree
    - goc_game_tree.h/cpp contain the class responsible for this
    - main.cpp contains the actual calls responsible for output to terminal/file
- GOC_visualizer/ contains the source code for the interactive and visual usage of the code. This portion of the project is implemented with the pygame library (and is a work in progress)
- board_encodings/ contains the .txt file encodings of particular game boards (whose formatting is to be described)
- board_drawings/ contains labeled diagrams of encoded boards (for user reference)
- board_embeddings/ contains the .txt files used by the pygame visualizer for displaying game boards.
- nimber_data/ contains the .txt files containing results of the game tree computation when written to files

### Usage

After cloning the repository into a local directory, users should open their terminal and navigate to the src/ directory. To create the executable, run "make". From this point, users can select any board whose encoding exists under the board_encodings/ directory.
- For output to terminal:
```bash
./main <boardname>_encoding.txt
```
- For output to file:
```bash
./main <boardname>_encoding.txt to_file
```
The to_file prompt will create a file (if it does not already exist) in the nimbers_data/ directory named <boardname>_nimbers.txt. Each line will contain the data of a game state in the following order: Level in the tree (number of edges marked), ternary hash number, nimber (and is space delimited).

### Formatting of Board Encodings

The program's ability to analyze a game board is dependent on an encoding given by the user conveying the necessary structures of the graph; namely, its edge connections and cycle cells. Below is an example to explain this formatting:

Consider the following gameboard:

![wedge4_embedding](https://github.com/BennTaylor/Game-of-Cycles/assets/92824057/74ea60af-8e50-4dc3-b6c0-f79d32d224a8)

The first step is to enumerate the edges and vertices (which should be 0-indexed), such as shown above. With each edge we arbitrarily draw an arrow to indicate the "positive orientation" of that edge. For instance, positive orientation of edge 2 connects vertex 0 to vertex 2.

Next, we write the encoding: The first line is reserved for the name of the game board. The second line stores two integers, the number of vertices and the number of edges. The following line should read "EDGES" to indicate the beginning of the edge information. Each of these lines should represent one edge, written in the order of the previous enumeration. The line should contain two numbers: the numbers of the start vertex then the end vertex (according to the choice of positive orientation on that edge). The line following the last edge should read "CYCLES" to indicate the beginning of the cycle-cell information. Each line of this section encodes a single cycle-cell. The line should include each edge contributing to the cell, space-delimited. Before each edge number should be a '+' or '-' to indicate which orientation of the edge to use. When writing the line for a cell, its perimeter should be "walked" (clockwise or CCW, the choice is arbitrary) and at each edge we choose the orientation which is consistent with our walk.

### Implementation
The motivation to develop this program came from learning of the mex-rule, a computationally exhaustive approach to understanding impartial combinatorial games of perfect information. While effective, I knew it would be computationally expensive as it required complete evaluations of game trees. In fact, my initial approach failed for this reason. The construction of the tree was given recursively: for each state of a game board determine the possible successor states, and then evaluate from those. The trouble arose from the fact the number of distinct play sequences on a given game is enormous (factorial in the number of edges). 

There was a substantial optimization to be made: Memoization. A nice property of this (class of) game is that all information necessary at a given turn is stored in the state of the board alone; i.e. the sequence of moves to get there is irrelevant. With this in mind, we ammend our tree construction to check whether a successor state has already been encountered, in which case we simply link its parent, and otherwise we continue with the usual evaluation. 

The identification of game states relies on a hash function. 
