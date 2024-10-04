#include "crow.h"

int main(){
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello from Crow/C++";
    });

    app.port(8000).multithreaded().run();
}