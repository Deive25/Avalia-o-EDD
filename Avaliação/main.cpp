#include <iostream>
#include <fstream>
#include "arvore.h"
using namespace std;
/*1) A partir de um arquivo txt, com números inteiros, um abaixo do outro, faça um programa em C++ que abra este arquivo e o popule em uma árvore binária 
de pesquisa. Entretanto, o código NÃO deve perrmitir números repetidos. Sugere-se que a árvore esteja balanceada e que se use um arquivo .h 
para os métodos de árvore.*/

Arvore *popularArvore(Arvore *arvore){
  string linha;
  char nomeArquivo[200];
  ifstream procurador;
  
  cout << "Informe o nome do Arquivo: ";
  cin >> nomeArquivo;
  procurador.open(nomeArquivo);
  if(!procurador){
    cout<<"Arquivo não localizado\n";
    return NULL;
  }
  int valor;
  
  while(getline(procurador,linha)){
    valor = stoi(linha);
    arvore = inserir(valor,arvore);
  }
  return arvore;
} 

int main() {
  Arvore *raiz = NULL;
  
  raiz = popularArvore(raiz);
  exibir(raiz,0);
  
  raiz = excluirFolhasMultiplos(raiz,5);
  exibir(raiz,0);
  
  retornaEndereco(raiz,23);
  
  return 1;
}