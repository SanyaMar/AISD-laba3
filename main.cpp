#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <map>
#include <set>

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


}