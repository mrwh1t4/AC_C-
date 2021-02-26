#include"Trie.h"


int main()
{
    string rule1 = "she";
    string rule2 = "shr";
    string rule3 = "he";
    string rule4 = "shell";
    string rule5 = "script";
    vector<std::string> rules;
    rules.push_back(rule1);
    rules.push_back(rule2);
    rules.push_back(rule3);
    rules.push_back(rule4);
    rules.push_back(rule5);

    Trie m_trie=Trie();
    m_trie.build_trie(rules);
    string match_str = "hellscripts";

    m_trie.run(match_str);
    return 0;
}