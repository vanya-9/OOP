#pragma once
#include <memory>
template <typename T>
class IObserver;

template <typename T>
class ISubject {
 public:
  virtual ~ISubject() {}
  virtual void Attach(std::shared_ptr<IObserver<T>> observer) = 0;
  virtual void Detach(std::shared_ptr<IObserver<T>> observer) = 0;
  virtual void Notify(const T& event_data) = 0;
};