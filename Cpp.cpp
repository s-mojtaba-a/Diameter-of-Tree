#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename T>
T diameter(T i, T MAX_child[], T to_leaf[], T max_length[], pair<int, int> who[], vector<vector<T>> &s, T father, T &ans, T &MAX_root)
{
    if (s[i].size() == 1)
    {
        to_leaf[i] = 0;
        who[i].first = -1;
        who[i].second = -1;
        MAX_child[i] = 0;
        return 0;
    }
    T MAX1 = -1, child1, MAX2 = -1, child2;
    for (auto v : s[i])
    {
        if (v == father)
            continue;
        diameter(v, MAX_child, to_leaf, max_length, who, s, i, ans, MAX_root);
        if (MAX1 < to_leaf[v])
        {
            child1 = v;
            MAX1 = to_leaf[v];
        }
        else
        {
            if (MAX2 < to_leaf[v])
            {
                MAX2 = to_leaf[v];
                child2 = v;
            }
        }
    }
    to_leaf[i] = MAX1 + 1;
    if (ans < MAX2 + MAX1 + 2)
    {
        MAX_root = i;
        ans = MAX2 + MAX1 + 2;
    }
    MAX_child[i] = child1;
    who[i].first = child1;
    who[i].second = child2;
    return ans;
}

void printpath(int i, int MAX_child[])
{
    if (MAX_child[i] == 0)
    {
        cout << i << ' ';
        return;
    }
    cout << i << ' ';
    printpath(MAX_child[i], MAX_child);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> s(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        s[a].emplace_back(b);
        s[b].emplace_back(a);
    }
    int ans = 0, MAX_root = 0;
    int to_leaf[n + 1] = {0}, max_length[n + 1] = {0}, MAX_child[n + 1];
    pair<int, int> who[n + 1];
    cout << diameter(1, MAX_child, to_leaf, max_length, who, s, 0, ans, MAX_root) << '\n';
    printpath(who[MAX_root].first, MAX_child);
    cout << MAX_root << ' ';
    printpath(who[MAX_root].second, MAX_child);
}