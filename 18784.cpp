#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

const int MOD = 1000000007;
int _N;
vector<pair<int, int>> _C;
vector<vector<int>> pivx, pivy, pivxs, pivys;

void getpiv();
bool cmpvec(vector<int> a, vector<int> b) {return a[0] < b[0];}

int main(void)
{
    scanf("%d", &_N);
    _C.assign(_N, pair<int, int>());

    for (int i = 0; i < _N; i++) scanf("%d%d", &_C[i].first, &_C[i].second);
    getpiv();
    
    lli ans = 0;

    for (int i = 0; i < pivy.size(); i++)
    {
        lli tmp = 0;
        for (int inj = 1; inj < pivy[i].size(); inj++)
        {
            int j = lower_bound(pivx.begin(), pivx.end(), vector<int>(1, pivy[i][inj]), cmpvec) - pivx.begin();
            int ini = lower_bound(pivx[j].begin() + 1, pivx[j].end(), pivy[i][inj]) - pivx[j].begin();
            lli xaxis = 0, yaxis = 0;
            yaxis = pivxs[j].back() * (pivx[j].size() - ini - 1) + pivxs[j][ini - 1] * (ini - 1) - pivx[j][ini] * (pivx[j].size() - 2 * ini);
            xaxis = pivys[i].back() * (pivy[i].size() - inj - 1) + pivys[i][inj - 1] * (inj - 1) - pivy[i][inj] * (pivy[i].size() - 2 * inj);
            
            yaxis %= MOD; xaxis %= MOD;
            ans = (ans + yaxis * xaxis % MOD) % MOD;
        }
    }
    
    ans = ans < 0 ? ans + MOD : ans;
    printf("%lld", ans);
    return 0;
}

bool cmpback(pair<int, int> a, pair<int, int> b)
{
    return a.second != b.second ? a.second < b.second : a.first < b.first;
}

void getpiv()
{
    sort(_C.begin(), _C.end());
    for (int i = 0; i < _N; i++)
    {
        if (pivx.empty()) pivx.push_back(vector<int>(1, _C[i].first));
        else if (pivx.back()[0] != _C[i].first) pivx.push_back(vector<int>(1, _C[i].first));
        pivx.back().push_back(_C[i].second);
    }
    
    sort(_C.begin(), _C.end(), cmpback);
    for (int i = 0; i < _N; i++)
    {
        if (pivy.empty()) pivy.push_back(vector<int>(1, _C[i].second));
        else if (pivy.back()[0] != _C[i].second) pivy.push_back(vector<int>(1, _C[i].second));
        pivy.back().push_back(_C[i].first);
    }

    pivxs = pivx;
    for (int i = 0; i < pivxs.size(); i++)
    {
        for (int j = 2; j < pivxs[i].size(); j++)
        {
            pivxs[i][j] = (pivxs[i][j - 1] + pivxs[i][j]) % MOD;
        }
    }

    pivys = pivy;
    for (int i = 0; i < pivys.size(); i++)
    {
        for (int j = 2; j < pivys[i].size(); j++)
        {
            pivys[i][j] = (pivys[i][j - 1] + pivys[i][j]) % MOD;
        }
    }
}