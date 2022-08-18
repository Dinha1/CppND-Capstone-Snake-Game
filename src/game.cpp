#include "game.h"
#include <iostream>
#include "SDL.h"

const std::string filename = "highscore.txt";

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      scoreList(ScoreList(filename)) {
  PlaceFood();
}

void Game::Run(Controller const &&controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  bool enteringName = false;
  bool showingHighScore = false;
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, showingHighScore, scoreList);
    if(!snake.alive && !enteringName)
    {
      enteringName = true;
      //std::thread enterName(&Renderer::EnterName, &renderer);
      std::thread enterName([&]{
        std::cout << "Now start thread enter name\n";
        std::string _name;
        renderer.UpdateName(_name + std::string("_"));
        renderer.Render(snake, food, showingHighScore, scoreList);
        bool _threadRunning = true;
        SDL_StartTextInput();
        while ( _threadRunning ) {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
          SDL_Event ev;
          std::cout << "In _thread running loop\n";
          while ( SDL_PollEvent( &ev ) ) {
            if ( ev.type == SDL_TEXTINPUT && _name.size() < maxNameLength) {
              //std::lock_guard<std::mutex> _lock(_mtx);
              _name += ev.text.text;
              renderer.UpdateName(_name + std::string("_"));
            } else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && _name.size()) {
              _name.pop_back();
              renderer.UpdateName(_name + std::string("_"));
              //renderer.Render(snake, food);
            } else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN){
              if(!_name.size())
              {
                _name = "Player";
              }
              renderer.UpdateName(_name + std::string("_"));
              std::cout << " > " << _name << std::endl;
              scoreList.AddScore(_name, GetScore());
              scoreList.SaveHighScore();
              _threadRunning = false;
              showingHighScore = true;
            }
          }
          renderer.Render(snake, food, showingHighScore, scoreList);
        }
        SDL_StopTextInput();
      });
      enterName.join();
      //renderer.EnterName();
    } 
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

