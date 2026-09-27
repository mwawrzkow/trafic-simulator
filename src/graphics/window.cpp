#include "graphics/window.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <memory>

using namespace Graphics;

Window::Window(int w, int h, std::string_view title)
    : window(std::make_shared<sf::RenderWindow>(sf::VideoMode({800, 600}),
                                                title)) {}

Window::Window(Window &ref) { this->window = ref.window; }

auto Window::processEvents() -> void {
  auto onClose = [this](const sf::Event::Closed &) {
    auto val = InputEvent{};
    WindowInputMessage message{InputMessage::CLOSE_REQUEST_SENT, val};
    notifyAll(message);
  };
  auto onKeyPressed = [this](const sf::Event::KeyPressed &KeyPressed) {
    auto val = InputEvent{KeyPressed};
    WindowInputMessage msg{InputMessage::INPUT_PRESS_EVENT_OCCURED, val};
    notifyAll(msg);
  };
  auto onKeyReleased = [this](const sf::Event::KeyReleased &KeyReleased) {
    auto val = InputEvent{KeyReleased};
    WindowInputMessage msg{InputMessage::INPUT_RELEASE_EVENT_OCCURED, val};
    notifyAll(msg);
  };
  window->handleEvents(onClose, onKeyPressed, onKeyReleased);
}

auto Window::draw(DrawPriorityQueuePtr queue) -> void {
  for (auto &[idx, list] : *queue) {
    for (const auto &drawable : list)
      window->draw(drawable);
  }
}

auto Window::clear(sf::Color color) -> void {
  window->clear(color);
  window->display();
}

auto Window::running() -> const bool { return window->isOpen(); }
