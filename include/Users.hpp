#pragma once
#include <json/json.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
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

    std::shared_ptr<SQLite::Database> db;

    std::random_device rd;
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
};

using Users_ptr = std::shared_ptr<Users>;
