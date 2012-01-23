#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <vector>

# define MAX 100

using namespace std;

int my_array[MAX][MAX];     	// Graf jako macierz incydencji
int nowy[MAX][MAX];     		// Graf jako macierz incydencji


int n, m;						// n -liczba wierzcholkow, m - krawedzi
int paleta = 4; 				// cztery kolory, nie więcej!
vector<vector <int> > sasiedzi;
vector<vector <int> > cykle;

enum VertexState { White, Gray, Black };
VertexState *odwiedzone = new VertexState[MAX];

string KOLORY[]= {"black","red","blue","green", "yellow"};

bool sprawdz_polaczenie(vector <int> x, vector <int> y) {
	int i,j;
	for(i=0; i < x.size();i++) {
		for(j=0; j < y.size(); j++) {
			if(x[i] == y[j])
				return true;
		}
	}
		
}

void znajdz(int v, int poczatkowy) {

	cykle[v].push_back(v);
	
	for(int i=1; i< sasiedzi[v].size()-1; i++) {
		if(sprawdz_polaczenie(sasiedzi[sasiedzi[v][i]], sasiedzi[sasiedzi[v][i+1]])){
			cykle[v].push_back(sasiedzi[v][i]);
			cykle[v].push_back(sasiedzi[v][i+1]);	
		}
	}

}

void find_cycles() {

	int i,j;
	VertexState *odwiedzone = new VertexState[n];

	for(i=0;i<n; i++) {
		//bierzemy pierwszy wierzchołek
		//tworzymy liste i wrzucamy pierwszy wierzcholek?
		sasiedzi.push_back ( vector<int>() );
		//v[i].push_back(i);

		for(j=0; j<n; j++) {
			//szukamy wszystkie polaczenia odchodzace od niego i wrzucamy na liste
			if(my_array[j][i] == 1)
			{
				sasiedzi[i].push_back(j);
			} 
		}		
	}
	
	//just 4info
	for(i=0; i<n; i++) {
		cout<< "wierzcholek " << i << ": ";
		for(j=0; j < sasiedzi[i].size(); j++) {
			cout << sasiedzi[i][j] << ' ';
		}
		cout << endl;
	}

	//teraz przejdziemy po strukturze szukajac najmniejszych cykli
	for(i=0; i<n; i++) {
		cykle.push_back ( vector<int>() );
		znajdz(i,0);
	}
	
	for(i=0; i < n; i++) {
		cout<< "cykl" << i <<": ";
		for(j=0; j< cykle[i].size(); j++) {
			cout << cykle[i][j]<< " ";
		}
		cout <<endl;
	}
	
}

void Backtrace_coloring(int i) {	
	int kolor = 0;
	int a, m;
	
	if(i == n) {
		for(m=0; m < n; m++) {
			cout <<"\nWierzcholek "<< m <<" ma kolor " << my_array[m][m] << ", i sasiaduje z: ";   
			//cout <<"\nWierzcholek "<< m+1 <<" ma kolor " << KOLORY[(nowy[m][m]+1)] << ", i sasiaduje z: ";   
			
			for(a = 0; a < n; a++) {
				if(my_array[m][a] !=0 && a != m) {
					cout << a << "(" << my_array[a][a]<<"), ";
				}
							
			}			
		}
		cout<<endl;
	}
	while(kolor < paleta && i < n) {
		for(m=0; m < i; m++) {
			if(my_array[i][m]!= 0 && i != m && my_array[m][m] == kolor) {
				kolor++;
                m--;
                continue;
			}
		}
		if(kolor < paleta) {
			my_array[i][i] = kolor; 
			Backtrace_coloring(i+1);
		}             
		kolor++;
	}
} 

void wczytaj_macierz(char *filename) {
	int row, col;
	string line;

	ifstream file (filename);
	
	getline(file, line);
	stringstream ss(line);
	ss >> n >> m;
	
	if(file.is_open()) {
		row = 0;		
		while(file.good()) {
			getline (file,line);
			stringstream ss(line);
			
			col=0;
			
			while(ss >> my_array[row][col]) {
				col++;
			}
			row++;		
		}
		file.close();
	}
}

void print_array() {
	int i, j;
	cout << n << " " << m <<endl;
	cout<<endl;
	
	for(i=0; i<n; i++) {
		for(j=0;j<n;j++) {
			cout << my_array[i][j];
			
		}
		cout << endl;
	}
}

void wygeneruj_graf() {
	ofstream file("graf.dot");
	file << "Graph {\n";
	
	for(int i=0; i<n; i++) {
		file << "vertex" << i << " [style=filled, color="<< KOLORY[my_array[i][i]]<<"]\n";		
	}
	
	//teraz relacje?
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(my_array[i][j] !=0 && j != i) {
				file << "vertex" << i << " -- " << "vertex" << j << "\n";
			}
				my_array[j][i] = 0;
		}	
		file << "\n";
		
	}
	
	file << "}\n";
	file.close();
	
	cout<< "wygenerowalem graf!\n";
	
}

void zrob_wierzcholki() {
	int i, j, k, l, m;
	int edge = 0;
	
	
	cykle.push_back ( vector<int>() );
	cykle.push_back ( vector<int>() );
	cykle.push_back ( vector<int>() );
	cykle.push_back ( vector<int>() );
	
	
	cykle[0].push_back(0);
	cykle[0].push_back(1);
	cykle[0].push_back(3);
	cykle[0].push_back(4);
	
	
	cykle[1].push_back(1);
	cykle[1].push_back(2);
	cykle[1].push_back(3);
	
	
	cykle[2].push_back(2);
	cykle[2].push_back(3);
	cykle[2].push_back(4);
	cykle[2].push_back(5);
	cykle[2].push_back(6);
	
	cykle[3].push_back(1);
	cykle[3].push_back(2);
	cykle[3].push_back(7);
	cykle[3].push_back(8);
	
	
		
	int nowy[cykle.size()][cykle.size()];
	
	
	for(i=0; i<cykle.size(); i++) {
		for(j=0; j<cykle.size(); j++){
			//nowy[i][j]=0;
			my_array[i][j]=0;
		}
		
	}
	
	for(i=0; i<cykle.size(); i++) {
		cout<<"cykl " << i<< ": ";
		for(j=0; j<cykle[i].size(); j++){
			cout<< cykle[i][j]<<" ";
		}
		cout<<endl;
	}
	
	int poloczone[cykle.size()][cykle.size()];	
	int ilosc_cykli = cykle.size();
	
	//liczymy wspolne wierzcholki
	for(i=0; i < ilosc_cykli; i++) {
		vector <int> tmp = cykle[i];

		for(k=0; k< ilosc_cykli; k++) {
			
			
			for(j=0; j < tmp.size();j++) { 		
				for(m=0; m < cykle[k].size(); m++) {
					if(tmp != cykle[k]) {
						if(tmp[j] == cykle[k][m]) {
							edge++;
							//poloczone[k][m]
							/*cout <<"przebieg i:" << i << ", akutalny mielony cykl:" << k 
							//<<", "<<" tmp: " << tmp[j] << " z " << cykle[k][m] << endl; 
							//cout<< tmp[j] <<" i "<<cykle[k][m]<<" rowne\n";
							*/
						}
					}
					
				}
				
			}
			//sprawdzilismy obie tablice
			if(edge > 1) {
				//napewno miedzy 2 cyklami istnieje wspolna krawedz!
				//nowy[k][i] = 1;
				my_array[k][i] = 1;					
			}
			edge=0;
			
		}
		cout<<endl;
		edge=0;
		
	}
	
	cout<< "Wygenerowalem macierz sasiedztwa!\n"<<endl;
	for(i=0; i < cykle.size(); i++) {
		for(j=0; j<cykle.size(); j++){
			//cout<< nowy[i][j] << ' ';
			cout<< my_array[i][j] << ' ';
		
		}
		cout<<endl;
	}
	
	n = cykle.size();
	
	//teraz go pokoloruj i wygeneruj graf graphviza
	print_array();
	Backtrace_coloring(0);
	print_array();
	wygeneruj_graf();
}

int main(int argc, char *argv[]) {
	wczytaj_macierz(argv[1]);
	//print_array();
	//find_cycles();
	
	Backtrace_coloring(0);
	print_array();
	wygeneruj_graf();	
	
	//zalozmy ze mamy juz cykle zapisane w wektorze...
	//zrob_wierzcholki();
	
	cout << endl;
	return 0;
}
