#pragma once
#include "APIBase.hpp"

class FileResponse : public http_resource
{
public:
    FileResponse(std::string path, std::string type) : path(path), type(type) {}

    response_ptr render(const http_request& request);

private:
    std::string path, type;
};
