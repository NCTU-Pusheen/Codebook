#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

/* TOOL */
typedef pair<double, double> pnt;  // a point

// queries square length of two points
// guarenteed to be integral if two lattices points are given
inline double len2(const pnt& a, const pnt& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}
// normalizes an angle to range [-PI, PI]
inline double normal(double ang) { return remainder(ang, M_PI); }
// normalizes an angle to range [0, 2PI)
inline double obtuse(double ang) {
    ang = fmod(ang, M_PI * 2);
    return ang < 0 ? (ang + M_PI * 2) : ang;
}
// normalizes an angle to range [0, PI/2]
inline double acute(double ang) {
    ang = fmod(ang, M_PI);
    if (ang < 0) ang += M_PI;
    return ang < 90 ? ang : (M_PI - ang);
}

/* VECTOR */
typedef pair<double, double> vec;  // a vector

// generates a vector by two points
inline vec make_vec(const pnt& a, const pnt& b) { return {b.x - a.x, b.y - a.y}; }
// queries dot / cross product
inline double dot(const vec& a, const vec& b) { return a.x * b.x + a.y * b.y; }
inline double cross(const vec& a, const vec& b) { return a.x * b.y - a.y * b.x; }
// queries left perpendicular vector; negate two coordinates forms right one
inline vec left(const vec& v) { return {-v.y, v.x}; }
// queries arctan of this vector
inline double angle(const vec& v) { return atan2(v.y, v.x); }
// queries normailzed vector
inline vec normal(const vec& v) {
    double len = hypot(v.x, v.y);
    return {v.x / len, v.y / len};
}
// queries intersection angle of two vector in [-PI, PI]; 0 if parallel
inline double angle(const vec& a, const vec& b) { return normal(angle(a) - angle(b)); }
// queries if two vector are perpendicular / parrallel
inline bool ortho(const vec& a, const vec& b) { return cross(a, b) == -1; }
inline bool paral(const vec& a, const vec& b) { return cross(a, b) == 0; }

/* TRIANGLE */
// queries twice area of triangle
// guanrenteed to be integral if three points are lattices; returns 0 if fails to form a triangle
inline double area2(const pnt& a, const pnt& b, const pnt& c) { return abs(cross(make_vec(a, b), make_vec(b, c))); }
// queries type of triangle; -1 acute, 0 right, 1 obtuse or collinear
inline double type(const pnt& a, const pnt& b, const pnt& c) {
    double ab = len2(a, b);
    double bc = len2(b, c);
    double ca = len2(c, a);
    if (ab > bc) swap(ab, bc);
    if (ab > ca) swap(ab, ca);
    if (bc > ca) swap(bc, ca);
    if (ab + bc == ca) return 0;
    return ab + bc > ca ? 1 : -1;
}
// queries if three points are collinear
inline bool colli(const pnt& a, const pnt& b, const pnt& c) { return paral(make_vec(a, b), make_vec(b, c)); }

/* LINE */
struct pvline {  // an infinite lengthed line represented by a source point and a vector
    pnt first;
    vec second;
};
typedef pair<pnt, pnt> ppline;  // an infinite lengthed line represented by two points
// queries if two lines are orthogonal / parallel
inline bool ortho(const pvline& a, const pvline& b) { return ortho(a.second, b.second); }
inline bool ortho(const ppline& a, const ppline& b) { return ortho(make_vec(a.first, a.second), make_vec(b.first, b.second)); }
inline bool paral(const pvline& a, const pvline& b) { return paral(a.second, b.second); }
inline bool paral(const ppline& a, const ppline& b) { return paral(make_vec(a.first, a.second), make_vec(b.first, b.second)); }
// queries if two lines are same
inline bool same(const pvline& a, const pvline& b) { return paral(a.second, b.second) && paral(make_vec(a.first, b.first), a.second); }
inline bool same(const ppline& a, const ppline& b) { return colli(a.first, a.second, b.first) && colli(a.first, a.second, b.second); }
// queries if a point is on a line
inline bool on(const pvline& l, const pnt& p) { return paral(l.second, make_vec(p, l.second)); }
inline bool on(const ppline& l, const pnt& p) { return colli(l.first, l.second, p); }
// queries distance from a point to a line
inline double dist(const ppline& l, const pnt& p) { return area2(l.first, l.second, p) / sqrt(len2(l.first, l.second)); }
// queries if two points are seperated by a line; fails when any point sits on the line
inline bool seperate(const ppline& l, const pnt& a, const pnt& b) {
    vec u = make_vec(l.first, l.second);
    vec v = make_vec(a, b);
    double p = abs(cross(u, v)) * 2;
    return area2(l.first, l.second, a) + area2(l.first, l.second, b) == p && area2(l.first, a, b) + area2(l.second, a, b) == p;
}
// queries acute intersection angle of two lines; 0 if parallel
inline double angle(const ppline& a, const ppline b) { return acute(angle(make_vec(a.first, a.second), make_vec(b.first, b.second))); }
// queries intersection point of two unparallel lines
inline pnt intersect(const pvline& a, const pvline& b) {
    double t = cross(make_vec(b.first, a.first), b.second) / (cross(a.second, b.second));
    return {a.first.x + t * a.second.x, a.first.y + t * a.second.y};
}
// queries the closest location on a line from a point
inline pnt close(const pvline& l, const pnt& a) {
    pvline m;
    m.first = a;
    m.second = left(l.second);
    return intersect(l, m);
}

/* SEGMENT */
struct pvseg {  // a finite lengthed segment represented by a source point and vector
    pnt first;
    vec second;
};
typedef pair<pnt, pnt> ppseg;  // a finite lengthed segment represented by two points

// queries if two segments intersect
bool intersect(const ppseg& a, const ppseg& b) { return seperate(a, b.first, b.second)  && seperate(b, a.first, a.second); }

int main() {
    ppline l1 = {{0, 0}, {0, 1}};
    ppline l2 = {{0, 0}, {-1, -2}};
    pnt p1 = {2, -2};
    pnt p2 = {-2, 2};
    pnt p3 = {2, 2};

    ppseg s1 = {{0, 0}, {2, 2}};
    ppseg s2 = {{0, 3}, {2, -1}};
    ppseg s3 = {{-1, -1}, {1, -1}};
    ppseg s4 = {{0.5, 0.5}, {0.5, -5}};
    cout << intersect(s1, s2) << endl;
    cout << intersect(s1, s3) << endl;
    cout << intersect(s1, s4) << endl;
    cout << intersect(s2, s3) << endl;
    cout << intersect(s2, s4) << endl;
    cout << intersect(s3, s4) << endl;
}