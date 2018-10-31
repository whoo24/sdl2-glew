#include "stdafx.h"

#include "GL/glew.h"
#include "SDL2/include/SDL.h"

class InitializeException : public std::exception {
public:
  InitializeException (const std::string& message) : message_(message) {
    
  }
private:
  std::string message_;
};

struct AppContext {
  SDL_Window* mainWindow = nullptr;
  SDL_GLContext mainContext = nullptr;
};

void Init (AppContext* app) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw InitializeException("Failed to init SDL");
  }

  app->mainWindow = SDL_CreateWindow("SDL2GlewMain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  if (!app->mainWindow)
  {
    std::string error = "Unable to create window ";
    error += SDL_GetError();
    throw InitializeException(error);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  app->mainContext = SDL_GL_CreateContext(app->mainWindow);

  SDL_GL_SetSwapInterval(1);

  // Init GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

int main (int argc, char *argv[]) {
    return 0;
}

