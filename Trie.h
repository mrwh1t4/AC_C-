#include<string>
#include<vector>
#include<iostream>
#define MAX_NUM 62
typedef struct Node Node;
typedef struct Q_node Q_node;

using std::vector;
using std::string;
class Trie
{
    public:

    //  构造函数
    Trie();
    //  析构函数
    ~Trie();
    //  建立字典树
    bool build_trie(vector<std::string> &rules);
    bool run(string match_str);
    private:

    //  创建节点
    Node *create_node(char cur_letter);
    //  插入节点
    Node *insert_node(char cur_letter, Node *father);
    bool legal_rules();
    bool fail_tree(Node *m_node);
    bool add_queue(Q_node *q_head, Q_node *q_tail);
    bool goto_table(string match_str);
    
    //  根节点
    Node *root;
    //  树大小
    int tree_size;

    // 队列根
    Q_node *q_root;

};