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


### Implementation
