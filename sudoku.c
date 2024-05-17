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

int is_valid(Node* n)
{
   
   //VERIFICAR FILA POR FILA
   for(int i = 0 ; i < 9 ; i++) //FILAS
   {
      int *arreglo = (int *) calloc(sizeof(int), 9);
      for(int j = 0 ; j < 9 ; j++) //COLUMNAS
      {
         int numero = n->sudo[i][j];
         arreglo[numero-1]++;
      }
      //VERIFICAR ARREGLO
      for(int k = 0 ; k < 9 ; k++)
      {
         if(arreglo[k] > 1)
            return 0;
      }
   }

   //VERIFICAR COLUMNA POR COLUMNA
   for(int j = 0 ; j < 9 ; j++) //COLUMNAS
   {
      int *arreglo = (int *) calloc(sizeof(int), 9); //FILAS
      for(int i = 0 ; i < 9 ; i++)
      {
         int numero = n->sudo[i][j];
         arreglo[numero-1]++;
      }
      //VERIFICAR ARREGLO
      for(int k = 0 ; k < 9 ; k++)
      {
         if(arreglo[k] > 1)
            return 0;
      }
   }

   //VERIFICAR BLOQUE POR BLOQUE
   for(int i = 0 ; i < 9 ; i++) //BLOQUE 
   {
      int *arreglo = (int *) calloc(sizeof(int), 9);
      for(int j = 0 ; j < 9 ; j++) //RECORRER EL BLOQUE
      {
         int k = 3*(i/3) + (j/3);
         int l = 3*(i%3) + (j%3);
         int numero = n->sudo[k][l];
         arreglo[numero-1]++;
      }
      //VERIDICAR ARREGLO
      for(int m = 0 ; m < 9 ; m++)
      {
         if(arreglo[m] > 1)
            return 0;
      }
   }
   
   
    return 1;
}



List* get_adj_nodes(Node* n){
   List* list = createList();
   int found = 0;
   int i;
   int j;

   //SI NO ES VALIDO RETORNAR LISTA VACIA
   if (!is_valid(n))
      return list;
   
   //RECORRER LAS CASILLAS HASTA ENCONTRAR UNA CASILLA VACIA
   for (i = 0 ; i < 9 ; i++)
   {
      for (j = 0 ; j < 9 ; j++)
         if (n->sudo[i][j] == 0)
         {
            found = 1;
            break;
         }
      if (found == 1)
         break;
   }
   
   //COPIAR EL NODO PRINICIPAL Y CREAR EL NUEVO NODO ADYACENTE
   int k;
   for (k = 1 ; k <= 9 ; k++)
   {
      Node *nuevoNodo = createNode();
      nuevoNodo = copy(n);
      nuevoNodo->sudo[i][j] = k;
      if(is_valid(nuevoNodo))
         pushBack(list, nuevoNodo);
   }
   
   return list;
}


int is_final(Node* n){

    //TODOS LOS VALORES SON DISTINTOS DE 0
   for(int i = 0 ; i < 9 ; i++)
      for(int j = 0 ; j < 9 ; j++)
         if(n->sudo[i][j] == 0)
            return 0;

   //SI NO HAY 0 PERO ES UN SUDOKU INVALIDO RETORNAR 0
   if(is_valid(n))
      return 1;

   return 0;
}

Node* DFS(Node* initial, int* cont){
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