#pragma once

#include <fstream>
#include "BaseObserver.h"

template <typename T>
class LoggingObserver : public BaseObserver<T> {
 protected:
 std::string file_name;
  std::ofstream shows_file;


 public:
  LoggingObserver(std::shared_ptr<Subject<T>> subject,
                                    std::string file_name)
    : BaseObserver<T>(subject), file_name(file_name) {}
  ~LoggingObserver() {
  if (shows_file.is_open()) {
    shows_file.close();
  }
}

  void ObserverAction(const T& event_data) override;
};






template <typename T>
void LoggingObserver<T>::ObserverAction(const T& event_data) {
shows_file.open(file_name, std::ios::app);
  if (shows_file.is_open()) {
    shows_file << "\": Log_EventData --> " << event_data << "\n";
    // shows_file.flush();
    shows_file.close();
  }
}

template <>
void LoggingObserver<CustomEvent>::ObserverAction(
    const CustomEvent& event_data) {
  shows_file.open(file_name, std::ios::app);
  if (shows_file.is_open()) {
    shows_file << "\": Log_EventDataMoney --> " << event_data.despositing_money
               << "\n"
                  "\": Log_EventDataId --> "
               << event_data.client_id
               << "\n"
                  "\": Log_EventDataName --> "
               << event_data.client_name << "\n";
    // shows_file.flush();
    shows_file.close();
  }
}

template class LoggingObserver<CustomEvent>;
