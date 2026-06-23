#include "editor/application.hpp"
#include "core/logger.hpp"

int main(int argc, char** argv) {
    try {
        bp::core::Logger::initialize();
        bp::core::Logger::info("Blender Pro v0.1.0 starting...");

        bp::editor::Application app;
        app.initialize();
        app.run();
        app.shutdown();

        bp::core::Logger::info("Blender Pro shutdown successfully");
        return 0;
    }
    catch (const std::exception& e) {
        bp::core::Logger::error("Fatal error: {}", e.what());
        return 1;
    }
}
