
#ifndef SCORE_H
#define SCORE_H

#include <string>
class Score {
    public:
        Score(std::string name, int score);
        int GetScore() const;
        std::string GetName() const;
    private:
        std::string _playerName;
        int _score;
};
#endif