#include <bits/stdc++.h>

using namespace std;

int _N, _M, _K;

void repeat(vector<int> & ans, vector<int> func);

int main(void)
{
    scanf("%d%d%d", &_N, &_M, &_K);

    vector<int> arr;
    for (int i = 1; i <= _N; i++) arr.push_back(i);

    for (int i = 0; i < _M; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        --a; --b;
        for (int j = 0; j < (b - a + 1) / 2; j++) swap(arr[a + j], arr[b - j]);
    }

    vector<int> ans(arr);
    for (int i = 1; i < _K; i++) repeat(ans, arr);

    for (int i = 0; i < _N; i++) printf("%d\n", ans[i]);
    return 0;
}

void repeat(vector<int> & ans, vector<int> func)
{
    for (int i = 0; i < _N; i++) ans[i] += ans[func[i] - 1] % 10000 * 10000;
    for (int i = 0; i < _N; i++) ans[i] /= 10000;
}