#include <APIBase.hpp>
#include <Authorization.hpp>

int main()
{
    webserver server = create_webserver(8080);

    Users_ptr users = std::make_shared<Users>();

    APIBase api(users);
    server.register_resource("/index", &api);

    Authorization auth(users);
    server.register_resource("/auth", &auth);

    server.start(true);
}
