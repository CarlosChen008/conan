#include <iostream>
#include <vector>
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/time/time.h"
#include "absl/container/flat_hash_map.h"
#include "absl/random/random.h"
#include "absl/log/log.h"

int main() {
    // 字符串处理
    {
        std::string str1 = "Hello";
        std::string str2 = "Abseil";
        std::string str3 = "!";
        std::string result = absl::StrCat(str1, ", ", str2, str3);
        std::cout << "String concatenation: " << result << std::endl;

        std::string str = "a,b,c";
        std::vector<std::string> vec = absl::StrSplit(str, ',');
        std::cout << "String splitting: ";
        for (const auto& s : vec) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }

    // 时间处理
    {
        absl::Time now = absl::Now();
        std::cout << "Current time: " << now << std::endl;

        std::string formatted_time = absl::FormatTime("%Y-%m-%d %H:%M:%S", now, absl::LocalTimeZone());
        std::cout << "Formatted time: " << formatted_time << std::endl;
    }

    // 容器操作
    {
        absl::flat_hash_map<std::string, int> map;
        map["apple"] = 1;
        map["banana"] = 2;
        map["cherry"] = 3;

        std::cout << "Container operations:" << std::endl;
        for (const auto& pair : map) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    // 随机数生成
    {
        thread_local absl::BitGen bitgen;
        int random_num = absl::Uniform(bitgen, 0, 100);
        std::cout << "Random number: " << random_num << std::endl;
    }

    // 日志记录
    {
        LOG(INFO) << "This is an info message";
        LOG(WARNING) << "This is a warning message";
        LOG(ERROR) << "This is an error message";
    }

    return 0;
}
