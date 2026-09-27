#pragma once
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "meta/Observer.hpp"
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string_view>
#include <vector>
namespace Graphics {
typedef std::vector<sf::Drawable> DrawQueue;
typedef std::map<int, DrawQueue> DrawPriorityQueue;
typedef std::shared_ptr<DrawPriorityQueue> DrawPriorityQueuePtr;
struct InputEvent {
  const std::optional<sf::Event> event{std::nullopt};
};
enum class InputMessage : uint_fast16_t {
  INPUT_PRESS_EVENT_OCCURED,
  INPUT_RELEASE_EVENT_OCCURED,
  CLOSE_REQUEST_SENT,
};

typedef meta::ObserverPattern::Message<InputMessage, InputEvent>
    WindowInputMessage;

class Window : public meta::ObserverPattern::Subject<WindowInputMessage> {
public:
  Window(int w, int h, std::string_view title);
  Window(Window &);
  auto processEvents() -> void;

  auto draw(DrawPriorityQueuePtr queue) -> void;
  auto clear(sf::Color color = sf::Color::Black) -> void;
  auto running() -> const bool;

private:
  std::shared_ptr<sf::RenderWindow> window;
};
} // namespace Graphics
