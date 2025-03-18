import time
import json
import ujson
import orjson

data = {
    "name": "John",
    "age": 30,
    "city": "New York",
    "children": [
        {"name": "Anna", "age": 10},
        {"name": "Alex", "age": 8}
    ]
}

def test_json_libs(data):
    # Test json.dumps
    start = time.time()
    for _ in range(100000):
        json_str = json.dumps(data)
    print(f"json.dumps: {time.time() - start:.6f} seconds")

    # Test json.loads
    start = time.time()
    for _ in range(100000):
        json.loads(json_str)
    print(f"json.loads: {time.time() - start:.6f} seconds")

    # Test ujson.dumps
    start = time.time()
    for _ in range(100000):
        ujson_str = ujson.dumps(data)
    print(f"ujson.dumps: {time.time() - start:.6f} seconds")

    # Test ujson.loads
    start = time.time()
    for _ in range(100000):
        ujson.loads(ujson_str)
    print(f"ujson.loads: {time.time() - start:.6f} seconds")

    # Test orjson.dumps
    start = time.time()
    for _ in range(100000):
        orjson_str = orjson.dumps(data)
    print(f"orjson.dumps: {time.time() - start:.6f} seconds")

    # Test orjson.loads
    start = time.time()
    for _ in range(100000):
        orjson.loads(orjson_str)
    print(f"orjson.loads: {time.time() - start:.6f} seconds")

if __name__ == "__main__":
    test_json_libs(data)
    """
        json.dumps: 0.220375 seconds
        json.loads: 0.184415 seconds
        ujson.dumps: 0.098533 seconds
        ujson.loads: 0.114357 seconds
        orjson.dumps: 0.026280 seconds
        orjson.loads: 0.063810 seconds
    """
