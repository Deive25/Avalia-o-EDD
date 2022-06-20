#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct no{
  int dado;
  struct no *esq;
  struct no *dir;
  int fb; //fator de balanceamento
}Arvore;

int calcularAltura (Arvore *raiz){
  if(raiz){
    int altEsq = calcularAltura(raiz->esq); //avançou completamente para a esquerda
    int altDir = calcularAltura(raiz->dir);//avançou completamente para a direita

    //testou a altura maior e retornou ela +1
    if(altEsq>altDir){
      return altEsq + 1;
    }
    else{
      return altDir + 1;
    }
  } else{
    return 0;
  }
}

Arvore *rodarEsq(Arvore *r){
  Arvore *pai,*filho,*tmp;

  pai = r;
  filho = pai->dir;
  r = filho;
  
  tmp = filho->esq;
  filho->esq = pai;
  pai->dir = tmp;
  
  return r;
}

Arvore *rodarDir(Arvore *r){
  Arvore *pai,*filho,*tmp;

  pai = r;
  filho = pai->esq;
  r = filho;
  
  tmp = filho->dir;
  filho->dir = pai;
  pai->esq = tmp;
  
  return r;
}

void atualizarFB(Arvore *r){
  if(r){
    atualizarFB(r->esq);
    atualizarFB(r->dir);

    r->fb = calcularAltura(r->esq) - calcularAltura(r->dir);
  }
}

Arvore *inserir(int valor, Arvore *r){
  if(r){
    if(valor<r->dado){
      if(valor == r->dado){
        cout<<"Valor repetido tente novamente";
        return r;
      }
      r->esq = inserir(valor,r->esq);
    }
    else{
      if(valor == r->dado){
        cout<<"Valor: "<< r->dado <<" não colocado pois o valor ja é existente na arvore\n\n";
        return r;
      }
      r->dir = inserir(valor, r->dir);
    }

    r->fb = calcularAltura(r->esq) - calcularAltura(r->dir);

    //testes de balanceamento
    if(r->fb == -2){
      if(r->fb < 0 && r->dir->fb < 0 ){
          r = rodarEsq(r);
        }
       else if(r->fb < 0 && r->dir->fb > 0){
        //primeiro no filho
         r->dir = rodarDir(r->dir);
        //segundo no pai
         r = rodarEsq(r);
        }
    }
    else if(r->fb == 2){
      if(r->fb > 0 && r->esq->fb > 0){
        r = rodarDir(r);
      }
      else if(r->fb > 0 && r->esq->fb < 0){
        //primeiro no filho
        r->esq = rodarEsq(r->esq);
        //segundo no pai
        r = rodarDir(r);
      }
    }
    //atualizar o fb da subarvore alterada
    atualizarFB(r);
    return r;
  }
  else{
    Arvore *novo = (Arvore*)malloc(sizeof(Arvore));
    novo->dado = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->fb = 0; //todo nodo inserido, o fb é 0
    return novo;
  }
}

void exibir(Arvore *r,int nivel){
  if(r){
    exibir(r->dir,nivel+1);
    for(int i = 0; i<nivel; i++){
      cout << "      ";
    }
    cout << "(" << nivel << ")" << r->dado<<"["<< r->fb <<"]"<< endl;
    exibir(r->esq, nivel+1);
  }
}

Arvore *remover(int valor,Arvore *raiz){
  if(raiz){
    if(valor == raiz->dado){
      //é folha
      if(!raiz->esq && !raiz->dir){
        free(raiz);
        return NULL;
      }
      else{
        Arvore *novoPai;
        Arvore *p;
        if(raiz->esq) novoPai= raiz->esq;
        else novoPai = raiz->dir;

        for(p = novoPai; p->dir ; p = p->dir);
        
        p->dir = raiz->dir;
        novoPai->dir = p->dir;
        cout<<"Dado:"<<p->dir->dado<<endl;
        free(raiz);
        
        //Atualiza fb
        atualizarFB(novoPai);
        
        //balacear pra valer
        if(novoPai->fb == -2){
          if(novoPai->fb < 0 && novoPai->dir->fb < 0 ){
              novoPai = rodarEsq(novoPai);
            }
           else if(novoPai->fb < 0 && novoPai->dir->fb > 0){
            //primeiro no filho
             novoPai->dir = rodarDir(novoPai->dir);
            //segundo no pai
             novoPai = rodarEsq(novoPai);
            }
        }
        else if(novoPai->fb == 2){
          if(novoPai->fb > 0 && novoPai->esq->fb > 0){
            novoPai = rodarDir(novoPai);
          }
          else if(novoPai->fb > 0 && novoPai->esq->fb < 0){
            //primeiro no filho
            novoPai->esq = rodarEsq(novoPai->esq);
            //segundo no pai
            novoPai = rodarDir(novoPai);
          }
        }
        atualizarFB(novoPai);
        
        return novoPai;
      }
    }
    else{
      if(valor< raiz->dado){
        raiz ->esq = remover(valor, raiz->esq);
      }
      else{
        raiz->dir = remover(valor,raiz->dir);
      }
    }
  }
  return NULL;
}

Arvore *podar(Arvore *r){
  if(r){
    if(!r->esq && !r->dir){
      free(r);
    }
  }
  else{
    return NULL;
  }
};

/*2) A partir do código anterior, faça um método em C++ (métodos de árvore .h) que recebe um ponteiro para uma árvore binária de pesquisa e um valor 
inteiro. Em seguida, o método deve apagar todos os nós folhas que são múltiplos do valor passado no parâmetro.*/

Arvore *excluirFolhasMultiplos(Arvore *r, int num){
  if(r){
    //testar se é um nó folha ese é multiplo
    if(r->dado == num || r->dado%num == 0 && !r->esq && !r->dir){
      //excluir nó
      cout<<"Nó folha excluido: "<< r->dado << "\n\n";
      free(r);
      return NULL;
    }
    //percorrer toda a arvore
    r->esq = excluirFolhasMultiplos(r->esq,num);
    r->dir = excluirFolhasMultiplos(r->dir,num);
    return r;
  }
  else{
    return NULL;
  }
};

/*3) Faça um método que receba um ponteiro para uma árvore binária de pesquisa e um valor inteiro. O método dever retornar o endereço físico desse valor,
caso contrário, deve retornar NULL (indicando que o valor não foi localizado)*/

Arvore *retornaEndereco(Arvore *r, int num){
  if(r){
    //testa se o nó é igual ao numero
    if(r->dado == num){
      //exibir o endereço fisico do valor
      cout<<"O numero: "<<r->dado<<" esta localizado na memoria disica em: "<< r <<"\n";
    }
    //percorrer a raiz
    retornaEndereco(r->esq,num);
    retornaEndereco(r->dir,num);
  } 
  return NULL;
}
