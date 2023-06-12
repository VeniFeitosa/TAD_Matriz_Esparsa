/*
 *  Discentes:
 *  Venicius Feitosa - 537799
 *  Gustavo Erick - 536884
*/

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H
#include "Node.h"
/*
 * Classe que gera uma lista encadeada circular
 * com no sentinela.
 */
class SparseMatrix{
    private:
        Node* m_head = nullptr;
        int m;
        int n;
    public:
        /*
         * Construtor da classe. Essa função checa
         * se os valores passados são válidos e inicia
         * a matriz com m linhas e n colunas, caso contrario
         * lança uma excessao.
         */
        SparseMatrix(int m, int n);

        /*
         * Construtor de copia. Essa função recebe
         * uma matriz esparsa como parâmetro e retorna
         * uma matriz cópia da passada de parâmetro.
         */
        SparseMatrix(const SparseMatrix& sp);

        /*
         * Destrutor da classe. Essa função libera
         * toda a memoria alocada, inclusive a do
         * sentinela.
         */
        ~SparseMatrix();

        /*
         * Função que aloca as m linhas da matriz.
         */
        void alocarLinhas(int m);

        /*
         * Função que aloca as n colunas da matriz.
         */
        void alocarColunas(int n);

        /*
         * Função que retorna o número de linhas da matriz.
         */
        int getLinhas();

        /* 
         * Função que retorna o número de colunas da matriz.
         */
        int getColunas();

        /*
         * Essa função insere um valor na posição (i,j) da matriz se
         * os valores passados forem válidos
         */
        void insert(int i, int j, double value);

        /*
         * Essa função serve para popular a matriz
         * a fim de facilitar os testes.
         */
        void popularMatriz();

        /*
         * Essa função serve para printar a matriz.
         */
        void print();
        
        /*
         * Essa função esvazia a matriz, desalocando
         * todos os nós que não são sentinelas.
         */
        void clear();

        /*
         * Essa função desaloca as linhas sentinelas da matriz.
         */
        void desalocarLinhas();

        /*
         * Essa função desaloca as colunas sentinelas da matriz.
         */
        void desalocarColunas();

        /*
         * Essa função retorna o elemento (i, j) da matriz, caso
         * os índices passados forem válidos.
         */
        double get(int i, int j) const;

        /*
        * Essa função verifica se a matriz está vazia. 
        */
       bool empty() const;
};

#endif