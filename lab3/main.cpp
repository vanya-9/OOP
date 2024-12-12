#include <iostream>
#include <list>
#include <memory>
#include <string>

typedef struct CustomEvent {
  size_t despositing_money;
  size_t client_id;
  std::string client_name;
} CustomEvent;

template <typename T>
class IObserver {
 public:
  virtual ~IObserver() {}
  virtual void onEvent(const T& event_data) = 0;
};

template <typename T>
class ISubject {
 public:
  virtual ~ISubject() {}
  virtual void Attach(std::shared_ptr<IObserver<T>> observer) = 0;
  virtual void Detach(std::shared_ptr<IObserver<T>> observer) = 0;
  virtual void Notify(const T& event_data) = 0;
};

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
Subject<T>::Subject() : pimpl{std::make_unique<SubjectImpl>()} {}

template <typename T>
Subject<T>::~Subject() {
  std::cout << "Goodbye, I was the Subject.\n";
}

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
  // this->data_ = data_event;
  pimpl->SetData(data_event);
  Notify(data_event);
}
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
    HowManyObserver();
    for (auto& observer : list_observer_) {
      observer->onEvent(event_data);
    }
  }

  void CreateEvent(T data_event) {
    SetData(data_event);
    Notify(data_);
  }
  void HowManyObserver() {
    std::cout << "There are " << list_observer_.size()
              << " observers in the list.\n";
  }

  void SetData(T data_event) { data_ = data_event; }
};

template <typename T>
class ConsoleObserver
    : public IObserver<T>,
      public std::enable_shared_from_this<ConsoleObserver<T>> {
 public:
  ConsoleObserver(std::shared_ptr<Subject<T>> subject) : subject_(subject) {
    std::cout << "Hi, I'm the Observer \"" << ++ConsoleObserver::static_number_
              << "\".\n";
    this->number_ = ConsoleObserver::static_number_;
  }
  virtual ~ConsoleObserver() {
    std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
  }

  void onEvent(const T& event_data) override {
    data_ = event_data;
    PrintInfo(event_data);
  }
  void RemoveMeFromTheList() {
    subject_->Detach(this->shared_from_this());
    std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
  }

  void PrintInfo(const T& event_data) {
    std::cout << "Observer \"" << this->number_ << "\": EventData --> "
              << event_data << "\n";
  }

  void Setting() { subject_->Attach(this->shared_from_this()); }

 private:
  T data_;
  std::shared_ptr<Subject<T>> subject_;
  static int static_number_;
  int number_;
};

template <>
void ConsoleObserver<CustomEvent>::PrintInfo(const CustomEvent& event_data) {
  std::cout << "Observer \"" << this->number_ << "\": EventDataMoney --> "
            << event_data.despositing_money
            << "\n"
               "\": EventDataId --> "
            << event_data.client_id
            << "\n"
               "\": EventDataName --> "
            << event_data.client_name << "\n";
}

template <typename T>
int ConsoleObserver<T>::static_number_ = 0;

void ClientCode() {
  auto subject_int_type = std::make_shared<Subject<int>>();
  auto int_observer = std::make_shared<ConsoleObserver<int>>(subject_int_type);
  int_observer->Setting();
  subject_int_type->CreateEvent(25);
  int_observer->RemoveMeFromTheList();

  auto subject_string_type = std::make_shared<Subject<std::string>>();
  auto sting_observer =
      std::make_shared<ConsoleObserver<std::string>>(subject_string_type);
  sting_observer->Setting();
  subject_string_type->CreateEvent("Pricolvkontakte");
  sting_observer->RemoveMeFromTheList();

  auto subject_custom_type = std::make_shared<Subject<CustomEvent>>();
  auto custom_observer =
      std::make_shared<ConsoleObserver<CustomEvent>>(subject_custom_type);
  custom_observer->Setting();
  subject_custom_type->CreateEvent({1412, 4214, "boris"});
  custom_observer->RemoveMeFromTheList();
}

int main() {
  ClientCode();
  return 0;
}
