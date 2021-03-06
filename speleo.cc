#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

typedef vector<vector<bool>> grille;

double proba (int nbt, int n, double p);
void cin_grilleA (grille& libre, int n);
void check(double p);
void stub(grille& libre, grille& passage, int x, int y, int n);
void cout_grille(grille& libre, int n);
void c_t(vector<vector<double>>& probtab);
bool c(const vector<double>& v1, const vector<double>& v2);

int main() {
	char abc;
	int n;
	cin >> abc >> n;
	if (abc=='a') {
		grille libre(n,vector<bool>(n,false));
		cin_grilleA (libre, n);
		grille passage(n,vector<bool>(n,false));
		for (int i(0); i<n; i++) {
			stub (libre, passage, 0, i, n);	
		}
		cout_grille(passage, n);
	}
	
	if (abc=='b') {
		double p;
		int nbt;
		cin >> p >> nbt;
		check(p);
		cout << fixed << setprecision(6) << proba(nbt, n, p);
	}
	
	if (abc=='c') {
		int nbt(0);
		cin >> nbt;
		double m(0), M(1), r(1), b(0.5);
		const double D(0.000001), E(0.01);
		vector<vector<double>> t(1, vector<double>(2,0));
		while (M-m>D && abs(r)>E) {
			b=(m+M)/2;
			double p = proba(nbt, n, b);
			vector<double> a{b,p};
			r=p-b;
			if (r>0) {
				M=b;
			} else {
				m=b;
			}
			t.push_back(a);
		}
		sort(t.begin(), t.end(), c);
		c_t(t);
	}
	
	if (abc=='d') {
		int nbt;
		cin >> nbt;
		vector<vector<double>> t(1, vector<double>(2,0));
		for (double p(0); p<1; p+=1/double(nbt-2)) {
			cout << p << " " << proba(nbt, n, p) << endl;
		}
		c_t(t);
	}
	return 0;
}

void cin_grilleA(grille& libre, int n) {
	for (int i(0); i<n; i++) {
		for (int j(0); j<n; j++) {
			int k(0);
			cin >> k;
			libre[i][j]=(k==0)?true:false;
		}
	}
}

double proba(int nbt, int n, double p) {
	int count(0);
	default_random_engine e;
	bernoulli_distribution b(p);
	for (int i=0; i<nbt; i++) {
			grille libre(n,vector<bool>(n,false));
			for (int j(0); j<n; j++) {
				for (int z(0); z<n; z++) {
					libre[j][z]=b(e);
				}
			}
			grille passage(n,vector<bool>(n,false));
			for (int i(0); i<n; i++) {
				stub (libre, passage, 0, i, n);	
			}
			for (int i(0); i<n; i++) {
				if (passage[n-1][i]==true) {
					count++;
					break;
				}
			}
			//cout_grille(passage, n); //test
		}
		return (double(count)/nbt);
}

void check(double p) {
	if (p<0 or p>1) exit(0);
}

void stub(grille& libre, grille& passage, int x, int y, int n) {
	if (libre[x][y]==true && passage[x][y]==false) {
		passage[x][y]=true;
		if (x>0) stub(libre, passage, x-1, y, n);
		if (x<n-1) stub( libre, passage, x+1, y, n);
		if (y>0) stub(libre, passage, x, y-1, n);
		if (y<n-1) stub (libre, passage, x,y+1, n);
	}
}

bool c(const vector<double>& v1, const vector<double>& v2) {
	return v1[0] < v2[0];
}

void cout_grille(grille& grille1, int n) {
	cout << "P1" << endl << n << " " << n << endl;
	for (int i(0); i<n; i++) {
		for (int j(0); j<n; j++) {
			if (grille1[i][j]==true) cout << "0";
			else cout << "1";
			cout << " ";
		}
		cout << endl;
	}
}

void c_t(vector<vector<double>>& probtab) {
	//cout << endl << "p | p'" << endl; //test
	for(long unsigned int i(0); i<probtab.size();i++) {
		cout << fixed << setprecision(6) << probtab[i][0] << " " << probtab[i][1] << endl;
	}
}
