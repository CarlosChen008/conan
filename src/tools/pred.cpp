#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct KLine {
    std::string time;
    double open;
    double high;
    double low;
    double close;
};

std::vector<KLine> readCSV(const std::string& filename) {
    std::vector<KLine> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return data;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        KLine kline;
        std::string token;

        std::getline(ss, kline.time, ',');
        std::getline(ss, token, ',');
        kline.open = std::stod(token);
        std::getline(ss, token, ',');
        kline.high = std::stod(token);
        std::getline(ss, token, ',');
        kline.low = std::stod(token);
        std::getline(ss, token, ',');
        kline.close = std::stod(token);

        data.push_back(kline);
    }

    file.close();
    return data;
}

double calculateExpectedReturn(const std::vector<KLine>& data, const std::string& pattern) {
    double totalReturn = 0.0;
    int count = 0;

    for (size_t i = 0; i < data.size() - 5; ++i) {
        // Example pattern: if the close price is higher than the open price
        // this indicates a bullish pattern
        if (pattern == "bullish" && data[i].close > data[i].open) {
            double return5min = (data[i + 5].close - data[i].close) / data[i].close;
            totalReturn += return5min;
            ++count;
        }
        // Add more patterns as needed
    }

    return count > 0 ? totalReturn / count : 0.0;
}

int main() {
    std::string filename = "data.csv";
    std::vector<KLine> data = readCSV(filename);

    if (data.empty()) {
        std::cerr << "No data read from file" << std::endl;
        return 1;
    }

    std::string pattern = "bullish";
    double expectedReturn = calculateExpectedReturn(data, pattern);

    std::cout << "Expected return for pattern '" << pattern << "' over 5 minutes: " << expectedReturn << std::endl;

    return 0;
}