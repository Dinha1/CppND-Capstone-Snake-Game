#include "renderer.h"
#include <iostream>
#include <string>

std::mutex _mtx;
//const char* font = "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf";
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  if(TTF_Init() == -1) {
    std::cerr << "SDL_ttf could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf",25);
  if(!font) {
    std::cerr << "SDL_ttf could not load font.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}


Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, bool showHighScore, ScoreList scoreList) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  if(!snake.alive)
  {
    if(!showHighScore) {
      EnteringName();
    } else {
      ShowHighScore(scoreList);
    }
  }
  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0x60);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0x60);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0x60);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0x60);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
void Renderer::EnteringName() {
    std::unique_lock<std::mutex> _lock(_mtx);
    const std::string _output = "Enter name: " + _name;
    _lock.unlock();
    SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
    SDL_Color color = { 0xFF, 0xCC, 0x00, 0xFF};

    text = TTF_RenderText_Solid( font, _output.c_str(), color );
    if ( !text ) {
      std::cerr << "SDL_ttf could not render text.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
    SDL_Texture* text_texture;

    text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text );

    SDL_Rect dest = { (int)(screen_width - text->w)/2, (int)screen_height/2 - 100 , text->w, text->h };

    SDL_FreeSurface(text);
    SDL_RenderCopy(sdl_renderer, text_texture,NULL, &dest);
}

void Renderer::ShowHighScore(ScoreList scoreList) {
    SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
    SDL_Color color = { 0xFF, 0xCC, 0x00, 0xFF};
    std::string output("HIGH SCORES");
    text = TTF_RenderText_Solid( font, output.c_str(), color );
    if ( !text ) {
      std::cerr << "SDL_ttf could not render text.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
    SDL_Texture* text_texture;

    text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text );

    SDL_Rect captionDest = { (int)(screen_width - text->w)/2, 100, text->w, text->h };
    SDL_Rect dest;

    SDL_FreeSurface(text);
    SDL_RenderCopy(sdl_renderer, text_texture,NULL, &captionDest);
    //for(int i = 0; i < scoreList.; i++) {
    std::vector<Score> _listHighScore = scoreList.GetHighScoreList();
    for(int i = 0; i < _listHighScore.size(); i++)
    {
      //std::string _output = scoreList.playerName[i] + std::string("......") + std::to_string(scoreList.score[i]);
      text = TTF_RenderText_Solid( font, _listHighScore[i].GetName().c_str(), color );
      if ( !text ) {
        std::cerr << "SDL_ttf could not render text.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
      }
      text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text );

      dest = { captionDest.x - 100, captionDest.y + (i + 1) * 40, text->w, text->h };

      SDL_FreeSurface(text);
      SDL_RenderCopy(sdl_renderer, text_texture,NULL, &dest);

      text = TTF_RenderText_Solid( font, std::to_string(_listHighScore[i].GetScore()).c_str(), color );
      if ( !text ) {
        std::cerr << "SDL_ttf could not render text.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
      }

      text_texture = SDL_CreateTextureFromSurface(sdl_renderer, text );

      dest = { captionDest.x + captionDest.w + 50, captionDest.y + (i + 1) * 40, text->w, text->h };

      SDL_FreeSurface(text);
      SDL_RenderCopy(sdl_renderer, text_texture,NULL, &dest);
    }
}
void Renderer::UpdateName(std::string name) {
  // Clear screen
  std::unique_lock<std::mutex> _lock(_mtx);
  _name = name;
  _lock.unlock();
}
