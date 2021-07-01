#include <iostream>
#include <vector>
#include <random>
using namespace std;

typedef vector<vector<bool>> grille;

double proba (int nbt, int n, double p);
void check(double p);
void stub(grille libre, grille& passage, int x, int y, int n);
void grillecontrol(grille& libre, int n);
void passagecontrol(grille& passage, int n);

int main() {
	cout << "abc, n, p, nbt" << endl;
	char abc;
	int n;
	cin >> abc >> n;
	if (abc=='a') {
		grille libre(n,vector<bool>(n,false));
		for (int i(0); i<n; i++) {
			for (int j(0); j<n; j++) {
				int k(0);
				cin >> k;
				if (k==0) {
					libre[i][j]=true;
				} else {
					libre[i][j]=false;
				}
			}
			cout << endl;
		}
		grillecontrol(libre, n);
		grille passage(n,vector<bool>(n,false));
		for (int i(0); i<n; i++) {
			stub (libre, passage, 0, i, n);	
		}
		passagecontrol(passage, n);
	}
	if (abc=='b') {
		double p;
		int nbt;
		cin >> p >> nbt;
		check(p);
		cout << proba(nbt, n, p);
	}
	if (abc=='c') {
		//ajouter echantillonage dichotomique
		int nbt;
		cin >> nbt;
		for (double p(0); p<=1; p+=1/double(nbt-2)) {
			cout << p << " " << proba(nbt, n, p) << endl ;
		}
	}
	
	return 0;
}
double proba (int nbt, int n, double p) {
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
			//grillecontrol(passage, n);
		}
		return (double(count)/nbt);
}

void check(double p) {
	if (p<0 or p>1) {
		exit(0); }
}
void stub(grille libre, grille& passage, int x, int y, int n) {
	if (libre[x][y]==true && passage[x][y]==false) {
		passage[x][y]=true;
		if (x>0) stub(libre, passage, x-1, y, n);
		if (x<n-1) stub( libre, passage, x+1, y, n);
		if (y>0) stub(libre, passage, x, y-1, n);
		if (y<n-1) stub (libre, passage, x,y+1, n);
	}
}

void grillecontrol(grille& libre, int n) {
	cout << "grille" << endl;
	for (int i(0); i<n; i++) {
		for (int j(0); j<n; j++) {
			if (libre[i][j]==true) {
				cout << "0";
			} else {
				cout << "1";
			}
		}
		cout << endl;
	}
}

void passagecontrol(grille& passage, int n) {
	cout << "passage" << endl;
	for (int i(0); i<n; i++) {
		for (int j(0); j<n; j++) {
			if (passage[i][j]==true) cout << "0";
			else cout << "1";
			
		}
		cout << endl;
	}
}
