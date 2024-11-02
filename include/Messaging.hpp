#pragma once
#include "APIBase.hpp"
#include <SQLiteCpp/Database.h>
#include <json/value.h>
#include <memory>

class Messaging : public http_resource
{
public:
    Messaging(Users_ptr users);

    response_ptr render_POST(const http_request& request);
    response_ptr render_GET(const http_request& request);

private:
    Json::Value Authenticate(std::string key);
    Json::Value SendMessage(std::string senderKey, int receiverId, std::string message);

private:
    std::unique_ptr<SQLite::Database> db;

private:
    Users_ptr users;
};

using Messaging_ptr = std::unique_ptr<Messaging>;
