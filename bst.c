#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int id = 0;
link novoNo (int item, link l, link r) {
  link t = malloc(sizeof(struct node));
  t->item = item;
  t->l = l;
  t->r = r;
  t->N = 1;
  t->id = id++;
  return t;
}

Tree createTree(){
  Tree t = malloc (sizeof (struct tree));
  t->z = malloc (sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->N = 0;
  t->z->r = t->z;
  return t;
}

link rotR (Tree t, link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  return x;
}

link rotL (Tree t, link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  return x;
}

link searchR(Tree t, link h, int query) {
  if (h == t->z) {
    return NULL;
  }
  if(h->item == query) 
    return h;
  if (h->item >= query) 
    return searchR(t, h->l, query);
  return searchR(t, h->r, query);
} 

link search (Tree t, int query){
   return searchR(t, t->head, query);
}

link insertR (Tree t, link h, link n) {
  if (h == t->z) {
    return  n;
  }

  if(h->item >= n->item)
    h->l = insertR(t, h->l, n);
  else 
    h->r = insertR(t, h->r, n);
  (h->N)++;
  return h;
}

link insert (Tree t, int item){
  if(t->head == t->z) {
    return (t->head =novoNo(item, t->z, t->z));
  }
  return insertR(t, t->head, novoNo(item, t->z, t->z));
}

void imprimeEmOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimeEmOrdem (t, h->l);
  printf("<chave: %d N: %d>", h->item, h->N); 
  imprimeEmOrdem (t, h->r);
}

void imprimePosOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimePosOrdem (t, h->l);
  imprimePosOrdem (t, h->r);
  printf("<chave: %d N: %d>", h->item, h->N); 
}

void imprimePreOrdem (Tree t, link h, int k) {
  if(h == t->z) return;
  int i; // mudan�a pois n�o compilava
  for(i = 0; i <= k; i++)
    printf (" . ");
  printf("<chave: %d N: %d>\n", h->item, h->N); 
  imprimePreOrdem (t, h->l, k + 1); 
  imprimePreOrdem (t, h->r, k + 1);
}

void printnode (char  *x, int h) {
    int i;
    for(i = 0; i < h; i++)
        printf("\t");
    printf("%s\n", x);
}

int c = 0;
void imprimeR(Tree a, link t){
    char s[255];
    if(t==a->z) { return;}
    imprimeR(a,t->r);
    printf ("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\" ]\n", t->id, t->item, t->N);
    if(t->l != a->z){
        printf("%d:f0->%d:f1;\n", t->id, t->l->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f0->z%d;\n", t->id, c);
        c++;
    }
    if(t->r != a->z){
        printf("%d:f2->%d:f1;\n", t->id, t->r->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f2->z%d;\n", t->id, c );
        c++;
    }
    imprimeR(a,t->l);
}

void imprime(Tree a, char *s) {
    c = 0;
    printf("digraph %s {\n", s);
    printf ("node [shape=record,style=rounded, height=.1]\n");
    imprimeR(a, a->head);
    printf("}\n");
}

void imprimeFromNode(Tree a, link h, char *s) {
  c = 0;
  printf("digraph  {\n" );
  printf ("name [label = \"%s\",shape=plaintext]\n", s);
  printf ("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, h);
  printf("}\n");
}

// NOVA IMPLEMENTACAO -- Inserir recursivamente os novos nós

link AVLinsertR (Tree t, link h, int item){
  if(h == t->z) {
    return novoNo(item, t->z, t->z); // Se o nó for vazio, retorna um novo nó
  }
  
  if(item < h->item) {
    h->l = AVLinsertR(t, h->l, item); //Se o valor for menor, ele irá para esquerda
  } else if(item > h->item) {
    h->r = AVLinsertR(t, h->r, item); //Se o valor for maior, ele irá para direita
  } else {
    return h; // Se o valor já existir na árvore, simplesmente retorna
  }
  
  if(h->l->N > h->r->N) { //Definir a nova contagem de nós, se o numeno de nós da esqueda for maior que o numero de nós da direita
	  h->N = 1 + h->l->N; // Soma o nó atual, mais os nós que tem para esquerda
  } else {
	  h->N = 1 + h->r->N; // Soma o nó atual, mais os nós que tem para direita
  }
  
  int fb = h->l->N - h->r->N; // Fator de balanceamento // altura da esqueda menos a direita
  
  if(fb > 1) { // Caso 1, fator maior que 1 -> desbalanceada para esqueda
	  if(item < h->l->item) { //Se o valor for menor que o que o valor do nó atual, necessario rotação para direita
		  h = rotR(t, h);
	  } else {
		  h->l = rotL(t, h->l); //Se não, é necessario fazer uma rotação dupla rotacao primeiro uma rotação esqueda no nó atual, alinhando os valores
		  h = rotR(t, h); // E posteriormente uma rotação a direita no nó anterior, sendo o novo pai, o novo nó inserido
	  }
  }
  if(fb < -1) { // Caso 2, fator menor que -1 -> desbalanceado para direita
  	if(item > h->r->item) { // Valor maior que o valor do nó a direita
		  h = rotL(t, h); // rotação esquerda
	  } else {
		  h->r = rotR(t, h->r); //Se não, é necessario fazer uma rotação dupla, primeiro para direita no nó atual, alinhando os valores para direita
		  h = rotL(t, h); // Depois, uma rotacao esquerda, no nó anterior, sendo o novo pai, o novo nó inserido
	  }
  }
  
  return h; // retorna a raiz
}

link AVLinsert(Tree t, int item) {
	if(t->head == t->z) { 
		t->head = novoNo(item, t->z, t->z); //Cria novo nó, se a raiz da arvore for vazia
		return t->head;
	} else {
		t->head = AVLinsertR(t, t->head, item); // Caso o nó já exista, chama a função AVLinsert recursivamente, passando como argumento, a arvore, a raiz, e o valor que será inserido
	}
}

