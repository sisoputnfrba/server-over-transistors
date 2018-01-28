#include <sot/server.h>

void handle(t_sot_parsed request, void(*writer)(char*)){
    writer(request._raw);
}

int main(){
    t_sot_server_config config = {
        .port = "8080",
        .handler = handle
    };

    run_server(config);

    return EXIT_SUCCESS;
}