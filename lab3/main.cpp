#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>
template <typename T>
class IObserver {
 public:
  virtual ~IObserver() {}
  virtual void onEvent(const T& event_data) = 0;
};

template <typename T>
class Subject {
 public:
  Subject();
  ~Subject();

  void Attach(std::shared_ptr<IObserver<T>> observer);
  void Detach(std::shared_ptr<IObserver<T>> observer);
  void Notify(const T& event_data);

 private:
  class SubjectImpl;
  std::list<std::shared_ptr<IObserver<T>>> list_observer_;

  std::unique_ptr<SubjectImpl> pimpl;
};

template <typename T>
class Subject<T>::SubjectImpl {
 private:
  std::list<std::shared_ptr<IObserver<T>>> list_observer_;

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
};

template <typename T>
Subject<T>::Subject() : pimpl(std::make_unique<SubjectImpl>()) {}

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
void Subject<T>::Notify(const T& event_data) {
  pimpl->Notify(event_data);
}

template <typename T>
class ConsoleObserver : public IObserver<T> {
 public:
  void onEvent(const T& event_data) override {
    std::cout << "\": Cons_EventData --> " << event_data << std::endl;
  }
};

template <typename T>
class LoggingObserver : public IObserver<T> {
 protected:
  std::ofstream& file_;

 public:
  LoggingObserver(std::ofstream& file) : file_(file) {}

  ~LoggingObserver() = default;

  void onEvent(const T& event_data) override {
    file_ << "LoggingObserver data --> " << event_data << std::endl;
  }
};

typedef struct CustomEvent {
  size_t despositing_money;
  size_t client_id;
  std::string client_name;
} CustomEvent;

std::ostream& operator<<(std::ostream& os, const CustomEvent& event) {
  os << "CustomEvent  despositing_money -->  " << event.despositing_money
     << ", id -->  " << event.client_id << ", name -->  " << event.client_name;
  return os;
}

int main() {
  std::ofstream out_file("out_file.txt");
  if (!out_file.is_open()) {
    return EIO;
  }

  Subject<int> subject_int_type;
  auto console_int_observer = std::make_shared<ConsoleObserver<int>>();
  auto log_int_observer = std::make_shared<LoggingObserver<int>>(out_file);

  subject_int_type.Attach(console_int_observer);
  subject_int_type.Attach(log_int_observer);
  subject_int_type.Notify(25);

  Subject<std::string> subject_string_type;
  auto console_sting_observer = std::make_shared<ConsoleObserver<std::string>>();
  auto log_string_observer = std::make_shared<LoggingObserver<std::string>>(out_file);
  subject_string_type.Attach(console_sting_observer);
  subject_string_type.Attach(log_string_observer);
  subject_string_type.Notify("Pricolvkontakte");

  Subject<CustomEvent> subject_custom_type;
  auto console_custom_observer = std::make_shared<ConsoleObserver<CustomEvent>>();
  auto log_custom_observer = std::make_shared<LoggingObserver<CustomEvent>>(out_file);
  subject_custom_type.Attach(console_custom_observer);
  subject_custom_type.Attach(log_custom_observer);
  subject_custom_type.Notify({1412, 4214, "boris"});
  return 0;
}
