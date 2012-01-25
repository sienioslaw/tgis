/*	Marcin Sienkiewicz
 *  nr. indeksu 186475
 *  Kolorowanie map, na podstawie algorytmu ze strony 
 *  http://www.authorstream.com/Presentation/ankush85-159098-backtracking-126-134-education-ppt-powerpoint/
 *  strony 48-58
 */ 
#include "header.h" 

//zmienne globalne
int my_array[MAX][MAX];     		// Graf jako macierz incydencji
vector <int> X;						// tymczasowy wektor do zapisu informacji o kolorach

int n;								// n -liczba wierzcholkow
int paleta = 4; 					// cztery kolory, nie więcej!

string KOLORY[]= {"black","red","blue","green", "yellow"};

void wyswietl_info(){
	int a, m;
	for(m=0; m < n; m++) {
			cout <<"\nWierzcholek "<< m <<" ma kolor " << KOLORY[my_array[m][m]] << ", i sasiaduje z: ";   
			
			for(a = 0; a < n; a++) {
				if(my_array[m][a] !=0 && a != m) {
					cout << a << "(" << KOLORY[my_array[a][a]]<<"), ";
				}
							
			}			
		}
		cout<<endl;
}

void NextValue(int k) {
	int j;
	
	do {	
	X[k] = (X[k]+1) % (paleta+1);	//nastepny kolor
	if(X[k] == 0) {
		return;						//wszystkie kolory zostaly wykorzystane...
	}
	
	for(j=0; j < n; j++) {	
		if((my_array[k][j] != 0) && (X[k] == X[j])){
			break;
		}
	}
	
	if(j == n)
		return;
	
	}while(!0);
	
}

void Mcoloring(int k) {
	int i;
	
	do
	{
		NextValue(k);	//przypisz wierzcholkowi kolor
		if(X[k] == 0) {
			return;		//brak kolorow
		}
		
		
		if(k == n-1) {			
			for(i=0; i < n; i++) {
				my_array[i][i] = X[i];
			}
			wyswietl_info();
		}
		else {
			Mcoloring(k+1);
		}
		
		} while(!0);
}

void wczytaj_macierz(char *filename) {
	int row, col;
	string line;

	ifstream file (filename);
	
	getline(file, line);
	stringstream ss(line);
	ss >> n;
	
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
	
	for(int i=0; i < n; i++) {
		X.push_back(0);
	}
	
}

void print_array() {
	int i, j;
	cout << "wierzcholkow: " << n <<endl;
	cout << "macierz:"<<endl;
	for(i=0; i<n; i++) {
		for(j=0;j<n;j++) {
			cout << my_array[i][j];
			
		}
		cout << endl;
	}
	cout<<endl;
}

void wygeneruj_graf() {
	ofstream file("graf.dot");
	file << "Graph {\n";
	
	for(int i=0; i<n; i++) {
		file << "vertex" << i+1 << " [style=filled, color="<< KOLORY[my_array[i][i]]<<"]\n";		
	}
	
	//teraz relacje?
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(my_array[i][j] !=0 && j != i) {
				file << "vertex" << i+1 << " -- " << "vertex" << j << "\n";
			}
				my_array[j][i] = 0;
		}	
		file << "\n";
		
	}
	
	file << "}\n";
	file.close();
	
	cout<< "wygenerowalem graf!\n";
	
}

int main(int argc, char *argv[]) {
	wczytaj_macierz(argv[1]);

	Mcoloring(0);
	print_array();

	wygeneruj_graf();	
			
	cout << endl;
	return 0;
}
