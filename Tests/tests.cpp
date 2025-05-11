/*!
 * @file tests.cpp
 * @brief Тестовые графы для алгоритма Левита
 */

#ifndef TESTS_CPP
#define TESTS_CPP

#include "../Methods/mainMethod.cpp"

using json = nlohmann::json;

/*!
 * @brief Простой связный граф (5 вершин)
 */
inline std::pair<json, std::vector<std::vector<std::pair<int, int>>>> test_graph_simple() {
    std::vector<std::vector<std::pair<int, int>>> graph = {
        {{1, 5}, {2, 3}},  // 0 -> 1(5), 0 -> 2(3)
        {{3, 2}},           // 1 -> 3(2)
        {{3, 7}, {4, 1}},   // 2 -> 3(7), 2 -> 4(1)
        {{4, 3}},           // 3 -> 4(3)
        {}                  // 4
    };
    
    json graph_json;
    graph_json["graph"] = graph;
    graph_json["start"] = 0;
    
    return {graph_json, graph};
}

/*!
 * @brief Граф с отрицательными весами (4 вершины)
 */
inline std::pair<json, std::vector<std::vector<std::pair<int, int>>>> test_graph_negative_weights() {
    std::vector<std::vector<std::pair<int, int>>> graph = {
        {{1, 4}, {2, 5}},  // 0 -> 1(4), 0 -> 2(5)
        {{3, -2}},          // 1 -> 3(-2)
        {{3, 3}},           // 2 -> 3(3)
        {}                  // 3
    };
    
    json graph_json;
    graph_json["graph"] = graph;
    graph_json["start"] = 0;
    
    return {graph_json, graph};
}

/*!
 * @brief Большой случайный граф (100 вершин, 500 ребер)
 */
inline std::pair<json, std::vector<std::vector<std::pair<int, int>>>> test_graph_large_random() {
    return generate_random_graph(100, 500, 100);
}

/*!
 * @brief Граф с недостижимыми вершинами (6 вершин)
 */
inline std::pair<json, std::vector<std::vector<std::pair<int, int>>>> test_graph_unreachable() {
    std::vector<std::vector<std::pair<int, int>>> graph = {
        {{1, 2}},           // 0 -> 1(2)
        {{2, 3}},           // 1 -> 2(3)
        {},                 // 2
        {{4, 1}},           // 3 -> 4(1)
        {{5, 2}},           // 4 -> 5(2)
        {}                  // 5
    };
    
    json graph_json;
    graph_json["graph"] = graph;
    graph_json["start"] = 0;
    
    return {graph_json, graph};
}

#endif
