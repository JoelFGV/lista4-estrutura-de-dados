#include <iostream>
#include <vector>
#include <string>

#include "Trie.hpp"
#include "GamesDatabase.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./app k prefix" << std::endl;
        return 1;
    }

    int k = std::stoi(argv[1]);
    std::string prefix = argv[2];

    Trie trie;

    for (int i = 0; i < numberOfGames; i++) {
        trie.insert(&games[i]);
    }

    std::vector<Game*> results = trie.autocomplete(prefix, k);

    if (results.empty()) {
        std::cout << "No results found" << std::endl;
        return 0;
    }

    for (Game* game : results) {
        std::string description = game->getShortDescription();

        if (description.length() > 80) {
            description = description.substr(0, 80) + "...";
        }

        std::cout
        << game->getTitle() << " | "
        << description << " | "
        << game->getPopularity()
        << std::endl;
    }

    return 0;
}