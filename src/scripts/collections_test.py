import time
import random
from collections import deque

# Function to test performance of list for appending
def test_list_append(n):
    lst = []
    start_time = time.time()
    for i in range(n):
        lst.append(i)
    end_time = time.time()
    return end_time - start_time

# Function to test performance of deque for appending
def test_deque_append(n):
    dq = deque()
    start_time = time.time()
    for i in range(n):
        dq.append(i)
    end_time = time.time()
    return end_time - start_time

# Function to test performance of list for prepending
def test_list_prepend(n):
    lst = []
    start_time = time.time()
    for i in range(n):
        lst.insert(0, i)
    end_time = time.time()
    return end_time - start_time

# Function to test performance of deque for prepending
def test_deque_prepend(n):
    dq = deque()
    start_time = time.time()
    for i in range(n):
        dq.appendleft(i)
    end_time = time.time()
    return end_time - start_time

# Function to test performance of list for random access
def test_list_random_access(n):
    lst = list(range(n))
    start_time = time.time()
    for _ in range(n):
        _ = lst[random.randint(0, n-1)]
    end_time = time.time()
    return end_time - start_time

# Function to test performance of deque for random access
def test_deque_random_access(n):
    dq = deque(range(n))
    start_time = time.time()
    for _ in range(n):
        _ = dq[random.randint(0, n-1)]
    end_time = time.time()
    return end_time - start_time

if __name__ == "__main__":
    n = 100000  # Number of elements to add

    list_append_time = test_list_append(n)
    deque_append_time = test_deque_append(n)
    list_prepend_time = test_list_prepend(n)
    deque_prepend_time = test_deque_prepend(n)
    list_random_access_time = test_list_random_access(n)
    deque_random_access_time = test_deque_random_access(n)

    print(f"Time taken by list for appending: {list_append_time:.6f} seconds")
    print(f"Time taken by deque for appending: {deque_append_time:.6f} seconds")
    print(f"Time taken by list for prepending: {list_prepend_time:.6f} seconds")
    print(f"Time taken by deque for prepending: {deque_prepend_time:.6f} seconds")
    print(f"Time taken by list for random access: {list_random_access_time:.6f} seconds")
    print(f"Time taken by deque for random access: {deque_random_access_time:.6f} seconds")
    """
    Time taken by list for appending: 0.005559 seconds
    Time taken by deque for appending: 0.005181 seconds
    Time taken by list for prepending: 0.904640 seconds
    Time taken by deque for prepending: 0.002640 seconds
    Time taken by list for random access: 0.036173 seconds
    Time taken by deque for random access: 0.168359 seconds
    """
