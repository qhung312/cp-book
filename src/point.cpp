#pragma once

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Point {
	T x, y;
	Point(T x = 0, T y = 0) : x(x), y(y) {}
	friend bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }
	Point operator+(Point o) const { return Point(x + o.x, y + o.y); }
	Point operator-(Point o) const { return Point(x - o.x, y - o.y); }
	Point operator*(T o) const { return Point(x * o, y * o); }
	Point operator/(T o) const { return Point(x / o, y / o); }

	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt(dist2()); }
	double angle() const { return atan2(y, x); }
	Point unit() const { return *this / dist(); }
	Point perp() const { return Point(-y, x); }
	Point normal() const { return perp().unit(); }
	Point rotate(double a) const {
		return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}

	friend T dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
	friend T cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
	friend bool ccw(Point a, Point b, Point c) { return cross(b - a, c - b) > 0; }
	friend bool collinear(Point a, Point b, Point c) { return cross(b - a, c - b) == 0; }
	friend bool cw(Point a, Point b, Point c) { return cross(b - a, c - b) < 0; }
	friend ostream& operator<<(ostream& out, Point a) {
		out << "(" << a.x << ", " << a.y << ")";
		return out;
	}
};

// signed distance from point p to line from a to b
template<typename P>
double line_dist(P a, P b, P p) {
	return (double) cross(b - a, p - a) / (b - a).dist();
}

// project point p onto line from a to b
template<typename P>
P project(P a, P b, P p) {
	return a + (b - a) * (double) dot(b - a, p - a) / (b - a).dist2();
}

// reflect point p over line from a to b
template<typename P>
P reflect(P a, P b, P p) {
	auto ap = p - a;
	auto ah = project(a, b, p) - a;
	return ah * 2 - ap + a;
}

// intersection between line a->b and c->d
// returns:
// {1, p} if there is unique intersection
// {0, (0, 0)} if there is no intersection
// {-1, (0, 0)} if there are infinitely many intersections
template<typename P>
pair<int, P> line_intersect(P a, P b, P c, P d) {
	auto bad = cross(b - a, d - c);
	if (bad == 0) {
		auto s = cross(b - a, c - a);
		if (s == 0) {
			return {-1, P(0, 0)};
		} else {
			return {0, P(0, 0)};
		}
	}

	auto k = -cross(a - c, d - c) / cross(b - a, d - c);
	return {1, a + (b - a) * k};
}

// twice the signed area of a polygon (negative if points are given clockwise)
template<typename T>
T polygon_area2(vector<Point<T>>& v) {
	T ans = 0;
	int n = v.size();
	for (int i = 0; i < n; i++) {
		ans += v[i].x * v[(i + 1) % n].y;
		ans -= v[i].x * v[(i - 1 + n) % n].y;
	}
	return ans;
}

// check if p is on the segment from a to b
template<typename P>
bool on_seg(P a, P b, P p) {
	return collinear(a, b, p) && dot(p - a, b - p) >= 0;
}

// Check if p is inside a polygon
// Has optional parameter for strictly inside
template<typename P>
bool inside_polygon(vector<P>& v, P p, bool s = true) {
	int cnt = 0;
	int n = v.size();

	for (int i = 0; i < n; i++) {
		auto a = v[i], b = v[(i + 1) % n];
		if (on_seg(a, b, p)) return !s;
		if (a.y <= p.y && p.y < b.y) cnt ^= cross(a - p, b - p) > 0;
		if (b.y <= p.y && p.y < a.y) cnt ^= cross(b - p, a - p) > 0;
	}
	return cnt % 2 == 1;
}

// Find convex hull of a set of points in O(nlogn)
template<typename P>
vector<P> convex_hull(vector<P> v) {
	if (v.size() == 1) return v;

	sort(v.begin(), v.end(), [&](auto i, auto j) -> bool {
		if (i.y == j.y) return i.x < j.x;
		return i.y < j.y;
	});
	sort(v.begin() + 1, v.end(), [&](auto i, auto j) -> bool {
		if (collinear(v[0], i, j)) {
			return (i - v[0]).dist2() < (j - v[0]).dist2();
		}
		return ccw(v[0], i, j);
	});

	vector<P> ans;
	for (auto p : v) {
		while (ans.size() >= 2 && !ccw(ans[ans.size() - 2], ans[ans.size() - 1], p)) {
			ans.pop_back();
		}
		ans.push_back(p);
	}
	return ans;
}

// Return shortest distance from a point to a line segment
template<typename P>
double seg_dist(P a, P b, P p) {
	auto t = (double) dot(b - a, p - a) / (b - a).dist2();
	double ans = fmin((p - a).dist(), (p - b).dist());
	if (t >= 0 && t <= 1.0) {
		ans = fmin(ans, fabs(line_dist(a, b, p)));
	}
	return ans;
}

// Intersection between line segments
// returns:
// - Empty vector if no intersection
// - Vector of size 1 if there is unique intersection
// - Vector of size 2 if there are infinitely many intersections
template<typename P>
vector<P> seg_intersect(P a, P b, P c, P d) {
	auto bad = cross(b - a, d - c);
	if (bad == 0) {
		if (collinear(a, b, c)) {
			vector<P> ans;
			if (on_seg(c, d, a)) ans.push_back(a);
			if (on_seg(c, d, b)) ans.push_back(b);
			if (on_seg(a, b, c)) ans.push_back(c);
			if (on_seg(a, b, d)) ans.push_back(d);

			return ans;
		} else {
			return {};
		}
	} else {
		auto t1 = -cross(a - c, d - c) / cross(b - a, d - c);
		auto t2 = -cross(c - a, b - a) / cross(d - c, b - a);
		auto p = a + (b - a) * t1;

		vector<P> ans;
		if (t1 >= 0 && t1 <= 1.0 && t2 >= 0 && t2 <= 1.0) {
			ans.push_back(p);
		}
		return ans;
	}
}

// Calculate Minkowski sum of two convex polygons (https://cp-algorithms.com/geometry/minkowski.html)
// Uses mks_reorder as helper function
// Works in O(n+m)
template<typename P>
void mks_reorder(vector<P>& a) {
	int p = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i].y < a[p].y) {
			p = i;
		} else if (a[i].y == a[p].y && a[i].x < a[p].x) {
			p = i;
		}
	}
	rotate(a.begin(), a.begin() + p, a.end());
}

template<typename P>
vector<P> minkowski(vector<P> a, vector<P> b) {
	mks_reorder(a);
	mks_reorder(b);
	a.push_back(a[0]); a.push_back(a[1]);
	b.push_back(b[0]); b.push_back(b[1]);

	int i = 0, j = 0;
	vector<P> ans;
	while (i + 2 < a.size() || j + 2 < b.size()) {
		ans.push_back(a[i] + b[j]);
		auto cr = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
		if (cr >= 0) i++;
		if (cr <= 0) j++;
	}
	return ans;
}
