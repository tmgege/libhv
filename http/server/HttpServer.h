#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_

#include "hexport.h"
#include "HttpService.h"

struct WebSocketServerCallbacks;
typedef struct http_server_s {
    char host[64];
    int port; // http_port
    int https_port;
    int http_version;
    int worker_processes;
    int worker_threads;
    HttpService* service;
    WebSocketServerCallbacks* ws;
    void* userdata;
//private:
    int listenfd[2]; // 0: http, 1: https
    void* privdata;

#ifdef __cplusplus
    http_server_s() {
        strcpy(host, "0.0.0.0");
        // port = DEFAULT_HTTP_PORT;
        // https_port = DEFAULT_HTTPS_PORT;
        port = 8080;
        https_port = 8443;
        http_version = 1;
        worker_processes = 0;
        worker_threads = 0;
        service = NULL;
        ws = NULL;
        listenfd[0] = listenfd[1] = -1;
        userdata = NULL;
        privdata = NULL;
    }
#endif
} http_server_t;

/*
#include "HttpServer.h"

int main() {
    HttpService service;
    service.base_url = "/v1/api";
    service.GET("/ping", [](HttpRequest* req, HttpResponse* resp) {
        resp->body = "pong";
        return 200;
    });

    http_server_t server;
    server.port = 8080;
    server.worker_processes = 4;
    server.service = &service;
    http_server_run(&server);
    return 0;
}
*/
HV_EXPORT int http_server_run(http_server_t* server, int isMainThreadEnabled = 1, int isLoop = 1);

HV_EXPORT void http_server_update(http_server_t* server);

// NOTE: stop all loops and join all threads
HV_EXPORT int http_server_stop(http_server_t* server);

#endif
