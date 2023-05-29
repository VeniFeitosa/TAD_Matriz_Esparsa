#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "SparseMatrix.h"
using namespace std;

SparseMatrix* readSparseMatrix(string diretorio){
	ifstream fin;
	fin.open("./Entradas/" + diretorio);
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
		cout << "Diretorio " << diretorio << " não encontrado"<< endl;
		return nullptr;
	}
}

// Recebe uma referencia para o objeto B do tipo Matriz que possui
    // m linhas e n colunas e soma a matriz B com a matriz atual.
    // Lembre que a soma de uma matriz A com uma matriz B so eh possivel  
    // se o numero de linhas e de colunas de A for igual ao numero de 
    // linhas e de colunas de B, respectivamente. 
    // Se for possivel fazer a soma, um ponteiro para uma nova matriz C
    // contendo o resultado da soma deve ser retornado (note que a matriz C 
    // deve ser alocada dinamicamente dentro da funcao-membro).
    // Caso contrario, retorna nullptr indicando que nao foi possivel 
    // fazer a soma das matrizes.
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
		throw out_of_range("deu ruim papai");
	}
}

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
		throw out_of_range("melhore");
	}
}

int main() {
	system("chcp 65001 > nul");
	vector<SparseMatrix*> matrizes;
	
	while(true) {
		cout << "──────────────────────────" << endl;
		cout << "-> ";
		string input, comando;
		getline(cin, input);
		stringstream ss{ input };
        ss >> comando;

        // cout << "$" << ss.str() << endl;
        cout << "➥  " << ss.str() << endl;
		// exit
		if(comando == "exit") {
			for(int i = 0; i < matrizes.size(); i++)
				delete matrizes[i];
			matrizes.clear();
			break;
		}
		// create
		else if(comando == "create") {
            int m, n;
            ss >> m >> n;
			SparseMatrix *mat = new SparseMatrix(m, n);
			matrizes.push_back(mat);
		}else if(comando == "testConstrutor"){
			int l;
			ss >> l;
			matrizes[l]->testConstructor();
			
		}else if(comando == "print"){
			int l;
			ss >> l;
			matrizes[l]->print();
			//insert 0 2 3 10
		}else if(comando == "insert"){
			// int index, i, j, val;
			int index, i, j;
			double val;
            // ss >> index >> i >> j >> val;
            ss >> index >> i >> j;
			ss >> fixed >> setprecision(2) >> val;
			matrizes[index]->insert(i, j, val);
		}else if(comando == "clear"){
			int index;
            ss >> index;
			matrizes[index]->clear();
		}else if(comando == "get"){
			int idc, i, j;
            ss >> idc >> i >> j;
			cout << fixed << setprecision(2) << matrizes[idc]->get(i, j) << endl;
		}else if(comando == "popular"){
			int l;
			ss >> l;
			matrizes[l]->popularMatriz();
		}else if(comando == "createFrom"){
			string diretorio;
			ss >> diretorio;
			SparseMatrix*ptr = readSparseMatrix(diretorio);
			matrizes.push_back(ptr);
		}else if(comando == "somar"){
			int a, b;
			ss >> a >> b;
			SparseMatrix* ptr = sum(matrizes[a], matrizes[b]);
			matrizes.push_back(ptr);
		}else if("multiplicar") {
			int a, b;
			ss >> a >> b;
			SparseMatrix* ptr = multiply(matrizes[a], matrizes[b]);
			matrizes.push_back(ptr);
		} else{
			cout << "comando inexistente" << endl;
		}
		//oi mofi
		// // createWith l
		// else if(comando == "createWith") {
		// 	// int l;
        //     // ss >> l;
		// 	// ForwardList *mat = new ForwardList(*matrizes[l]);
		// 	// matrizes.push_back(mat);
		// }
		// // pushback x l
		// else if(comando == "pushback") {
		// 	// int x, l;
        //     // ss >> x >> l;
		// 	// matrizes[l]->push_back(x);
		// }
        // // pushfront x l
		// else if(comando == "pushfront") {
		// 	// int x, l;
        //     // ss >> x >> l;
		// 	// matrizes[l]->push_front(x);
		// }
        // // popfront l
		// else if(comando == "popfront") {
		// 	// int l;
        //     // ss >> l;
		// 	// matrizes[l]->pop_front();
		// }
        // // popback l
		// else if(comando == "popback") {
		// 	int l;
        //     ss >> l;
		// 	matrizes[l]->pop_back();
		// }
        // // front l
		// else if(comando == "front") {
		// 	int l;
        //     ss >> l;
		// 	cout << "front: " << matrizes[l]->front() << endl;
		// }
        // // back l
		// else if(comando == "back") {
		// 	int l;
        //     ss >> l;
        //     cout << "back: " << matrizes[l]->back() << endl;
		// }
        // // show 
		// else if(comando == "show") {
        //     for(unsigned i = 0; i < matrizes.size(); ++i) {
        //         cout << "lista " << i << ": " << (*matrizes[i]).toString() << endl;
        //     }	
		// }
		// else {
		// 	cout << "input inexistente" << endl;
		// }
	}
	return 0;
}