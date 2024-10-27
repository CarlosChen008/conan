#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

struct User {
    std::string name;
    int age;
};

// 序列化
std::string SerializeUser(const User& user) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    writer.StartObject();
    writer.Key("name");
    writer.String(user.name.c_str());
    writer.Key("age");
    writer.Int(user.age);
    writer.EndObject();

    return buffer.GetString();
}

// 反序列化
User DeserializeUser(const std::string& json) {
    User user;
    rapidjson::Document document;
    document.Parse(json.c_str());

    if (document.IsObject()) {
        user.name = document["name"].GetString();
        user.age = document["age"].GetInt();
    }

    return user;
}

int main() {
    // 创建一个 User 对象
    User user;
    user.name = "Alice";
    user.age = 30;

    // 序列化为 JSON
    std::string jsonString = SerializeUser(user);
    std::cout << "Serialized JSON: " << jsonString << std::endl;

    // 反序列化 JSON 为 User 对象
    User deserializedUser = DeserializeUser(jsonString);
    std::cout << "Deserialized User Name: " << deserializedUser.name << std::endl;
    std::cout << "Deserialized User Age: " << deserializedUser.age << std::endl;

    return 0;
}
