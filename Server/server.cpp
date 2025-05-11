/*!
 * @file server.cpp
 * @brief Сервер для вычисления кратчайших путей (алгоритм Левита)
 */

#ifndef SERVER_CPP
#define SERVER_CPP

#include "../Include/httplib.h"
#include "../Methods/mainMethod.cpp"

using json = nlohmann::json;

int main() {
	httplib::Server svr;

	/*!
	 * @brief Обработчик POST-запроса для алгоритма Левита
	 * 
	 * Принимает JSON вида:
	 * ```json
	 * {
	 *     "graph": [[[1, 5], [2, 3]], ...], // список смежности
	 *     "start": 0                         // начальная вершина
	 * }
	 * ```
	 * 
	 * Возвращает JSON с расстояниями:
	 * ```json
	 * {
	 *     "distances": [0, 5, 3, ...]
	 * }
	 * ```
	 */
	svr.Post("/process", [](const httplib::Request& req, httplib::Response& res) {
			try {
			auto json_data = json::parse(req.body);

			// Преобразуем JSON в граф
			std::vector<std::vector<std::pair<int, int>>> graph;
			for (const auto& adj_list : json_data["graph"]) {
			std::vector<std::pair<int, int>> edges;
			for (const auto& edge : adj_list) {
			edges.emplace_back(edge[0], edge[1]);
			}
			graph.push_back(edges);
			}

			int start_node = json_data["start"];
			auto distances = levit_algorithm(graph.size(), graph, start_node);

			// Формируем ответ
			json response;
			response["distances"] = distances;
			res.set_content(response.dump(), "application/json");

			} catch (const std::exception& e) {
				res.status = 400;
				res.set_content(json({{"error", e.what()}}).dump(), "application/json");
			}
	});

	std::cout << "Сервер запущен на http://localhost:8080\n";
	svr.listen("127.0.0.1", 8080);
	return 0;
}

#endif
