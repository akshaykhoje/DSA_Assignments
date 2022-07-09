#include<stdio.h>
#include"sparse.h"
#include<stdlib.h>


int main(){
    sparse m1,m2;
    init(&m1,"matrix1.txt");
   /* sparse* m3,*m4;
    init(&m2,"matrix2.txt");
    printmat(&m1);
    printf("\n");
    printmat(&m2);
    printf("\n");
    // m3=sparseadd(&m1,&m2);
    // printmat(m3);
    printf("\n");
    m4=multimatrices(&m1,&m2);*/
    // printmat(&m1);
    sparse* m5;
    m5=transpose(&m1);
    printmat(m5);

   

}