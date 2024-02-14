#include <iostream>
#include <string>
#include <vector>
using namespace std;
void show(vector<int> v)
{
    for (size_t i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << "\n";
}
void merge_sort(vector<int> &v, vector<int> &s, int l, int r)
{
    int m = (l + r) / 2;
    int i(l), j(m + 1), k(l);
    while (i <= m || j <= r)
    {
        if (j > r)
            s[k++] = v[i++];
        else if (i > m)
            s[k++] = v[j++];
        else if (v[i] < v[j])
            s[k++] = v[i++];
        else
            s[k++] = v[j++];
    }
}
void merge(vector<int> &v, vector<int> &s, int l, int r)
{
    vector<int> t(s.size());
    if (l == r)
        s[l] = v[l];
    else
    {
        int m = (l + r) / 2;
        merge(v, t, l, m);
        merge(v, t, m + 1, r);
        merge_sort(t, s, l, r);
    }
}
int main()
{
    vector<int> v = {1, 3, 7, 2, 14, 12, 5, 8};
    // vector<int> s(v.size());
    cout << "The initial array:\n";
    show(v);
    int l(0), r(v.size() - 1);
    merge(v, v, l, r);
    cout << "After the mergesort:\n";
    show(v);
    system("pause");
    return 0;
}
