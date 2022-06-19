#include<stdio.h>
#include"sparse.h"
#include<stdlib.h>


int main(){
    sparse m1,m2;
    sparse* m3;
    init(&m1,"matrix1.txt");
    init(&m2,"matrix2.txt");
    printf("\n\n");
    m3=sparseadd(&m1,&m2);
    printmat(m3);
    printf("\n\n");
    multimatrices(&m1,&m2);
   

}