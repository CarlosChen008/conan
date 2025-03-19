#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(const string& key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }
        // Move the accessed element to the front of the list
        // splice() transfers elements from one list to another.
        // Here, it moves the element pointed by cacheMap[key] to the beginning of cacheList.
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        return cacheMap[key]->second;
    }

    void put(const string& key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            // Update the value and move the element to the front of the list
            cacheMap[key]->second = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        } else {
            if (cacheMap.size() >= capacity) {
                // Remove the least recently used element
                string lruKey = cacheList.back().first;
                cacheList.pop_back();
                cacheMap.erase(lruKey);
            }
            // Insert the new element at the front of the list
            cacheList.emplace_front(key, value);
            cacheMap[key] = cacheList.begin();
        }
    }

private:
    int capacity;
    list<pair<string, int>> cacheList; // List of key-value pairs
    unordered_map<string, list<pair<string, int>>::iterator> cacheMap; // Key to list iterator map
};

int main() {
    LRUCache cache(2);
    cache.put("1", 1);
    cache.put("2", 2);
    cout << cache.get("1") << endl; // returns 1
    cache.put("3", 3); // evicts key "2"
    cout << cache.get("2") << endl; // returns -1 (not found)
    cache.put("4", 4); // evicts key "1"
    cout << cache.get("1") << endl; // returns -1 (not found)
    cout << cache.get("3") << endl; // returns 3
    cout << cache.get("4") << endl; // returns 4
    return 0;
}
// g++ lru.cpp -o lru.bin --std=c++17 --static