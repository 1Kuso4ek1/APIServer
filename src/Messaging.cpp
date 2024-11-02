#include <Messaging.hpp>
#include <SQLiteCpp/Statement.h>
#include <json/value.h>

Messaging::Messaging(Users_ptr users) : users(users)
{
    db = std::make_unique<SQLite::Database>("database.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db->exec("CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, senderId INTEGER, receiverId INTEGER, message TEXT, status TEXT)");
}

response_ptr Messaging::render_POST(const http_request& request)
{
    Json::Value requestBody = Utils::ParseJson(std::string(request.get_content()));
    Json::Value response;

    auto key = std::string(request.get_header("Authorization"));

    try
    {
        if(requestBody["ok"].asBool() && !key.empty() && !requestBody["receiverId"].isNull() && !requestBody["message"].asString().empty())
        {
            response = SendMessage(key.substr(7), requestBody["receiverId"].asInt(), requestBody["message"].asString());
        }
        else
        {
            response["ok"] = false;
            response["response"]["error"] = "Sender, receiver or message is not specified";
        }
    }
    catch(const std::exception& e)
    {
        response["ok"] = false;
        response["response"]["error"] = e.what();
    }

    return response_ptr(new string_response(response.toStyledString(), response["ok"].asBool() ? 200 : 400, "application/json"));
}

response_ptr Messaging::render_GET(const http_request& request)
{
    Json::Value response;

    auto key = std::string(request.get_header("Authorization"));

    if(!key.empty())
        response = Authenticate(key.substr(7));

    if(key.empty() || !response["response"]["auth"].asBool())
    {
        response["ok"] = false;
        response["error"] = "Authorization failed";

        return response_ptr(new string_response(response.toStyledString(), 401, "application/json"));
    }

    SQLite::Statement query(*db, "SELECT * FROM messages WHERE receiverId = ? AND status = \"sent\"");
    SQLite::Statement updateQuery(*db, "UPDATE messages SET status = \"unread\" WHERE receiverId = ? AND status = \"sent\"");

    query.bind(1, response["response"]["user"]["id"].asInt());
    updateQuery.bind(1, response["response"]["user"]["id"].asInt());

    response.clear();
    response["ok"] = true;

    int counter = 0;
    while(query.executeStep())
    {
        response["response"]["messages"][counter]["id"] = (int)query.getColumn(0);
        response["response"]["messages"][counter]["senderId"] = (int)query.getColumn(1);
        response["response"]["messages"][counter]["receiverId"] = (int)query.getColumn(2);
        response["response"]["messages"][counter]["message"] = (std::string)query.getColumn(3);
        response["response"]["messages"][counter]["status"] = (std::string)query.getColumn(4);

        counter++;
    }

    updateQuery.exec();

    if(counter == 0)
        response["response"]["message"] = "No new messages";

    return response_ptr(new string_response(response.toStyledString(), 200, "application/json"));
}

Json::Value Messaging::Authenticate(std::string key)
{
    Json::Value response;

    response = users->Authenticate(key);
    response["ok"] = response["response"]["auth"].asBool();

    return response;
}

Json::Value Messaging::SendMessage(std::string senderKey, int receiverId, std::string message)
{
    Json::Value response = Authenticate(senderKey);

    if(!response["ok"].asBool())
    {
        response["response"]["error"] = "Authorization failed";
        return response;
    }

    SQLite::Statement query(*db, "INSERT INTO messages (senderId, receiverId, message, status) VALUES (?, ?, ?, ?)");

    query.bind(1, response["response"]["user"]["id"].asInt());
    query.bind(2, receiverId);
    query.bind(3, message);
    query.bind(4, "sent");

    query.exec();

    query.reset();

    query = SQLite::Statement(*db, "SELECT * FROM messages WHERE id = last_insert_rowid()");

    query.executeStep();

    response.clear();
    
    response["ok"] = true;
    response["response"]["message"]["id"] = (int)query.getColumn(0);
    response["response"]["message"]["senderId"] = (int)query.getColumn(1);
    response["response"]["message"]["receiverId"] = (int)query.getColumn(2);

    return response;
}


