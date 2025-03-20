#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <random>
#include <fstream>
#include <algorithm>  // 添加这一行用于 std::sort

using namespace std;

class LDA {
public:
    LDA(int num_topics, int num_iterations, double alpha, double beta)
        : num_topics(num_topics), num_iterations(num_iterations), alpha(alpha), beta(beta) {}

    void fit(const vector<vector<string>>& documents) {
        initialize(documents);
        for (int iter = 0; iter < num_iterations; ++iter) {
            int topic_changes = 0;  // 记录本轮topic变更数量
            
            for (size_t d = 0; d < documents.size(); ++d) {
                for (size_t n = 0; n < documents[d].size(); ++n) {
                    int old_topic = topics[d][n];
                    string word = documents[d][n];
                    int word_id = word2id[word];
                    
                    // Decrement counts
                    doc_topic_count[d][old_topic]--;
                    topic_word_count[old_topic][word_id]--;
                    topic_count[old_topic]--;
                    doc_count[d]--;

                    // Sample new topic
                    vector<double> p(num_topics);
                    double sum_p = 0.0;
                    for (int k = 0; k < num_topics; ++k) {
                        p[k] = ((doc_topic_count[d][k] + alpha) / (doc_count[d] + num_topics * alpha)) *
                            ((topic_word_count[k][word_id] + beta) / (topic_count[k] + vocab_size * beta));
                        sum_p += p[k];
                    }
                    for (int k = 0; k < num_topics; ++k) {
                        p[k] /= sum_p;
                    }
                    int new_topic = sample(p);

                    // 记录topic是否发生变化
                    if (new_topic != old_topic) {
                        topic_changes++;
                    }

                    // Increment counts
                    topics[d][n] = new_topic;
                    doc_topic_count[d][new_topic]++;
                    topic_word_count[new_topic][word_id]++;
                    topic_count[new_topic]++;
                    doc_count[d]++;

                }
            }
            
            // 打印每轮的统计信息
            print_iteration_stats(iter, topic_changes);
        }
    }

    void print_iteration_stats(int iteration, int changes) {
        cout << "Iteration " << iteration + 1 << ": " 
             << changes << " words changed topics" << endl;
    }

    void print_topics() {
        for (int k = 0; k < num_topics; ++k) {
            cout << "Topic " << k << ": ";
            
            // 将map转换为vector以便排序
            vector<pair<int, int>> word_counts;
            for (const auto& p : topic_word_count[k]) {
                word_counts.push_back(p);
            }
            
            // 按词频降序排序
            std::sort(word_counts.begin(), word_counts.end(),
                [](const pair<int, int>& a, const pair<int, int>& b) {
                    return a.second > b.second;
                });
            
            // 打印前10个高频词
            int top_words = 10;
            for (const auto& p : word_counts) {
                if (top_words == 0) break;
                cout << id2word[p.first] << "(" << p.second << ") ";
                top_words--;
            }
            cout << endl;
        }
    }

    // 保存文档主题分布
    void save_doc_topics(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file for writing: " << filename << endl;
            return;
        }
        
        for (size_t d = 0; d < doc_topic_count.size(); ++d) {
            for (int k = 0; k < num_topics; ++k) {
                double prob = (doc_topic_count[d][k] + alpha) / 
                            (doc_count[d] + num_topics * alpha);
                file << prob;
                if (k < num_topics - 1) file << "\t";
            }
            file << endl;
        }
    }

    // 保存主题词分布
    void save_topic_words(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file for writing: " << filename << endl;
            return;
        }

        for (int k = 0; k < num_topics; ++k) {
            vector<pair<int, double>> word_probs;
            for (const auto& [word_id, count] : topic_word_count[k]) {
                double prob = (count + beta) / (topic_count[k] + vocab_size * beta);
                word_probs.emplace_back(word_id, prob);
            }
            
            sort(word_probs.begin(), word_probs.end(),
                [](const auto& a, const auto& b) { return a.second > b.second; });

            for (const auto& [word_id, prob] : word_probs) {
                file << id2word.at(word_id) << ":" << prob << "\t";
            }
            file << endl;
        }
    }

private:
    int num_topics;
    int num_iterations;
    double alpha;
    double beta;
    int vocab_size;

    vector<vector<int>> topics;
    vector<vector<int>> doc_topic_count;
    vector<unordered_map<int, int>> topic_word_count;
    vector<int> topic_count;
    vector<int> doc_count;  // 新增：记录每个文档的单词数

    unordered_map<string, int> word2id;
    unordered_map<int, string> id2word;

    void initialize(const vector<vector<string>>& documents) {
        int word_id = 0;
        for (const auto& doc : documents) {
            for (const auto& word : doc) {
                if (word2id.find(word) == word2id.end()) {
                    word2id[word] = word_id;
                    id2word[word_id] = word;
                    word_id++;
                }
            }
        }
        vocab_size = word_id;

        topics.resize(documents.size());
        doc_topic_count.resize(documents.size(), vector<int>(num_topics, 0));
        topic_word_count.resize(num_topics);
        topic_count.resize(num_topics, 0);
        doc_count.resize(documents.size(), 0);  // 初始化doc_count

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, num_topics - 1);

        for (size_t d = 0; d < documents.size(); ++d) {
            topics[d].resize(documents[d].size());
            doc_count[d] = documents[d].size();  // 设置初始文档单词数
            for (size_t n = 0; n < documents[d].size(); ++n) {
                int topic = dis(gen);
                topics[d][n] = topic;
                doc_topic_count[d][topic]++;
                topic_word_count[topic][word2id[documents[d][n]]]++;
                topic_count[topic]++;
            }
        }

    }

    int sample(const vector<double>& p) {
        random_device rd;
        mt19937 gen(rd());
        discrete_distribution<> dis(p.begin(), p.end());
        return dis(gen);
    }
};

struct LDAConfig {
    int num_topics;
    int num_iterations;
    double alpha;
    double beta;
    string train_file;
    string doc_topic_file;    // 新增：文档主题分布输出路径
    string topic_word_file;   // 新增：主题词分布输出路径
};

LDAConfig read_config(const string& config_file) {
    LDAConfig config = {0, 0, 0.0, 0.0, "", "", ""};  // 初始化所有值
    ifstream file(config_file);
    if (!file.is_open()) {
        cerr << "Error: Could not open config file: " << config_file << endl;
        exit(1);
    }
    string line;
    
    while (getline(file, line)) {
        // 跳过空行和注释
        if (line.empty() || line[0] == '[' || line[0] == '#') continue;
        
        // 去除行首尾的空格
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        size_t pos = line.find('=');
        if (pos == string::npos) continue;
        
        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);
        
        // 去除key和value的首尾空格
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        
        try {
            if (key == "num_topics") config.num_topics = stoi(value);
            else if (key == "num_iterations") config.num_iterations = stoi(value);
            else if (key == "alpha") config.alpha = stod(value);
            else if (key == "beta") config.beta = stod(value);
            else if (key == "train_file") config.train_file = value;
            else if (key == "doc_topic_file") config.doc_topic_file = value;
            else if (key == "topic_word_file") config.topic_word_file = value;
        } catch (const exception& e) {
            cerr << "Error parsing value for key '" << key << "': " << e.what() << endl;
            exit(1);
        }
    }

    // 验证配置值
    if (config.num_topics <= 0 || config.num_iterations <= 0 || 
        config.alpha <= 0 || config.beta <= 0 || config.train_file.empty()) {
        cerr << "Error: Invalid configuration values detected:" << endl
             << "num_topics: " << config.num_topics << " (must be > 0)" << endl
             << "num_iterations: " << config.num_iterations << " (must be > 0)" << endl
             << "alpha: " << config.alpha << " (must be > 0)" << endl
             << "beta: " << config.beta << " (must be > 0)" << endl
             << "train_file: " << (config.train_file.empty() ? "missing" : config.train_file) << endl;
        exit(1);
    }

    cout << "Config loaded successfully:" << endl
         << "num_topics: " << config.num_topics << endl
         << "num_iterations: " << config.num_iterations << endl
         << "alpha: " << config.alpha << endl
         << "beta: " << config.beta << endl
         << "train_file: " << config.train_file << endl;
    return config;
}

vector<vector<string>> read_documents(const string& filename) {
    vector<vector<string>> documents;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open training file: " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> doc;
        string word;
        while (iss >> word) {
            doc.push_back(word);
        }
        documents.push_back(doc);
    }
    cout << "Documents loaded successfully:" << endl
         << "Number of documents: " << documents.size() << endl;
    if (!documents.empty()) {
        cout << "First document size: " << documents[0].size() << " words" << endl;
    }
    return documents;
}

string parse_args(int argc, char* argv[]) {
    string config_path;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-c" && i + 1 < argc) {
            config_path = argv[++i];
        }
    }
    return config_path;
}

void print_usage() {
    cout << "Usage: LDA -c <config_file_path>" << endl;
    cout << "Example: LDA -c config/lda_config.ini" << endl;
}

int main(int argc, char* argv[]) {
    cout << "Starting LDA program..." << endl;
    
    string config_path = parse_args(argc, argv);
    if (config_path.empty()) {
        print_usage();
        return 1;
    }
    
    cout << "Using config file: " << config_path << endl;
    
    LDAConfig config = read_config(config_path);
    vector<vector<string>> documents = read_documents(config.train_file);
    
    if (documents.empty()) {
        cerr << "Error: No documents loaded" << endl;
        return 1;
    }

    cout << "Initializing LDA model..." << endl;
    LDA lda(config.num_topics, config.num_iterations, config.alpha, config.beta);
    cout << "Starting training..." << endl;
    lda.fit(documents);
    cout << "\nTraining completed. Topic results:" << endl;
    lda.print_topics();

    // 保存结果到文件
    if (!config.doc_topic_file.empty()) {
        cout << "Saving document-topic distribution to " << config.doc_topic_file << endl;
        lda.save_doc_topics(config.doc_topic_file);
    }
    if (!config.topic_word_file.empty()) {
        cout << "Saving topic-word distribution to " << config.topic_word_file << endl;
        lda.save_topic_words(config.topic_word_file);
    }

    return 0;
}
// g++ src/tools/LDA.cpp -o bin/LDA -std=c++11