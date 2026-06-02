#include <string>

#include "Game.hpp"

Game::Game() 
    : title(""), 
      shortDescription(""), 
      popularity(0) {}

Game::Game(std::string title, std::string shortDescription, int popularity) 
    : title(title),
      shortDescription(shortDescription),
      popularity(popularity) {}

Game::~Game() {}


std::string Game::getTitle() {
    return title;
}

std::string Game::getShortDescription() {
    return shortDescription;
}

int Game::getPopularity() {
    return popularity;
}