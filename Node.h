/*
 *  Discentes:
 *  Venicius Feitosa - 537799
 *  Gustavo Erick - 536884
*/

#ifndef NODE_H
#define NODE_H


struct Node {
    Node* next;
    Node* bottom;
    int linha;
    int coluna;
    double valor;

    Node(int l, int c, double v,Node* ptrNext = nullptr, Node* ptrBottom = nullptr){
        this->linha = l;
        this->coluna = c;
        this->valor = v;
        this->next = ptrNext;
        this->bottom = ptrBottom;
    }
};


#endif