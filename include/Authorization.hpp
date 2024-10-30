#pragma once
#include "APIBase.hpp"
#include <json/value.h>

class Authorization : public http_resource
{
public:
    Authorization(Users_ptr users) : users(users) {}

    response_ptr render_POST(const http_request& request);
    response_ptr render_GET(const http_request& request);

private:
    Json::Value Authenticate(std::string name, std::string password);
    Json::Value DeleteUser(std::string name, std::string password);

    Users_ptr users;
};

using Authorization_ptr = std::shared_ptr<Authorization>;
