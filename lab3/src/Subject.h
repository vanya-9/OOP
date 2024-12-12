#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "ISubject.h"
template <typename T>
class Subject : public ISubject<T> {
 public:
  Subject();
  virtual ~Subject();

  void Attach(std::shared_ptr<IObserver<T>> observer) override;
  void Detach(std::shared_ptr<IObserver<T>> observer) override;
  void Notify(const T& event_data) override;

  void CreateEvent(T data_event);
  void HowManyObserver();
  void SetData(T data_event);

 private:
  class SubjectImpl;
  std::list<std::shared_ptr<IObserver<T>>> list_observer_;

  std::unique_ptr<SubjectImpl> pimpl;
};

template <typename T>
class Subject<T>::SubjectImpl {
 private:
  std::list<std::shared_ptr<IObserver<T>>> list_observer_;
  T data_;

 public:
  void Attach(std::shared_ptr<IObserver<T>> observer) {
    list_observer_.push_back(observer);
  }
  void Detach(std::shared_ptr<IObserver<T>> observer) {
    list_observer_.remove(observer);
  }
  void Notify(const T& event_data) {
    for (auto& observer : list_observer_) {
      observer->onEvent(event_data);
    }
  }

  void CreateEvent(T data_event) {
    SetData(data_event);
    Notify(data_);
  }

  void SetData(T data_event) { data_ = data_event; }
};

template <typename T>
Subject<T>::Subject() : pimpl{std::make_unique<SubjectImpl>()} {}

template <typename T>
Subject<T>::~Subject() {}

template <typename T>
void Subject<T>::Attach(std::shared_ptr<IObserver<T>> observer) {
  pimpl->Attach(observer);
}

template <typename T>
void Subject<T>::Detach(std::shared_ptr<IObserver<T>> observer) {
  pimpl->Detach(observer);
}

template <typename T>
void Subject<T>::SetData(T data_event) {
  pimpl->SetData(data_event);
}

template <typename T>
void Subject<T>::Notify(const T& data_event) {
  pimpl->Notify(data_event);
}

template <typename T>
void Subject<T>::CreateEvent(T data_event) {
  pimpl->SetData(data_event);
  Notify(data_event);
}
