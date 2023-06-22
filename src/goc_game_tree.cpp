#include "goc_game_tree.h"

GOC::GOC(string& encoding_file_path) {
    cout << "reading encoding..." << endl;
    // read in encoding
    fstream board_encoding(encoding_file_path, ios::in);
    string line;

    // check file opens
    if (!board_encoding.is_open()) {
        throw invalid_argument("Unable to open " + encoding_file_path);
    }

    // read in number nodes/edges
    getline(board_encoding, line);
    board_name_ = line;

    getline(board_encoding, line);
    pair<short int, short int> p = edges_parser(line);
    edges_ = vector<pair<short int,short int>>();
    vertex_degrees_ = vector<short int>(p.first);

    // formatting check
    getline(board_encoding, line);
    if (line != "EDGES") {
        throw invalid_argument("Incorrect formatting.");       
    }   

    // load edges 
    getline(board_encoding, line);
    while (line != "CYCLES") {
        p = edges_parser(line);
        edges_.push_back(p);
        vertex_degrees_[p.first]++;
        vertex_degrees_[p.second]++;

        getline(board_encoding, line);
    }
    
    // load cycle cells
    while(getline(board_encoding, line)) {
        vector<pair<short int, bool>> cycle = cycles_parser(line);
        cycle_cells_.push_back(cycle);
    }

    cout << "...game board initialized\n" << endl;
}

void GOC::compute_tree() {
    cout << "computing game tree..." << endl;

    num_end_states_ = 0;
    p1_wins_ = 0;
    p2_wins_ = 0;

    head_ = new Node(State());
    head_->state.markings = vector<short int>(edges_.size());
    head_->state.outgoing_edges = vector<short int>(vertex_degrees_.size());
    hash_to_node_[0] = head_;
    
    compute_descendants(head_);

    cout << "...tree initialized\n" << endl;
}

void GOC::compute_descendants(Node* n) {
    set<pair<short int, bool>> next_moves = legal_moves(n->state);
    // quick for board w/ no remaining moves and update game_over flag
    if (next_moves.empty()) {
        n->state.game_over = true;
    }
    // check for end states
    if (n->state.game_over) {
        num_end_states_++;
        
        if (n->state.turn % 2 == 0) {
            p2_wins_++;
        } else {
            p1_wins_++;
        }

        return;     // no descendants
    }

    // n is an internal state: for each available move check the resulting state...
    for (auto move : next_moves) {
        int h = n->state.hash;
        
        // find h corr. with resulting state
        if (move.second) {  // positive orientation
            h += pow(3,move.first);
        } else {            // negative orientation
            h += 2*pow(3,move.first);
        }

        // if h already exists in tree, link it
        if (hash_to_node_.find(h) != hash_to_node_.end()) {
            n->children.push_back(hash_to_node_[h]);
            continue;
        }

        // h does not exist so new state should be created and eval'd from
        State next_state = n->state;
        take_turn(move, &next_state);
        Node* child = new Node(next_state);
        // insert into tree and map
        n->children.push_back(child);
        hash_to_node_[h] = child;
        //recurse
        compute_descendants(child);
    }
}

set<pair<short int, bool>> GOC::legal_moves(State s) {
    if (s.game_over) {
        return set<pair<short int, bool>>();
    }

    set<pair<short int, bool>> moves = set<pair<short int, bool>>();
    for (int i = 0; i < int(edges_.size()); i++) {
        // check if already marked
        if (s.markings[i] != 0) {
            continue;
        }
        short int u = edges_[i].first;
        short int v = edges_[i].second;
        // check legality of positive orientation
        if (s.outgoing_edges[u] != vertex_degrees_[u]-1 &&
            s.outgoing_edges[v] != -(vertex_degrees_[v]-1)) {
            moves.insert(pair<short int, bool>(i,true));
        }
        // check legality of negative orientation
        if (s.outgoing_edges[u] != -(vertex_degrees_[u]-1) &&
            s.outgoing_edges[v] != vertex_degrees_[v]-1) {
            moves.insert(pair<short int, bool>(i,false));
        }
    }

    return moves;
}

void GOC::take_turn(pair<short int, bool> t, State* s) {
    if (s->markings[t.first] != 0) {    // check bad input (error w/ legal moves)
        throw invalid_argument("Not a legal turn.");
    }

    // add edge marking
    if (t.second) {
        s->markings[t.first] = 1;
    } else {
        s->markings[t.first] = -1;
    }

    // update vertex degrees
    short int u = edges_[t.first].first;
    short int v = edges_[t.first].second;
    if (t.second) {    // positive orientation
        s->outgoing_edges[u]++;
        s->outgoing_edges[v]--;
    } else {           // negative orientation
        s->outgoing_edges[u]--;
        s->outgoing_edges[v]++;
    }

    // check for cycle creation
    if (cell_cycled(s)) {
        s->game_over = true;
    }
    // update hash and num turns
    // find h corr. with resulting state
    if (t.second) {  // positive orientation
        s->hash += pow(3,t.first);
    } else {            // negative orientation
        s->hash += 2*pow(3,t.first);
    }

    s->turn++;
}

bool GOC::cell_cycled(State* s) {
    // flag for cycle direction

    // check each cycle
    for (auto cycle : cycle_cells_) {
        int length = cycle.size();  // total cycle length
        int k = 0;                  // length seen so far that's marked

        for (auto cyc_edge : cycle) {
            int e = cyc_edge.first;

            if (s->markings[e] == 0) { // unmarked cell in cycle
                break;
            }

            if ((cyc_edge.second && s->markings[e]==1) || 
                ((!cyc_edge.second && s->markings[e]==-1))) { // pos. cycle orien.
                k++;
            } else {                                          // neg. cycle orien.
                k--;
            }
        }
        if (abs(k) == length) {     // cell completed with alligned orientation
            return true;
        }
    }

    return false;
}

void GOC::mex_rule_normal() {
    cout << "computing nimbers (normal play)..." << endl;

    Node* root = head_;
    // using dequeue (double-ended queue) impl. of reverse level order trav.
    stack<Node*> s;
    queue<Node*> q;

    map<Node*, bool> seen_node;

    q.push(root);
    seen_node[root] = true;
    
    // traverse nodes in level order, pushing to stack as they are seen...
    while (!q.empty()) {
        root = q.front();
        q.pop();
        s.push(root);
        
        for (auto child : root->children) {
            if (seen_node.find(child) == seen_node.end()) {
                seen_node[child] = true;
                q.push(child);
            }
        }
    }
    // ...then reverse level order trav. is done by popping from stack
    while (!s.empty()) {
        root = s.top();

        // compute mex here
        if (root->state.game_over) {
            node_to_norm_nimber_[root] = 0;
        } else {
            int n = root->children.size();
            // mex is at most n; vector stores whether numbers less than n included in nimbers of children
            vector<bool> seen = vector<bool>(n+1);

            for (auto child : root->children) {
                if (node_to_norm_nimber_[child] < n) {
                    seen[node_to_norm_nimber_[child]] = true;
                }
            }
            // find mex
            for (int i = 0; i<=n; i++) {
                if (!seen[i]) {
                    node_to_norm_nimber_[root] = i;
                    break;
                }
            }
        }

        s.pop();
    }

    cout << "...nimbers evaluated\n" << endl;
}

void GOC::mex_rule_misere() {
    cout << "computing nimbers (misere play)..." << endl;

    Node* root = head_;
    // using dequeue (double-ended queue) impl. of reverse level order trav.
    stack<Node*> s;
    queue<Node*> q;

    map<Node*, bool> seen_node;

    q.push(root);
    seen_node[root] = true;
    
    // traverse nodes in level order, pushing to stack as they are seen...
    while (!q.empty()) {
        root = q.front();
        q.pop();
        s.push(root);
        
        for (auto child : root->children) {
            if (seen_node.find(child) == seen_node.end()) {
                seen_node[child] = true;
                q.push(child);
            }
        }
    }
    // ...then reverse level order trav. is done by popping from stack
    while (!s.empty()) {
        root = s.top();

        // compute mex here
        if (root->state.game_over) {
            node_to_mis_nimber_[root] = 1;
        } else {
            int n = root->children.size();
            // mex is at most n; vector stores whether numbers less than n included in nimbers of children
            vector<bool> seen = vector<bool>(n+1);

            for (auto child : root->children) {
                if (node_to_mis_nimber_[child] < n) {
                    seen[node_to_mis_nimber_[child]] = true;
                }
            }
            // find mex
            for (int i = 0; i<=n; i++) {
                if (!seen[i]) {
                    node_to_mis_nimber_[root] = i;
                    break;
                }
            }
        }

        s.pop();
    }

    cout << "...nimbers evaluated\n" << endl;
}

int GOC::hash_to_norm_nimber(int h) {
    if (hash_to_node_.find(h)==hash_to_node_.end() || node_to_norm_nimber_.find(hash_to_node_[h])==node_to_norm_nimber_.end()) {
        return -1;
    }

    return node_to_norm_nimber_[hash_to_node_[h]];
}

int GOC::hash_to_mis_nimber(int h) {
    if (hash_to_node_.find(h)==hash_to_node_.end() || node_to_mis_nimber_.find(hash_to_node_[h])==node_to_mis_nimber_.end()) {
        return -1;
    }

    return node_to_mis_nimber_[hash_to_node_[h]];
}

void GOC::play_game(bool normal_play) {
    // intended for use w/ knowledge of n and p positions
    if ((normal_play && node_to_norm_nimber_.empty()) || 
        (!normal_play && node_to_mis_nimber_.empty())) {
        throw invalid_argument("Nimbers not yet calculated.");
    }

    cout << "---------------------------- Game of Cycles on " << board_name_ << " Board ----------------------------" << endl;
    if (normal_play) {
        cout << "** Normal play style **\n" << endl;
    } else {
        cout << "** Misere play style **\n" << endl;
    }

    State game = State();
    game.markings = vector<short int>(edges_.size());
    game.outgoing_edges = vector<short int>(vertex_degrees_.size());

    set<pair<short int, bool>> avail_moves = legal_moves(game);

    while (!game.game_over && !avail_moves.empty()) {
        // display info of game state to console
        cout << "Turn " << game.turn+1 << ", ";
        if (game.turn%2 == 0) {
            cout << "player 1's move:" << endl;
        } else {
            cout << "player 2's move:" << endl;
        }
        cout << "moves written as (edge, orientation), 0 = - & 1 = +" << endl;
        cout << "Available moves:     ";
        print_moves(avail_moves);
        cout << "Moves to p-position: ";
        print_moves(p_moves(game, normal_play));

        // get player's move
        short int e;    // edge
        bool o;         // orientation
        cout << "edge:        ";
        cin >> e;
        cout << "orientation: ";
        cin >> o;

        pair<short int, bool> m = pair<short int, short int>(e,o);
        bool legal = (avail_moves.find(m)!=avail_moves.end());
        // retry input if not a legal move
        while(!legal) {
            cout << "Not a legal move. Try again:" << endl;
            cout << "edge:        ";
            cin >> e;
            cout << "orientation: ";
            cin >> o;

            m = pair<short int, short int>(e,o);
            legal = (avail_moves.find(m)!=avail_moves.end());
        }
        cout << endl;

        // update game state w/ player's move
        take_turn(m, &game);

        avail_moves = legal_moves(game);
    }

    cout << "*** GAME OVER ***" << endl;
    cout << "edges marked: " << game.turn << endl;
    cout << "winner: ";
    if ((normal_play && game.turn%2==0) ||
        (!normal_play && game.turn%2==1)) {
        cout << "player 2" << endl;
    } else {
        cout << "player 1" << endl;
    }
    cout << endl;

}

set<pair<short int, bool>> GOC::p_moves(State s, bool normal_play) {
    set<pair<short int, bool>> p_moves;
    int h = s.hash;
    for (auto child_node : hash_to_node_[h]->children) {
        State child_state = child_node->state;
        if ((normal_play && hash_to_norm_nimber(child_state.hash)==0) ||
            (!normal_play && hash_to_mis_nimber(child_state.hash)==0)) {
            p_moves.insert(hash_to_move(child_state.hash - h));
        }
    }
    return p_moves;
}

pair<short int, bool> GOC::hash_to_move(int h) {
    short int e = 0;
    while (h>=3) {
        h /= 3;
        e++;
    }
    if (h==1) {     // pos. orientation
        return pair<short int, bool>(e, true);
    } else {        // neg. orientation
        return pair<short int, bool>(e, false);
    }
}

void GOC::print_moves(set<pair<short int, bool>> moves) {
    if (moves.empty()) {
        cout << "...no moves available...";
    }
    for (auto move : moves) {
        cout << "(" << move.first << ", " << move.second << ") ";
    }
    cout << endl;
}

pair<short int, short int> GOC::edges_parser(string& l) {
    pair<short int, short int> p = pair<short int, short int>();

    string curr = "";
    for (unsigned int i = 0; i<l.length(); i++) {
        if (!isdigit(l[i]) && l[i]!=' ') {
            throw invalid_argument("Bad encoding formatting.");
        }

        if (l[i]==' ') {
            p.first = stoi(l.substr(0,i));
            p.second = stoi(l.substr(i+1, l.length()-i-1));
        }
    }

    return p;
}

vector<pair<short int, bool>> GOC::cycles_parser(string& l) {
    vector<pair<short int, bool>> cycle = vector<pair<short int, bool>>();
    
    string curr = "";
    pair<short int,bool> p = pair<short int,bool>();
    for (unsigned int i = 0; i<l.length(); i++) {
        // end of entry
        if (l[i] == ' ') {
            p.first = stoi(curr);
            cycle.push_back(p);
            curr = "";
            continue;
        }
        // orientation marker
        if (l[i] == '+') {
            p.second = true;
            continue;
        } else if (l[i] == '-') {
            p.second = false;
            continue;
        }
        // digits
        if (!isdigit(l[i])) {
            throw invalid_argument("Bad encoding formatting.");
        }
        curr += l[i];
    }
    p.first = stoi(curr);
    cycle.push_back(p);

    return cycle;
}

void GOC::print_info() {
    // DISPLAY BOARD INFO
    cout << "------------ " << board_name_ << " Game of Cycles ------------ " << endl;
    cout << "BOARD INFO" << endl;
    cout << "#vertices = " << vertex_degrees_.size() 
         << ", #edges = " << edges_.size() 
         << ", #cycle-cells = " << cycle_cells_.size() << endl;
    cout << "edges:" << endl;
    for (auto edge : edges_) {
        cout << "(" << edge.first << ", " << edge.second << ")" << endl;
    }
    cout << "cycle-cells:" << endl;
    for (auto cycle : cycle_cells_) {
        for (auto p : cycle) {
            if (p.second == true) {
                cout << "+" << p.first << " ";
            } else {
                cout << "-" << p.first << " ";
            }
        }
        cout << endl;
    }
    cout << endl;

    if (head_ == NULL) {            // gametree not built
        cout << "* Game tree not yet initialized *\n" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        return;
    }
    // DISPLAY TREE INFO
    cout << "COMPLETE GAMETREE" << endl;
    cout << "total game states: " << hash_to_node_.size() <<endl;
    cout << "total end sates: " << num_end_states_ << endl;
    cout << "player 1 wins: " << p1_wins_ << endl;
    cout << "player 2 wins: " << p2_wins_ << endl;

    cout << endl;

    if (node_to_norm_nimber_.empty()) { // nimbers not calculated
        cout << "* Misere play nimbers not yet evaluated *\n" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        return;
    }
    // DISPLAY NIMBER INFO
    cout << "NIMBERS CALCULATION (NORMAL PLAY):" << endl;
    int head_nimber = node_to_norm_nimber_[head_];
    cout << "The initial (empty) gameboard has nimber " << head_nimber << " and is therefore ";
    if (head_nimber == 0) {     // head is p-position
        cout << "a p-position,\nso player 2 holds a winning stategy on the " << board_name_ << " gameboard.\n" << endl;
    } else {                    // head is n-position
        cout << "an n-position,\nso player 1 holds a winning stategy on the " << board_name_ << " gameboard.\n" << endl;
    }

    if (node_to_mis_nimber_.empty()) { // nimbers not calculated
        cout << "* Normal play nimbers not yet evaluated *\n" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        return;
    }
    cout << "NIMBERS CALCULATION (MISERE):" << endl;
    head_nimber = node_to_mis_nimber_[head_];
    cout << "The initial (empty) gameboard has nimber " << head_nimber << " and is therefore ";
    if (head_nimber == 0) {     // head is p-position
        cout << "a p-position,\nso player 2 holds a winning stategy on the " << board_name_ << " gameboard.\n" << endl;
    } else {                    // head is n-position
        cout << "an n-position,\nso player 1 holds a winning stategy on the " << board_name_ << " gameboard.\n" << endl;
    }

    cout << "-------------------------------------------------------------------------------" << endl;
}