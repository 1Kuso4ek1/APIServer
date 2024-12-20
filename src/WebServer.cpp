#include <WebServer.hpp>
#include <httpserver.hpp>
#include <memory>
#include <Messaging.hpp>

WebServer::WebServer(int port) :
    index("../html/index.html", "text/html"), 
    css  ("../html/style.css", "text/css"),
    js   ("../html/APICall.js", "text/javascript"),

    server(create_webserver(port)),
    users (std::make_unique<Users>()),
    auth  (std::make_unique<Authorization>(users)),
    messaging (std::make_unique<Messaging>(users)) {}

void WebServer::Setup()
{
    server.register_resource("/auth", auth.get());
    server.register_resource("/messaging", messaging.get());

    server.register_resource("/", &index);
    server.register_resource("/style.css", &css);
    server.register_resource("/APICall.js", &js);
}

void WebServer::Run()
{
    server.start(true);
}
