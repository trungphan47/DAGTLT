#include<iostream>
#include<math.h>
#include<iomanip>
#include<fstream>
using namespace std;
float a[100][100];
float z[100][100];
float m[100][100];
void output1(int c, int h,float p[100][100]) {
	fstream f;
	f.open("OUTPUT.TXT", ios::out);
	f << " Ma tran sau khi du doan cac rating con thieu" << endl << endl ;
	f << "      ";
	for (int i = 0; i < c; i++) {
		f << setw(5) << "u" << i;
	}
	f << endl << "         " << "-------------------------------------" << endl << endl;
	for (int i = 0; i < h; i++) {
		f << setw(2) << "i" << i << " |  ";
		for (int j = 0; j < c; j++) {
			f << setw(6) << p[i][j];
		}
		f << endl;
	}
	f.close();

}
void input(int c, int h, float e[100][100]) {


	for (int i = 0; i < h; i++) {
		for (int j = 0; j < c; j++) {
			cout << "z[" << i << "][" << j << "]=";
			cin >> e[i][j];
		}
	}
}
void output(int c, int h, float e[100][100]) {
	cout << "      ";
	for (int i = 0; i < c; i++) {
		cout << setw(5) <<"u" <<i;
	}
	cout << endl << "         " << "-------------------------------------" << endl << endl;
	for (int i = 0; i < h; i++) {
		cout << setw(2) << "i"<<i << " |  ";
		for (int j = 0; j < c; j++) {
			cout << setw(6) << e[i][j];
		}
		cout << endl;
	}
}
float arr[100];
void TimTrungBinh(int c, int h) {
	int u = 0;
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < h; j++) {
			if (z[j][i] != -1) {
				arr[i] += z[j][i];
				u++;
			}
		}
		arr[i] = floorf(arr[i] / u * 100) / 100;
		u = 0;
	}
	cout << "Mang cac gia tri trung binh : " << endl;
	cout << "      ";
	for (int i = 0; i < c; i++) {
		cout << setw(6) << arr[i];
	}
	cout << endl;
}
float tinhCos(int n, float x[], float y[]) {

	float sum = 0;
	float Can1 = 0;
	float Can2 = 0;

	for (int i = 0; i < n; i++) {
		sum += x[i] * y[i];
		Can1 += x[i] * x[i];
		Can2 += y[i] * y[i];

	}
	return floorf(sum / (sqrt(Can1)*sqrt(Can2)) * 100) / 100;
}

void matrancos(int n) {
	float x[100], y[100];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				x[k] = a[k][j];
				y[k] = a[k][i];
			}
			m[i][j] = tinhCos(n, x, y);
		}
	}
	cout << endl;
	cout << "Ma tran User similarity " << endl;
	output(n, n, m);
}
void TimMaTranTrungBinh(int c, int h) {
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < h; j++) {
			if (z[j][i] != -1) {
				a[j][i] = z[j][i] - arr[i];
			}
			else {
				a[j][i] = 0;
			}

		}
	}
	cout << endl;
	cout << "Ma Tran da chuan hoa : " << endl;
	output(c, h, a);
}

void duDoanConThieu(int c, int h) {

	int max1 = -998, max2 = -999;
	int vt1 = 0;
	int vt2 = 0;
	float l[100][100];
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < c; j++) {
			l[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < c; j++) {
			if (a[i][j] == 0) {
				for (int k = 0; k < c; k++) {
					if (m[j][k] != 1 && a[i][k] != 0) {
						vt1 = k;
						break;
					}
				}
				for (int k = 0; k < c; k++) {
					if (m[j][k] != 1 && a[i][k] != 0 && vt1 != k) {
						if (m[j][k] > m[j][vt1]) {
							vt1 = k;
						}
					}
				}
				for (int k = 0; k < c; k++) {
					if (m[j][k] != 1 && a[i][k] != 0 && vt1 != k) {
						vt2 = k;
						break;
					}
				}
				for (int k = 0; k < c; k++) {
					if (m[j][k] != 1 && a[i][k] != 0 && k != vt2 && vt1 != k) {
						if ((m[j][vt1] - m[j][k]) < (m[j][vt1] - m[j][vt2])) {
							vt2 = k;
						}
					}

				}

				cout << vt1 << "  " << vt2 << endl;
				l[i][j] = floorf((m[j][vt1] * a[i][vt1] + m[j][vt2] * a[i][vt2]) / (abs(m[j][vt1]) + abs(m[j][vt2])) * 100) / 100;
				z[i][j] = l[i][j] + arr[j];
				vt1 = 0;
				vt2 = 0;
			}
		}
	}
	cout << endl;
	cout << "Ma tran du doan cac ratings con thieu  (normalized) :" << endl;
	output(c, h, l);
	cout << endl;
	cout << "Ma tran du doan cac ratings con thieu  (denormalized) :" << endl;
	output(c, h, z);
	output1(c, h,z);
}



int main() {

	int c, h;
	cout << "Nhap so hang:";
	cin >> h;
	cout << "Nhap so cot:";
	cin >> c;
	cout << "nhap ma tran:" << endl;
	input(c, h, z);
	cout << "Ma Tran vua Nhap : " << endl;
	output(c, h, z);
	cout << endl << endl;
	TimTrungBinh(c, h);
	TimMaTranTrungBinh(c, h);
	matrancos(c);
	cout << endl;
	duDoanConThieu(c, h);
	system("pause");
	return 0;
}