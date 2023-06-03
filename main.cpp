#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "SparseMatrix.h"
using namespace std;

SparseMatrix* readSparseMatrix(string arquivo){
	ifstream fin;
	fin.open("./Matrizes/" + arquivo);
	if (fin.is_open()){
		int m, n;
		fin >> m;
		fin >> n;
		cout << "Matriz: " << m << "x" << n << endl;
		SparseMatrix* nova = new SparseMatrix(m, n);
		while (fin.good()){
			int i, j;
			double val;
			fin >> i;
			fin >> j;
			fin >> val;
			nova->insert(i, j, val);
		}
		cout << "Matriz alocada com sucesso ☑" << endl;
		return nova;
	}else{
		cout << "arquivo " << arquivo << " não encontrado"<< endl;
		return nullptr;
	}
}

void exportSparseMatrix(SparseMatrix* ptr, string arquivo){
	ofstream fout;
	int m, n;
	m = ptr->getLinhas();
	n = ptr->getColunas();
	fout.open("./Matrizes/" + arquivo);
	fout << m << " " << n << endl;

	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			double valor = ptr->get(i, j);
			if (valor != 0){
				fout << i << " " << j << " " << valor << endl;
			}
		}
	}
}

/*
** Recebe duas matrizes esparsas e retorna outra matriz correspondente a soma.
** Caso o numero de linhas e colunas de ambas as matrizes nao forem iguais, lanca
** uma excessao. 
*/
SparseMatrix* sum(SparseMatrix* A, SparseMatrix* B) {
	if ((A->getLinhas() == B->getLinhas()) && (A->getColunas() == B->getColunas())){

		int nLinhas = A->getLinhas(), nColunas = B->getColunas();

		SparseMatrix* AB = new SparseMatrix(nLinhas, nColunas);
		for (int i = 1; i <= nLinhas; i++) {
			for (int j = 1; j <= nColunas; j++) {
				double value = A->get(i, j) + B->get(i, j);
				AB->insert(i, j, value);
			}
		}
		return AB;
	} else{
		throw out_of_range("Numero de linhas e colunas diferentes");
	}
}


/*
** Recebe duas matrizes esparsas e retorna outra matriz correspondente a multiplicação das matrizes.
** Caso o numero de colunas da primeira matriz não for igual ao número de linhas da primeira, lança
** uma exceção 
*/
SparseMatrix *multiply(SparseMatrix *A, SparseMatrix *B) {
	if (A->getColunas() == B->getLinhas()) {
		int nLinhas = A->getLinhas(), nColunas = B->getColunas();
		SparseMatrix* AB = new SparseMatrix(nLinhas, nColunas);

		for(int i = 1; i <= nLinhas; i++) {
			for (int j = 1; j <= nColunas; j++){
			    double value = 0;
				for(int x = 1; x <= A->getColunas(); x++) {
					value += A->get(i, x) * B->get(x, j);
				}
				AB->insert(i, j, value);
			}
		}
		return AB;
	} else{
		throw out_of_range("Numero de colunas da primeira matriz nao corresponde com o numero de linhas da segunda");
	}
}

int main() {
	system("chcp 65001 > nul");
	vector<SparseMatrix*> matrizes;
	
	while(true) {
		cout << "──────────────────────────" << endl;
		cout << "-> ";
		string input, command;
		getline(cin, input);
		stringstream ss{ input };
        ss >> command;

        cout << "➥  " << ss.str() << endl;

		if(command == "exit") {
			for(size_t i = 0; i < matrizes.size(); i++)
				delete matrizes[i];
			matrizes.clear();
			break;
		}
		else if(command == "create") {
            int m, n;
            ss >> m >> n;
			SparseMatrix *mat = new SparseMatrix(m, n);
			matrizes.push_back(mat);
		}else if(command == "testConstrutor"){
			int l;
			ss >> l;
			matrizes[l]->testConstructor();
			
		}else if(command == "print"){
			int l;
			ss >> l;
			matrizes[l]->print();
			//insert 0 2 3 10
		}else if(command == "printAll"){
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			for (size_t i = 0; i < matrizes.size(); i++){
				cout << "Matriz " << i << endl;
				matrizes[i]->print();
				if (i + 1 != matrizes.size()){
					cout << "--------------------------" << endl;
				}
			}
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		}else if(command == "insert"){
			int index, i, j;
			double val;
            ss >> index >> i >> j;
			ss >> fixed >> setprecision(2) >> val;
			matrizes[index]->insert(i, j, val);
		}else if(command == "clear"){
			int index;
            ss >> index;
			matrizes[index]->clear();
		}else if(command == "get"){
			int index, i, j;
            ss >> index >> i >> j;
			cout << fixed << setprecision(2) << matrizes[index]->get(i, j) << endl;
		}else if(command == "popular"){
			int m;
			ss >> m;
			matrizes[m]->popularMatriz();
		}else if(command == "createFrom"){
			string arquivo;
			ss >> arquivo;
			SparseMatrix* ptr = readSparseMatrix(arquivo);
			if (ptr != nullptr){
				matrizes.push_back(ptr);
			}
		}else if(command == "export"){
			int m;
			string arquivo;
			ss >> m;
			ss >> arquivo;
			exportSparseMatrix(matrizes[m], arquivo);
		}else if(command == "sum"){
			int a, b;
			ss >> a >> b;
			SparseMatrix* ptr = sum(matrizes[a], matrizes[b]);
			matrizes.push_back(ptr);
		}else if(command == "multiply") {
			int a, b;
			ss >> a >> b;
			SparseMatrix* ptr = multiply(matrizes[a], matrizes[b]);
			matrizes.push_back(ptr);
		}else if(command == "copy") {
			int index;
			ss >> index;
			SparseMatrix* mat = new SparseMatrix(*matrizes[index]);
			matrizes.push_back(mat);
		} else{
			cout << "comando inexistente" << endl;
		}
	}
	return 0;
}