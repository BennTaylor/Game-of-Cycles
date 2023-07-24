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
  
    ./main boardname_encoding.txt

- For output to file:
  
    ./main boardname_encoding.txt to_file

### Formatting of Board Encodings


### Implementation
