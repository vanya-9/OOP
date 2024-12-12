#pragma once

#include <CustomEvent.h>
#include <iostream>
#include <memory>
#include <string>
#include "IObserver.h"
#include "Subject.h"

template <typename T>
class BaseObserver : public IObserver<T>,
                     public std::enable_shared_from_this<BaseObserver<T>> {
 public:
  virtual void ObserverAction(const T& event_data) = 0;
  BaseObserver(std::shared_ptr<Subject<T>> subject) : subject_(subject) {}
  virtual ~BaseObserver() = default;

  void onEvent(const T& event_data) override {
    data_ = event_data;
    ObserverAction(event_data);
  }
  void RemoveMeFromTheList() { subject_->Detach(this->shared_from_this()); }

  void Setting() { subject_->Attach(this->shared_from_this()); }

 private:
  T data_;
  std::shared_ptr<Subject<T>> subject_;
};
