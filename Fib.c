#include <stdio.h>

int main() {
   int i, next;
   int t1 = 1;
   int t2 = 1;
   
   printf("Fibonacci Series: ");
 
   for (i = 1; i <= 10; i++){
      printf("%d ", t1);
      next = t1 + t2;
      t1 = t2;
      t2 = next;
   }

   return 0;
}
