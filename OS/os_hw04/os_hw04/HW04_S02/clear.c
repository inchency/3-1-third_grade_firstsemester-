#include <stdio.h>

void main(int argc, char **argv){
   FILE *c = fopen("Count.txt", "w");
   FILE *r1 = fopen("R1.txt", "w");
   FILE *r2 = fopen("R2.txt", "w");
   FILE *r3 = fopen("R3.txt", "w");

   fprintf(c, "");
   fclose(c);
   fprintf(r1, "1\n");
   fclose(r1);
   fprintf(r2, "1\n");
   fclose(r2);
   fprintf(r3, "1\n");
   fclose(r3);
}

