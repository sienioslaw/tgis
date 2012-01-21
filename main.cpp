#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>


using namespace std;

# define MAX 100

int my_array[MAX][MAX];     	// Graf jako macierz incydencji

int n, m;						// n -liczba wierzcholkow, m - krawedzi
int paleta = 4; 				// cztery kolory, nie więcej!
vector<vector <int> > v;
vector<vector <int> > cykle;

enum VertexState { White, Gray, Black };
VertexState *odwiedzone = new VertexState[MAX];

string KOLORY[]= {"red","blue","green", "yellow"};


void DFS_visit(int u) {
	int i;
	odwiedzone[u] = Gray;
	
	
	//dla kazdego sasiada wierzcholka u
	for(i=1; i< v[u].size(); i++) {
		if(odwiedzone[v[u][i]] == Gray && cykle[u][i-1] != i) {
			cout << "Istnieje cykl!"<<endl;
			return;
		}
		if(odwiedzone[v[u][i]] == White) {
				cykle[u].push_back(u);
				DFS_visit(v[u][i]);
		}
		
	}	
	odwiedzone[u] = Black;
}

void DFS_cycle() {
	int i;
	for(i=0; i< n; i++) {
		odwiedzone[i] = White;
		cykle[i].empty();
	}

	for(i=0; i< n;i++) {
		if (odwiedzone[i] == White) {
           // DFS_visit(i);
		}
	}
	
}

void Znajdz_cykle(int startingNode, int currentNode, int originNode, vector<int> visitedNodes) {

	vector <int> cycles; 
	
	visitedNodes.push_back(currentNode);
   //v[currentNode]
    
    
    for(i=1; i < v[currentNode].size(); i++) { 
   	if (i == originNode) {
			continue;
		}
        if (i == startingNode) {
                    // mamy cykl
                    vector <int> cykl;
                    
                    for(int cycleNode=0; i< visitedNodes.size();cycleNode++) {
                       ;
                        cykl.push_back(cycleNode);
                    }
                    cycle.push_back(startingNode);

					//tutaj dodaje cykl
                }
                else {
                    // szukamy dalej
                
                }
            }


	//return cykle;
}

void find_cycles() {

	int i,j;
	VertexState *odwiedzone = new VertexState[n];

	for(i=0;i<n; i++) {
		//bierzemy pierwszy wierzchołek
		//tworzymy liste i wrzucamy pierwszy wierzcholek?
		v.push_back ( vector<int>() );
		v[i].push_back(i);

		for(j=0; j<n; j++) {
			//szukamy wszystkie polaczenia odchodzace od niego i wrzucamy na liste
			if(my_array[j][i] == 1)
			{
				v[i].push_back(j);
			} 
		}		
	}
	
	//just 4info
	for(i=0; i<n; i++) {
		cout<< "wierzcholek " << v[i][0] << ": ";
		for(j=1; j < v[i].size(); j++) {
			cout << v[i][j] << ' ';
		}
		cout << endl;
	}


	vector <int> cykl;

	/*teraz przejdziemy po strukturze szukajac najmniejszych cykli
	for(i=0; i<n; i++) {
		//teraz mamy informacje o wierzchalkach graniczacych z aktualnym wierzcholkiem 'i'
		cykl.push_back(v[i][0]);
		
		for(j=0; j < v[i].size(); j++) { 
				//musimy przejsc po grafie i znalezc wszystkie cykle
				//zaczynajace i konczace sie na wierzholku 'i'
				//potem musimy przefiltrowac?
				
				//jezeli sasiedzi nie odwiedzeni - idz tam
				
		
		
		}
	}
	*/

}

void Backtrace_coloring(int i) {	
	int kolor = 0;
	int a, m;
	
	if(i == n) {
		for(m=0; m < n; m++) {
			//printf("\nWierchołek %d ma kolor (%d) i sasiaduje z ",m+1, my_array[m][m]+1);
			
			for(a = 0; a < n; a++) {
				if(my_array[m][a] !=0 && a != m) {
				//	printf("%d(%d) ", a+1, my_array[a][a]+1);
				}
			}
		}
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
		
		}
		file << "\n";
		
	}
	
	file << "}\n";
	file.close();
}

int main(int argc, char *argv[]) {
	wczytaj_macierz(argv[1]);
	//print_array();
	find_cycles();
	//Backtrace_coloring(0);
	//print_array();
	//wygeneruj_graf();	
	
	
	cout << endl;
	return 0;
}
