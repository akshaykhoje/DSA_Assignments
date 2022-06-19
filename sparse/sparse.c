#include <stdio.h>
#include <stdlib.h>
#include "sparse.h"

void init(sparse *s, char *filename)
{

    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Unable to open the file\n");
        return;
    }

    fscanf(fp, "%d", &s->rw);
    fscanf(fp, "%d", &s->cl);
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
    printf("succesfull initalization:\n");
    // sparse* curr=s;
    node *curr = s->row[0];
    node *docur = s->col[0];
    for (int i = 0; i < s->rw; i++)
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
                node *newnode = (node *)malloc(sizeof(node));
                newnode->row = i;
                newnode->col = j;
                newnode->value = x;
                newnode->right = newnode->down = NULL;
                if (curr == NULL)
                {
                    s->row[i] = newnode;
                    curr = s->row[i];
                }
                else
                {
                    while (curr->right != NULL)
                    {
                        curr = curr->right;
                    }
                    curr->right = newnode;
                }

                if (docur == NULL)
                {
                    s->col[j] = newnode;
                    // docur=newnode;
                    docur = s->col[j];
                }
                else
                {
                    while (docur->down != NULL)
                    {
                        docur = docur->down;
                    }
                    docur->down = newnode;
                }
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
    m3->cl = m1->cl;
    m3->rw = m1->rw;
    // printf("row value is %d\n", m3->rw);
    // printf("column value is %d\n", m3->cl);

    m3->row = (node **)malloc(sizeof(node *) * m3->rw);
    m3->col = (node **)malloc(sizeof(node *) * m3->cl);

    for (int i = 0; i < m3->rw; i++)
    {
        m3->row[i] = NULL;
    }
    for (int i = 0; i < m3->cl; i++)
    {
        m3->col[i] = NULL;
    }
    node *rm;
    node *cm;

    node *p1, *p2, *q1, *q2;
    for (int i = 0; i < m1->rw; i++)
    {
        p1 = m1->row[i];
        p2 = m2->row[i];
        rm = m3->row[i];
        for (int j = 0; j < m1->cl; j++)
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

                // formation ofnew matrix
                node *newnode = (node *)malloc(sizeof(node));
                newnode->row = rw_n;
                newnode->col = cl_n;
                newnode->value = data;
                newnode->right = newnode->down = NULL;
                if (rm == NULL)
                {
                    m3->row[i] = newnode;
                    rm = m3->row[i];
                }
                else
                {
                    while (rm->right != NULL)
                    {
                        rm = rm->right;
                    }
                    rm->right = newnode;
                }

                if (cm == NULL)
                {
                    m3->col[j] = newnode;
                    // docur=newnode;
                    cm = m3->col[j];
                }
                else
                {
                    while (cm->down != NULL)
                    {
                        cm = cm->down;
                    }
                    cm->down = newnode;
                }
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

void multimatrices(sparse *m1, sparse *m2)
{
    if (!m1 || !m2)
    {
        return;
    }
    sparse *curr1, *curr2;
    curr1 = m1;
    curr2 = m2;
    if (curr1->cl != curr2->rw)
    {
        printf("Invalid matrix multiplication\n");
        return;
    }
    node *p, *q;
    for (int i = 0; i < curr1->rw; i++)
    {
        // p=curr1->row[i];
        for (int j = 0; j < curr2->cl; j++)
        {
            q = curr2->col[j];
            p = curr1->row[i];
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
            printf(" %d ", sum);
        }
        printf("\n");
    }
}