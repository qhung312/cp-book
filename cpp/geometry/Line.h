#pragma once
#include <bits/stdc++.h>
#include "Point.h"
using namespace std;

template<typename T>
struct Line {
    Point<T> a, d;
    Line() : a(), d() {}
    Line(const Point<T> &s, const Point<T> &t) : a(s), d(t.x - s.x, t.y - s.y) {}
    bool operator!() { return d != Point(0, 0); }
    Point<T> b() const { return a + d; }

    template<typename T1>
    friend bool onLine(const Point<T1> &p, const Line<T1> &l) {
        if (!l) return p == l.a;
        return cross(p - l.a, l.d) == 0;
    }
    template<typename T1>
    friend bool onSegment(const Point<T1> &p, const Line<T1> &l) {
        if (!l) return p == l.a;
        return cross(p - l.a, l.d) == 0 && dot(l.a - p, l.b() - p) <= 0;
    }
    template<typename T1>
    friend double distLine(const Point<T1> &p, const Line<T1> &l) {
        if (!l) return (p-l.a).dist();
        return (double) cross(l.a - p, l.b() - p) / l.d.dist();
    }
    template<typename T1>
    friend double distSegment(const Point<T1> &p, const Line<T1> &l) {
        if (dot(p - l.a, l.d) <= 0) return (p - l.a).dist();
        if (dot(p - l.b, l.d) >= 0) return (p - l.b()).dist();
        return distLine(p, l);
    }
    template<typename T1>
    friend double projection(const Point<T1> &p, const Line<T1> &l) {
    }
};
