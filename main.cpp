#include <APIBase.hpp>
#include <Authorization.hpp>
#include <FileResponse.hpp>

int main()
{
    webserver server = create_webserver(8080);

    Users_ptr users = std::make_shared<Users>();

    FileResponse index("../html/index.html", "text/html");
    FileResponse css("../html/style.css", "text/css");
    FileResponse js("../html/APICall.js", "text/javascript");

    APIBase api(users);
    server.register_resource("/api", &api);

    Authorization auth(users);
    server.register_resource("/auth", &auth);

    server.register_resource("/", &index);
    server.register_resource("/style.css", &css);
    server.register_resource("/APICall.js", &js);

    server.start(true);
}
