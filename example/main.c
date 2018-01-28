#include <sot/server.h>

void handle(t_sot_parsed request, void(*writer)(char*)){
    char *resp = string_from_format("Hola! bienvenido a %s", request.endpoint);
    writer(resp);
    free(resp);
}

int main(){
    t_sot_server_config config = {
        .port = "8080",
        .handler = handle
    };

    run_server(config);

    return EXIT_SUCCESS;
}