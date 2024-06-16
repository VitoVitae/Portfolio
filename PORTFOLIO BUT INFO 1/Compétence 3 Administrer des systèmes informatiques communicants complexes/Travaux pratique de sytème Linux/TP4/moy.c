#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
   int val, somme = 0, nb_vals = 0, ret;
   bool fini = false;

   while (fini == false) {
      printf("Entrez une valeur entière strictement positive ou 0 pour terminer : ");
      scanf("%d", &val);
      if (val > 0) {
         somme = somme + val;
         nb_vals = nb_vals + 1;
      } else if (val == 0) {
         fini = true;
      } else {
         fprintf(stderr, "%d est une valeur erronée, recommencez\n", val);
      }
   }
   if (nb_vals > 0) {
      printf("La moyenne vaut %.2f\n", (float)somme / (float)nb_vals);
      ret = EXIT_SUCCESS;
   } else {
      fprintf(stderr, "Impossible de calculer la moyenne !\n");
      ret = EXIT_FAILURE;
   }
   return ret;
}