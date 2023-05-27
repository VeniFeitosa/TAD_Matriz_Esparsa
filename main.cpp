#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SparseMatrix.h"
using namespace std;

int main() {

	vector<SparseMatrix*> matrizes;
	
	while(true) {
		string input, comando;
		getline(cin, input);
		stringstream ss{ input };
        ss >> comando;

        cout << "$" << ss.str() << endl;

		// exit
		if(comando == "exit") {
			// for(int i = 0; i < matrizes.size(); i++)
			// 	delete matrizes[i];
			// matrizes.clear();
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
			int index, i, j, val;
            ss >> index >> i >> j >> val;
			matrizes[index]->insert(i, j, val);
		}else if(comando == "clear"){
			int index;
            ss >> index;
			matrizes[index]->clear();
		}else if(comando == "get"){
			int idc, i, j;
            ss >> idc >> i >> j;
			cout << matrizes[idc]->get(i, j) << endl;
		}else {
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