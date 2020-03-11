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

int main(void)
{
	scanf("%d", &_T);

	while (_T--)
	{
		scanf("%d%d", &_N, &_W);
		vector<pair<int, int>> enemies(_N, { 0, 0 });
		vector<dpdatc> dpm(_N, dpdatc());
		
		enemies.assign(_N, { 0, 0 });
		for (int i = 0; i < _N * 2; i++) scanf("%d", &dpm[i / _N][i % 2]);

		dpm[0][0] = enemies[0].first + enemies[0].second <= _W ? 1 : 2;
		dpm[0][1] = 1;
		dpm[0][2] = 1;

		for (int i = 1; i < _N; i++)
		{
			dpm[i][0] = min(
				dpm[i - 1][1] + (enemies[i].first + enemies[i].second <= _W || enemies[i - 1].second + enemies[i].second <= _W ? 1 : 2),
				dpm[i - 1][2] + (enemies[i].first + enemies[i].second <= _W || enemies[i - 1].first + enemies[i].first <= _W ? 1 : 2)
			);
			dpm[i][0] = min(dpm[i][0], dpm[i - 1][0] + (enemies[i].first + enemies[i].second <= _W ? 1 : 2));
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

		for (int i = 0; i < _N; i++)
		{
			for (int j = 0; j < 3; j++) printf("%d ", dpm[i][j]);
			printf("\n");
		}

		int ans = dpm[_N - 1][0];
		ans = min(ans, dpm[_N - 2][0] + 4 - int(enemies[0].first + enemies[_N - 1].first <= _W) - int(enemies[0].second + enemies[_N - 1].second <= _W));
		ans = min(ans, dpm[_N - 2][1] + 3 - int(enemies[0].second + enemies[_N - 1].second <= _W));
		ans = min(ans, dpm[_N - 2][2] + 3 - int(enemies[0].first + enemies[_N - 1].first <= _W));

		printf("%d\n", ans);
	}

	return 0;
}