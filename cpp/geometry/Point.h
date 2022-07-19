#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Point {
    T x, y;
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    friend ostream& operator<<(ostream &out, const Point &p) { out << "(" << p.x << "," << p.y << ")"; return out; }
    friend istream& operator>>(istream &in, Point &p) { in >> p.x >> p.y; return in; }
    friend bool operator==(const Point &a, const Point &b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const Point &a, const Point &b) { return !(a == b); }

    Point& operator+=(const Point &b) { x += b.x; y += b.y; return *this; }
    Point& operator-=(const Point &b) { x -= b.x; y -= b.y; return *this; }
    Point& operator*=(const T &b) { x *= b; y *= b; return *this; }
    Point& operator/=(const T &b) { x /= b; y /= b; return *this; }
    Point operator+() const { return Point(x, y); }
    Point operator-() const { return Point(-x, -y); }

    friend Point operator+(const Point &a, const Point &b) { return Point(a.x + b.x, a.y + b.y); }
    friend Point operator-(const Point &a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }
    friend Point operator*(const Point &a, const T &b) { return Point(a.x * b, a.y * b); }
    friend Point operator/(const Point &a, const T &b) { return Point(a.x / b, a.y / b); }

    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt(dist2()); }
    Point unit() const { return *this / dist(); }
    double angle() const { return atan2(y, x); }
    Point rotate(double a) { return Point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
    Point perp_ccw() const { return Point(-y, x); }
    Point perp_cw() const { return Point(y, -x); }

    friend T dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }
    friend T cross(const Point &a, const Point &b) { return a.x * b.y - a.y * b.x; }
    friend bool ccw(const Point &a, const Point &b, const Point &c) { return cross(b - a, c - b) > 0; }
    friend bool cw(const Point &a, const Point &b, const Point &c) { return cross(b - a, c - b) < 0; }
};
