#include <iostream>
#include <list>
#include <memory>
#include <string>
#include "ConsoleObserver.h"
#include "LoggingObserver.h"
#include "Subject.h"

int main(int argc, char* argv[]) {
  std::string file_name = "file.txt";
  if (argc == 2) {
    file_name = argv[1];
  }

  auto subject_int_type = std::make_shared<Subject<int>>();

  auto int_observer = std::make_shared<ConsoleObserver<int>>(subject_int_type);
  auto log_int_observer = std::make_shared<LoggingObserver<int>>(subject_int_type, file_name);
 
  int_observer->Setting();
  log_int_observer->Setting();

  subject_int_type->CreateEvent(25);

  int_observer->RemoveMeFromTheList();
  log_int_observer->RemoveMeFromTheList();

  auto subject_string_type = std::make_shared<Subject<std::string>>();

  auto sting_observer = std::make_shared<ConsoleObserver<std::string>>(subject_string_type);
  auto log_string_observer = std::make_shared<LoggingObserver<std::string>>(subject_string_type, file_name);

  sting_observer->Setting();
  log_string_observer->Setting();

  subject_string_type->CreateEvent("Pricolvkontakte");
  sting_observer->RemoveMeFromTheList();
  log_string_observer->RemoveMeFromTheList();

  auto subject_custom_type = std::make_shared<Subject<CustomEvent>>();

  auto custom_observer = std::make_shared<ConsoleObserver<CustomEvent>>(subject_custom_type);
  auto log_custom_observer = std::make_shared<LoggingObserver<CustomEvent>>(subject_custom_type, file_name);
  
  custom_observer->Setting();
  log_custom_observer->Setting();

  subject_custom_type->CreateEvent({1412, 4214, "boris"});
  custom_observer->RemoveMeFromTheList();
  log_custom_observer->RemoveMeFromTheList();
  return 0;
}
