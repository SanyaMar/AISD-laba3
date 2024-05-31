#pragma once
#include <vector> 
#include <iostream> 
#include <queue> 
#include <algorithm> 
#include <limits> 
#include <map> 
#include <unordered_map>

using namespace std;

namespace funct {

    template<typename Vertex, typename Distance = double>
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;

        Edge(Vertex from, Vertex to) : from(from), to(to), distance(0) {};
        Edge(Vertex from, Vertex to, Distance distance) : from(from), to(to), distance(distance) {};
    };
    template<typename Vertex, typename Distance = double>
    class Graph {
    private:
        vector<Vertex> _vertices;
        vector<Edge<Vertex, Distance>> _edges;
    public:

        Graph() : _edges(vector<Edge<Vertex, Distance>>()), _vertices(vector<Vertex>()) {};

        void print() const {
            for (const Edge<Vertex, Distance>& edge : _edges) {
                cout << edge.from << " --> " << edge.to << " : " << edge.distance << endl;
            }
        }

        vector<Vertex> vertices() const {
            return _vertices;
        }
        //проверка вершины
        bool has_vertex(const Vertex& v) const {
            return find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
        }
        //добавление вершины
        void add_vertex(const Vertex& v) {
            if (!has_vertex(v)) {
                _vertices.push_back(v);
            }
        }
        //удаление вершины
        bool remove_vertex(const Vertex& v) {
            if (has_vertex(v)) {
                for (int i = 0; i < _vertices.size(); i++) {
                    if (_vertices[i] == v) {
                        _vertices.erase(_vertices.begin() + i);
                        break;
                    }
                }

                for (int i = 0; i < _edges.size(); i++) {
                    if (_edges[i].to == v || _edges[i].from == v) {
                        remove_edge(_edges[i]);
                        i--;
                    }
                }
                return true;
            }
            return false;
        }
        //удаление ребра c учетом рассто€ни€
        bool remove_edge(const Edge<Vertex, Distance>& e) {
            if (has_edge(e)) {
                for (int i = 0; i < _edges.size(); i++) {
                    if (_edges[i].from == e.from && _edges[i].to == e.to && _edges[i].distance == e.distance)
                        _edges.erase(_edges.begin() + i);
                    return true;
                }
            }
            return false;
        }
            
        //проверка ребра
        bool has_edge(const Vertex& from, const Vertex& to) const {
            for (const Edge<Vertex, Distance>& edge : _edges) {
                if (edge.from == from && edge.to == to) {
                    return true;
                }
            }
            return false;
        }
        //проверка ребра c учетом рассто€ни€ 
        bool has_edge(const Edge<Vertex, Distance>& e) const {
            for (const auto& edge : _edges) {
                if (edge.from == e.from && edge.to == e.to && edge.distance == e.distance) {
                    return true;
                }
            }
            return false;
        }
        //добавление ребра
        void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
            if (has_vertex(from) || has_vertex(to)) {

                Edge edge(from, to, d);
                if (!has_edge(edge)) {
                    _edges.push_back(edge);
                }
            }
        }
        //удаление ребра
        bool remove_edge(const Vertex& from, const Vertex& to) {
            if (has_edge(from, to)) {

                for (int i = 0; i < _edges.size(); i++) {
                    if (_edges[i].from == from && _edges[i].to == to)
                        _edges.erase(_edges.begin() + i);
                    return true;
                }
            }
            return false;
        }
        //получение всех ребер, выход€щих из вершины
        vector<Edge<Vertex, Distance>> edges(const Vertex& vertex) {
            vector<Edge<Vertex, Distance>> result;
            for (Edge<Vertex, Distance>& edge : _edges) {
                if (edge._from == vertex) {
                    result.push_back(edge);
                }
            }
            return result;
        }
        //пор€док 
        size_t order() const {
            return _vertices.size();
        }
        //степень вершины
        size_t degree(const Vertex& v) const {
            size_t deg = 0;
            for (const Edge<Vertex, Distance>& edge : _edges) {
                if (edge.from == v) {
                    deg++;
                }
            }
            return deg;
        }
        //поиск кратчайшего пути
        pair<vector<Edge<Vertex, Distance>>, unordered_map<Vertex, Distance>> shortest_path(const Vertex& from, const Vertex& to) const {
            if (has_vertex(from) || has_vertex(to)) {
                unordered_map<Vertex, Distance> distances;
                unordered_map<Vertex, Vertex>  previous;
                vector<Edge<Vertex, Distance>> path;

                for (const Vertex& v : _vertices) {
                    distances[v] = numeric_limits<Distance>::max();

                }
                distances[from] = 0;
                for (size_t i = 0;i < _vertices.size() - 1; ++i) {
                    for (const auto& edge : _edges) {
                        if (distances[edge.from] + edge.distance < distances[edge.to]) {
                            distances[edge.to] = distances[edge.from] + edge.distance;
                            previous[edge.to] = edge.from;
                        }
                    }
                }

                Vertex current = to;
                while (current != from) {
                    for (const Edge<Vertex, Distance>& edge : _edges) {
                        if (edge.to == current && previous[current] == edge.from) {
                            path.push_back(edge);
                            current = edge.from;
                            break;
                        }
                    }
                }
                reverse(path.begin(), path.end());
                return pair<vector<Edge<Vertex, Distance>>, unordered_map<Vertex, Distance>>(path, distances);
            }
            return pair<vector<Edge<Vertex, Distance>>, unordered_map<Vertex, Distance>>();
        }
        //обход
        vector<Vertex> walk(const Vertex& start_vertex) const {
            queue<Vertex> queue;
            unordered_map<Vertex, bool> visited;
            unordered_map<Vertex, int> depth;

            queue.push(start_vertex);
            visited[start_vertex] = true;
            depth[start_vertex] = 0;

            vector<Vertex> result;

            while (!queue.empty()) {
                Vertex current = queue.front();
                queue.pop();
                result.push_back(current);

                for (const Edge<Vertex, Distance>& edge : _edges) {
                    if (edge.from == current) {
                        if (!visited[edge.to]) {
                            visited[edge.to] = true;
                            queue.push(edge.to);
                            depth[edge.to] = depth[current] + 1;
                        }
                    }
                }
            }

            return result;
        }
        //«адача    
        /*1. ѕусть дан св€зный граф, в котором узлы Ц это торговые точки.
            Ќеобходимо превратить одну из торговых точек в склад.ќчевидно, склад должен иметь минимальное среднее рассто€ние до остальных точек.
            Ќапишите функцию, котора€ находит такую точку.*/

        Distance average_distance(const Vertex& v) const {
            Distance dist = 0;
            size_t count = 0;

            auto distances = shortest_path(v, _vertices.back()).second;
            for (const auto& e : distances) {
                dist += e.second;
                count++;
            }

            if (count == 0) {
                return numeric_limits<Distance>::max();
            }

            return dist / count;
        }

        Vertex warehouse() const{
            Vertex vertex;
            Distance min_distance = numeric_limits<Distance>::max();

            for (auto& v : _vertices) {
                Distance average = average_distance(v);

                if (average < min_distance) {
                    min_distance = average;
                    vertex = v;
                }
            }

            return vertex;
        }


    };
}
