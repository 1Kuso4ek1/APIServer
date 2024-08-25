#pragma once
#include <httpserver.hpp>
#include <random>

#include "Users.hpp"

using namespace httpserver;

using response_ptr = std::shared_ptr<http_response>;

namespace Utils
{
    Json::Value ParseJson(std::string json);
}

class APIBase : public http_resource
{
public:
    APIBase(Users_ptr users) : users(users) {}

    response_ptr render(const http_request& request);

private:
    Users_ptr users;
};
