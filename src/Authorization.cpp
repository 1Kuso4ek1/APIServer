#include <Authorization.hpp>

response_ptr Authorization::render_POST(const http_request& request)
{
    Json::Value response;

    if(!request.get_arg("user").get_all_values().empty())
        response["key"] = users->GetNewAPIKey(request.get_arg("user"));
    else
        response["error"] = "User name is not specified";

    return response_ptr(new string_response(response.toStyledString() + "\n", 200, "application/json"));
}

response_ptr Authorization::render_GET(const http_request& request)
{
    Json::Value response;

    auto key = std::string(request.get_header("Authorization"));

    if(!key.empty())
        response = users->Authenticate(key.substr(7));
    else
        response["error"] = "Authorization key is not specified";

    return response_ptr(new string_response(response.toStyledString() + "\n", 200, "application/json"));
}
