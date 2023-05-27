#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"
#include "SparseMatrix.h"
using namespace std;

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

void SparseMatrix::testConstructor(){
    Node* aux = this->m_head->bottom;

    //mostra os sentinelas das linhas
    while (aux != m_head){
        cout << "linha: " << aux->linha << endl;
        aux = aux->bottom;
    }
    aux = this->m_head->next;
    //mostra os sentinelas das colunas
    while (aux != m_head){
        cout << "Coluna: " << aux->coluna << endl;
        aux = aux->next;
    }
    
}

void SparseMatrix::insert(int i, int j, double value){
    if (i > this->m || j > this->n){
        /* lancar excessão*/
    }else{
        Node* auxLinha = m_head->bottom;
        Node* auxColuna = m_head->next;
        Node* novo = new Node(i, j, value);
        while(auxLinha->linha != i){
            auxLinha = auxLinha->bottom;
        }
        // nesse momento o auxLinha aponta para o no sentinela
        // da linha correta
        while(auxColuna->coluna != j){
            auxColuna = auxColuna->next;
        }
        // nesse momento o auxColuna aponta para o no sentinela
        // da coluna correta

        //caso base: não tem nada na linha nem na coluna
        if (auxLinha->next == auxLinha && auxColuna->bottom == auxColuna){
            /* faço algo */
            auxLinha->next = novo;
            auxColuna->bottom = novo;

            novo->next = auxLinha;
            novo->bottom = auxColuna;
        }else{
            
        } 

    }    

};

void SparseMatrix::print(){
    
    Node* auxLinha = this->m_head->bottom;
    Node* auxColuna;

    while (auxLinha != m_head){
        auxColuna = auxLinha;
        int qtd = this->n;
        while (auxColuna->coluna != this->n){
            if (auxColuna->next != auxLinha){
                int distancia = auxColuna->next->coluna - auxColuna->coluna;

                for (int i = 1; i < distancia; i++){
                    cout << "0 ";
                }
                auxColuna = auxColuna->next;
                cout << auxColuna->valor << " ";
                qtd = qtd - distancia;
            }else{
                for (int i = 0; i < qtd; i++){
                    cout << "0 ";
                }
                break;
            }
        }
        cout << endl;
        auxLinha = auxLinha->bottom;
}
    

    // Node* auxLinha = this->m_head->bottom;
    
    // while (auxLinha != m_head){
    //     Node* auxColuna = this->m_head->next;
    //     while (auxColuna != m_head){
    //         if (auxLinha->next != auxLinha && auxColuna->bottom != auxColuna){
    //             /* faço algo */
    //         }else{
    //             cout << "0 "; 
    //         }
            
    //         auxColuna = auxColuna->next;
    //     }
    //     cout << endl;
    //     auxLinha = auxLinha->bottom;
    // }
}
