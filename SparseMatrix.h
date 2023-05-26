#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include "Node.h"
/**
 * Classe que gera uma lista encadeada circular
 * com no centinela 
 */
class SparseMatrix{
    private:
        Node* m_head = nullptr;
        int m;
        int n;
    public:
        /**
         * Construtor da classe. Essa função checa
         * Se os valores passados são válidos e inicia
         * A matriz com m linhas e n colunas
         */
        SparseMatrix(int m, int n);
        /**
         * Função que aloca as linhas da matriz
         * 
         */
        void alocarLinhas(int m);
        /**
         * Função que aloca as colunas da matriz
         * 
         */
        void alocarColunas(int n);
};

#endif