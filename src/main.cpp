#include "main.hpp"
#include "graphics/engine.hpp"
#include "graphics/window.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

int main(int argc, char *argv[]) {
  auto engine = std::make_shared<Graphics::Engine>();
  engine->run();

  return 0;
}
