#include <gtest/gtest.h>
#include "main.cpp"
#include <iostream>
#include<iterator>


using namespace funct;
using namespace std;

TEST(GraphTest, AddHasVertexTest) {
	Graph<int> g;
	g.add_vertex(1);
	g.add_vertex(2);
	g.add_vertex(3);

	EXPECT_TRUE(g.has_vertex(2));
	EXPECT_FALSE(g.has_vertex(11));
}

TEST(GraphTest, RemoveHasVertexTest) {
	Graph<int> g;
	g.add_vertex(1);
	g.add_vertex(2);
	g.add_vertex(3);

	g.remove_vertex(2);
	g.remove_vertex(1);

	EXPECT_TRUE(g.has_vertex(3));
	EXPECT_FALSE(g.has_vertex(2));
	EXPECT_FALSE(g.has_vertex(1));
}

TEST(GraphTest, AddHasEdgesTest) {
	Graph<int> g;
	g.add_vertex(1);
	g.add_vertex(2);
	g.add_vertex(3);
	g.add_vertex(5);
	g.add_vertex(10);

	g.add_edge(1, 2, 5);
	g.add_edge(1, 3, 8);
	g.add_edge(2, 3, 4);
	g.add_edge(3, 5, 11);
	g.add_edge(3, 10, 6);

	EXPECT_TRUE(g.has_edge(1, 3));
	EXPECT_TRUE(g.has_edge(2, 3));
	EXPECT_TRUE(g.has_edge(3, 10));
	EXPECT_TRUE(g.has_edge(Edge<int, double>(1, 2, 5)));
	EXPECT_FALSE(g.has_edge(1, 10));
}

TEST(GraphTest, RemoveHasEdgesTest) {
	Graph<int> g;
	g.add_vertex(1);
	g.add_vertex(2);
	g.add_vertex(5);
	g.add_vertex(10);

	g.add_edge(1, 5, 5);
	g.add_edge(5, 10, 9);
	g.add_edge(2, 1, 8);
	g.add_edge(10, 2, 1);

	g.remove_edge(1, 5);
	g.remove_edge(5, 10);

	EXPECT_FALSE(g.has_edge(1, 5));
	EXPECT_TRUE(g.has_edge(10, 2));
	EXPECT_FALSE(g.has_edge(5, 10));
}

TEST(GraphTests, WalkTest) {
	Graph<int> g;

	for (int i = 0; i < 10; i++)
		g.add_vertex(i);

	g.add_edge(0, 2, 5);
	g.add_edge(1, 3, 8);
	g.add_edge(2, 3, 4);
	g.add_edge(3, 5, 11);
	g.add_edge(3, 4, 6);
	g.add_edge(4, 6, 2);
	g.add_edge(6, 7, 1);
	g.add_edge(2, 7, 3);

	auto path= g.walk(2);
	for (auto& e : path) {
		cout << e  << endl;
	}
	cout << "All super";
}

TEST(GraphTests, ShortestPathTest) {
	Graph<int> g;

	/*for (int i = 0; i < 8; i++)
		g.add_vertex(i);
	g.add_edge(6, 7, 1);
	g.add_edge(0, 2, 5);
	g.add_edge(2, 7, 3);
	g.add_edge(1, 3, 8);
	g.add_edge(3, 5, 11);
	g.add_edge(2, 3, 4);
	g.add_edge(3, 4, 6);
	g.add_edge(4, 6, 2);*/

	for (int i = 0; i < 5; i++)
		g.add_vertex(i);
	g.add_edge(3, 2, 4);
	g.add_edge(3, 4, 4);
	g.add_edge(2, 4, 4);
	g.add_edge(1, 2, 9);
	g.add_edge(1, 3, 7);

	auto path = g.shortest_path(1, 4).first;
	int count = 0;
	for (const auto& e : path) {
		cout << e.from << " --> " << e.to << " : " << e.distance << endl;
		count += e.distance;
	}
	cout << count;
}

TEST(GraphTests, WarehouseTest) {
	Graph<int> g;

	for (int i = 0; i < 4; i++)
		g.add_vertex(i);

	g.add_edge(0, 1, 5);
	g.add_edge(1, 0, 5);
	g.add_edge(0, 2, 10);
	g.add_edge(2, 0, 10);
	g.add_edge(1, 2, 4);
	g.add_edge(2, 1, 4);
	g.add_edge(2, 3, 3);
	g.add_edge(3, 2, 3);

	g.print();

	auto h = g.warehouse();
	cout << h;
}