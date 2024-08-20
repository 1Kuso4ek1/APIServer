#include <FileResponse.hpp>

response_ptr FileResponse::render(const http_request& request)
{
    return response_ptr(new file_response(path, 200, type));
}
