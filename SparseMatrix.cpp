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

            //viaja até o no anterior ao no na linha
            while (viajanteLinha->coluna + 1 != j){
                if (viajanteLinha->next != auxLinha){
                    viajanteLinha = viajanteLinha->next;
                }else{
                    break;
                }
            }
            //viaja até o no anterior ao no na coluna
            while (viajanteColuna->linha + 1 != i){
                if (viajanteColuna->bottom != auxColuna){
                    viajanteColuna = viajanteColuna->next;
                }else{
                    break;
                }
            }
            
            //Subcaso 2.1: Ja existe um no nessa posição
            if (viajanteLinha->next->linha == i && viajanteColuna->bottom->coluna == j){
                int antigo = viajanteLinha->next->valor;
                cout << "Valor antigo: " << antigo << endl;
                viajanteLinha->next->valor = value;
                delete novo;
            }
            //Subcaso 2.2: 
            else if(viajanteLinha->coluna + 1 == j && viajanteColuna->linha + 1 == i){
                
                novo->next = viajanteLinha->next;
                viajanteLinha->next = novo;
                novo->bottom = viajanteColuna->bottom;
                viajanteColuna->bottom = novo;
            }
            
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
        }else{
            
        } 

    }    

};

void SparseMatrix::print(){

    
    Node* auxLinha = this->m_head->bottom;
    Node* auxColuna;

    // percorre todos os sentinelas de linha
    while (auxLinha != m_head){
        string str;
        str += "[ ";
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
                    //cout << "0 ";
                    str += "0 ";
                }
                auxColuna = auxColuna->next;
                //cout << auxColuna->valor << " ";
                str += to_string(auxColuna->valor) + " ";
                qtd = qtd - distancia;
            }else{
                for (int i = 0; i < qtd; i++){
                    //cout << "0 ";
                    str += "0 ";
                }
                break;
            }
        }
        //cout << endl;
        str += "]";
        cout << str << endl;
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

void SparseMatrix::clear() {

    Node* auxLinha = this->m_head->bottom;
    Node* auxColuna;

    while (auxLinha != m_head){
        auxColuna = auxLinha;
        
        while (auxColuna->next != auxLinha){
            Node* aux = auxColuna->next;
            auxColuna->next = aux->next;
            delete aux;
        }

        //Node* aux = auxLinha;
        //auxLinha->bottom = aux->bottom;
        //delete aux;
        auxLinha = auxLinha->bottom;

        /*
        CERTIFICAR-SE DE QUE A FUNCAO ESTA FUNCIONANDO ANTES
        DE MUDAR O TAMANHO DA MATRIZ!
        */
        m = 0;
        n = 0;
    }
    //m_head->bottom = m_head;
}

SparseMatrix::~SparseMatrix(){
    clear();
    delete m_head;
}

double SparseMatrix::get(int i, int j) {

    if ((i < 0 || i > m) && (j < 0 || i > n)) {
        throw runtime_error("Indices invalidos");
    } else {
        Node* auxLinha = m_head->bottom;
        Node* auxColuna;

        int linha{0}, coluna{0};
        //ATENCA! A FUNCAO ESTA INCOMPLETA
        while (auxLinha != m_head) {
            if (linha != i) {
                i++;
                auxLinha = auxLinha->next;
            } else {
                auxColuna = auxLinha;
                while (auxColuna->next != auxLinha) {
                    if (coluna != j) {
                        if (auxColuna->next == auxColuna) return 0;
                        j++;
                        auxColuna = auxColuna->next;
                    } else {
                        return auxColuna->valor;
                    }
                }
                /*
                caso o next de auxColuna for igual a auxLinha
                o while nao eh executado, retornando 0 de imediato
                */
                return 0; 
            }
        }

        /*
        Node* auxLinha = m_head->bottom;
        Node* auxColuna;

        int linha{0}, coluna{0};
        //ATENCA! A FUNCAO ESTA INCOMPLETA
        while (auxLinha != m_head) {
            if (linha != i) {
                i++;
                auxLinha = auxLinha->next;
            } else {
                auxColuna = auxLinha;
                if (coluna != j) {
                    j++;
                    auxLinha = auxLinha->next;
                } else {
                    cout << auxColuna->valor;
                }
            }
        }
        */
        return 0;
    }
}
