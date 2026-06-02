#include "Trie.hpp"

// TrieNode
TrieNode::TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        children[i] = nullptr;
    }
    isEndOfTitle = false;
    game = nullptr;
}

TrieNode::~TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        delete children[i];
    }
}



// Trie
Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    delete root;
}

bool Trie::insert(Game* game) {
    if (game == nullptr) {
        return false;
    }

    std::string key = toSearchKey(game->title);

    TrieNode* current = root;
    for (char c : key) {
        int i = getIndex(c);
        if (current->children[i] == nullptr) {
            current->children[i] = new TrieNode();
        }
        current = current->children[i];
    }

    current->isEndOfTitle = true;
    current->game = game;
    return true;
}


bool Trie::contains(std::string title) {
    TrieNode* current = root;

    std::string key = toSearchKey(title);
    for (char c : key) {
        int i = getIndex(c);
        if (current->children[i] == nullptr) {
            return false;
        }
        current = current->children[i];
    }

    return current->isEndOfTitle;
}


std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {
    std::vector<Game*> results;

    if (k <= 0) {
        return results;
    }

    std::string key = toSearchKey(prefix);

    TrieNode* current = root;
    for (char c : key) {
        int i = getIndex(c);
        if (current->children[i] == nullptr) {
            return results;
        }
        current = current->children[i];
    }

    getGames(current, results);
    sortResults(results);
    
    if (results.size() > k) {
        results.resize(k);
    }

    return results;
}


std::string Trie::toSearchKey(std::string text) {
    std::string key = "";

    for (char c : text) {
        if (c == ' ') {
            continue;
        }

        // [A-Z] --> [a-z]
        if ('A' <= c && c <= 'Z') {
            c = c + 32;
        }

        if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
            key += c;
        }
    }

    return key;
}

void Trie::sortResults(std::vector<Game*>& games) {
    if (games.empty()) {
        return;
    }

    int size = games.size();
    for (int i = size - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            bool swap = (
                (games[j]->popularity < games[j + 1]->popularity) || 
                (
                    (games[j]->popularity == games[j + 1]->popularity) && 
                    (toSearchKey(games[j]->title) > toSearchKey(games[j + 1]->title))
                )
            );
            
            if (swap) {
                Game* temp = games[j];
                games[j] = games[j + 1];
                games[j + 1] = temp;
            }
        }
    }
}

int Trie::getIndex(char c) {
    if ('a' <= c && c <= 'z') {
        return c - 'a' + 10; // 10-35
    } else if ('0' <= c && c <= '9') {
        return c - '0'; // 0-9
    }

    return -1;
}

void Trie::getGames(TrieNode* node, std::vector<Game*>& results) {
    if (node == nullptr) {
        return;
    }

    if (node->isEndOfTitle) {
        results.push_back(node->game);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        getGames(node->children[i], results);
    }
}
