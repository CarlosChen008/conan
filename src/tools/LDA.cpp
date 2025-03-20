#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <random>
#include <fstream>

using namespace std;

class LDA {
public:
    LDA(int num_topics, int num_iterations, double alpha, double beta)
        : num_topics(num_topics), num_iterations(num_iterations), alpha(alpha), beta(beta) {}

    void fit(const vector<vector<string>>& documents) {
        initialize(documents);
        for (int iter = 0; iter < num_iterations; ++iter) {
            for (size_t d = 0; d < documents.size(); ++d) {
                for (size_t n = 0; n < documents[d].size(); ++n) {
                    int topic = topics[d][n];
                    string word = documents[d][n];
                    int word_id = word2id[word];

                    // Decrement counts
                    doc_topic_count[d][topic]--;
                    topic_word_count[topic][word_id]--;
                    topic_count[topic]--;

                    // Sample new topic
                    vector<double> p(num_topics);
                    double sum_p = 0.0;
                    for (int k = 0; k < num_topics; ++k) {
                        p[k] = (doc_topic_count[d][k] + alpha) *
                               (topic_word_count[k][word_id] + beta) /
                               (topic_count[k] + beta * vocab_size);
                        sum_p += p[k];
                    }
                    for (int k = 0; k < num_topics; ++k) {
                        p[k] /= sum_p;
                    }
                    topic = sample(p);

                    // Increment counts
                    topics[d][n] = topic;
                    doc_topic_count[d][topic]++;
                    topic_word_count[topic][word_id]++;
                    topic_count[topic]++;
                }
            }
        }
    }

    void print_topics() {
        for (int k = 0; k < num_topics; ++k) {
            cout << "Topic " << k << ": ";
            for (const auto& word_id : topic_word_count[k]) {
                cout << id2word[word_id.first] << " ";
            }
            cout << endl;
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

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, num_topics - 1);

        for (size_t d = 0; d < documents.size(); ++d) {
            topics[d].resize(documents[d].size());
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

vector<vector<string>> read_documents(const string& filename) {
    vector<vector<string>> documents;
    ifstream file(filename);
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
    return documents;
}

int main() {
    string filename = "train.dat"; // Path to your training data
    vector<vector<string>> documents = read_documents(filename);

    int num_topics = 3;
    int num_iterations = 100;
    double alpha = 0.1;
    double beta = 0.01;

    LDA lda(num_topics, num_iterations, alpha, beta);
    lda.fit(documents);
    lda.print_topics();

    return 0;
}
// g++ src/tools/LDA.cpp -o bin/LDA -std=c++11