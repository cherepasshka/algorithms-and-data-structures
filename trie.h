#include <vector>
#include <string>

struct Node {
    std::vector<int> to, go;
    bool is_terminate;
    int parent, suff_link, simb, term_pref;
    Node(int par = -1, int suff = -1, int smb = -1) {
        parent = par, suff_link = suff, simb = smb;
        is_terminate = false;
        term_pref = -1;
        to.assign(2, -1);
        go.assign(2, -1);
    }
};
struct Trie {
    std::vector<Node> array_memory;
    Trie() {
        array_memory = std::vector<Node>(1);
    }
    void add(std::string& s) {
        int v = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (array_memory[v].to[s[i] - '0'] == -1) {
                array_memory.push_back(Node(v, -1, s[i] - '0'));
                array_memory[v].to[s[i] - '0'] = array_memory.size() - 1;
            }
            v = array_memory[v].to[s[i] - '0'];
        }
        array_memory[v].is_terminate = true;
    }
    int get_link(int v) {
        if (array_memory[v].suff_link == -1) {
            if (array_memory[v].parent == 0 || v == 0) {
                array_memory[v].suff_link = 0;
            } else {
                array_memory[v].suff_link = go(get_link(array_memory[v].parent), array_memory[v].simb);
            }
        }
        return array_memory[v].suff_link;
    }
    int go(int v, int simb) {
        if (array_memory[v].go[simb] == -1) {
            if (array_memory[v].to[simb] != -1) {
                array_memory[v].go[simb] = array_memory[v].to[simb];
            } else if (v == 0) {
                array_memory[v].go[simb] = 0;
            } else {
                array_memory[v].go[simb] = go(get_link(v), simb);
            }
        }
        return array_memory[v].go[simb];
    }
    int has_terminal_pref(int v) {
        if (array_memory[v].term_pref == -1) {
            if (array_memory[v].is_terminate) {
                array_memory[v].term_pref = 1;
            } else {
                array_memory[v].term_pref = 0;
                array_memory[v].term_pref += has_terminal_pref(get_link(v));
            }
        }
        return array_memory[v].term_pref;
    }
};