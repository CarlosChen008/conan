import os
import pickle
from collections import OrderedDict
from typing import Any  # 新增导入

class LRUCache:
    def __init__(self, capacity: int):
        self.cache = OrderedDict()
        self.capacity = capacity

    def get(self, key: str) -> Any:  # 修改返回类型为 Any
        if key not in self.cache:
            return None
        value = self.cache.pop(key)
        self.cache[key] = value
        return value

    def put(self, key: str, value: Any) -> None:  # 修改参数类型为 Any
        if key in self.cache:
            self.cache.pop(key)
        elif len(self.cache) >= self.capacity:
            self.cache.popitem(last=False)
        self.cache[key] = value

    def save_to_file(self, file_path: str) -> None:
        with open(file_path, 'wb') as f:
            pickle.dump(self.cache, f)

    def load_from_file(self, file_path: str) -> None:
        if os.path.exists(file_path):
            with open(file_path, 'rb') as f:
                self.cache = pickle.load(f)

# Example usage:
lru = LRUCache(3)
lru.put("a", "1")
lru.put("b", "2")
lru.put("c", "3")
lru.save_to_file("lru_cache.pkl")
lru.load_from_file("lru_cache.pkl")
print(lru.get("a"))