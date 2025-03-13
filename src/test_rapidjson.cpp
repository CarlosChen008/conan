#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

int main() {
    // 1. 创建 JSON 对象
    rapidjson::Document doc;
    doc.SetObject(); // 设置文档的类型为对象类型（而不是数组、字符串或其他类型）
    auto& allocator = doc.GetAllocator();

    // 添加简单的键值对
    doc.AddMember("name", "张三", allocator);
    doc.AddMember("age", 25, allocator);
    
    // 添加数组
    rapidjson::Value array(rapidjson::kArrayType); // 用于说明value的类型为数组类型, 而不是其他类型
    array.PushBack("跑步", allocator);
    array.PushBack("游泳", allocator);
    array.PushBack("篮球", allocator);
    array.PushBack("足球", allocator);
    doc.AddMember("hobbies", array, allocator);

    // 转换为字符串并输出
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer); // 这个是序列化的过程
    std::cout << "Created JSON: " << buffer.GetString() << std::endl;

    // 2. 解析 JSON 字符串
    const char* json = R"({"name":"李四","age":30,"scores":[85,90,95]})"; // R() 是 C++11 的原始字符串, 不用转义，可以换行
    rapidjson::Document doc2;
    doc2.Parse(json);

    // 3. 读取各种类型的值
    if (doc2.HasMember("name")) {
        std::cout << "Name: " << doc2["name"].GetString() << std::endl;
    }
    if (doc2.HasMember("age")) {
        std::cout << "Age: " << doc2["age"].GetInt() << std::endl;
    }
    if (doc2.HasMember("scores")) {
        size_t arraySize = doc2["scores"].GetArray().Size();
        std::cout << "Scores count: " << arraySize << std::endl;
    }
    if (doc2.HasMember("scores")) {
        std::cout << "Scores: ";
        for (auto& score : doc2["scores"].GetArray()) {
            std::cout << score.GetInt() << " ";
        }
        std::cout << std::endl;
    }
    // 4. 修改值
    if (doc2.HasMember("age")) {
        doc2["age"].SetInt(31);
    }

    // 输出修改后的结果
    buffer.Clear();
    writer.Reset(buffer);
    doc2.Accept(writer);
    std::cout << "Modified JSON: " << buffer.GetString() << std::endl;

    return 0;
}
