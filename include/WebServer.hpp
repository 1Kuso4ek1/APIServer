#pragma once
#include "Authorization.hpp"
#include "FileResponse.hpp"
#include "Application.hpp"

class WebServer : public Application
{
public:
    WebServer(int port);

    void Setup() override;
    void Run() override;

private:
    webserver server;

    Users_ptr users;

    FileResponse index;
    FileResponse css;
    FileResponse js;

    Authorization_ptr auth;
};
