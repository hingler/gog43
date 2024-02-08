#ifndef IOSTREAM_LOGGER_H_
#define IOSTREAM_LOGGER_H_

#include "gog43/Logger.hpp"

#include <unordered_map>
#include <iostream>
#include <mutex>

namespace gog43 {
  class IOStreamLogger : public Logger {
  public:
    void logger_print(std::string& msg) override;
    void logger_print(std::string&& msg) override;

    void benchStart(const std::string& name) override;
    void benchEnd(const std::string& name) override;

  private:
    std::unordered_map<std::string, uint64_t> benches;

    uint64_t getUsecs();

    std::recursive_mutex print_lock;
  };
}

#endif