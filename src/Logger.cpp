#include "gog43/Logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>


namespace std {
  string to_string(const char* value) {
    return string(value);
  }
}

namespace gog43 {
  class NoOpLogger : public Logger {
  public:
    void logger_print(std::string& msg) override {
      // no op
    }

    void logger_print(std::string&& msg) override {
      // no op
    }

    void benchStart(const std::string& name) override {
      // no op
    }

    void benchEnd(const std::string& name) override {
      // no op
    }
  };

  static Logger* sharedLogger = new NoOpLogger();

  static std::string get_time() {
    auto dur = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(dur);

    std::tm* time_ptr = std::localtime(&time);

    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(dur.time_since_epoch()).count() % 1000;
    // tba: simple toggle for colorted output
    std::stringstream stream;
    stream << "[ \33[33m" << std::put_time(time_ptr, "%b %e %Y | %T") << "." << std::setfill('0') << std::setw(3) << millis << "\33[0m ] - ";
    return stream.str();
  }

  void provide_logger(Logger* logger) {
    if (sharedLogger != nullptr) {
      delete sharedLogger;
    }
    sharedLogger = logger;
  }

  void print(std::string& msg) {
    auto time = get_time();
    time.append(msg);
    sharedLogger->logger_print(time);
  }

  void print(std::string&& msg) {
    auto time = get_time();
    time.append(msg);
    sharedLogger->logger_print(std::forward<std::string>(time));
  }


  void print(const char* msg) {
    print(std::string(msg));
  }

  void benchStart(const std::string& name) {
    sharedLogger->benchStart(name);
  }

  void benchEnd(const std::string& name) {
    sharedLogger->benchEnd(name);
  }
}