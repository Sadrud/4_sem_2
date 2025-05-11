/*!
 * @file mainMethod.cpp
 * @brief Файл, содержащий основной графовый метод, метод для создания случайного графа и для записи результата в файл
 */

#ifndef MAINMETHOD_CPP
#define MAINMETHOD_CPP

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <deque>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
const int INF = 1e9;

/*!
 * @brief Реализация алгоритма Левита
 * @param n Количество вершин
 * @param graph Граф в виде списка смежности
 * @param start Начальная вершина
 * @return Вектор расстояний до всех вершин
 */
inline std::vector<int> levit_algorithm(int n, const std::vector<std::vector<std::pair<int, int>>>& graph, int start) {
	std::vector<int> dist(n, INF);
	dist[start] = 0;

	std::vector<int> m(n, 2);
	m[start] = 1;

	std::deque<int> q;
	q.push_back(start);

	while (!q.empty()) {
		int v = q.front();
		q.pop_front();
		m[v] = 0;

		for (const auto& [u, w] : graph[v]) {
			if (dist[u] > dist[v] + w) {
				dist[u] = dist[v] + w;

				if (m[u] == 2) {
					m[u] = 1;
					q.push_back(u);
				} else if (m[u] == 0) {
					m[u] = 1;
					q.push_front(u);
				}
			}
		}
	}

	return dist;
}

/*!
 * @brief Генерирует случайный граф
 * @param n Количество вершин
 * @param m Количество рёбер
 * @param max_weight Максимальный вес ребра
 * @return Пара: граф в виде JSON и список смежности
 */
inline std::pair<json, std::vector<std::vector<std::pair<int, int>>>> generate_random_graph(int n, int m, int max_weight) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> weight_dist(1, max_weight);
	std::uniform_int_distribution<> node_dist(0, n-1);

	std::vector<std::vector<std::pair<int, int>>> graph(n);
	json graph_json;

	for (int i = 0; i < m; ++i) {
		int u = node_dist(gen);
		int v = node_dist(gen);
		while (v == u) v = node_dist(gen);

		int w = weight_dist(gen);
		graph[u].emplace_back(v, w);
		graph_json["graph"][u].push_back({v, w});
	}

	graph_json["start"] = 0; // Стартовая вершина по умолчанию
	return {graph_json, graph};
}


/*!
 * @brief Сохраняет результаты в файл
 * @param filename Имя файла
 * @param graph Исходный граф
 * @param distances Результаты работы алгоритма
 */
inline void save_results(const std::string& filename, 
		const std::vector<std::vector<std::pair<int, int>>>& graph,
		const std::vector<int>& distances) {
	std::ofstream fout(filename);

	fout << "Исходный граф:\n";
	for (int u = 0; u < graph.size(); ++u) {
		for (const auto& [v, w] : graph[u]) {
			fout << u << " -> " << v << " [weight=" << w << "]\n";
		}
	}

	fout << "\nРезультаты (расстояния от вершины 0):\n";
	for (int i = 0; i < distances.size(); ++i) {
		fout << "Вершина " << i << ": ";
		if (distances[i] == INF) {
			fout << "недостижима\n";
		} else {
			fout << distances[i] << "\n";
		}
	}

	fout.close();
}

#endif
