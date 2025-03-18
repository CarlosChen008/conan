#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <queue> // 添加优先队列头文件

int main() {
    // Vector demo
    std::vector<int> vec = {1, 2, 3, 4, 5}; // 创建一个包含初始值的向量, O(n)
    vec.push_back(6); // 在向量末尾添加元素6, O(1) 均摊
    vec.insert(vec.begin(), 0); // 在向量开头插入元素0, O(n)
    vec.erase(vec.begin() + 1); // 移除向量中第二个元素, O(n)
    vec.pop_back(); // 移除向量末尾的元素, O(1)
    std::cout << "Vector elements: "; // 输出提示信息
    for (const auto& elem : vec) { // 遍历向量中的每个元素, O(n)
        std::cout << elem << " "; // 输出当前元素
    }
    std::cout << std::endl; // 输出换行符

    /*
        vector 当数组中内存空间不够时，会重新申请一块内存空间并进行内存拷贝; VS6.0是两倍，VS2005是1.5倍;
    */

    // List demo
    std::list<int> lst = {1, 2, 3, 4, 5}; // 创建一个包含初始值的列表, O(n)
    lst.push_back(6); // 在列表末尾添加元素6, O(1)
    lst.push_front(0); // 在列表开头添加元素0, O(1)
    lst.pop_back(); // 移除列表末尾的元素, O(1)
    lst.pop_front(); // 移除列表开头的元素, O(1)
    lst.remove(3); // 移除列表中所有值为3的元素, O(n)
    std::cout << "List elements: "; // 输出提示信息
    for (const auto& elem : lst) { // 遍历列表中的每个元素, O(n)
        std::cout << elem << " "; // 输出当前元素
    }
    std::cout << std::endl; // 输出换行符
    /*
        优点：(1) 不使用连续内存完成动态操作。
                (2) 在内部方便的进行插入和删除操作
                (3) 可在两端进行push、pop
        缺点：(1) 不能进行内部的随机访问，即不支持[ ]操作符和vector.at()
                (2) 相对于verctor占用内存多
    */

    // Deque demo (deque是在功能上合并了vector和list, 类似python的list)
    std::deque<int> deq = {1, 2, 3, 4, 5}; // 创建一个包含初始值的双端队列, O(n)
    deq.push_back(6); // 在双端队列末尾添加元素6, O(1)
    deq.push_front(0); // 在双端队列开头添加元素0, O(1)
    deq.pop_back(); // 移除双端队列末尾的元素, O(1)
    deq.pop_front(); // 移除双端队列开头的元素, O(1)
    deq.insert(deq.begin() + 2, 10); // 在双端队列中间插入元素10, O(n)
    deq.erase(deq.begin() + 2); // 移除双端队列中间的元素, O(n)
    std::cout << "Deque elements: "; // 输出提示信息
    for (const auto& elem : deq) { // 遍历双端队列中的每个元素, O(n)
        std::cout << elem << " "; // 输出当前元素
    }
    std::cout << std::endl; // 输出换行符

    // deque的中央数组是一个指向多个小数组的指针数组，每个小数组的大小是固定的（通常是64或128），
    // 这样可以在两端快速插入和删除元素。deque的中央数组布局如下：
    // [空闲] [空闲] [块指针1] [块指针2] [块指针3] [块指针4] [空闲] [空闲]
    /*
        List vs Deque:
        1. List是双向链表，Deque是双端队列，底层实现不同。
        2. List在插入和删除操作上性能更好，因为它不需要移动其他元素。
        3. Deque支持随机访问，但List不支持。
        4. Deque在内存使用上更高效，因为它使用连续的内存块。
    */
    /*
        deque的优点：
        1. 支持在两端快速插入和删除元素。
        2. 支持随机访问，类似于vector。
        3. 内存使用效率高，因为它使用连续的内存块。

        deque的缺点：
        1. 相比于vector，deque的内存开销更大，因为它需要维护多个小数组。
        2. 在中间插入和删除元素时性能较差，因为需要移动其他元素。
    */
    // Set demo
    std::set<int> st = {1, 2, 3, 4, 5}; // 创建一个包含初始值的集合, O(n log n)
    st.insert(6); // 在集合中插入元素6, O(log n)
    st.erase(3); // 从集合中移除元素3, O(log n)
    auto it = st.find(4); // 查找集合中的元素4, O(log n)
    if (it != st.end()) {
        std::cout << "Found 4 in set" << std::endl; // 输出查找结果
    }
    std::cout << "Set elements: "; // 输出提示信息
    for (const auto& elem : st) { // 遍历集合中的每个元素, O(n)
        std::cout << elem << " "; // 输出当前元素
    }
    std::cout << std::endl; // 输出换行符

    // Map demo
    std::map<int, std::string> mp = {{1, "one"}, {2, "two"}, {3, "three"}}; // 创建一个包含初始值的映射, O(n log n)
    mp[4] = "four"; // 在映射中插入或更新键值对, O(log n)
    mp.erase(2); // 从映射中移除键为2的键值对, O(log n)
    auto mit = mp.find(3); // 查找映射中的键3, O(log n)
    if (mit != mp.end()) {
        std::cout << "Found key 3 with value " << mit->second << std::endl; // 输出查找结果
    }
    std::cout << "Map elements: "; // 输出提示信息
    for (const auto& pair : mp) { // 遍历映射中的每个键值对, O(n)
        std::cout << "{" << pair.first << ", " << pair.second << "} "; // 输出当前键值对
    }
    std::cout << std::endl; // 输出换行符

    // Unordered Map demo
    std::unordered_map<int, std::string> ump = {{1, "one"}, {2, "two"}, {3, "three"}}; // 创建一个包含初始值的无序映射, O(n)
    ump[4] = "four"; // 在无序映射中插入或更新键值对, O(1) 均摊
    ump.erase(2); // 从无序映射中移除键为2的键值对, O(1) 均摊
    auto umit = ump.find(3); // 查找无序映射中的键3, O(1) 均摊
    if (umit != ump.end()) {
        std::cout << "Found key 3 with value " << umit->second << std::endl; // 输出查找结果
    }
    if (ump.count(4) > 0) { // 检查无序映射中是否存在键4, O(1) 均摊
        std::cout << "Key 4 is in unordered map with value " << ump[4] << std::endl; // 输出检查结果
    }
    std::cout << "Unordered Map elements: "; // 输出提示信息
    for (const auto& pair : ump) { // 遍历无序映射中的每个键值对, O(n)
        std::cout << "{" << pair.first << ", " << pair.second << "} "; // 输出当前键值对
    }
    std::cout << std::endl; // 输出换行符

    // Unordered Set demo
    std::unordered_set<int> ust = {1, 2, 3, 4, 5}; // 创建一个包含初始值的无序集合, O(n)
    ust.insert(6); // 在无序集合中插入元素6, O(1) 均摊
    ust.erase(3); // 从无序集合中移除元素3, O(1) 均摊
    auto usit = ust.find(4); // 查找无序集合中的元素4, O(1) 均摊
    if (usit != ust.end()) {
        std::cout << "Found 4 in unordered set" << std::endl; // 输出查找结果
    }
    if (ust.count(5) > 0) { // 检查无序集合中是否存在元素5, O(1) 均摊
        std::cout << "5 is in unordered set" << std::endl; // 输出检查结果
    }
    std::cout << "Unordered Set elements: "; // 输出提示信息
    for (const auto& elem : ust) { // 遍历无序集合中的每个元素, O(n)
        std::cout << elem << " "; // 输出当前元素
    }
    std::cout << std::endl; // 输出换行符

    // String demo
    std::string str = "Hello, World!"; // 创建一个包含初始值的字符串, O(n)
    str.append(" How are you?"); // 在字符串末尾追加内容, O(m) 其中m为追加内容的长度
    str.insert(7, "beautiful "); // 在字符串中间插入内容, O(n)
    str.erase(7, 10); // 从字符串中间移除内容, O(n)
    std::cout << "String: " << str << std::endl; // 输出字符串, O(n)

    // Algorithm demo
    std::sort(vec.begin(), vec.end(), std::greater<int>()); // 对向量进行降序排序, O(n log n)
    std::sort(vec.begin(), vec.end()); // 对向量进行升序排序, O(n log n)
    std::reverse(vec.begin(), vec.end()); // 反转向量中的元素顺序, O(n)
    std::cout << "Sorted vector in descending order: "; // 输出提示信息
    for (const auto& elem : vec) { // 遍历向量中的每个元素, O(n)
        std::cout << elem << " "; // 输出当前元素
    }
    std::cout << std::endl; // 输出换行符

    // Priority Queue demo
    std::priority_queue<int> pq; // 创建一个空的优先队列, O(1)
    pq.push(5); // 向优先队列中插入元素5, O(log n)
    pq.push(1); // 向优先队列中插入元素1, O(log n)
    pq.push(3); // 向优先队列中插入元素3, O(log n)
    pq.push(4); // 向优先队列中插入元素4, O(log n)
    pq.push(2); // 向优先队列中插入元素2, O(log n)

    std::cout << "Priority Queue elements (in descending order): "; // 输出提示信息
    while (!pq.empty()) { // 当优先队列不为空时, O(n log n)
        std::cout << pq.top() << " "; // 输出优先队列的顶部元素, O(1)
        pq.pop(); // 移除优先队列的顶部元素, O(log n)
    }
    std::cout << std::endl; // 输出换行符

    /*
        优先队列的实现:
        1. 优先队列通常使用堆（heap）数据结构实现，C++标准库中的优先队列使用最大堆。
        2. 最大堆是一种完全二叉树，其中每个节点的值都大于或等于其子节点的值。
        3. 插入和删除操作的时间复杂度为O(log n)，访问顶部元素的时间复杂度为O(1)。
    */

    // stack
    std::stack<int> stck; // 创建一个空的栈, O(1)
    stck.push(1); // 向栈中插入元素1, O(1)
    stck.push(2); // 向栈中插入元素2, O(1)
    stck.push(3); // 向栈中插入元素3, O(1)
    std::cout << "Stack top element: " << stck.top() << std::endl; // 输出栈顶元素, O(1)
    stck.pop(); // 移除栈顶元素, O(1)
    std::cout << "Stack top element after pop: " << stck.top() << std::endl; // 输出栈顶元素, O(1)
    stck.pop(); // 移除栈顶元素, O(1)
    std::cout << "Stack top element after pop: " << stck.top() << std::endl; // 输出栈顶元素, O(1)
    stck.pop(); // 移除栈顶元素, O(1)
    /*
        stack的实现:
        1. 栈通常使用链表或动态数组实现。
        2. 链表实现的栈在插入和删除操作上性能更好，因为它不需要移动其他元素。
        3. 动态数组实现的栈在内存使用上更高效，但在扩展时可能需要移动其他元素。
    */
    // queue
    std::queue<int> que; // 创建一个空的队列, O(1)
    que.push(1); // 向队列中插入元素1, O(1)
    que.push(2); // 向队列中插入元素2, O(1)
    que.push(3); // 向队列中插入元素3, O(1)
    std::cout << "Queue front element: " << que.front() << std::endl; // 输出队列前端元素, O(1)
    que.pop(); // 移除队列前端元素, O(1)
    std::cout << "Queue front element after pop: " << que.front() << std::endl; // 输出队列前端元素, O(1)
    que.pop(); // 移除队列前端元素, O(1)
    std::cout << "Queue front element after pop: " << que.front() << std::endl; // 输出队列前端元素, O(1)
    que.pop(); // 移除队列前端元素, O(1)
    /*
        queue的实现:
        1. 队列通常使用链表或动态数组实现。
        2. 链表实现的队列在插入和删除操作上性能更好，因为它不需要移动其他元素。
        3. 动态数组实现的队列在内存使用上更高效，但在扩展时可能需要移动其他元素。
    */
    /*
        stack vs queue:
        1. stack是后进先出（LIFO）的数据结构，queue是先进先出（FIFO）的数据结构。
        2. stack支持push和pop操作，queue支持push和pop操作。
        3. stack的top操作返回栈顶元素，queue的front操作返回队列前端元素。
    */
    /*
        stack的优点：
        1. 支持后进先出的数据访问模式，适合处理递归和回溯问题。
        2. 实现简单，内存使用高效。

        stack的缺点：
        1. 不支持随机访问，只能访问栈顶元素。
        2. 在需要频繁插入和删除操作时性能较差。

        queue的优点：
        1. 支持先进先出的数据访问模式，适合处理排队和调度问题。
        2. 实现简单，内存使用高效。

        queue的缺点：
        1. 不支持随机访问，只能访问队列前端元素。
        2. 在需要频繁插入和删除操作时性能较差。
    */
   // 使用 list 实现队列
    std::list<int> lque; // 创建一个空的列表作为队列, O(1)
    lque.push_back(1); // 向队列中插入元素1, O(1)
    lque.push_back(2); // 向队列中插入元素2, O(1)
    lque.push_back(3); // 向队列中插入元素3, O(1)
    std::cout << "List Queue front element: " << lque.front() << std::endl; // 输出队列前端元素, O(1)
    lque.pop_front(); // 移除队列前端元素, O(1)
    std::cout << "List Queue front element after pop: " << lque.front() << std::endl; // 输出队列前端元素, O(1)
    lque.pop_front(); // 移除队列前端元素, O(1)
    std::cout << "List Queue front element after pop: " << lque.front() << std::endl; // 输出队列前端元素, O(1)
    lque.pop_front(); // 移除队列前端元素, O(1)
    /*
        使用 list 实现队列的优点：
        1. 支持在两端快速插入和删除元素。
        2. 内存使用效率高，因为它使用连续的内存块。

        使用 list 实现队列的缺点：
        1. 相比于 vector，list 的内存开销更大，因为它需要维护多个小数组。
        2. 在中间插入和删除元素时性能较差。
    */
    // 使用 list 实现栈
    std::list<int> lstck; // 创建一个空的列表作为栈, O(1)
    lstck.push_back(1); // 向栈中插入元素1, O(1)
    lstck.push_back(2); // 向栈中插入元素2, O(1)
    lstck.push_back(3); // 向栈中插入元素3, O(1)
    std::cout << "List Stack top element: " << lstck.back() << std::endl; // 输出栈顶元素, O(1)
    lstck.pop_back(); // 移除栈顶元素, O(1)
    std::cout << "List Stack top element after pop: " << lstck.back() << std::endl; // 输出栈顶元素, O(1)
    lstck.pop_back(); // 移除栈顶元素, O(1)
    std::cout << "List Stack top element after pop: " << lstck.back() << std::endl; // 输出栈顶元素, O(1)
    lstck.pop_back(); // 移除栈顶元素, O(1)
    /*
        使用 list 实现栈的优点：
        1. 支持后进先出的数据访问模式，适合处理递归和回溯问题。
        2. 内存使用效率高，因为它使用连续的内存块。

        使用 list 实现栈的缺点：
        1. 相比于 vector，list 的内存开销更大，因为它需要维护多个小数组。
        2. 在中间插入和删除元素时性能较差。
    */
    // 使用 deque 实现栈
    std::deque<int> dstack; // 创建一个空的双端队列作为栈, O(1)
    dstack.push_back(1); // 向栈中插入元素1, O(1)
    dstack.push_back(2); // 向栈中插入元素2, O(1)
    dstack.push_back(3); // 向栈中插入元素3, O(1)
    std::cout << "Deque Stack top element: " << dstack.back() << std::endl; // 输出栈顶元素, O(1)
    dstack.pop_back(); // 移除栈顶元素, O(1)
    std::cout << "Deque Stack top element after pop: " << dstack.back() << std::endl; // 输出栈顶元素, O(1)
    dstack.pop_back(); // 移除栈顶元素, O(1)
    std::cout << "Deque Stack top element after pop: " << dstack.back() << std::endl; // 输出栈顶元素, O(1)
    dstack.pop_back(); // 移除栈顶元素, O(1)
    /*
        使用 deque 实现栈的优点：
        1. 支持后进先出的数据访问模式，适合处理递归和回溯问题。
        2. 内存使用效率高，因为它使用连续的内存块。

        使用 deque 实现栈的缺点：
        1. 相比于 vector，deque 的内存开销更大，因为它需要维护多个小数组。
        2. 在中间插入和删除元素时性能较差。
    */
    // 使用 deque 实现队列
    std::deque<int> dque; // 创建一个空的双端队列作为队列, O(1)
    dque.push_back(1); // 向队列中插入元素1, O(1)
    dque.push_back(2); // 向队列中插入元素2, O(1)
    dque.push_back(3); // 向队列中插入元素3, O(1)
    std::cout << "Deque Queue front element: " << dque.front() << std::endl; // 输出队列前端元素, O(1)
    dque.pop_front(); // 移除队列前端元素, O(1)
    std::cout << "Deque Queue front element after pop: " << dque.front() << std::endl; // 输出队列前端元素, O(1)
    dque.pop_front(); // 移除队列前端元素, O(1)
    std::cout << "Deque Queue front element after pop: " << dque.front() << std::endl; // 输出队列前端元素, O(1)
    dque.pop_front(); // 移除队列前端元素, O(1)
    /*
        使用 deque 实现队列的优点：
        1. 支持在两端快速插入和删除元素。
        2. 内存使用效率高，因为它使用连续的内存块。

        使用 deque 实现队列的缺点：
        1. 相比于 vector，deque 的内存开销更大，因为它需要维护多个小数组。
        2. 在中间插入和删除元素时性能较差。
    */
    // 使用 vector 实现栈
    std::vector<int> vstack; // 创建一个空的向量作为栈, O(1)
    vstack.push_back(1); // 向栈中插入元素1, O(1)
    vstack.push_back(2); // 向栈中插入元素2, O(1)
    vstack.push_back(3); // 向栈中插入元素3, O(1)
    std::cout << "Vector Stack top element: " << vstack.back() << std::endl; // 输出栈顶元素, O(1)
    vstack.pop_back(); // 移除栈顶元素, O(1)
    std::cout << "Vector Stack top element after pop: " << vstack.back() << std::endl; // 输出栈顶元素, O(1)
    vstack.pop_back(); // 移除栈顶元素, O(1)
    std::cout << "Vector Stack top element after pop: " << vstack.back() << std::endl; // 输出栈顶元素, O(1)
    vstack.pop_back(); // 移除栈顶元素, O(1)
    /*
        使用 vector 实现栈的优点：
        1. 支持后进先出的数据访问模式，适合处理递归和回溯问题。
        2. 内存使用效率高，因为它使用连续的内存块。

        使用 vector 实现栈的缺点：
        1. 相比于 list，vector 的内存开销更大，因为它需要维护多个小数组。
        2. 在中间插入和删除元素时性能较差。
    */

    return 0;
}

// g++ std.cpp -o std.bin --std=c++11 --static