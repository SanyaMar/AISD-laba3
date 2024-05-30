#pragma once
#include <vector> 
#include <iostream> 
#include <queue> 
#include <iterator> 
#include <algorithm> 
#include <limits> 
#include <map> 
#include <exception>
#include <unordered_map>

using namespace std;

namespace funct {

    template<typename Vertex, typename Distance = double>
    class Graph {
    public:
        struct Edge {
            Vertex from;
            Vertex to;
            Distance distance;

            Edge(Vertex from, Vertex to) : from(from), to(to), dist(0) {};
            Edge(Vertex from, Vertex to, Distance dist) : from(from), to(to), dist(dist) {};
        };
    private:
        vector<Vertex> _vert;
        vector<Edge<Vertex, Distance>> > _edges;
    public:

        Graph() : _edges(vector<Edge<Vertex, Distance>>()), _vert(vector<Vertex>()) {};

        void print() const {
            for (Edge<Vertex, Distance>& edge : _edges) {
                cout<< edge.from <<" --> "<<edge.to<<" : "<< edge.distanse;
            }
        }

        bool has_vertex(const Vertex& v) const {
            return find(_vert.begin(), _vert.end(), v) != _vert.end();
        }

        void add_vertex(const Vertex& v) {
            if (!has_vertex(v)) {
                _vert.push_back(v);
            }
        }

        bool remove_vertex(const Vertex& v) {
            if (has_vertices(v)) {
                for (int i = 0; i < _vert.size(); i++) {
                    if (_vert[i] == v) {
                        _vert.erase(_vert.begin() + i);
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
        bool remove_edge(const Edge<Vertex, Distance>& e) {
            if (!has_edge(e)) {
                return false;
            }
            for (int i = 0; i < _edges.size(); i++) {
                if (_edges[i].from == e.from && _edges[i].to == e.to && _edges[i].distance == e.distance) {
                    _edges.erase(_edges.begin() + i);
                    return true;
                }
            }
            return false;
        }
        std::vector<Vertex> vertices() const {
            return _vert;
        }
        bool has_edge(const Vertex& from, const Vertex& to) const {
            for (const Edge<Vertex, Distance>& edge : _edges) {
                if (edge.from == from && edge.to == to) {
                    return true;
                }
            }
            return false;
        }

        bool has_edge(const Edge<Vertex, Distance>& e) const {
            return find(_edges.begin(), _edges.end(), e) != _edges.end();
        }

        void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
            if (!has_vertex(from) || !has_vertex(to)) {
                throw std::invalid_argument("Vertices in edge not found in graph");
            }
            _edges.push_back(Edge<Vertex, Distance>(from, to, d));
        }
        bool remove_edge(const Vertex& from, const Vertex& to) {
            if (!has_edge(from, to)) return false;

            _edges.erase(remove_if(_edges.begin(), _edges.end(), [&](Edge& e) { return (e._from == from) && (e._to == to); }), _edges.end());

            return false;
        }
        vector<Edge<Vertex, Distance>> edges(const Vertex& vertex) {
            vector<Edge<Vertex, Distance>> result;
            for (const Edge<Vertex, Distance>& edge : _edges) {
                if (edge.from == vertex) {
                    result.push_back(edge);
                }
            }
            return result;
        }

        size_t order() const {
            return _vert.size();
        }

        size_t degree(const Vertex& v) const {
            size_t deg = 0;
            for (const Edge<Vertex, Distance>& edge : _edges) {
                if (edge.from == v) {
                    deg++;
                }
            }
            return deg;
        }

        vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {

            unordered_map<Vertex, Distance> distances;
            unordered_map<Vertex, Vertex>  previous;
            vector<Edge> path;

            for (const Vertex& v : _vertices) {
                distances[v] = numeric_limits<Distance>::max();

            }
            distances[from] = 0;
            for (size_t i = 0;i < _vert.size() - 1, ++i) {
                for (const Edge<Vertex, Distance>& edge : _edges) {
                    if (distances[edge.from] + edge.distance < distances[edge.to]) {
                        distances[edge.to] = distances[edge.from] + edge.distance;
                        previous[edge.to] = edge.from;
                    }
                }
            }

            Vertex current = to;
            while (current != from) {
                for (const Edge& edge : _edges) {
                    if (edge.to == current && previous[current] == edge.from) {
                        path.push_back(edge);
                        current = edge.from;
                        break;
                    }
                }
            }
            reverse(path.begin(), path.end());
            return path;
        }
    };
}
