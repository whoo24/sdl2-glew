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
  SDL_Window* main_window = nullptr;
  SDL_GLContext main_context = nullptr;
};

void Init (AppContext* app) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw InitializeException("Failed to init SDL");
  }

  app->main_window = SDL_CreateWindow("SDL2GlewMain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  if (!app->main_window)
  {
    std::string error = "Unable to create window ";
    error += SDL_GetError();
    throw InitializeException(error);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  app->main_context = SDL_GL_CreateContext(app->main_window);

  SDL_GL_SetSwapInterval(1);

  // Init GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void CleanUp (AppContext* app) {
  SDL_GL_DeleteContext(app->main_context);
  SDL_DestroyWindow(app->main_window);
  SDL_Quit();
}

