#include "graphics/engine.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "graphics/window.hpp"
#include <print>
using namespace Graphics;
Engine::Engine() : window(800, 600, "Example Game") {}

auto Engine::init() -> void { window.subscribe(this->shared_from_this()); }

auto Engine::run() -> void {
  this->init();
  this->_start();
}

auto Engine::_start() -> void {
  while (window.running()) {
    window.processEvents();
    //    window.draw(queue);
    window.clear();
  }
}
void Engine::notify(WindowInputMessage &message) {
  switch (message.id) {
  case InputMessage::INPUT_PRESS_EVENT_OCCURED:
  case InputMessage::INPUT_RELEASE_EVENT_OCCURED:
    this->onInputEvent(message.id, message.data);
    break;
  case InputMessage::CLOSE_REQUEST_SENT:
    // TODO: add handling close request
    break;
  }
}

auto Engine::onInputEvent(InputMessage &inputAction, InputEvent &event)
    -> void {
  std::string message;
  std::string key = "";
  switch (inputAction) {
  case Graphics::InputMessage::INPUT_PRESS_EVENT_OCCURED:
    message = "Input Press occured on key: ";
    key = sf::Keyboard::getDescription(
        event.event->getIf<sf::Event::KeyPressed>()->scancode).toAnsiString();
    break;
  case Graphics::InputMessage::INPUT_RELEASE_EVENT_OCCURED:
    message = "Input Release occured on key: ";
    key = sf::Keyboard::getDescription(
        event.event->getIf<sf::Event::KeyReleased>()->scancode).toAnsiString();
  }
  std::println("{} {}", message, key);
}
