// 支援區間加值、區間反轉、區間 rotate 、區間刪除、插入元素、求區間
// 最小值的元素的 Treap。使用前建議 srand(time(0)); 除了 size()
// 方法以外，所有操作都是 O(log N) 。所有 public 方法各自獨立，請
// 斟酌要使用到哪些方法，有需要的才抄。
class Treap {
   private:
    struct Node {
        int pri = rand(), size = 1;
        ll val, mn, inc = 0;
        bool rev = 0;
        Node *lc = 0, *rc = 0;
        Node(ll v) { val = mn = v; }
    };
    Node* root = 0;
    void rev(Node* t) {
        if (!t) return;
        swap(t->lc, t->rc), t->rev ^= 1;
    }
    void update(Node* t, ll v) {
        if (!t) return;
        t->val += v, t->inc += v, t->mn += v;
    }
    void push(Node* t) {
        if (t->rev) rev(t->lc), rev(t->rc), t->rev = 0;
        update(t->lc, t->inc), update(t->rc, t->inc);
        t->inc = 0;
    }
    void pull(Node* t) {
        t->size = 1 + size(t->lc) + size(t->rc);
        t->mn = t->val;
        if (t->lc) t->mn = min(t->mn, t->lc->mn);
        if (t->rc) t->mn = min(t->mn, t->rc->mn);
    }
    // 看你要不要釋放記憶體
    void discard(Node* t) {
        if (!t) return;
        discard(t->lc), discard(t->rc);
        delete t;
    }
    void split(Node* t, Node*& a, Node*& b, int k) {
        if (!t) return a = b = 0, void();
        push(t);
        if (size(t->lc) < k) {
            a = t;
            split(t->rc, a->rc, b, k - size(t->lc) - 1);
            pull(a);
        } else {
            b = t;
            split(t->lc, a, b->lc, k);
            pull(b);
        }
    }
    Node* merge(Node* a, Node* b) {
        if (!a || !b) return a ? a : b;
        if (a->pri > b->pri) {
            push(a);
            a->rc = merge(a->rc, b);
            pull(a);
            return a;
        } else {
            push(b);
            b->lc = merge(a, b->lc);
            pull(b);
            return b;
        }
    }
    inline int size(Node* t) { return t ? t->size : 0; }
   public:
    int size() { return size(root); }
    void add(int l, int r, ll val) {
        Node *a, *b, *c, *d;
        split(root, a, b, r);
        split(a, c, d, l - 1);
        update(d, val);
        root = merge(merge(c, d), b);
    }
    // 反轉區間 [l, r]
    void reverse(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, a, b, r);
        split(a, c, d, l - 1);
        swap(d->lc, d->rc);
        d->rev ^= 1;
        root = merge(merge(c, d), b);
    }
    // 區間 [l, r] 向右 rotate k 次， k < 0 表向左 rotate
    void rotate(int l, int r, int k) {
        int len = r - l + 1;
        Node *a, *b, *c, *d, *e, *f;
        split(root, a, b, r);
        split(a, c, d, l - 1);
        k = (k + len) % len;
        split(d, e, f, len - k);
        root = merge(merge(c, merge(f, e)), b);
    }
    // 插入一個元素 val 使其 index = i
    // 注意 i <= size
    void insert(int i, ll val) {
        if (i == size() + 1) {
            push_back(val);
            return;
        }
        assert(i <= size());
        Node *a, *b;
        split(root, a, b, i - 1);
        root = merge(merge(a, new Node(val)), b);
    }
    void push_back(ll val) {
        root = merge(root, new Node(val));
    }
    void remove(int l, int r) {
        int len = r - l + 1;
        Node *a, *b, *c, *d;
        split(root, a, b, l - 1);
        split(b, c, d, len);
        discard(c); // 看你要不要釋放記憶體
        root = merge(a, d);
    }
    ll minn(int l, int r) {
        Node *a, *b, *c, *d;
        split(root, a, b, r);
        split(a, c, d, l - 1);
        int ans = d->mn;
        root = merge(merge(c, d), b);
        return ans;
    }
};
