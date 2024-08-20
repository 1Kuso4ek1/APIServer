#pragma once
#include <json/json.h>
#include <random>

class Users
{
public:
    Users();

    std::string GetNewAPIKey(std::string user);

    Json::Value Authenticate(std::string key);

private:
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    Json::Value users;

    std::random_device rd;
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
};

using Users_ptr = std::shared_ptr<Users>;
