#include<bits/stdc++.h>
using namespace std;
class Trie
{
private:
    struct Node
    {
        int cnt = 0;
        int sum = 0;
        Node *tr[128] = {};
        ~Node()
        {
            for(int i=0;i<128;i++)
                if(tr[i])delete tr[i];
        }
    };
    Node* root;
public:
    void insert(char *s)
    {
        Node* ptr = root;
        for(;*s;s++)
        {
            if(!ptr->tr[*s])
                ptr->tr[*s] = new Node();
            ptr = ptr->tr[*s];
            ptr->sum++;
        }
        ptr->cnt++;
    }
    inline int count(char *s)
    {
        Node *ptr = find(s);
        return ptr ? ptr->cnt : 0;
    }
    Node* find(char *s)
    {
        Node* ptr = root;
        for(;*s;s++)
        {
            if(!ptr->tr[*s])return 0;
            ptr = ptr->tr[*s];
        }
        return ptr;
    }
    bool erase(char *s)
    {
        Node *ptr = find(s);
        if(!ptr)return false;
        int num = ptr->cnt;
        if(!num)return false;
        ptr = root;
        for(;*s;s++)
        {
            Node *tmp = ptr;
            ptr = ptr->tr[*s];
            ptr->sum -= num;
            if(!ptr->sum)
            {
                delete ptr;
                tmp->tr[*s] = 0;
                return true;
            }
        }
    }
    Trie(){root = new Node();}
    ~Trie(){delete root;}
};

int main()
{
    Trie *trie = new Trie();
    string op;
    char s[20];
    while(cin>>op)
    {
        if(op=="END")
        {
            delete trie;
            break;
        }
        else if(op=="insert")
        {
            cin >> s;
            trie->insert(s);
        }
        else if(op=="erase")
        {
            cin >> s;
            if(trie->erase(s))printf("Success erase");
            else printf("Fail erase");
        }
        else if(op=="count")
        {
            cin >> s;
            printf("%d\n",trie->count(s));
        }
    }
    return 0;
}
