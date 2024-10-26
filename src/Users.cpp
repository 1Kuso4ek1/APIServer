#include <SQLiteCpp/Statement.h>
#include <Users.hpp>
#include <json/value.h>
#include <memory>

Users::Users()
{
    generator = std::mt19937(rd());
    distribution = std::uniform_int_distribution<>(0, characters.size() - 1);

    db = std::make_shared<SQLite::Database>("users.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db->exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, password TEXT, key TEXT)");
}

bool Users::AddUser(std::string name, std::string password)
{
    SQLite::Statement query(*db, "SELECT * FROM users WHERE name = ?");
    query.bind(1, name);

    if(query.executeStep())
        return false;

    query.reset();
    
    query = SQLite::Statement(*db, "INSERT INTO users (name, password) VALUES (?, ?)");
    
    query.bind(1, name);
    query.bind(2, password);
    
    query.exec();

    return true;
}

std::string Users::GetNewAPIKey(std::string name, std::string password)
{
    SQLite::Statement query(*db, "SELECT * FROM users WHERE name = ? AND password = ?");
    query.bind(1, name);
    query.bind(2, password);

    if(!query.executeStep())
        return "";

    std::string key;
    for(int i = 0; i < 32; i++)
        key += characters[distribution(generator)];

    query.reset();

    query = SQLite::Statement(*db, "UPDATE users SET key = ? WHERE name = ? AND password = ?");

    query.bind(1, key);
    query.bind(2, name);
    query.bind(3, password);
    
    query.exec();

    return key;
}

Json::Value Users::Authenticate(std::string key)
{
    SQLite::Statement query = SQLite::Statement(*db, "SELECT * FROM users WHERE key = ?");
    query.bind(1, key);

    Json::Value response;
    response["response"]["user"]["key"] = Json::Value::null;

    if(query.executeStep())
    {
        response["response"]["auth"] = true;
        response["response"]["user"]["name"] = (std::string)query.getColumn(1);
        response["response"]["user"]["key"] = (std::string)query.getColumn(3);
        
        if(response["response"]["user"]["key"].asString().empty())
            response["response"]["user"]["key"] = Json::Value::null;
    }
    else
        response["response"]["auth"] = false;

    return response;
}

Json::Value Users::Authenticate(std::string name, std::string password)
{
    SQLite::Statement query = SQLite::Statement(*db, "SELECT * FROM users WHERE name = ? AND password = ?");
    query.bind(1, name);
    query.bind(2, password);

    Json::Value response;
    response["response"]["user"]["key"] = Json::Value::null;

    if(query.executeStep())
    {
        response["response"]["auth"] = true;
        response["response"]["user"]["name"] = (std::string)query.getColumn(1);
        response["response"]["user"]["key"] = (std::string)query.getColumn(3);

        if(response["response"]["user"]["key"].asString().empty())
            response["response"]["user"]["key"] = Json::Value::null;
    }
    else
        response["response"]["auth"] = false;

    return response;
}
