#include "crow.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <cstdlib>  

std::vector<nlohmann::json> chat_history;

int main() {
    crow::SimpleApp app;

    nlohmann::json personality_message = {
        {"role", "system"},
        {"content", "You are a 30-35 year-old woman who is friendly, loves to chat over text, and enjoys casual, engaging conversations. give your ans short and concise"}
    };

    chat_history.push_back(personality_message);

    CROW_ROUTE(app, "/")([](){
        return "Hello from Crow/C++ chat server";
    });

    CROW_ROUTE(app, "/chat").methods(crow::HTTPMethod::Post)([] (const crow::request& req) {
        try {
            
            auto req_body = nlohmann::json::parse(req.body);
            std::string user_message = req_body["message"];

            const char* api_key = std::getenv("OPENAI_API_KEY");
            if (!api_key) {
                return crow::response(500, "OpenAI API key not set.");
            }

            nlohmann::json user_message_json = {
                {"role", "user"},
                {"content", user_message}
            };
            chat_history.push_back(user_message_json);

            if (chat_history.size() > 10) {
                chat_history.erase(chat_history.begin());
            }

            nlohmann::json json_payload;
            json_payload["model"] = "gpt-4o-mini";
            json_payload["messages"] = chat_history;
            json_payload["max_tokens"] = 100;
            json_payload["temperature"] = 0.7;

            cpr::Response r = cpr::Post(
                cpr::Url{"https://api.openai.com/v1/chat/completions"},                       
                cpr::Header{{"Authorization", std::string("Bearer ") + api_key},       
                            {"Content-Type", "application/json"}},
                cpr::Body{json_payload.dump()}                       
            );

            auto response_json = nlohmann::json::parse(r.text);
            std::string bot_response = response_json["choices"][0]["message"]["content"];

            nlohmann::json bot_message_json = {
                {"role", "assistant"},
                {"content", bot_response}
            };
            chat_history.push_back(bot_message_json);

            if (chat_history.size() > 10) {
                chat_history.erase(chat_history.begin());
            }

            nlohmann::json response_body = {
                {"bot_response", bot_response}
            };
            return crow::response(200, response_body.dump());

        } catch (const std::exception& e) {
            return crow::response(500, "Internal Server Error");
        }
    });

    app.port(8000).multithreaded().run();
}
