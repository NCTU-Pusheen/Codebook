class Trie {
private:
    struct Node {
        int cnt = 0, sum = 0;
        Node *tr[128] = {};
        ~Node() {
            for (int i = 0; i < 128; i++)
                if (tr[i]) delete tr[i];
        }
    };
    Node *root;
public:
    void insert(char *s) {
        Node *ptr = root;
        for (; *s; s++) {
            if (!ptr->tr[*s]) ptr->tr[*s] = new Node();
            ptr = ptr->tr[*s];
            ptr->sum++;
        }
        ptr->cnt++;
    }
    inline int count(char *s) {
        Node *ptr = find(s);
        return ptr ? ptr->cnt : 0;
    }
    Node *find(char *s) {
        Node *ptr = root;
        for (; *s; s++) {
            if (!ptr->tr[*s]) return 0;
            ptr = ptr->tr[*s];
        } return ptr;
    }
    bool erase(char *s) {
        Node *ptr = find(s);
        if (!ptr) return false;
        int num = ptr->cnt;
        if (!num) return false;
        ptr = root;
        for (; *s; s++) {
            Node *tmp = ptr;
            ptr = ptr->tr[*s];
            ptr->sum -= num;
            if (!ptr->sum) {
                delete ptr;
                tmp->tr[*s] = 0;
                return true;
            }
        }
    }
    Trie() { root = new Node(); }
    ~Trie() { delete root; }
};
