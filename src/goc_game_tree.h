#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <stdexcept>
#include <cmath>


using namespace std;

class GOC {
public:
    /*
     * Constructor:
     * Processes graph encoding and initializes edges and cycle cells.
     * Creates head of tree (empty board); does not begin tree computation.
     */
    GOC(string& encoding_file_path);

    /*
     * Builds out game tree for specific board.
     */
    void compute_tree();

    /*
     * Uses mex rule to compute n/p-positions of board with normal play.
     */
    void mex_rule_normal();

    /*
     * Uses mex rule to compute n/p-positions of board with misere play.
     */
    void mex_rule_misere();

    /*
     * Returns the number calculated by mex_rule() corr. w/ the unique hash of a game state (normal play).
     */
    int hash_to_norm_nimber(int h);

    /*
     * Returns the number calculated by mex_rule() corr. w/ the unique hash of a game state (misere play).
     */
    int hash_to_mis_nimber(int h);

    /*
     * For user play through console;
     * attempts to move plyr1 (or plyr2 if p1==false) to p-positions
     * given other players' moves.
     */
    // void decision_maker(bool p1);

    /*
     * Displays analysis to terminal.
     * Shows board info, game tree info, and nimber info
     */
    void print_info();

    /*
     * Allows for play of game through terminal.
     * Intended to track winning strategy for player with advantage.
     * .....more things....
     */
    void play_game(bool normal_play);

    string name() { return board_name_; }

private:
// structs
    /*
     * Represents a particular game state.
     */
    struct State {
        /*
         * Counts the number of markings made on the board so far.
         */ 
        short int turn;

        /*
         * Boolean flag indicating whether a game is in a final state.
         */
        bool game_over;

        /*
         * Unique integer associated with current game state.
         */
        int hash;

        /*
         * Stores edge marking info: 
         * 0=unmarked; 1=positive orientation; -1=negative orientation
         * Note: choice of orientation is arbitrary but should be consistent with encoding
         */
        vector<short int> markings;

        /*
         * For sink/source checking:
         * vertex_degrees_[i]=(n,k) means node i has degree n in the underlying graph.
         * If the marking u->v is illegal then either a) u is an almost-source or b) v is an almost-sink.
         * a) then vertex_degrees_[u] = n-1
         * b) then vertex_degrees[v] = -(n-1)
         * outgoing edges add 1 to the second value; incoming edges subtract 1
         */
        vector<short int> outgoing_edges;

        State() : turn(0), game_over(false), hash(0), 
                  markings(vector<short int>()), outgoing_edges(vector<short int>())
                  { /* nothing */ }
    };

    /*
     * Node in game tree.
     */
    struct Node {   
        State state;
        vector<Node*> children;

        Node(State s) : state(s), children(vector<Node*>()) { /* nothing */ }
    };

// helper functions
    /*
     * For reading board encoding files.
     */
    pair<short int, short int> edges_parser(string& line);
    vector<pair<short int, bool>> cycles_parser(string& line);

    /*
     * Recursively computes game tree headed at given node.
     */
    void compute_descendants(Node* n);

    /*
     * Returns a set of all legal moves from a given game state.
     * Each element of the set of pairs represents the edge and the orientation to be marked.
     */
    set<pair<short int, bool>> legal_moves(State s);

    /*
     * Updates game state according to move t.
     * Checks for cycles after move.
     * Updates hash.
     * Does not check whether no legal turns remain (avoids redundant work in game tree where it is curr. checked).
     */
    void take_turn(pair<short int, bool> t, State* s);

    /*
     * Checks if a cycle cell exists on the board.
     */
    bool cell_cycled(State* s);

    /*
     * Displays given moves to console.
     * Used by play_game.
     */
    void print_moves(set<pair<short int, bool>> moves);

    /*
     * Returns set of moves to a game state which is a p-position.
     * Looks at nimbers of child states of s in game tree.
     * normal_play = true means normal nimbers used; false meanse misere nimbers used.
     */
    set<pair<short int, bool>> p_moves(State s, bool normal_play);

    /*
     * Helper for p_moves.
     * Given the difference in hashes between a game state and a child state, the corr. move is returned as a pair.
     */
    pair<short int, bool> hash_to_move(int h);

// member vars
    /*
     * Name used to identify game board.
     */
    string board_name_;

    /*
     * Stores edges:
     * e[i]=(u,v) means e_i with positive orientation connects u to v,
     * conversely negative orientation connects v to u
     */
    vector<pair<short int, short int>> edges_;

    /*
     * Stores cells on board and their orientation.
     * Each entry represents a cell. An entry of [(1,T),(3,T),(4,F),(2,T)] would indicate a 
     * cycle cell corr. w/ edges 1,3,2 oriented positively, and 4 oriented negatively.
     */
    vector<vector<pair<short int,bool>>> cycle_cells_;

    /*
     * Degree of vertices in underlying graph.
     * For sink/source checking; compare with state variable source_count
     */
    vector<short int> vertex_degrees_;

    /*
     * Stores root of tree (empty gameboard).
     */
    Node* head_;

    /*
     * Basic tree info.
     */
    int num_end_states_;
    int p1_wins_;
    int p2_wins_;

    /*
     * For memoization:
     * Maps unique board state identifier to its corr. node, if its been initialized
     */
    map<int, Node*> hash_to_node_;

    /*
     * For mex rule.
     * Stores nimbers for calculating n/p-positions (normal play).
     */
    map<Node*, int> node_to_norm_nimber_;

    /*
     * For mex rule.
     * Stores nimbers for calculating n/p-positions (misere play).
     */
    map<Node*, int> node_to_mis_nimber_;
};