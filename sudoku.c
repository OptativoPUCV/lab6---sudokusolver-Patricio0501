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
    int i, j, num;

    for (i = 0; i < 9; i++) {
        int row_check[10] = {0};
        int col_check[10] = {0};
        
        for (j = 0; j < 9; j++) {

            num = n->sudo[i][j];
            if (num != 0 && row_check[num] == 1) {
                return 0; 
            }
            row_check[num] = 1;

            num = n->sudo[j][i];
            if (num != 0 && col_check[num] == 1) {
                return 0;
            }
            col_check[num] = 1;
        }
    }

    for (i = 0; i < 9; i += 3) {
        for (j = 0; j < 9; j += 3) {
            int submatrix_check[10] = {0};
            
            for (int x = i; x < i + 3; x++) {
                for (int y = j; y < j + 3; y++) {
                    num = n->sudo[x][y];
                    if (num != 0 && submatrix_check[num] == 1) {
                        return 0;
                    }
                    submatrix_check[num] = 1;
                }
            }
        }
    }

    return 1; 
}



List* get_adj_nodes(Node* n) {
    List* list = createList();
    int i, j;
    
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                int num;
                Node* new_node;
                for (num = 1; num <= 9; num++) {
                    new_node = copy(n); 
                    new_node->sudo[i][j] = num; 
                    if (is_valid(new_node)) {
                        pushBack(list, new_node);
                    } else {
                        free(new_node); 
                    }
                }
                
                return list; 
            }
        }
    }

    return list; 
}

int is_final(Node* n) {
    int i, j;
    
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                return 0;
            }
        }
    }
    
    return 1; 
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