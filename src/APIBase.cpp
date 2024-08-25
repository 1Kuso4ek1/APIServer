#include <APIBase.hpp>

Json::Value Utils::ParseJson(std::string json)
{
    Json::Value ret;
    Json::CharReaderBuilder rbuilder;

    std::stringstream stream(json);
    std::string errors;

    bool result = Json::parseFromStream(rbuilder, stream, &ret, &errors);

    ret["ok"] = result;
    if(!result)
        ret["error"] = "JSON parsing failed: " + errors;

    return ret;
}

response_ptr APIBase::render(const http_request& request)
{
    Json::Value requestBody = Utils::ParseJson(std::string(request.get_content()));

    return response_ptr(new string_response(requestBody.toStyledString(), requestBody["ok"].asBool() ? 200 : 400, "application/json"));
}
