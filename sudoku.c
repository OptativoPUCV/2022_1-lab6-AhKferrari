#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int * aux;
  int i,j,k,p = 0;

  for(i = 0; i < 9; i++){
    aux = calloc(10,sizeof(int));
    for(j = 0; j < 9; j++){
      if(aux[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0) aux[n->sudo[i][j]] = 1;
      else if(aux[n->sudo[i][j]] == 1 && n->sudo[i][j] != 0)  return 0;    
    }
  }

  for(j = 0; j < 9; j++){
    aux = calloc(10,sizeof(int));
    for(i = 0; i < 9; i++){
      if(aux[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0) aux[n->sudo[i][j]] = 1;
      else if(aux[n->sudo[i][j]] == 1 && n->sudo[i][j] != 0) return 0;
    }
  }

  for(k = 0; k < 9; k++){
    aux = calloc(10,sizeof(int));
    for(p = 0; p < 9; p++){
      int i=3*(k/3) + (p/3);
      int j=3*(k%3) + (p%3);
    
    if(aux[n->sudo[i][j]] == 0 && n->sudo[i][j] != 0) aux[n->sudo[i][j]] = 1;
    else if(aux[n->sudo[i][j]] == 1 && n->sudo[i][j] != 0) 
       return 0;  
      
    }  
  }
  free(aux);
  return 1;
  }


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j,k;

    for(i = 0; i < 9 ; i++){
      for(j = 0; j < 9 ; j++){
        if(n->sudo[i][j] == 0)
          for(k = 0; k < 9; k++){
          Node * aux = createNode();
          n->sudo[i][j] = k + 1;
          aux = copy(n);
          if(is_valid(aux) == 1) pushBack(list, aux);
          }
      }
    }
return list;
}


int is_final(Node* n){
  int i,j;

  for(i = 0; i < 9 ;i++){
    for(j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack * pila = createStack();
    push(pila,initial);

    while(get_size(pila) > 0){
      Node * nodo = top(pila);
      pop(pila);
      if(is_final(nodo)) return nodo;
      cont++;
      List * adj = get_adj_nodes(nodo);
      Node * aux = first(adj);
    
      while(aux != NULL){
        push(pila, aux);
        aux = next(adj);
      }  
    }
  
  free (nodo);

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/