#include <Users.hpp>

Users::Users()
{
    generator = std::mt19937(rd());
    distribution = std::uniform_int_distribution<>(0, characters.size() - 1);
}

std::string Users::GetNewAPIKey(std::string user)
{
    std::string key;
    for(int i = 0; i < 32; i++)
        key += characters[distribution(generator)];

    users[key]["user"]["name"] = user;

    return key;
}

Json::Value Users::Authenticate(std::string key)
{
    Json::Value response;

    if(users.isMember(key))
    {
        response["auth"] = true;
        response["user"] = users[key]["user"];
    }
    else
        response["auth"] = false;

    return response;
}
