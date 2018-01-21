#include <iostream>
#include <string>

class Handler {
  Handler* next;
  int message;

  public:

  int getMessage() {
    return message;
  }

  Handler* nextHandler() {
    return next;
  }

  void add(Handler* handler) {
    if (next) {
      next->add(handler);
    }
    else {
      next = handler;
    }
  }

  virtual bool canHandle() {
    return true;
  }
  virtual bool needToPass() {
    return true;
  }
  virtual void handle() = 0;

  virtual void resolve(int message) {
    this->message = message;
    if(canHandle()) {
      handle();
    }
    if(needToPass() && nextHandler()) {
      std::cout << "Passing to the next handler..." << std::endl;
      nextHandler()->resolve(message);
    }
  }
};

class ZeroHanlder : public Handler {
  public:
    bool needToPass() {
      if(getMessage() == 0) {
        log("Stop processing ZERO!");
        return false;
      }
      return true;
    }

    void handle() {
      log("Prepare the message for real work");
    }

    void log(std::string str) {
      std::cout << "I'm the Zero handler. " << str << std::endl;
    }
};

class NonpositiveHandler : public Handler {
  public:
    bool canHandle() {
      if(getMessage() > 0) {
        log("Can't handle message greater than zero :(");
        return false;
      }
      return true;
    }

    void handle() {
      log("I handle the " + std::to_string(getMessage()));
    }

    void log(std::string str) {
      std::cout << "I'm the First handler. " << str << std::endl;
    }
};

class MainHandler : public Handler {
  public:
    bool canHandle() {
      if (getMessage() < -5) {
        log("Can't handle such small number =(");
        return false;
      }
      return true;
    }

    void handle() {
      log("I carefully handle the " + std::to_string(getMessage()));
    }

    void log(std::string str) {
      std::cout << "I'm the Second handler. " << str << std::endl;
    }
};

void sendMessage(Handler* handler, int message) {
  std::cout << "Send message: " << message << std::endl;
  handler->resolve(message);
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  auto chain = new NonpositiveHandler();
  chain->add(new ZeroHanlder());
  chain->add(new MainHandler());

  sendMessage(chain, -9);
  sendMessage(chain, -1);
  sendMessage(chain, 0);
  sendMessage(chain, 1);
  return 0;
}
