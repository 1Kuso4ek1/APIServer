#include <Users.hpp>

Users::Users()
{
    generator = std::mt19937(rd());
    distribution = std::uniform_int_distribution<>(0, characters.size() - 1);
}

bool Users::AddUser(std::string name, std::string password)
{
    if(users.isMember(name))
        return false;

    users[name]["user"] = name;
    users[name]["password"] = password;

    return true;
}

std::string Users::GetNewAPIKey(std::string name, std::string password)
{
    if(users[name]["password"].asString() != password)
        return "";

    std::string key;
    for(int i = 0; i < 32; i++)
        key += characters[distribution(generator)];

    apiKeys[key] = name;
    users[name]["key"] = key;

    return key;
}

Json::Value Users::Authenticate(std::string key)
{
    Json::Value response;

    if(apiKeys.isMember(key))
    {
        response["response"]["auth"] = true;
        response["response"]["user"] = users[apiKeys[key].asString()];
    }
    else
        response["response"]["auth"] = false;

    return response;
}

Json::Value Users::Authenticate(std::string name, std::string password)
{
    Json::Value response;

    if(users.isMember(name) && users[name]["password"].asString() == password)
    {
        response["response"]["auth"] = true;
        response["response"]["user"] = users[name];
    }
    else
        response["response"]["auth"] = false;

    return response;
}
