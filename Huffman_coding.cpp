#include <bits/stdc++.h>
using namespace std;
//#define __portable__

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
        void add_branch(Node* nd){
            nd->pa = this;
                 if(!l) l = nd;
            else if(!r) r = nd;
            else ::exit(1);
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
        stringstream inp; inp << in;
        std::map<int,Conjung*> mp;
        bt.clear();
        this->root = mp[0] = new Conjung(0, 0);
        Str str;
        int num;
        while (inp >> str >> num){
            if (str.front() != '%'){
                int dif = std::stoi(str);
                mp[num]->add_branch(mp[dif] = new Conjung(0, 0));
            }else{
                mp[num]->add_branch(bt[str[1]] = new Leaf(str[1]));
        }}
        return *this;
    }
    Str get_hash_tree() const {
        std::map<Node*, int, Node::ptr_ads_cmp> mp;
        std::queue<Node*> q({root});
        stringstream out;
        int x = 0;
        mp[root] = x++;
        while (!q.empty()){
            auto nd = q.front(); q.pop();
            auto conj = dynamic_cast<Conjung*>(nd);
            for (auto ptr : {conj->l, conj->r}){
                if (auto leaf = dynamic_cast<Leaf*>(ptr)){
                    out << '%' << leaf->ch << ' ' << mp[nd] << ' ';
                }else{
                    out << (mp[ptr] = x++) << ' ' << mp[nd] << ' ';
                    q.push(ptr);
        }}}
        return out.str();
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
        cout << hfm << endl;
        while (std::cout << "query : " && std::cin >> s && s != "break"){
            auto en = hfm.encode(s);
            cout << s << '\t' << en << endl;
            assert (s == hfm.decode(en));
#ifdef __portable__
            hfm = Huffman().build_from_hash_tree(hfm.get_hash_tree());
#endif
    }}
}
