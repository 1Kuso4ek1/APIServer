#include <Authorization.hpp>

response_ptr Authorization::render_POST(const http_request& request)
{
    Json::Value requestBody = Utils::ParseJson(std::string(request.get_content()));
    Json::Value response;

    try
    {
        if(requestBody["ok"].asBool() && !requestBody["name"].asString().empty() && !requestBody["password"].asString().empty())
        {
            response = users->Authenticate(requestBody["name"].asString(), requestBody["password"].asString());
            response["ok"] = response["response"]["auth"].asBool();

            if(response["response"]["auth"].asBool())
            {
                if(response["response"]["user"]["key"].isNull())
                    response["response"]["user"]["key"] = users->GetNewAPIKey(requestBody["name"].asString(), requestBody["password"].asString());
            }
            else
            {
                if(users->AddUser(requestBody["name"].asString(), requestBody["password"].asString()))
                {
                    response["ok"] = response["response"]["auth"] = true;
                    response["response"]["message"] = "User added successfully";
                }
                else
                    response["response"]["error"] = "User with this name already exists";
            }
        }
        else
        {
            response["ok"] = false;
            response["response"]["error"] = "User name or password is not specified";
        }
    }
    catch(const std::exception& e)
    {
        response["ok"] = false;
        response["response"]["error"] = e.what();
    }

    return response_ptr(new string_response(response.toStyledString(), response["ok"].asBool() ? 200 : 400, "application/json"));
}

response_ptr Authorization::render_GET(const http_request& request)
{
    Json::Value response;

    auto key = std::string(request.get_header("Authorization"));
    int code = 200;

    if(!key.empty())
        response = users->Authenticate(key.substr(7));
    if(key.empty() || !response["response"]["auth"].asBool())
    {
        response["error"] = "Authorization failed";
        code = 401;
    }

    response["ok"] = code == 200;

    return response_ptr(new string_response(response.toStyledString(), code, "application/json"));
}
