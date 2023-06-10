#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <random>
#include "Node.h"
#include "SparseMatrix.h"
using namespace std;

//cria um gerador de double aleatórios com intervalo de -50.0 a 50.0
default_random_engine generator;
uniform_real_distribution<double> distribution(-50.0,50.0);

// Construtor da classe
SparseMatrix::SparseMatrix(int m, int n){
    if (m > 0 && n > 0){
        this->m = m;
        this->n = n;
        m_head = new Node(0, 0 , 0);
        alocarLinhas(m);
        alocarColunas(n);
    } else {
        throw out_of_range("Linhas ou colunas invalidos");
    }
}

SparseMatrix::SparseMatrix(const SparseMatrix& sp) {
    m = sp.m;
    n = sp.n;
    m_head = new Node(0, 0 , 0);
    alocarLinhas(m);
    alocarColunas(n);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            insert(i, j, sp.get(i, j));
        }
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

void SparseMatrix::insert(int i, int j, double value){
    if (i > this->m || j > this->n){
        throw out_of_range("Indices invalidos");
    } else{
        Node* auxLinha = m_head->bottom;
        Node* auxColuna = m_head->next;
        
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
        //faz o viajanteColuna apontar para o no
        //da coluna que será o anterior ao meu novo no
        while (viajanteColuna->bottom != auxColuna){
            if (viajanteColuna->bottom->linha >= i){
                break;
            }else{
                viajanteColuna = viajanteColuna->bottom;
            }
        }
        //caso 1: O nó já existe, apenas atualiza o valor
        if (viajanteLinha->next == viajanteColuna->bottom){
            //Se o insert for de valor 0, remove o nó correspondente
            if (value == 0) {
                //cria um nó aux apontando pro nó que será apagado
                Node* aux = viajanteLinha->next;
                //faz o viajanteLinha->next apontar pro prox
                viajanteLinha->next = viajanteLinha->next->next;
                //faz o viajanteColuna->bottom apontar pro abaixo
                viajanteColuna->bottom = viajanteColuna->bottom->bottom;
                //deleta o nó correspondente
                delete aux;
            } else{
                viajanteLinha->next->valor = value;
            }
        }
        //caso 2: Não existe um nó nessa posicao
        else{
            //Adiciona o nó caso o valor for diferente de 0
            //caso for == 0, não adiciona
            if (value != 0) {
                Node* novo = new Node(i, j, value);
                novo->next = viajanteLinha->next;
                viajanteLinha->next = novo;
                novo->bottom = viajanteColuna->bottom;
                viajanteColuna->bottom = novo;
            }
        }
    }
}

void SparseMatrix::popularMatriz(){

    // Percorre todas as linhas da matriz.
    for (int i = 1; i <= m; i++){

        // Dentro de cada linha, percorre todas as colunas.
        for (int j = 1; j <= n; j++){

            // Insere um valor aleatório na posição (i, j) da matriz.
            this->insert(i, j, distribution(generator));
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
    // Cria um ponteiro auxiliar para percorrer as linhas da matriz.
    Node* auxLinha = m_head->bottom;

    // Percorre todas as linhas da matriz.
    while (auxLinha != m_head){

        // Cria um ponteiro auxiliar para percorrer os nós da linha atual.
        Node* viajante = auxLinha->next;
        
        // Percorre todas os nós da linha atual.
        while (viajante != auxLinha){

            // Salva o nó atual em um ponteiro auxiliar.
            Node* aux = viajante;

            // Avança o ponteiro viajante para o próximo nó.
            viajante = viajante->next;

            // Remove o nó atual da lista.
            auxLinha->next = viajante;

            // Deleta o nó atual.
            delete aux;
        }

        // Avança o ponteiro auxLinha para a próxima linha.
        auxLinha = auxLinha->bottom;
    }

    // Cria um ponteiro auxiliar para percorrer as colunas da matriz.
    Node* auxColuna = m_head->next;

    // Percorre todas as colunas da matriz.
    while (auxColuna != m_head) {

        // Define o ponteiro bottom da coluna atual para apontar para ele mesmo.
        auxColuna->bottom = auxColuna;

        // Avança o ponteiro auxColuna para a próxima coluna.
        auxColuna = auxColuna->next;
    }
}

int SparseMatrix::getLinhas(){
    return m;
}

int SparseMatrix::getColunas(){
    return n;
}

void SparseMatrix::desalocarLinhas(){
    // Cria um ponteiro auxiliar para percorrer as linhas sentinelas da matriz.
    Node* auxLinha = m_head->bottom;

    // Percorre todas as linhas sentinelas da matriz.
    while (auxLinha != m_head) {

        // Salva o nó atual em um ponteiro auxiliar.
        Node* aux = auxLinha;

        // Avança o ponteiro auxLinha pra próxima linha.
        auxLinha = auxLinha->bottom;

        // Remove o nó sentinela atual da lista.
        m_head->bottom = auxLinha;

        cout << "desalocando sentinela linha: " << aux->linha << endl;

        // Deleta o nó sentinela atual.
        delete aux;
    }
}

void SparseMatrix::desalocarColunas(){
    // Cria um ponteiro auxiliar para percorrer as colunas sentinelas da matriz.
    Node* auxColuna = m_head->next;

    // Percorre as colunas sentinelas da matriz.
    while (auxColuna != m_head) {

        // Salva o nó sentinela atual em um ponteiro auxiliar.
        Node* aux = auxColuna;

        // Avança o ponteiro auxColuna para a próxima coluna.
        auxColuna = auxColuna->next;

        // Remove a coluna sentinela da lista.
        m_head->next = auxColuna;

        cout << "desalocando sentinela coluna: " << aux->coluna << endl;

        // Deleta o nó sentinela atual.
        delete aux;
    }

}

SparseMatrix::~SparseMatrix(){
    // Limpa a matriz, removendo todos os elementos não-zero.
    clear();

    // Desaloca todas as linhas sentinelas da matriz.
    desalocarLinhas();

    // Desaloca todas as colunas sentinelas da matriz.
    desalocarColunas();

    // Deleta o nó cabeça.
    delete m_head;
}

double SparseMatrix::get(int i, int j) const{

    // Verifica se os índices fornecidos estão dentro dos limites da matriz.
    // Se os índices estiverem fora dos limites, uma exceção é lançada.
    if ((i <= 0 || i > m) || (j <= 0 || j > n)) {
        throw runtime_error("Indices invalidos");
    } else {
        // Cria um ponteiro para o nó auxiliar que começa na primeira linha da matriz.
        Node* auxLinha = m_head->bottom;

        // Percorre as linhas da matriz até encontrar a linha especificada.
        while (auxLinha->linha != i) {
            auxLinha = auxLinha->bottom;
        }

        // Cria um ponteiro para o nó auxiliar que começa na primeira coluna da linha especificada.
        Node* auxColuna = auxLinha->next;

        // Percorre as colunas da linha especificada.
        while (auxColuna != auxLinha) {

            // Se a coluna atual corresponder à coluna especificada, retorna o valor do nó atual.
            if (auxColuna->coluna == j) {
                return auxColuna->valor;
            } 
            // Se a coluna atual for maior que a coluna especificada, isso significa que a coluna especificada não existe na matriz esparsa.
            // Portanto, retorna 0, pois os elementos não existentes em uma matriz esparsa são considerados 0.
            else if (auxColuna->coluna > j) {
                return 0;
            }

            // Se a coluna atual for menor que a coluna especificada, passa para a próxima coluna.
            else {
                auxColuna = auxColuna->next;
            }
        }

        // Se o método chegar a este ponto, isso significa que a coluna especificada não existe na matriz esparsa.
        // Portanto, retorna 0, pois os elementos não existentes em uma matriz esparsa são considerados 0.
        return 0;
    }
}

bool SparseMatrix::empty() {

    // Cria um ponteiro auxiliar para percorrer todas as linhas sentinelas da matriz,
    // apontando para o primeiro nó sentinela da linha.
    Node* auxLinha = m_head->bottom;

    // Percorre todas as linhas sentinelas da matriz.
    while (auxLinha != m_head) {

        // Verifica se o nó à direita da linha é diferente da linha atual.
        if (auxLinha->next != auxLinha) {

            // Caso seja diferente significa que a matriz não está vazia.
            return false;
        }

        // Avança o ponteiro auxLinha para a próxima linha.
        auxLinha = auxLinha->bottom;
    }

    // Se o método chegar a este ponto significa que não há nenhum nó na matriz além dos sentinelas.
    return true;

}