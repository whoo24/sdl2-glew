#include "stdafx.h"

#include "SDL2GlewMain/Application.h"

enum class EventResult {
  kUpdate,
  kQuit
};

EventResult UpdateEventHandler() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return EventResult::kQuit;
      case SDL_KEYUP:
      case SDL_KEYDOWN:
        break;
      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEBUTTONDOWN:
        break;
      case SDL_MOUSEMOTION:
        break;
    }
  }
  return EventResult::kUpdate;
}

void Render(SDL_Window* window) {
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
}

void Update(AppContext* app) {
  auto event = EventResult::kUpdate;
  while (event != EventResult::kQuit) {
    event = UpdateEventHandler();
    Render(app->main_window);
  }
}

int main(int argc, char *argv[]) {
  AppContext context;
  Init(&context);
  Update(&context);
  CleanUp(&context);
  return 0;
}

