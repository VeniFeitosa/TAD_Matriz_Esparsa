#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
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
        throw runtime_error("Indices invalidos");
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
            auxLinha->next = novo;
            auxColuna->bottom = novo;

            novo->next = auxLinha;
            novo->bottom = auxColuna;
        }
        //caso 2 já existe elemento na linha e na coluna
        else if(auxLinha->next != auxLinha && auxColuna->bottom != auxColuna){
            Node* viajanteLinha = auxLinha;
            Node* viajanteColuna = auxColuna;

            //faz o viajanteLinha apontar para o no 
            //da linha que será o anterior ao meu novo no
            while (viajanteLinha->next != auxLinha){
                if (viajanteLinha->next->coluna >= j){
                    break;
                }else{
                    viajanteLinha = viajanteLinha->next;
                }
            }
            // cout << viajanteLinha->linha << endl;
            // cout << viajanteLinha->coluna << endl;
            //faz o viajanteColuna apontar para o no
            //da coluna que será o anterior ao meu novo no
            while (viajanteColuna->bottom != auxColuna){
                if (viajanteColuna->bottom->linha >= i){
                    break;
                }else{
                    viajanteColuna = viajanteColuna->bottom;
                }
            }
            // cout << viajanteColuna->linha << endl;
            // cout << viajanteColuna->coluna << endl;

            // cout << "entrou no if de subcasos \n";
            if (viajanteLinha->next == viajanteColuna->bottom){
                // cout << "caiu no caso 2.1 \n";
                // int antigo = viajanteLinha->next->valor;
                // cout << "Valor antigo: " << antigo << endl;
                viajanteLinha->next->valor = value;
                delete novo;
            }
            //Subcaso 2.2: Nao existe um no nessa posicao
            else{
                // cout << "caiu no caso 2.2 \n";
                novo->next = viajanteLinha->next;
                viajanteLinha->next = novo;
                novo->bottom = viajanteColuna->bottom;
                viajanteColuna->bottom = novo;
            }

            // if (viajanteLinha->next != auxLinha && viajanteColuna->bottom != auxColuna){
            //     //Subcaso 2.1: Ja existe um no nessa posição
            //     cout << "entrou no if de subcasos \n";
            //     if (viajanteLinha->next == viajanteColuna->bottom){
            //         cout << "caiu no caso 2.1 \n";
            //         int antigo = viajanteLinha->next->valor;
            //         cout << "Valor antigo: " << antigo << endl;
            //         viajanteLinha->next->valor = value;
            //         delete novo;
            //     }
            //     //Subcaso 2.2: Nao existe um no nessa posicao
            //     else{
            //         cout << "caiu no caso 2.2 \n";
            //         novo->next = viajanteLinha->next;
            //         viajanteLinha->next = novo;
            //         novo->bottom = viajanteColuna->bottom;
            //         viajanteColuna->bottom = novo;
            //     }
                
            // }
        }
        //caso 3: inserir numa linha que tem algum no, mas numa coluna
        //que não tem nenhum no  
        else if(auxLinha->next != auxLinha && auxColuna->bottom == auxColuna){
            Node* viajante = auxLinha;
            while (viajante->coluna + 1 != j){
                if (viajante->next != auxLinha){
                    viajante = viajante->next;
                }else{
                    break;
                }
                
            }
            novo->next = viajante->next;
            viajante->next = novo;
            auxColuna->bottom = novo;
            novo->bottom = auxColuna;
        }
        //caso 4: inserir numa coluna que tem algum no, mas numa linha
        //que não tem nenhum no 
        else if(auxLinha->next == auxLinha && auxColuna->bottom != auxColuna){
            Node* viajante = auxColuna;
            while (viajante->linha + 1 != i){
                if (viajante->bottom != auxColuna){
                    viajante = viajante->bottom;
                }else{
                    break;
                }
                
            }
            novo->bottom = viajante->bottom;
            viajante->bottom = novo;
            auxLinha->next = novo;
            novo->next = auxLinha;
        }

    }    

};

void SparseMatrix::popularMatriz(){
    int count = 1;
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            this->insert(i, j, count);
            count++;
        }   
    }
}

void SparseMatrix::print(){
    Node* auxLinha = this->m_head->bottom;
    Node* auxColuna;

    // percorre todos os sentinelas de linha
    while (auxLinha != m_head){
        string str;
        // str += "[ ";
        cout << fixed << setprecision(2);
        cout << "[";
        // esse auxiliar de coluna server para percorrer
        // as colunas da linha atual
        auxColuna = auxLinha;
        // qtd é a quantidade de zeros que a linha deve ter
        // conforme forem impressos números na linha, a quantidade
        // de zeros que ela deve ter diminui
        int qtd = this->n;
        while (auxColuna->coluna != this->n){
            if (auxColuna->next != auxLinha){
                int distancia = auxColuna->next->coluna - auxColuna->coluna;

                for (int i = 1; i < distancia; i++){
                    cout << setw(6) << "0.00" << " ";
                    // str += "0 ";
                }
                auxColuna = auxColuna->next;
                // cout << auxColuna->valor << " ";
                cout << setw(6) << auxColuna->valor << " ";
                // str += to_string(auxColuna->valor) + " ";
                qtd = qtd - distancia;
            }else{
                for (int i = 0; i < qtd; i++){
                    cout << setw(6) << "0.00" << " ";
                    // str += "0 ";
                }
                break;
            }
        }
        //cout << endl;
        cout << "]" << endl;
        // str += "]";
        // cout << str << endl;
        auxLinha = auxLinha->bottom;
    }
}

void SparseMatrix::clear() {
    Node* auxLinha = m_head->bottom;

    while (auxLinha != m_head){
        Node* auxColuna = auxLinha->next;
        
        while (auxColuna != auxLinha){
            Node* aux = auxColuna;
            auxColuna = auxColuna->next;
            auxLinha->next = auxColuna;
            delete aux;
        }
        auxLinha = auxLinha->bottom;
    }

    auxLinha = auxLinha->next;

    while(auxLinha != m_head) {
        auxLinha->bottom = auxLinha;
        auxLinha = auxLinha->next;
    }
}

int SparseMatrix::getLinhas(){
    return m;
}

int SparseMatrix::getColunas(){
    return n;
}

void SparseMatrix::desalocarLinhas(){

    Node* auxLinha = m_head->bottom;
    while (auxLinha != m_head) {
        Node* aux = auxLinha;
        auxLinha = auxLinha->bottom;
        m_head->bottom = auxLinha;
        cout << "desalocando sentinela linha: " << aux->linha << endl;
        delete aux;
    }
}

void SparseMatrix::desalocarColunas(){

    Node* auxColuna = m_head->next;
    while (auxColuna != m_head) {
        Node* aux = auxColuna;
        auxColuna = auxColuna->next;
        m_head->next = auxColuna;
        cout << "desalocando sentinela coluna: " << aux->coluna << endl;
        delete aux;
    }

}

SparseMatrix::~SparseMatrix(){
    clear();
    desalocarLinhas();
    desalocarColunas();
    delete m_head;
}

double SparseMatrix::get(int i, int j) {
    if ((i <= 0 || i > m) || (j <= 0 || j > n)) {
        throw runtime_error("Indices invalidos");
    } else {
        Node* auxLinha = m_head->bottom;

        while (auxLinha->linha != i) {
            auxLinha = auxLinha->bottom;
        }

        Node* auxColuna = auxLinha->next;

        while (auxColuna != auxLinha) {
            if (auxColuna->coluna == j) {
                return auxColuna->valor;
            } else if (auxColuna->coluna > j) {
                return 0;
            } else {
                auxColuna = auxColuna->next;
            }
        }
        //se nao tiver nenhum elemento retorna 0
        return 0;
    }
}
