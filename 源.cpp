#include<iostream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
int chessmap[10][10];
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
class boss {
private:
	int HP;
public:
	boss() {
		HP = 5000;
	}
};
class player {
private:
	int HP;
	int power;
public:
	player() {
		HP = 1000;
		power = 0;
	}
};
void initialize() {
	for (int i = 1; i <= 7; ++i) {
		for (int j = 1; j <= 8; ++j) {
			chessmap[i][j] = rand() % 4 + 1;
		}
	}
	return;
}
void show() {
	system("cls");
	cout << "  ";
	for (int i = 1; i <= 8; ++i) {
		cout << i << " ";
	}
	cout << endl;
	for (int i = 1; i <= 7; ++i) {
		cout << i << " ";
		for (int j = 1; j <= 8; ++j) {
			cout << chessmap[i][j] << " ";
		}
		cout << endl;
	}
	return;
}
void change(int x1, int y1, int x2, int y2) {
	int temp = chessmap[x1][y1];
	chessmap[x1][y1] = chessmap[x2][y2];
	chessmap[x2][y2] = temp;
	return;
}
bool check() {
	for (int i = 1; i <= 7; ++i) {
		for (int j = 1; j <= 8; ++j) {
			if (i <= 5 && chessmap[i][j] % 5 == chessmap[i + 1][j] % 5 && chessmap[i + 1][j] % 5 == chessmap[i + 2][j] % 5) return true;
			if (j <= 6 && chessmap[i][j] % 5 == chessmap[i][j + 1] % 5 && chessmap[i][j + 1] % 5 == chessmap[i][j + 2] % 5) return true;
		}
	}
	return false;
}
// 1-4对应的基础宝石 5对应s宝石 6-9对应的效果宝石
void update() {
	bool flag = false;
	for (int i = 1; i <= 7; ++i) {
		if (flag) break;
		for (int j = 1; j <= 8; ++j) {
			if (i <= 5 && chessmap[i][j] % 5 == chessmap[i + 1][j] % 5 && chessmap[i + 1][j] % 5 == chessmap[i + 2][j] % 5) {
				int temp = chessmap[i][j];
				int cnt = 0;
				int mem = 0;
				bool _4 = false;
				for (int k = i; chessmap[k][j] % 5 == temp % 5 && k <= 7; ++k) {
					cnt++;
					chessmap[k][j] = 0;
					int sum = 0;
					for (int l = j - 1; l >= 1 && chessmap[k][l] % 5 == temp % 5; --l) sum++;
					for (int l = j + 1; l <= 7 && chessmap[k][l] % 5 == temp % 5; ++l) sum++;
					if (sum >= 2) {
						mem = k;
						if (sum == 3) _4 = true;
						for (int l = j - 1; l >= 1 && chessmap[k][l] % 5 == temp % 5; --l) chessmap[k][l] = 0;
						for (int l = j + 1; l <= 7 && chessmap[k][l] % 5 == temp % 5; ++l) chessmap[k][l] = 0;
					}
				}
				if (cnt == 3) {
					if (_4) {
						chessmap[mem][j] = 5;
					}
					if (!_4 && mem != 0) chessmap[mem][j] = temp + 5;
				}
				if (cnt == 4) {
					if (mem == 0) chessmap[i][j] = temp + 5;
					else {
						chessmap[mem][j] = 5;
					}
				}
				else if (cnt == 5) {
					chessmap[i + 2][j] = 5;
				}
				flag = true;
				break;
			}
			else if (j <= 6 && chessmap[i][j] % 5 == chessmap[i][j + 1] % 5 && chessmap[i][j + 1] % 5 == chessmap[i][j + 2] % 5) {
				int temp = chessmap[i][j];
				int cnt = 0;
				int mem = 0;
				bool _4 = false;
				for (int k = j; k <= 8 && chessmap[i][k] % 5 == temp % 5; ++k) {
					cnt++;
					chessmap[i][k] = 0;
					int sum = 0;
					for (int l = i - 1; l >= 1 && chessmap[l][k] % 5 == temp % 5; --l) sum++;
					for (int l = i + 1; l <= 8 && chessmap[l][k] % 5 == temp % 5; ++l) sum++;
					if (sum >= 2) {
						mem = j;
						if (sum == 3) _4 = true;
						for (int l = i - 1; l >= 1 && chessmap[l][k] % 5 == temp % 5; --l) chessmap[l][k] = 0;
						for (int l = i + 1; l <= 8 && chessmap[l][k] % 5 == temp % 5; ++l) chessmap[l][k] = 0;
					}
				}
				if (cnt == 3) {
					if (!_4 && mem != 0) {
						chessmap[i][mem] = temp + 5;
					}
				}
				else if (cnt == 4) {
					if (mem != 0) chessmap[i][mem] = 5;
					else chessmap[i][j + 1] = temp + 5;
				}
				else if (cnt == 5) {
					chessmap[i][j + 2] = 5;
				}
				flag = true;
				break;
			}
		}
	}
	for (int j = 1; j <= 8; ++j) {
		for (int i = 7; i >= 1; --i) {
			if (chessmap[i][j] == 0) {
				int k = i - 1;
				while (chessmap[k][j] == 0) {
					k--;
					if (k == 0) break;
				}
				if (k >= 1) {
					chessmap[i][j] = chessmap[k][j];
					chessmap[k][j] = 0;
				}
			}
		}
		int flag = 7;
		while (chessmap[flag][j] != 0) {
			flag--;
			if (flag == 0) break;
		}		
		for (int i = flag; i >= 1; --i) {
			chessmap[i][j] = rand() % 4 + 1;
		}
	}
	return;
}
int main() {
	srand(time(0));
	do {
		initialize();
	} while (check());
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; ++j) {
			cout << dir[i][j];
		}
	}
	int x1, y1, x2, y2;
	while (1) {
		show();
		cout << "输入要操作的宝石：";
		cin >> x1 >> y1;
		while (1) {
			cout << "再输入第二个要操作的宝石：";
			cin >> x2 >> y2;
			if (abs(x1 - x2) + abs(y1 - y2) != 1) {
				cout << "输入有误" << endl;
				continue;
			}
			change(x1, y1, x2, y2);
			if (!check()) {
				cout << "无法操作" << endl;
				change(x2, y2, x1, y1);
				continue;
			}
			else break;
		}
		update();
		show();
		system("pause");
		while (check()) {
			update();
			show();
			system("pause");
		}
	}
	return 0;
}