#include <json/value.h>
#include <jsoncpp/json/json.h>
#include <restclient-cpp/restclient.h>
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

TEST_CASE("Test user registration", "[single-file]")
{
    REQUIRE(TestUserRegistration());
}

TEST_CASE("Test user deletion", "[single-file]")
{
    REQUIRE(TestUserDeletion());
}
