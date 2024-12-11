#include <iostream>
#include <list>
#include <string>
#include <memory>
template<class T>
class IObserver {
 public:
  virtual ~IObserver(){};
  virtual void onEvent(const T &event_data) = 0;
};

template<class T>
class ISubject {
 public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver<T> *observer) = 0;
  virtual void Detach(IObserver<T> *observer) = 0;
  virtual void Notify() = 0;
};

/**
 * Издатель владеет некоторым важным состоянием и оповещает наблюдателей о его
 * изменениях.
 */
template<class T>
class Subject : public ISubject<T> {
 public:
  virtual ~Subject() {
    std::cout << "Goodbye, I was the Subject.\n";
  }

  /**
   * Методы управления подпиской.
   */
  void Attach(IObserver<T> *observer) override {
    list_observer_.push_back(observer);
  }
  void Detach(IObserver<T> *observer) override {
    list_observer_.remove(observer);
  }
  void Notify() override {
    HowManyObserver();
    for (auto &observer : list_observer_) {
      observer->onEvent(message_);
    }
  }

  void CreateMessage(T message = "Empty") {
    this->message_ = message;
    Notify();
  }
  void HowManyObserver() {
    std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
  }


 private:
  std::list<IObserver<T> *> list_observer_;
  std::string message_;
};

template<class T>
class Observer : public IObserver<T> {
 public:
  Observer(Subject<T> &subject) : subject_(subject) {
    this->subject_.Attach(this);
    std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
    this->number_ = Observer::static_number_;
  }
  virtual ~Observer() {
    std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
  }

  void onEvent(const T &event_data) override {
    message_from_subject_ = event_data;
    PrintInfo();
  }
  void RemoveMeFromTheList() {
    subject_.Detach(this);
    std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
  }
  void PrintInfo() {
    std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
  }

 private:
  T message_from_subject_;
  Subject<T> &subject_;
  static int static_number_;
  int number_;
};

template<class T>
int Observer<T>::static_number_ = 0;

void ClientCode() {
  Subject<std::string> *subject = new Subject<std::string>;
  Observer<std::string> *observer1 = new Observer<std::string>(*subject);
  Observer<std::string> *observer2 = new Observer<std::string>(*subject);
  Observer<std::string> *observer3 = new Observer<std::string>(*subject);
  Observer<std::string> *observer4;
  Observer<std::string> *observer5;

  subject->CreateMessage("Hello World! :D");
  observer3->RemoveMeFromTheList();

  subject->CreateMessage("The weather is hot today! :p");
  observer4 = new Observer<std::string>(*subject);

  observer2->RemoveMeFromTheList();
  observer5 = new Observer<std::string>(*subject);

  subject->CreateMessage("My new car is great! ;)");
  observer5->RemoveMeFromTheList();

  observer4->RemoveMeFromTheList();
  observer1->RemoveMeFromTheList();

  delete observer5;
  delete observer4;
  delete observer3;
  delete observer2;
  delete observer1;
  delete subject;
}

int main() {
  ClientCode();
  return 0;
}