#include <iostream>
#include <list>
#include <memory>
#include <string>

template <class T>
class IObserver {
 public:
  virtual ~IObserver() {};
  virtual void onEvent(const T& event_data) = 0;
};

template <class T>
class ISubject {
 public:
  virtual ~ISubject() {};
  virtual void Attach(std::shared_ptr<IObserver<T>> observer) = 0;
  virtual void Detach(std::shared_ptr<IObserver<T>> observer) = 0;
  virtual void Notify() = 0;
};

/**
 * Издатель владеет некоторым важным состоянием и оповещает наблюдателей о его
 * изменениях.
 */
template <class T>
class Subject : public ISubject<T> {
 public:
  virtual ~Subject() { std::cout << "Goodbye, I was the Subject.\n"; }

  /**
   * Методы управления подпиской.
   */
  void Attach(std::shared_ptr<IObserver<T>> observer) override {
    list_observer_.push_back(observer);
  }
  void Detach(std::shared_ptr<IObserver<T>> observer) override {
    list_observer_.remove(observer);
  }
  void Notify() override {
    HowManyObserver();
    for (auto& observer : list_observer_) {
      observer->onEvent(message_);
    }
  }

  void CreateMessage(T message = "Empty") {
    this->message_ = message;
    Notify();
  }
  void HowManyObserver() {
    std::cout << "There are " << list_observer_.size()
              << " observers in the list.\n";
  }

 private:
  std::list<std::shared_ptr<IObserver<T>>> list_observer_;
  T message_;
};

template <class T>
class Observer : public IObserver<T>,
                 public std::enable_shared_from_this<Observer<T>> {
 public:
  Observer(Subject<T>& subject) : subject_(subject) {
    // this->subject_.Attach(this->shared_from_this());
    std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_
              << "\".\n";
    this->number_ = Observer::static_number_;
  }
  virtual ~Observer() {
    std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
  }

  void onEvent(const T& event_data) override {
    message_from_subject_ = event_data;
    PrintInfo();
  }
  void RemoveMeFromTheList() {
    subject_.Detach(this->shared_from_this());
    std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
  }
  void PrintInfo() {
    std::cout << "Observer \"" << this->number_
              << "\": a new message is available --> "
              << this->message_from_subject_ << "\n";
  }

  void AttachToSubject() { subject_.Attach(this->shared_from_this()); }

 private:
  T message_from_subject_;
  Subject<T>& subject_;
  static int static_number_;
  int number_;
};

template <class T>
int Observer<T>::static_number_ = 0;

template <typename T>
std::shared_ptr<Observer<T>> CreateObserver(Subject<T>& subject) {
  auto observer = std::make_shared<Observer<T>>(subject);
  observer->AttachToSubject();
  return observer;
};

void ClientCode() {
    auto subject = std::make_shared<Subject<std::string>>();

    auto observer1 = CreateObserver<std::string>(*subject); // T = std::string
    auto observer2 = CreateObserver<std::string>(*subject); // T = std::string
    auto observer3 = CreateObserver<std::string>(*subject); // T = std::string
    std::shared_ptr<Observer<std::string>> observer4;
    std::shared_ptr<Observer<std::string>> observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = CreateObserver<std::string>(*subject); // T = std::string

    observer2->RemoveMeFromTheList();
    observer5 = CreateObserver<std::string>(*subject); // T = std::string

    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();
}

int main() {
  ClientCode();
  return 0;
}