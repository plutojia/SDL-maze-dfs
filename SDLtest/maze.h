#pragma once
#include <iostream>
#include <vector>
#include <random>
#define MX 5
#define MY 5

struct point {
	int i;
	int j;
	point() = default;
	point(int ii, int jj) :i(ii), j(jj) {}
};
class cell {
public:
	cell() = default;
	cell(int ttop, int tdown, int tright, int tleft) :top(ttop), down(tdown), right(tright), left(tleft), used(false) {}
	bool used;
	int top, down, right, left;
};

class maze {
public:
	maze() {
		for (int i = 0; i<MY; i++) {
			std::vector<cell> cell_row(MX);
			cells.push_back(cell_row);
		}
	}
	std::random_device rd;
	int generate();
	void print() const;
	void draw() const;
	//#ifdef whole
	void render() const;
	void renderroute() const;
	//	#endif
	int find(int i, int j);
	point getroute(int step) {
		if (!route.empty())
			return route[step];
	}
	bool routeempty() {
		return route.empty();
	}
	void showroute();
private:
	std::vector <std::vector<cell> > cells;
	std::vector <point> route;
	int rand1();
};