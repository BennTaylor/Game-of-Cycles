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
     *         board.mex_rule();
     * - To get nimber of specific game state, first determine (manually) its unique hash h, ensuring
     *   consistency w/ encoding of board, then run:
     *         board.nimber_from_hash(h);
     */
    
    // spiral board of 5 nodes
    string f_sp = "../board_encodings/SP5_encoding.txt";
    GOC sp5 = GOC(f_sp);
    sp5.compute_tree();
    sp5.mex_rule_normal();
    sp5.mex_rule_misere();
    sp5.print_info();
    
    // // lemon wedge graph of 3 cells
    // string f_w3 = "../board_encodings/wedge3_encoding.txt";
    // GOC w3 = GOC(f_w3);
    // w3.compute_tree();
    // w3.mex_rule_normal();
    // w3.mex_rule_misere();
    // w3.print_info();

    // // complete graph of three nodes (triangle board)
    // string f_tr = "../board_encodings/K3_encoding.txt";
    // GOC k3 = GOC(f_tr);
    // k3.compute_tree();
    // k3.mex_rule_normal();
    // k3.mex_rule_misere();
    // k3.print_info();
    
    // // complete graph of 4 nodes
    // string f_k4 = "../board_encodings/K4_encoding.txt";
    // GOC K4 = GOC(f_k4);
    // K4.compute_tree();
    // K4.mex_rule_normal();
    // K4.mex_rule_misere();
    // K4.print_info();

    // // sun graph of three outer cells
    // string f_sun3 = "../board_encodings/sun3_encoding.txt";
    // GOC sun3 = GOC(f_sun3);
    // sun3.compute_tree();
    // sun3.mex_rule_normal();
    // sun3.mex_rule_misere();
    // sun3.print_info();

    // // 4-cell lemon wedge
    // string f_wedge4 = "../board_encodings/wedge4_encoding.txt";
    // GOC wedge4 = GOC(f_wedge4);
    // wedge4.compute_tree();
    // wedge4.mex_rule_normal();
    // wedge4.mex_rule_misere();
    // wedge4.print_info();

    // // 5-cell lemon wedge
    // string f_wedge5 = "../board_encodings/wedge5_encoding.txt";
    // GOC wedge5 = GOC(f_wedge5);
    // wedge5.compute_tree();
    // wedge5.mex_rule_normal();
    // wedge5.mex_rule_misere();
    // wedge5.print_info();

    // // 6-cell lemon wedge
    // string f_wedge6 = "../board_encodings/wedge6_encoding.txt";
    // GOC wedge6 = GOC(f_wedge6);
    // wedge6.compute_tree();
    // wedge6.mex_rule_normal();
    // wedge6.mex_rule_misere();
    // wedge6.print_info();

    // // 7-cell lemon wedge
    // string f_wedge7 = "../board_encodings/wedge7_encoding.txt";
    // GOC wedge7 = GOC(f_wedge7);
    // wedge7.compute_tree();
    // wedge7.mex_rule_normal();
    // wedge7.mex_rule_misere();
    // wedge7.print_info();
}