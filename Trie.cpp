#include"Trie.h"


struct Node
{   
    Node *son_node[MAX_NUM];
    Node *fail_node;
    int floor;
    int son_amoumt;
    char letter;
    const char* res;
    Node()
    {
        for(int i=0;i<MAX_NUM;i++)
            son_node[i]=nullptr;
        fail_node = nullptr;
        son_amoumt = 0;
        floor = 0;
        res = nullptr;
    }
    ~Node()
    {
        for(int i=0;i<MAX_NUM;i++)
        {
            if(son_node[i])
            {
                delete son_node[i];
                son_node[i] = nullptr;
            }
        }
    }
};

//  链队列 用于实现BFS
struct Q_node
{
    // 指针域
    Q_node *next_node;
    // 数据域
    Node *data_node;
    Q_node(Node *m_node)
    {
        next_node = nullptr;
        data_node = m_node;
    }
};


Trie::Trie()
{
    root = new Node();
    q_root = new Q_node(root);
    tree_size = 0;
}

Trie::~Trie()
{
    if(root)
    {
        delete root;
        root = nullptr;
    }
    if(q_root)
    {
        delete q_root;
        q_root = nullptr;
    }
}
// 计算一个节点的子节点个数


Node *Trie::create_node(char cur_letter)
{
   Node *m_node = new Node();
   m_node->letter = cur_letter;
   return m_node;
}

Node *Trie::insert_node(char cur_letter, Node *father)
{
    int cur_num = 0;
    // TODO son_amoumt 超出范围限制
    while(cur_num < father -> son_amoumt && cur_letter != father -> son_node[cur_num] -> letter)
    {
        cur_num ++;
    }
   if(cur_num < father -> son_amoumt)
   {
       return father -> son_node[cur_num];
   }
   else
   {
        Node *m_node = create_node(cur_letter);
        father -> son_node[cur_num] = m_node;
        father -> son_amoumt ++;
        return m_node;
   }
}

bool Trie::fail_tree(Node *m_node)
{
    
    for(int i = 0; i < m_node -> son_amoumt; i++)
    {
        if(m_node == root)
        m_node -> son_node[i] -> fail_node = root;
        else
        {
            int j = 0;
            while(j < m_node -> fail_node -> son_amoumt && m_node -> son_node[i] -> letter !=  m_node -> fail_node -> son_node[j] -> letter )
            {
                j++;
            }
            if(j < m_node -> fail_node -> son_amoumt)
            {
                m_node -> son_node[i] -> fail_node =  m_node -> fail_node -> son_node[j];
            }
            else
            {
                m_node -> son_node[i] -> fail_node = root;
            }
        }
    }
    return true;     
}

bool Trie::add_queue(Q_node *q_head, Q_node *q_tail)
{
    for(int i = 0; i < q_head -> data_node -> son_amoumt; i++)
    {
        Q_node *q_node = new Q_node(q_head -> data_node -> son_node[i]);
        q_tail -> next_node = q_node;
        fail_tree(q_node -> data_node);
        q_tail = q_node;
    }
    if(q_head != q_tail)
    {
        Q_node *new_head = q_head -> next_node;
        delete q_head;
        return add_queue(new_head, q_tail);
    }
    else
    {
        return true;
    }
}

bool Trie::goto_table(string match_str)
{
    Node *m_node = root;
    for(int count = 0; count<match_str.length(); count++)
    {
        int i = 0;
        // 当前节点的子节点的字母  当前字母   
        while(i < m_node -> son_amoumt && m_node -> son_node[i] -> letter != match_str[count])
        {
            i++;
        }
        if(i < m_node -> son_amoumt)
        {
            m_node = m_node -> son_node[i];
            // 非贪婪
            if(m_node -> res)
            {
                std::cout<<m_node->res<<std::endl;
                m_node = root;
            }
            // 贪婪
            // if(!m_node -> son_amoumt)
            // {
            //     std::cout<<m_node->res<<std::endl;
            //     m_node = root;
            // } 
        }
        // 当节点为最后一层的节点  肯定失效
        else
        {
            m_node = m_node -> fail_node;
            if(m_node != root)
                count --;
        }
    }
    return true;
}

bool Trie::build_trie(vector<string> &rules)
{
    // 字典树
    Node *m_node;
    for(string &rule : rules)
    {
        m_node = root;
        for(char &letter : rule)
        {
            m_node = insert_node(letter, m_node);
        }
        m_node -> res = rule.c_str();
    }

    // 失效树
    root -> fail_node = root;
    fail_tree(root);
    add_queue(q_root, q_root);
    return true;
}

bool Trie::run(string match_str)
{
    goto_table(match_str);
    return true;
}
