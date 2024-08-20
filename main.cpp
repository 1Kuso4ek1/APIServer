#include <APIBase.hpp>

int main()
{
    webserver server = create_webserver(8080);

    APIBase api;
    server.register_resource("/index", &api);

    server.start(true);
}
