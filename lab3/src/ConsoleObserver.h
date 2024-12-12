#pragma once
#include <CustomEvent.h>
#include <CustomEvent.h>
#include <iostream>
#include <memory>
#include <string>
#include <BaseObserver.h>


template <typename T>
class ConsoleObserver : public BaseObserver<T> {
 public:
 
  void ObserverAction(const T& event_data)override;
  ConsoleObserver(std::shared_ptr<Subject<T>> subject)
    : BaseObserver<T>(subject){}

};

template <typename T>
void ConsoleObserver<T>::ObserverAction(const T& event_data) {
  std::cout << "\": Cons_EventData --> " << event_data << "\n";
}



template <>
void ConsoleObserver<CustomEvent>::ObserverAction(
    const CustomEvent& event_data) {
  std::cout << "\": Cons_EventDataMoney --> " << event_data.despositing_money << "\n"
            << "\": Cons_EventDataId --> " << event_data.client_id << "\n"
            << "\": Cons_EventDataName --> " << event_data.client_name << "\n";
}

template class ConsoleObserver<CustomEvent>;
