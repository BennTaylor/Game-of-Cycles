#include <vector>
#include <string>
#include <iostream>

#include "goc_game_tree.h"


using namespace std;

int main(int argc, char** argv) {
    /*
     * GENERAL PROCEDURE FOR ANALYSIS OF GAMEBOARD
     * - add board_encoding.txt file for specific board to board_encodings directory following
     *    specified formatting
     * - run following to initialize GOC object w/ necessary specifications outlines in the encoding:
     *         string filename = "../board_encoding/board_encoding.txt";
     *         GOC board = GOC(filename);
     * - Before anything, gametree should be built by running:
     *         board.compute_tree();
     * - To compute nimbers, run:
     *         board.mex_rule_normal();
     *         board.mex_rule_misere();
     * - To get nimber of specific game state, first determine (manually) its unique hash h, ensuring
     *   consistency w/ encoding of board, then run:
     *         board.hash_to_norm_nimber(h);
     *         board.hash_to_mis_nimber(h);
     */

    if (argc == 1) {
        cout << "Invalid Input. Enter the name of any board encoding file existing under the board_encodings directory." << endl;
        cout << "Example input: ./main K4_encoding.txt" << endl;

        return 0;
    } else if (argc ==2) {
        string encoding_file = "../board_encodings/";
        encoding_file += argv[1];

        GOC board = GOC(encoding_file);
        board.compute_tree();
        board.mex_rule_normal();
        board.mex_rule_misere();
        board.print_info();

        cout << "Initiate game on " << board.name() << " board?";
        cout << "Enter '1' for normal play, '0' for misere play, anything else to stop: ";
        string cont = "NO";
        cin >> cont;
        cout << endl;

        while (cont == "0" || cont == "1") {
            bool normal_play = false;
            if (cont=="1")
                normal_play = true;
            board.play_game(normal_play);

            cout << "Initiate game on " << board.name() << " board?" << endl;
            cout << "Enter '1' for normal play, '0' for misere play, anything else to stop: ";
            cin >> cont;
            cout << endl;
        }
    } else if (strcmp(argv[2],"to_file")==0) {
        string encoding_file = "../board_encodings/";
        encoding_file += argv[1];

        GOC board = GOC(encoding_file);
        board.compute_tree();
        board.mex_rule_normal();
        board.mex_rule_misere();
        
        board.nimbers_to_file();
    }
}