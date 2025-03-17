#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h> // 添加头文件

int main() {
    // 创建一个彩色控制台日志记录器
    auto console = spdlog::stdout_color_mt("console");

    // 创建一个每天生成一个新文件的文件日志记录器，最多保留3个文件, 0点0分生成新文件
    auto file_logger = spdlog::daily_logger_mt("daily_logger", "../logs/daily_log.log", 0, 0, false, 3);
    file_logger->set_level(spdlog::level::debug); // 设置文件日志级别
    file_logger->flush_on(spdlog::level::info); // 设置自动刷新级别

    // 设置日志级别
    spdlog::set_level(spdlog::level::debug); // 可以设置为 info、warn、error 等

    // 记录不同级别的日志
    console->info("Welcome to spdlog!");
    file_logger->info("Welcome to spdlog!");
    
    console->warn("This is a warning message.");
    file_logger->warn("This is a warning message.");
    
    console->error("This is an error message.");
    file_logger->error("This is an error message.");

    // 记录调试信息
    console->debug("Debugging info: {}", 42);
    file_logger->debug("Debugging info: {}", 42);

    // 记录格式化字符串
    console->info("Formatted number: {:.2f}", 3.14159);
    file_logger->info("Formatted number: {:.2f}", 3.14159);

    return 0;
}
