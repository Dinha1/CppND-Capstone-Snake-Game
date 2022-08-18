#include "score.h"
Score::Score(std::string name, int score) : _playerName(name), _score(score) {}

int Score::GetScore() const {
    return _score;
}

std::string Score::GetName() const {
    return _playerName;
}

