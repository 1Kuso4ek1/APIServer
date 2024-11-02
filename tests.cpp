#include <iostream>
#include <json/value.h>
#include <jsoncpp/json/json.h>
#include <restclient-cpp/restclient.h>
#include <restclient-cpp/connection.h>
#include <catch2/catch_test_macros.hpp>

Json::Value Parse(std::string json)
{
    Json::Value ret;
    Json::CharReaderBuilder rbuilder;

    std::stringstream stream(json);
    std::string errors;

    bool result = Json::parseFromStream(rbuilder, stream, &ret, &errors);

    ret["ok"] = result;
    if(!result)
        ret["error"] = "JSON parsing failed: " + errors;

    return ret;
}

// Try to create a dummy user
bool TestUserRegistration()
{
    Json::Value user;
    
    user["name"] = "test";
    user["password"] = "test";
    user["action"] = "auth";

    auto result = RestClient::post("http://localhost:8080/auth", "application/json", user.toStyledString());
    auto json = Parse(result.body);

    return json["ok"].asBool();
}

// Try to delete a newly created dummy user
bool TestUserDeletion()
{
    Json::Value user;
    
    user["name"] = "test";
    user["password"] = "test";
    user["action"] = "del";

    auto result = RestClient::post("http://localhost:8080/auth", "application/json", user.toStyledString());
    auto json = Parse(result.body);

    return json["ok"].asBool();
}

// Try to send a message
bool TestSendMessage()
{
    Json::Value message;

    message["senderKey"] = "050OZXKTHKr6ifAqKHvwKcZ19AANUtEX";
    message["receiverId"] = 2;
    message["message"] = "testMessage";

    RestClient::Connection con("http://localhost:8080");

    con.AppendHeader("Content-Type", "application/json");
    con.AppendHeader("Authorization", "Bearer 050OZXKTHKr6ifAqKHvwKcZ19AANUtEX");

    auto result = con.post("/messaging", message.toStyledString());
    auto json = Parse(result.body);

    std::cout << json.toStyledString() << std::endl;

    return json["ok"].asBool() &&
           json["response"]["message"]["senderId"].asInt() == 1 &&
           json["response"]["message"]["id"].asInt() > 0 &&
           json["response"]["message"]["receiverId"].asInt() == 2;
}

// Try to get new messages
bool TestGetMessages()
{
    RestClient::Connection con("http://localhost:8080");

    con.AppendHeader("Content-Type", "application/json");
    con.AppendHeader("Authorization", "Bearer XwG4jVMSbrG7tYwtkyCY36DAw1rkTpBY");

    auto result = con.get("/messaging");
    auto json = Parse(result.body);

    std::cout << json.toStyledString() << std::endl;

    return json["ok"].asBool();
}

TEST_CASE("Test user registration", "[single-file]")
{
    REQUIRE(TestUserRegistration());
}

TEST_CASE("Test user deletion", "[single-file]")
{
    REQUIRE(TestUserDeletion());
}

TEST_CASE("Test message sending", "[single-file]")
{
    REQUIRE(TestSendMessage());
}

TEST_CASE("Test message getting", "[single-file]")
{
    REQUIRE(TestGetMessages());
}
