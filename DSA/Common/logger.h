#pragma once

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace common {

class Logger {
public:
    explicit Logger(const char* file_name) : log_stream_(file_name, std::ios::app) {}

    bool is_open() const {
        return log_stream_.is_open();
    }

    template <typename... Values>
    void info(Values&&... values) {
        write("INFO", make_message(std::forward<Values>(values)...));
    }

    template <typename... Values>
    void error(Values&&... values) {
        write("ERROR", make_message(std::forward<Values>(values)...));
    }

    template <typename... Values>
    [[noreturn]] void fatal(Values&&... values) {
        const std::string message = make_message(std::forward<Values>(values)...);
        write("FATAL", message);
        std::cerr << "[FATAL] " << message << std::endl;
        std::exit(EXIT_FAILURE);
    }

private:
    template <typename... Values>
    static std::string make_message(Values&&... values) {
        std::ostringstream message;
        (message << ... << std::forward<Values>(values));
        return message.str();
    }

    void write(const char* level, const std::string& message) {
        if (!log_stream_.is_open()) {
            return;
        }

        const auto now = std::chrono::system_clock::now();
        const std::time_t current_time = std::chrono::system_clock::to_time_t(now);
        std::tm local_time{};

#ifdef _WIN32
        localtime_s(&local_time, &current_time);
#else
        localtime_r(&current_time, &local_time);
#endif

        log_stream_ << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S")
                    << " [" << level << "] " << message << '\n';
        log_stream_.flush();
    }

    std::ofstream log_stream_;
};

}  // namespace common