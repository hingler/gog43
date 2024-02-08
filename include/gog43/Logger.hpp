#ifndef LOGGER_H_
#define LOGGER_H_

#include <any>
#include <array>
#include <type_traits>
#include <string>

// need to write a class which can perform logging on our behalf

namespace std {
  /* overrides for to_string (support logging) */
  string to_string(const char* value);

  // fall-through for incompatible types
  template <typename T, typename...>
  string to_string(T any) {
    return string(" <unsupported to_string: " + string(typeid(T).name()) + "> ");
  }
}

namespace gog43 {
  class Logger {
   public:
    virtual void logger_print(std::string& msg) = 0;
    virtual void logger_print(std::string&& msg) = 0;

    // start timer
    virtual void benchStart(const std::string& name) = 0;
    // finishes timer and logs time taken
    virtual void benchEnd(const std::string& name) = 0;
    virtual ~Logger() {}
  };

  void provide_logger(Logger* logger);

  void print(std::string& msg);
  void print(std::string&& msg);



  template <class... Args>
  static void print(const Args&... args) {
    // copied roughly from godot print defn
    std::string res = "";
    std::array<std::string, sizeof...(Args)> var_args { std::to_string(args)... };
    for (size_t i = 0; i < var_args.size(); i++) {
      res += var_args[i];
    }

    print(res);
  }

  // todo: i dont know what the debug flag is lole
  void print(const char* msg);

  void benchStart(const std::string& name);
  void benchEnd(const std::string& name);
}

#endif