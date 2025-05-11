/*!
 * @file client.cpp
 * @brief Клиент для тестирования алгоритма Левита
 */

#ifndef CLIENT_CPP
#define CLIENT_CPP

#include "../Include/httplib.h"
#include "../Tests/tests.cpp"

using json = nlohmann::json;

int main() {
    httplib::Client cli("http://127.0.0.1:8080");
    
    // Запускаем все тесты
    auto tests = {
        std::make_pair("simple", test_graph_simple()),
        std::make_pair("negative", test_graph_negative_weights()),
        std::make_pair("large_random", test_graph_large_random()),
        std::make_pair("unreachable", test_graph_unreachable())
    };
    
    for (const auto& [test_name, test_data] : tests) {
        auto [graph_json, graph] = test_data;
        
        // Отправляем на сервер
        auto res = cli.Post("/process", graph_json.dump(), "application/json");
        
        if (res && res->status == 200) {
            auto response = json::parse(res->body);
            std::vector<int> distances = response["distances"].get<std::vector<int>>();
            
            // Сохраняем результаты
            std::string filename = "result_" + std::string(test_name) + ".txt";
            save_results(filename, graph, distances);
            std::cout << "Тест '" << test_name << "' успешно сохранен в " << filename << "\n";
        } else {
            std::cerr << "Ошибка в тесте '" << test_name << "': " 
                     << (res ? res->body : "Нет соединения") << "\n";
        }
    }
    
    return 0;
}

#endif
