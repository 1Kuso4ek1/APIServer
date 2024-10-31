#include <WebServer.hpp>

int main()
{
    WebServer server(8080);

    server.Setup();
    server.Run();
}
