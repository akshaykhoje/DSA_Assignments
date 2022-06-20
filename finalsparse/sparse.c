#include <stdio.h>
#include <stdlib.h>
#include "sparse.h"
void createmat(sparse **m, node **r, node **c, int rw_n, int cl_n, int data);

void getmatrix(sparse **curr, int r, int c)
{
    sparse *s = *curr;
    s->rw = r;
    s->cl = c;
    s->row = (node **)malloc(sizeof(node *) * (s->rw));
    s->col = (node **)malloc(sizeof(node *) * (s->cl));

    for (int i = 0; i < s->rw; i++)
    {
        s->row[i] = NULL;
    }
    for (int i = 0; i < s->cl; i++)
    {
        s->col[i] = NULL;
    }
}

void init(sparse *s, char *filename)
{

    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Unable to open the file\n");
        return;
    }
    int r, c;
    fscanf(fp, "%d", &r);
    fscanf(fp, "%d", &c);
    getmatrix(&s, r, c);
    /*s->row = (node **)malloc(sizeof(node *) * (s->rw));
    s->col = (node **)malloc(sizeof(node *) * (s->cl));

    for (int i = 0; i < s->rw; i++)
    {
        s->row[i] = NULL;
    }
    for (int i = 0; i < s->cl; i++)
    {
        s->col[i] = NULL;
    }*/
    printf("succesfull initalization:\n");
    // sparse* curr=s;
    node *curr = s->row[0];
    node *docur = s->col[0];
    
    for (int i = 0; i < s->rw; i++)//inserting non-zero values in rows
    {
        curr = s->row[i];
        for (int j = 0; j < s->cl; j++)
        {
            docur = s->col[j];
            int x;
            fscanf(fp, "%d", &x);
            // printf("%d ",x);
            if (x)
            {
                createmat(&s, &curr, &docur, i, j, x);      
            }
        }
        // printf("\n");
    }
    // node *p = NULL;
    // for(int i=0;i<s->rw;i++){
    //     // printf("ith value %d\n",i);
    //     p=s->row[i];
    //     while(p){
    //         printf("%d:%d= %d\n",p->row,p->col,p->value);
    //         p=p->right;
    //     }
    // }
}

void createmat(sparse **m, node **r, node **c, int rw_n, int cl_n, int data)
{
    // formation ofnew matrix
    sparse *m3 = *m;
    node *rm = *r;
    node *cm = *c;
    node *newnode = (node *)malloc(sizeof(node));
    newnode->row = rw_n;
    newnode->col = cl_n;
    newnode->value = data;
    newnode->right = newnode->down = NULL;

    if (rm == NULL)
    {
        m3->row[rw_n] = newnode;     
        rm = m3->row[rw_n];
    }
    else
    {
        while (rm->right != NULL)   //traversing till the end of the row
        {
            rm = rm->right;
        }
        rm->right = newnode;
    }

    // inserting in a column
    if (cm == NULL)
    {
        m3->col[cl_n] = newnode;
        // docur=newnode;
        cm = m3->col[cl_n];
    }
    else
    {
        while (cm->down != NULL)
        {
            cm = cm->down;
        }
        cm->down = newnode;
    }
    *m = m3;
    *r = rm;
    *c = cm;
}

sparse *sparseadd(sparse *m1, sparse *m2)
{
    if (!m1 || !m2)
    {
        printf("error\n");
        return NULL;
    }
    if (m1->rw != m2->rw || m2->cl != m1->cl)
    {
        printf("Invalid matrix addtion\n");
        return NULL;
    }
    // take the one row and perform the addition of the elements
    // then check the column of the matrices if they same then add them if not same then
    // check the jth value of the two matrices which one is the bigger or smaller
    // if the jth value of that matrix is smaller then put this value to the new matrix
    // the function type should be sparse type we have to return the addition of the matrix
    //
    sparse *m3;
    m3 = (sparse *)malloc(sizeof(sparse));
    getmatrix(&m3, m1->rw, m1->cl);
    node *rm;
    node *cm;

    node *p1, *p2, *q1, *q2;
    for (int i = 0; i < m1->rw; i++)     //iterating rows
    {
        p1 = m1->row[i];
        p2 = m2->row[i];
        rm = m3->row[i];
        for (int j = 0; j < m1->cl; j++)       //iterating columns
        {
            int data, rw_n, cl_n;

            cm = m3->col[j];
            if (p1 || p2)
            {
                if (p1 && p2)
                {
                    if (p1->col == p2->col)
                    {
                        data = p1->value + p2->value;
                        rw_n = p1->row;
                        cl_n = p1->col;
                        // printf("%d ", p1->value + p2->value);
                        p1 = p1->right;
                        p2 = p2->right;
                    }
                    else if (p1->col < p2->col)
                    {
                        data = p1->value;
                        rw_n = p1->row;
                        cl_n = p1->col;
                        // printf("%d ", p1->value);
                        p1 = p1->right;
                    }
                    else
                    {
                        data = p2->value;
                        rw_n = p2->row;
                        cl_n = p2->col;
                        // printf("%d ", p2->value);
                        p2 = p2->right;
                    }
                }
                else if (p1)
                {
                    data = p1->value;
                    rw_n = p1->row;
                    cl_n = p1->col;
                    // printf("%d ", p1->value);
                    p1 = p1->right;
                }
                else if (p2)
                {
                    data = p2->value;
                    rw_n = p2->row;
                    cl_n = p2->col;
                    // printf("%d ", p2->value);
                    p2 = p2->right;
                }
                createmat(&m3, &rm, &cm, rw_n, cl_n, data);
            }
        }
    }
    return m3;
}

void printmat(sparse *m)
{
    sparse *curr = m;
    node *p, *q;
    FILE *fp = fopen("Additionmat.txt", "w");
    fprintf(fp, " %d ", curr->rw);
    fprintf(fp, " %d ", curr->cl);
    fprintf(fp, "\n");

    for (int i = 0; i < curr->rw; i++)
    {
        q = curr->row[i];
        for (int j = 0; j < curr->cl; j++)
        {
            // p = curr->col[j];
            if (q)
            {
                // printf("%d",q->value);
                if (q->col != j)
                {
                    fprintf(fp, " %d ", 0);
                    printf(" 0 ");
                }
                else
                {
                    fprintf(fp, " %d ", q->value);

                    printf(" %d ", q->value);
                    q = q->right;
                }
            }
            else
            {
                fprintf(fp, " %d ", 0);

                printf(" 0 ");
            }
        }
        fprintf(fp, "\n");
        printf("\n");
    }
}

// here is the code of the multiplication of matrices ;
// check first the column of first matrix equals to row of second matrix or not
//  sum =sum+a[i][j]*b[j][i] iterate it for number of columns of first matrix
//

sparse *multimatrices(sparse *m1, sparse *m2)
{
    if (!m1 || !m2)
    {
        return NULL;
    }
    sparse *curr1, *curr2;
    curr1 = m1;
    curr2 = m2;
    if (curr1->cl != curr2->rw)
    {
        printf("Invalid matrix multiplication\n");
        return NULL;
    }
    sparse *m3 = (sparse *)malloc(sizeof(sparse));
    getmatrix(&m3, curr1->rw, curr2->cl);
    node *p, *q;
    node *rm;
    node *cm;
    for (int i = 0; i < curr1->rw; i++)
    {
        // p=curr1->row[i];
        rm = m3->row[i];
        for (int j = 0; j < curr2->cl; j++)
        {
            p = curr1->row[i];
            q = curr2->col[j];
            cm = m3->col[j];
            int sum = 0;
            for (int k = 0; k < curr2->rw; k++)
            {
                if (!p || !q)
                {
                    continue;
                }

                int manja = p->col;
                int ganja = q->row;
                if (ganja < manja)
                {
                    q = q->down;
                    continue;
                }
                if (manja < ganja)
                {
                    p = p->right;
                    continue;
                }

                if (p->col == q->row)
                {
                    sum = sum + p->value * q->value;
                    p = p->right;
                    q = q->down;
                }
            }
            // printf("ith %d jth %d %d\n",i,j,sum);
            // printf(" %d ", sum);
            if (sum)
            {
                createmat(&m3, &rm, &cm, i, j, sum);
            }
        }
        // printf("\n");
    }
    // printmat(m3);
    return m3;
}

sparse *transpose(sparse *m1)
{
    if (!m1)
    {
        return NULL;
    }
    int r = m1->rw;
    int c = m1->cl;
    sparse *m3;
    m3 = (sparse *)malloc(sizeof(sparse));
    getmatrix(&m3, c, r);
    node *p, *q;
    node *rm, *cm;
    for (int i = 0; i < r; i++)
    {
        p = m1->row[i];
        if (p)
            rm = m3->col[p->row];
        else
            continue;
        for (int j = 0; j < c; j++)
        {
            if (p)
            {
                cm = m3->row[p->col];
                node *newnode = (node *)malloc(sizeof(node));
                newnode->col = p->row;
                newnode->row = p->col;
                newnode->value = p->value;
                if (!cm)
                {
                    m3->row[p->col] = newnode;
                }
                else
                {
                    while (cm->right != NULL)
                    {
                        cm = cm->right;
                    }
                    cm->right = newnode;
                }

                if (!rm)
                {
                    m3->col[p->row] = newnode;
                }
                else
                {
                    while (rm->down != NULL)
                    {
                        rm = rm->down;
                    }
                    rm->down = newnode;
                }

                p = p->right;
            }
            else
            {
                break;
            }
        }
    }
    return m3;
}