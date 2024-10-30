#pragma once
#include "APIBase.hpp"
#include "Authorization.hpp"
#include "FileResponse.hpp"
#include "Application.hpp"

class WebServer : public Application
{
public:
    WebServer() : 
        index("../html/index.html", "text/html"), 
        css("../html/style.css", "text/css"),
        js("../html/APICall.js", "text/javascript") {}

    void Setup() override;
    void Run() override;

private:
    webserver_ptr server;

    Users_ptr users;

    FileResponse index;
    FileResponse css;
    FileResponse js;

    Authorization_ptr auth;
};
