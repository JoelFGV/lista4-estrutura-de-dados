#ifndef TRIE_HPP
#define TRIE_HPP

#include <vector>
#include <string>

#include "Game.hpp"

const int ALPHABET_SIZE = 36; // [0-9] + [a-z]

class TrieNode {

public:

    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfTitle;
    Game* game;

    TrieNode();
    ~TrieNode();
};

class Trie {

private:

    TrieNode* root;

public:

    Trie();
    ~Trie();

    bool insert(Game* game);
    bool contains(std::string title);

    std::vector<Game*> autocomplete(std::string prefix, int k);

    std::string toSearchKey(std::string text);
    void sortResults(std::vector<Game*>& games);

    // Outros métodos auxiliares, se necessário
    int getIndex(char c);
    void getGames(TrieNode* node, std::vector<Game*>& results);
};

#endif