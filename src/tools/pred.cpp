#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include "absl/strings/str_split.h" // Include absl library

struct KLine {
    std::string time;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

std::vector<KLine> readCSV(const std::string& filename, bool skipHeader = false) {
    std::vector<KLine> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return data;
    }

    if (skipHeader && std::getline(file, line)) {
        // Skip the header line
    }

    while (std::getline(file, line)) {
        KLine kline;
        std::vector<std::string> tokens = absl::StrSplit(line, ',');
        
        if (tokens.size() < 6) continue; // Skip lines with less than 6 columns

        kline.time = tokens[0];
        kline.open = std::stod(tokens[1]);
        kline.high = std::stod(tokens[2]);
        kline.low = std::stod(tokens[3]);
        kline.close = std::stod(tokens[4]);
        kline.volume = std::stod(tokens[5]);

        data.push_back(kline);
    }

    file.close();
    return data;
}

double calculateExpectedReturn(const std::vector<KLine>& data, const std::string& pattern) {
    double totalReturn = 0.0;
    int count = 0;
    int winCount = 0; // Add win count
    std::mutex mtx;

    auto worker = [&](size_t start, size_t end) {
        double localTotalReturn = 0.0;
        int localCount = 0;
        int localWinCount = 0; // Add local win count

        for (size_t i = start; i < end; ++i) {
            // Example pattern: if the close price is higher than the open price
            // this indicates a bullish pattern
            if (pattern == "bullish" && data[i].close > data[i].open) {
                double return5min = (data[i + 5].close - data[i].close) / data[i].close;
                localTotalReturn += return5min;
                ++localCount;
                if (return5min > 0) {
                    ++localWinCount; // Increment local win count if return is positive
                }
            }
            // Add more patterns as needed
        }

        std::lock_guard<std::mutex> lock(mtx);
        totalReturn += localTotalReturn;
        count += localCount;
        winCount += localWinCount; // Add local win count to global win count
    };

    size_t numThreads = std::thread::hardware_concurrency();
    size_t blockSize = (data.size() - 5) / numThreads;
    std::vector<std::thread> threads;

    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * blockSize;
        size_t end = (i == numThreads - 1) ? data.size() - 5 : start + blockSize;
        threads.emplace_back(worker, start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    double winRate = count > 0 ? static_cast<double>(winCount) / count : 0.0; // Calculate win rate
    std::cout << "Win rate for pattern '" << pattern << "': " << winRate * 100 << "%" << std::endl; // Print win rate

    return count > 0 ? totalReturn / count : 0.0;
}

int main() {
    std::string filename = "data.csv";
    bool skipHeader = true; // Set to true to skip the header
    std::vector<KLine> data = readCSV(filename, skipHeader);

    if (data.empty()) {
        std::cerr << "No data read from file" << std::endl;
        return 1;
    }

    std::string pattern = "bullish";
    double expectedReturn = calculateExpectedReturn(data, pattern);

    std::cout << "Expected return for pattern '" << pattern << "' over 5 minutes: " << expectedReturn << std::endl;

    return 0;
}
// g++ -std=c++17 --static src/tools/pred.cpp -o pred -Wl,--start-group -I/home/chenliguo/.conan2/p/absei9cc4b7050682d/p/include -L/home/chenliguo/.conan2/p/absei9cc4b7050682d/p/lib -labsl_periodic_sampler -labsl_scoped_set_env -labsl_leak_check -labsl_bad_any_cast_impl -labsl_failure_signal_handler -labsl_random_internal_distribution_test_util -labsl_random_distributions -labsl_random_seed_sequences -labsl_random_internal_pool_urbg -labsl_random_internal_randen -labsl_random_internal_randen_hwaes -labsl_random_internal_randen_hwaes_impl -labsl_random_internal_randen_slow -labsl_random_internal_platform -labsl_random_internal_seed_material -labsl_random_seed_gen_exception -labsl_log_initialize -labsl_cordz_sample_token -labsl_statusor -labsl_status -labsl_log_internal_check_op -labsl_die_if_null -labsl_log_internal_conditions -labsl_log_internal_message -labsl_examine_stack -labsl_log_internal_format -labsl_log_internal_proto -labsl_log_internal_nullguard -labsl_log_internal_log_sink_set -labsl_log_internal_globals -labsl_log_sink -labsl_log_entry -labsl_strerror -labsl_log_flags -labsl_log_globals -labsl_vlog_config_internal -labsl_log_internal_fnmatch -labsl_flags_parse -labsl_flags_usage -labsl_flags_usage_internal -labsl_flags_internal -labsl_flags_marshalling -labsl_flags_reflection -labsl_flags_private_handle_accessor -labsl_flags_commandlineflag -labsl_flags_commandlineflag_internal -labsl_flags_config -labsl_flags_program_name -labsl_cord -labsl_cordz_info -labsl_cord_internal -labsl_cordz_functions -labsl_cordz_handle -labsl_crc_cord_state -labsl_crc32c -labsl_crc_internal -labsl_crc_cpu_detect -labsl_str_format_internal -labsl_raw_hash_set -labsl_hash -labsl_city -labsl_bad_variant_access -labsl_low_level_hash -labsl_hashtablez_sampler -labsl_exponential_biased -labsl_bad_optional_access -labsl_synchronization -lpthread -labsl_graphcycles_internal -labsl_kernel_timeout_internal -labsl_stacktrace -labsl_symbolize -labsl_debugging_internal -labsl_demangle_internal -labsl_malloc_internal -lpthread -labsl_time -labsl_civil_time -labsl_strings -lm -labsl_strings_internal -labsl_string_view -labsl_base -lpthread -lrt -labsl_spinlock_wait -labsl_int128 -labsl_throw_delegate -labsl_raw_logging_internal -labsl_log_severity -labsl_time_zone -lpthread -Wl,--end-group