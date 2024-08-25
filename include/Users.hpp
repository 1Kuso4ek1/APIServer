#pragma once
#include <json/json.h>
#include <random>

class Users
{
public:
    Users();

    bool AddUser(std::string name, std::string password);

    std::string GetNewAPIKey(std::string name, std::string password);

    Json::Value Authenticate(std::string key);
    Json::Value Authenticate(std::string name, std::string password);

private:
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    Json::Value users, apiKeys;

    std::random_device rd;
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
};

using Users_ptr = std::shared_ptr<Users>;
