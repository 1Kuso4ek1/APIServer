#pragma once
#include <httpserver.hpp>
#include <json/json.h>

using namespace httpserver;

using response_ptr = std::shared_ptr<http_response>;

class APIBase : public http_resource
{
public:
    response_ptr render(const http_request& request);

private:
    
};
