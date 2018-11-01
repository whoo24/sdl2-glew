#include "stdafx.h"

#include "SDL2GlewMain/Application.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

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

struct RenderContext {
  float fov = 45.0f;
  float width = 512.f;
  float height = 512.f;
  float near_plane = 0.01f;
  float far_plane = 10000.f;
  glm::vec3 eye = { 0, 0, 10.f };
  glm::vec3 look_at = { 0, 0, 0 };
  glm::vec3 up = { 0, 1.f, 0 };
};

void Render(SDL_Window* window, RenderContext* render) {
  glm::mat4 mat_proj = glm::perspective(render->fov, render->width / render->height, render->near_plane, render->far_plane);
  glm::mat4 mat_view = glm::lookAt(render->eye, render->look_at, render->up);
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
}

void Update(AppContext* app, RenderContext* render) {
  auto event = EventResult::kUpdate;
  while (event != EventResult::kQuit) {
    event = UpdateEventHandler();
    Render(app->main_window, render);
  }
}

int main(int argc, char *argv[]) {
  AppContext context;
  RenderContext render_context;
  Init(&context);
  Update(&context, &render_context);
  CleanUp(&context);
  return 0;
}

