#include <sot/server.h>
#include <stdlib.h>

void handle(t_sot_parsed request, void(*writer)(char*)){
    char *resp = string_from_format("Hola! bienvenido a %s", request.endpoint);
    writer(resp);
    free(resp);
}

char *get_port(){
    char* env_port = getenv("PORT");

    if(env_port == NULL)
        return "8080";
    else
        return env_port;
}

int main(){
    t_sot_server_config config = {
        .port = get_port(),
        .handler = handle
    };

    run_server(config);

    return EXIT_SUCCESS;
}