#include <bits/stdc++.h>

using namespace std;

int _T;
int _N, _W;

class dpdatc
{
public:
	int dat[3];
	dpdatc() { memset(dat, 0, sizeof(dat)); }
	int& operator[](int index) { return dat[index]; }
};

vector<pair<int, int>> enemies;
int dp(int type);

int main(void)
{
	scanf("%d", &_T);

	while (_T--)
	{
		scanf("%d%d", &_N, &_W);
		
		enemies.assign(_N, { 0, 0 });
		for (int i = 0; i < _N; i++) scanf("%d", &enemies[i].first);
		for (int i = 0; i < _N; i++) scanf("%d", &enemies[i].second);

		int ans = dp(0);
		if (enemies[0].first + enemies[_N - 1].first <= _W) ans = min(ans, dp(1));
		if (enemies[0].second + enemies[_N - 1].second <= _W) ans = min(ans, dp(2));
		if (enemies[0].first + enemies[_N - 1].first <= _W && enemies[0].second + enemies[_N - 1].second <= _W) ans = min(ans, dp(3));

		printf("%d\n", ans);
	}

	return 0;
}

int dp(int type)
{
	vector<dpdatc> dpm(_N, dpdatc());

	dpm[0][0] = enemies[0].first + enemies[0].second <= _W ? 1 : 2;
	dpm[0][1] = dpm[0][2] = 1;

	if (type != 0) dpm[0][0] = 2;
	if (type == 1) dpm[0][2] = 2e7;
	if (type == 2) dpm[0][1] = 2e7;
	if (type == 3) dpm[0][1] = dpm[0][2] = 2e7;

	for (int i = 1; i < _N; i++)
	{
		dpm[i][0] = min(
			dpm[i - 1][1] + (enemies[i].first + enemies[i].second <= _W || enemies[i - 1].second + enemies[i].second <= _W ? 2 : 3),
			dpm[i - 1][2] + (enemies[i].first + enemies[i].second <= _W || enemies[i - 1].first + enemies[i].first <= _W ? 2 : 3)
		);
		dpm[i][0] = min(dpm[i][0], dpm[i - 1][0] + (enemies[i].first + enemies[i].second <= _W ? 1 : 2));
		if (i > 1 && enemies[i - 1].first + enemies[i].first <= _W && enemies[i - 1].second + enemies[i].second <= _W) dpm[i][0] = min(dpm[i][0], dpm[i - 2][0] + 2);
		dpm[i][1] = min(
			dpm[i - 1][1] + 2,
			dpm[i - 1][2] + (enemies[i - 1].first + enemies[i].first <= _W ? 1 : 2)
		);
		dpm[i][2] = min(dpm[i][1], dpm[i - 1][0] + 1);
		dpm[i][2] = min(
			dpm[i - 1][1] + (enemies[i - 1].second + enemies[i].second <= _W ? 1 : 2),
			dpm[i - 1][2] + 2
		);
		dpm[i][2] = min(dpm[i][2], dpm[i - 1][0] + 1);
	}

	if (type == 1) return dpm[_N - 1][2];
	if (type == 2) return dpm[_N - 1][1];
	if (type == 3) return dpm[_N - 2][0];
	return dpm[_N - 1][0];
}