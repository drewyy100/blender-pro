#pragma once

#include <spdlog/spdlog.h>
#include <memory>

namespace bp::core {

class Logger {
public:
    static void initialize();
    
    template<typename... Args>
    static void info(const char* fmt, Args... args) {
        s_logger->info(fmt, args...);
    }
    
    template<typename... Args>
    static void warn(const char* fmt, Args... args) {
        s_logger->warn(fmt, args...);
    }
    
    template<typename... Args>
    static void error(const char* fmt, Args... args) {
        s_logger->error(fmt, args...);
    }

private:
    static std::shared_ptr<spdlog::logger> s_logger;
};

}
