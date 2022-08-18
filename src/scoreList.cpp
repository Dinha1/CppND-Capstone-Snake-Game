#include "scoreList.h"
ScoreList::ScoreList(std::string filename) : _filename(filename) {
  std::ifstream scoreFile(filename);
  if(scoreFile) {
    std::string line; 
    while(getline(scoreFile, line)) {
      std::istringstream sline(line);
      std::string _name;
      int _score;
      while(sline >> _name >> _score) {
        _listHighScore.emplace_back(Score(_name, _score));
      }
    }
  }
}

void ScoreList::AddScore(std::string name, int score) {
    _listHighScore.emplace_back(Score(name, score));
    std::sort(_listHighScore.begin(), _listHighScore.end(), [](const Score& s1, const Score& s2) {
        return s1.GetScore() > s2.GetScore();
    });
    while (_listHighScore.size() > _maxline) {
        _listHighScore.pop_back();
    }
}

std::vector<Score> ScoreList::GetHighScoreList() const {
    return _listHighScore;
}
void ScoreList::SaveHighScore() {
  std::ofstream file_out;

  file_out.open(_filename, std::ios_base::trunc);
  for (Score s : _listHighScore) {
    file_out << s.GetName() + std::string(" ") + std::to_string(s.GetScore()) << std::endl;
  }
}