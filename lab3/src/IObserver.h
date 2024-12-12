#pragma once
template <typename T>
class IObserver {
 public:
  virtual ~IObserver() {}
  virtual void onEvent(const T& event_data) = 0;
};