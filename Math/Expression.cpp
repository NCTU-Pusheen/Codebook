/**
 * 支援處理四則運算的工具。給四則運算的字串，檢查格式並計算其值。如果
 * 格式不合法，會丟出錯誤。複雜度 O(字串長度) 。支援的符號有四則運算
 * 和求餘數，先乘除後加減。可以使用括號、或前置正負號。數字開頭可以為
 * 零或禁止為零。可以兼容或禁止多重前置號 (例如 --1 視為 1 、+-+-1
 * 視為 -1) 。空字串視為不合法。運算範圍限於 long long 。如果試圖除
 * 以零或對零求餘也會丟出錯誤。
 */
void req(bool b) { if (!b) throw ""; }
const int B = 2; // 可以調整成 B 進位
class Expr {
   private:
    deque<char> src;
    Expr(const string& s) : src(s.begin(), s.end()) {}
    inline char top() {
        return src.empty() ? '\0' : src.front();
    }
    inline char pop() {
        char c = src.front(); src.pop_front(); return c;
    }
    ll n() {
        ll ret = pop() - '0';
        // 若要禁止數字以 0 開頭，加上這行
        // req(ret || !isdigit(top()));
        while (isdigit(top())) ret = B * ret + pop() - '0';
        return ret;
    }
    ll fac() {
        if (isdigit(top())) return n();
        if (top() == '-') { pop(); return -fac(); }
        if (top() == '(') {
            pop();
            ll ret = expr(1);
            req(pop() == ')');
            return ret;
        }
        // 若要允許前置正號，加上這行
        // if(top() == '+') { pop(); return fac(); }
        throw "";
    }
    ll term() {
        ll ret = fac(); char c = top();
        while (c == '*' || c == '/' || c == '%') {
            pop();
            if (c == '*') ret *= fac();
            else {
                ll t = fac(); req(t);
                if (c == '/') ret /= t; else ret %= t;
            }
            c = top();
        } return ret;
    }
    ll expr(bool k) {
        ll ret = term();
        while (top() == '+' || top() == '-')
            if (pop() == '+') ret += term();
            else ret -= term();
        req(top() == (k ? ')' : '\0'));
        return ret;
    }
   public:
    // 給定數學運算的字串，求其值。若格式不合法，丟出錯誤。
    static ll eval(const string& s) {
        // 若要禁止多重前置號，加上這四行
        // req(s.find("--") == -1); // 禁止多重負號
        // req(s.find("-+") == -1);
        // req(s.find("+-") == -1);
        // req(s.find("++") == -1);
        return Expr(s).expr(0);
    }
};
