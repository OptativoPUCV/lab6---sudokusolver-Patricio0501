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

int is_valid(Node* n) {
    int VerificacionFila[9][10];           // Array para verificar números en filas
    int VerificacionColumna[9][10];       // Array para verificar números en columnas
    int VerificacionSubMatriz[3][3][10];  // Array para verificar números en submatrices de 3x3

    int i, j;

    for (i = 0; i < 9; i++) {
        for (j = 1; j <= 9; j++) {
            VerificacionFila[i][j] = 0;           // Inicializar a 0
            VerificacionColumna[i][j] = 0;       // Inicializar a 0
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            for (int num = 1; num <= 9; num++) {
                VerificacionSubMatriz[i][j][num] = 0;  // Inicializar a 0
            }
        }
    }

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            
            // Verificar si el número ya se ha utilizado en la misma fila
            if (VerificacionFila[i][num] == 1) {
                return 0;  // El número se repite en la fila
            }
            
            // Verificar si el número ya se ha utilizado en la misma columna
            if (VerificacionColumna[j][num] == 1) {
                return 0;  // El número se repite en la columna
            }
            
            // Verificar si el número ya se ha utilizado en la misma submatriz de 3x3
            int CuadriculaFila = i / 3;
            int CuadriculaColumna = j / 3;
            if (VerificacionSubMatriz[CuadriculaFila][CuadriculaColumna][num] == 1) {
                return 0;  // El número se repite en la submatriz de 3x3
            }

            // Marcar el número como utilizado en la fila, columna y submatriz
            VerificacionFila[i][num] = 1;
            VerificacionColumna[j][num] = 1;
            VerificacionSubMatriz[CuadriculaFila][CuadriculaColumna][num] = 1;
        }
    }

    // Si todas las restricciones se cumplen, el estado/nodo es válido
    return 1;
}

List* get_adj_nodes(Node* n) {
    List* list = createList();
    int i, j;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                for (int num = 1; num <= 9; num++) {
                    Node* new_node = copy(n);
                    new_node->sudo[i][j] = num;
                    pushBack(list, new_node); 
                }
                return list; 
            }
        }
    }

    return list; 
}


int is_final(Node* n){
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