#include "gog43/IOStreamLogger.hpp"

#include <chrono>
#include <iostream>
#include <iomanip>
#include <ctime>

#include <sstream>

namespace gog43 {
  void IOStreamLogger::logger_print(std::string& msg) {
    std::lock_guard<std::recursive_mutex> lock(print_lock);
    std::cout << msg << std::endl;
  }

  void IOStreamLogger::logger_print(std::string&& msg) {
    std::lock_guard<std::recursive_mutex> lock(print_lock);
    std::cout << msg << std::endl;
  }

  void IOStreamLogger::benchStart(const std::string& name) {
    std::lock_guard<std::recursive_mutex> lock(print_lock);
    uint64_t current_time = getUsecs();
    benches.insert(std::make_pair(name, current_time));
  }

  void IOStreamLogger::benchEnd(const std::string& name) {
    std::lock_guard<std::recursive_mutex> lock(print_lock);
    auto start_time = benches.find(name);
    if (start_time != benches.end()) {
      gog43::print("log time for " + std::string(name) + ": " + std::to_string(getUsecs() - start_time->second) + "us");
      benches.erase(start_time);
    } else {
      gog43::print("could not find bench for log " + name);
    }
  }

  uint64_t IOStreamLogger::getUsecs() {
    auto pt = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(pt.time_since_epoch()).count();
  }
}