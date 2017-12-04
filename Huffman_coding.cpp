#include <bits/stdc++.h>
using namespace std;
#define __portable__

class Huffman {
public:
    struct Node {
        int cnt;
        Node* pa;
        virtual ~Node() {}
        Node(int n = 0): cnt(n), pa(nullptr) {}
        bool operator < (const Node& rhs) const {
            return cnt > rhs.cnt;
        }
        struct ptr_ads_cmp {
            bool operator ()(const Node* lhs, const Node* rhs){
                return lhs < rhs;
        }};
        struct ptr_cnt_cmp {
            bool operator ()(const Node* lhs, const Node* rhs){
                return lhs->cnt > rhs->cnt;
        }};
    };
    struct Leaf : public Node {
        char ch;
        Leaf(char c, int n = 0):
            Node(n), ch(c) {}
    };
    struct Conjung : public Node {
        Node *l, *r;
        Conjung(Node* _l = 0, Node* _r = 0):
            Node(0), l(_l), r(_r) {
                if(_l) _l->pa = this, Node::cnt += _l->cnt;
                if(_r) _r->pa = this, Node::cnt += _r->cnt;
        }
        bool add_branch(Node* nd){
            nd->pa = this;
                 if(!l) return l = nd;
            else if(!r) return r = nd;
            else return false;
        }
    };
    typedef std::string Str;
    typedef std::map<char, Node*> BackTrack;
    Huffman(Str str = ""): root(0), bt() {
        if (str != ""){
            build(str);
    }}
    Str encode(Node* nd) const {
        Str res;
        while (auto pa = dynamic_cast<Conjung*>(nd->pa)){
            res += nd == pa->l ? '0' : '1';
            nd = pa;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
    Str encode(Str str) const {
        Str res;
        for (char c : str){
            assert(bt.count(c));
            res += encode(bt.at(c));
        }
        return res;
    }
    Str decode(Str str) const {
        Str res;
        Node* tm = root;
        for (char c : str){
            assert(c == '0' || c == '1');
            auto cj = dynamic_cast<Conjung*>(tm);
            tm = c == '0' ? cj->l : cj->r;
            if (auto leaf = dynamic_cast<Leaf*>(tm)){
                res += leaf->ch;
                tm = root;
        }}
        return res;
    }
    void build(Str str){
        std::map<char, int> mp;
        for (char c : str) mp[c]++;
        std::priority_queue<Node*, vector<Node*>, Node::ptr_cnt_cmp> pq;
        for (auto p : mp){
            pq.push(bt[p.first] = new Leaf(p.first, p.second));
        }
        while (pq.size() != 1){
            Node* n1 = pq.top(); pq.pop();
            Node* n2 = pq.top(); pq.pop();
            pq.push(new Conjung(n1, n2));
        }
        this->root = const_cast<Node*>(pq.top());
    }
#ifdef __portable__
    Huffman& build_from_hash_tree(Str in){
        bt.clear();
        std::stack<Conjung*> stk;
        stk.push(dynamic_cast<Conjung*>(root = new Conjung(0, 0)));
        for (char ch : in.substr(1)){
            Node* nd;
            if (ch == '<')
                 nd = new Conjung(0, 0);
            else nd = bt[ch] = new Leaf(ch);
            while (!stk.top()->add_branch(nd)){
                    stk.pop();
        }}
        return *this;
    }
    Str get_hash_tree() const {
        Str out;
        std::stack<Node*> stk({root});
        while (!stk.empty()){
            auto nd = stk.top(); stk.pop();
            if (auto conj = dynamic_cast<Conjung*>(nd)){
                out += '>';
                stk.push(conj->r);
                stk.push(conj->l);
            }
            if (auto leaf = dynamic_cast<Leaf*>(nd)){
                out += leaf->ch;
        }}
        return out;
    }
#endif
    friend ostream& operator << (ostream& o, const Huffman& hfm){
#ifdef __portable__
        o << "parent list\n" << hfm.get_hash_tree() << endl;
#endif
        o << "binary list\n";
        for (auto p : hfm.bt){
            o << p.first << ' ' << hfm.encode(p.second) << endl;
        }
        return o;
    }
private:
    Node* root;
    BackTrack bt;
};

int main(){
    std::string s;
    std::cout << "key \'break\' to break\n";
    while (std::cout << "huffman coding : " && std::cin >> s && s != "break"){
        Huffman hfm(s);
        cout << s << '\n' << hfm << endl;
        while (std::cout << "query : " && std::cin >> s && s != "break"){
            auto en = hfm.encode(s);
            cout << s << '\t' << en << endl;
            assert (s == hfm.decode(en));
#ifdef __portable__
            hfm = Huffman().build_from_hash_tree(hfm.get_hash_tree());
#endif
    }}
}
