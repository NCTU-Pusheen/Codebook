#define cfl(str) (const frac& f) const { return str; }
#define cll(str) (ll l) const { return str; }
#define lfl(str) (ll l, const frac& f) { return str; }
#define ff inline frac operator
#define bb inline bool operator
#define fff inline friend frac operator
#define fbb inline friend bool operator

class frac {
   private: ll x, y;
   public:
    frac() : x(0), y(1) {}
    frac(ll v) : x(v), y(1) {}
    frac(ll xx, ll yy, bool f = 0) : x(xx), y(yy) {
        assert(y != 0);
        if (!f) {
            ll g = __gcd(x, y);
            x /= g, y /= g;
            if (y < 0) x *= -1, y *= -1;
        }
    }
    // 以下斟酌使用，不必全抄
    ff = (ll l) { return frac(l); }
    ff - () const { return frac(-x, y, 1); }
    ff ! () const {  // 倒數
        return x > 0 ? frac(y, x, 1) : frac(-y, -x, 1);
    }

    bb >  cfl(x * f.y > y * f.x)
    bb <  cfl(x * f.y < y * f.x)
    bb <= cfl(x * f.y <= y * f.x)
    bb >= cfl(x * f.y >= y * f.x)
    bb == cfl(x == f.x && y == f.y)
    bb != cfl(x != f.x || y != f.y)
    ff +  cfl(frac(x * f.y + y * f.x, y * f.y))
    ff -  cfl(frac(x * f.y - y * f.x, y * f.y))
    ff *  cfl(frac(x * f.x, y * f.y))
    ff /  cfl(frac(x * f.y, y * f.x))

    bb >  cll(x > l * y)
    bb <  cll(x < l * y)
    bb >= cll(x >= l * y)
    bb <= cll(x <= l * y)
    bb == cll(x == l * y)
    bb != cll(x != l * y)
    ff +  cll(frac(x + l * y, y))
    ff -  cll(frac(x - l * y, y))
    ff *  cll(frac(l * x, y))
    ff /  cll(frac(x, l * y))

    fbb <  lfl(f > l)
    fbb >  lfl(f < l)
    fbb <= lfl(f >= l)
    fbb >= lfl(f <= l)
    fbb == lfl(f == l)
    fbb != lfl(f != l)
    fff +  lfl(f + l)
    fff -  lfl(-f + l)
    fff *  lfl(f * l)
    fff /  lfl(!f * l)

    inline operator double() { return (double)x / y; }
    inline friend frac abs(const frac& f) {
        return frac(abs(f.x), f.y, 1);
    }
    inline friend ostream& operator <<
         (ostream & out, const frac& f) {
        out << f.x;
        if (f.y != 1) out << '/' << f.y;
        return out;
    }
};
