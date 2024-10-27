#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main() {
    // 创建一个彩色控制台日志记录器
    auto console = spdlog::stdout_color_mt("console");

    // 设置日志级别
    spdlog::set_level(spdlog::level::debug); // 可以设置为 info、warn、error 等

    // 记录不同级别的日志
    console->info("Welcome to spdlog!");
    console->warn("This is a warning message.");
    console->error("This is an error message.");

    // 记录调试信息
    console->debug("Debugging info: {}", 42);

    // 记录格式化字符串
    console->info("Formatted number: {:.2f}", 3.14159);

    return 0;
}

