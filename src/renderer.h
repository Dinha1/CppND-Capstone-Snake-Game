#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <mutex>
#include "SDL.h"
#include "SDL_ttf.h"
#include "snake.h"
#include "score.h"
#include "scoreList.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();


  void Render(Snake const snake, SDL_Point const &food, bool showHighScore, ScoreList scoreList);
  void UpdateWindowTitle(int score, int fps);
  void UpdateName(std::string name);
 private:
  void ShowHighScore(ScoreList scoreList);
  void EnteringName();

  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  TTF_Font *font;
  SDL_Surface* text;
  std::string _name;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif