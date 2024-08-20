#include <APIBase.hpp>

response_ptr APIBase::render(const http_request& request)
{
    Json::Value response;

    if(!request.get_arg("name").get_all_values().empty())
        response["user"]["name"] = std::string(request.get_arg("name"));
    else
        response["user"]["name"] = "Anonymous";

    response["message"] = "hello, " + response["user"]["name"].asString();

    return response_ptr(new string_response(response.toStyledString() + "\n", 200, "application/json"));
}
