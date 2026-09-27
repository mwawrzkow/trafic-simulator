#pragma once
#include "SpecializationOf.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <vector>

namespace meta::ObserverPattern {

template <typename T_0, typename T_1> struct Message {
  T_0 id{};
  T_1 &data;
};

template <typename M>
  requires SpecializationOf<M, ^^Message>
class Observer : public std::enable_shared_from_this<Observer<M>> {
public:
  virtual void notify(M &message) = 0;
};

template <typename T>
  requires SpecializationOf<T, ^^Message>
class Subject {
public:
  Subject() : observers() {}
  auto subscribe(std::shared_ptr<Observer<T>> observer) {
    this->observers.push_back(observer);
  }
  auto unsubscribe(std::shared_ptr<Observer<T>> observer) {
    auto reference = observer.get();
    for (auto begin = observers.begin(); begin != observers.end(); begin++)
      if (begin->get() == reference) {
        observers.erase(begin);
        return true;
      }
    return false;
  }
  void notifyAll(T &message) {
    for (auto &observer : observers) {
      if (auto lock = observer.lock())
        lock->notify(message);
    }
  }

  auto nofifyOnce(std::shared_ptr<Observer<T>> observer, T message) {
    observer->notify(message);
  }

private:
  std::vector<std::weak_ptr<Observer<T>>> observers;
};
} // namespace meta::ObserverPattern
