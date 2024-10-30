#include <WebServer.hpp>
#include <httpserver.hpp>
#include <memory>

void WebServer::Setup()
{
    server = std::make_unique<webserver>(create_webserver(8080));
    users = std::make_shared<Users>();
    auth = std::make_shared<Authorization>(users);
    
    server->register_resource("/auth", auth.get());

    server->register_resource("/", &index);
    server->register_resource("/style.css", &css);
    server->register_resource("/APICall.js", &js);
}

void WebServer::Run()
{
    server->start(true);
}
