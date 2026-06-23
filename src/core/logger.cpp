#include "core/logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace bp::core {

std::shared_ptr<spdlog::logger> Logger::s_logger;

void Logger::initialize() {
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("blender-pro.log"));
    
    s_logger = std::make_shared<spdlog::logger>("blender-pro", sinks.begin(), sinks.end());
    s_logger->set_level(spdlog::level::debug);
    s_logger->flush_on(spdlog::level::err);
    
    spdlog::register_logger(s_logger);
}

}
