import time
import random
from collections import deque, defaultdict
from array import array

# Arrays are more efficient for numerical data and require all elements to be of the same type.
# Lists are more flexible and can hold elements of different types.

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

# Function to test performance of array for appending
def test_array_append(n):
    arr = array('i')
    start_time = time.time()
    for i in range(n):
        arr.append(i)
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

# Function to test performance of array for prepending
def test_array_prepend(n):
    arr = array('i')
    start_time = time.time()
    for i in range(n):
        arr.insert(0, i)
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

# Function to test performance of array for random access
def test_array_random_access(n):
    arr = array('i', range(n))
    start_time = time.time()
    for _ in range(n):
        _ = arr[random.randint(0, n-1)]
    end_time = time.time()
    return end_time - start_time

# Function to test performance of defaultdict for inserting key-value pairs
def test_defaultdict_insert(n):
    dd = defaultdict(int)
    start_time = time.time()
    for i in range(n):
        dd[i] = i
    end_time = time.time()
    return end_time - start_time

# Function to test performance of defaultdict for querying key-value pairs
def test_defaultdict_query(n):
    dd = defaultdict(int, {i: i for i in range(n)})
    start_time = time.time()
    for _ in range(n):
        _ = dd[random.randint(0, n-1)]
    end_time = time.time()
    return end_time - start_time

if __name__ == "__main__":
    n = 100000  # Number of elements to add

    list_append_time = test_list_append(n)
    deque_append_time = test_deque_append(n)
    array_append_time = test_array_append(n)
    list_prepend_time = test_list_prepend(n)
    deque_prepend_time = test_deque_prepend(n)
    array_prepend_time = test_array_prepend(n)
    list_random_access_time = test_list_random_access(n)
    deque_random_access_time = test_deque_random_access(n)
    array_random_access_time = test_array_random_access(n)
    defaultdict_insert_time = test_defaultdict_insert(n)
    defaultdict_query_time = test_defaultdict_query(n)

    print(f"Time taken by list for appending: {list_append_time:.6f} seconds")
    print(f"Time taken by deque for appending: {deque_append_time:.6f} seconds")
    print(f"Time taken by array for appending: {array_append_time:.6f} seconds")
    print(f"Time taken by list for prepending: {list_prepend_time:.6f} seconds")
    print(f"Time taken by deque for prepending: {deque_prepend_time:.6f} seconds")
    print(f"Time taken by array for prepending: {array_prepend_time:.6f} seconds")
    print(f"Time taken by list for random access: {list_random_access_time:.6f} seconds")
    print(f"Time taken by deque for random access: {deque_random_access_time:.6f} seconds")
    print(f"Time taken by array for random access: {array_random_access_time:.6f} seconds")
    print(f"Time taken by defaultdict for inserting key-value pairs: {defaultdict_insert_time:.6f} seconds")
    print(f"Time taken by defaultdict for querying key-value pairs: {defaultdict_query_time:.6f} seconds")
    """
    Time taken by list for appending: 0.007607 seconds
    Time taken by deque for appending: 0.004413 seconds
    Time taken by array for appending: 0.009748 seconds
    Time taken by list for prepending: 0.871959 seconds
    Time taken by deque for prepending: 0.002194 seconds
    Time taken by array for prepending: 0.273761 seconds
    Time taken by list for random access: 0.033295 seconds
    Time taken by deque for random access: 0.165767 seconds
    Time taken by array for random access: 0.037452 seconds
    Time taken by defaultdict for inserting key-value pairs: 0.012345 seconds
    Time taken by defaultdict for querying key-value pairs: 0.062809 seconds
    """
