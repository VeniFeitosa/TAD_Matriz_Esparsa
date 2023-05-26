#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"
#include "SparseMatrix.h"

// Construtor da classe
SparseMatrix::SparseMatrix(int m, int n){
    if (m > 0 && n > 0){
        this->m = m;
        this->n = n;
        m_head = new Node(0, 0 , 0);
        alocarLinhas(m);
        alocarColunas(n);
    }
    
}

// Aloca M linhas na matriz
void SparseMatrix::alocarLinhas(int m){
    Node* aux = m_head;
    for (int i = 1; i <= m; i++){
        aux->bottom = new Node(i, 0, 0);
        aux = aux->bottom;
        aux->next = aux;
    }
    aux->bottom = m_head;
}

// Aloca N colunas na matriz
void SparseMatrix::alocarColunas(int n){
    Node* aux = m_head;
    for (int i = 1; i <= n; i++){
        aux->next = new Node(0, i, 0);
        aux = aux->next;
        aux->bottom = aux;
    }
    aux->next = m_head;
}