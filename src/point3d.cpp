#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> struct point3d {
    T x, y, z;
    point3d(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    bool operator==(point3d o) const {
        return x == o.x && y == o.y && z == o.z;
    }
    point3d operator+(point3d o) const {
        return point3d(x + o.x, y + o.y, z + o.z);
    }
    point3d operator-(point3d o) const {
        return point3d(x - o.x, y - o.y, z - o.z);
    }
    point3d operator*(T o) const { return point3d(x * o, y * o, z * o); }
    point3d operator/(T o) const { return point3d(x / o, y / o, z / o); }

    friend T dot(point3d a, point3d b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    friend point3d cross(point3d a, point3d b) {
        return point3d(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                       a.x * b.y - a.y * b.x);
    }

    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt((double)dist2()); }
    double phi() const { return atan2(y, x); }
    double theta() const { return atan2(sqrt(x * x + y * y), z); }

    point3d unit() const { return *this / (T)dist(); }
    point3d normal(point3d o) const { return cross(o).unit(); }
    point3d rotate(double angle, point3d axis) const {
        // rotate 'angle' radians around axis
        double s = sin(angle), c = cos(angle);
        point3d u = axis.unit();
        return u * dot(*this, u) * (1 - c) + (*this) * c - cross(*this, u) * s;
    }
};
