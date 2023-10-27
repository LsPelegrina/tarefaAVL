#include <stdio.h>
#include "bst.c" // mudanca

int main () { // mudanca na adicao de nos na arvore
  Tree t = createTree();
  link x;
  AVLinsert(t, 40);
  AVLinsert(t, 10);
  AVLinsert(t, 30);
  AVLinsert(t, 20);
  AVLinsert(t, 90);
  AVLinsert(t, 80);
  AVLinsert(t, 70);
  AVLinsert(t, 100);
  AVLinsert(t, 25);
  AVLinsert(t, 90);
  AVLinsert(t, 90);
  imprime(t, "oi");

  return 0;
}
