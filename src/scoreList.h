
#ifndef SCORELIST_H
#define SCORELIST_H

#include "score.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

class ScoreList {
    public:
        ScoreList(std::string filename);
        void AddScore(std::string name, int score);
        std::vector<Score> GetHighScoreList() const;
        void SaveHighScore();
    private:
        std::vector<Score> _listHighScore;
        std::string _filename;
        int _maxline{5};
};
#endif