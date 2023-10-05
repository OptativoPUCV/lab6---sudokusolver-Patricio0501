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
    // Verificar si todas las casillas están llenas y cumplen con las restricciones del Sudoku
    int usedRows[9][10] = {0};
    int usedCols[9][10] = {0};
    int usedSubgrids[3][3][10] = {0};
    
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            
            // Verificar si la casilla está vacía
            if (num == 0) {
                return 0; // El Sudoku no está completo
            }
            
            // Verificar si el número cumple con las restricciones en filas, columnas y submatrices
            if (usedRows[i][num] || usedCols[j][num] || usedSubgrids[i / 3][j / 3][num]) {
                return 0; // El Sudoku no cumple con las restricciones
            }
            
            // Marcar el número como utilizado en filas, columnas y submatrices
            usedRows[i][num] = 1;
            usedCols[j][num] = 1;
            usedSubgrids[i / 3][j / 3][num] = 1;
        }
    }
    
    return 1; // El Sudoku está completo y cumple con las restricciones
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

Node* DFS(Node* n, int* cont) {
    // Crear una pila e insertar el nodo inicial
    Stack* S = createStack();
    push(S, n);
    *cont = 0; // Inicializar el contador de iteraciones

    while (!is_empty(S)) {
        (*cont)++; // Incrementar el contador en cada iteración

        Node* current = top(S); // Obtener el nodo superior de la pila

        // Verificar si el nodo actual corresponde a un estado final
        if (is_valid(current)) {
            // Liberar la memoria de la pila y retornar el nodo
            free(S);
            return current;
        }

        // Obtener la lista de nodos adyacentes al nodo actual
        List* adj_nodes = get_adj_nodes(current);
        Node* adj_node;

        // Agregar los nodos adyacentes a la pila
        while ((adj_node = front(adj_nodes)) != NULL) {
            push(S, adj_node);
            popFront(adj_nodes); // Eliminar el nodo de la lista (se traspasó al stack)
        }

        // Liberar la memoria usada por el nodo actual
        free(current);

        // Liberar la memoria de la lista de nodos adyacentes
        clean(adj_nodes);
    }

    // Si no se encontró una solución, liberar la memoria de la pila y retornar NULL
    free(S);
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