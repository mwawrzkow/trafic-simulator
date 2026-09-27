#pragma once

#include "SFML/Window/Keyboard.hpp"
#include "graphics/window.hpp"
#include "meta/Observer.hpp"
#include "primitives/vector.hpp"
#include <cstddef>
#include <optional>
namespace Graphics {

enum class EngineInputEvent { KEY_PRESSED, KEY_RELEASED, MOUSE_LEFT_CLICK };
struct EventDetails {
  std::optional<sf::Keyboard::Scancode> keycode{std::nullopt};
  std::optional<Primitives::Vector2Di> mouse_pos{std::nullopt};
};

typedef meta::ObserverPattern::Message<InputEvent, EventDetails>
    EngineInputMessage;

class Engine : public meta::ObserverPattern::Observer<WindowInputMessage> {
public:
  Engine();
  auto run() -> void;
  virtual void notify(WindowInputMessage &message) override;

private:
  auto _start() -> void;
  auto init() -> void;

private:
  auto onInputEvent(InputMessage &inputAction, InputEvent &event) -> void;

private:
  Window window;
};
} // namespace Graphics
