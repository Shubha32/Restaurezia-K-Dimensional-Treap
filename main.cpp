#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<stdio.h>
#include<fstream>

using namespace std;
 typedef struct Kd_Treap_node
 {
     char key[20];
     int priority;
     struct Kd_Treap_node* left;
     struct Kd_Treap_node* right;
     struct Kd_Treap_node* next_dim;
     char filename[200];
 }node;

 node* get_node(char key[20])
 {
     node* temp = new node;
     strcpy(temp->key,key);
     temp->priority =rand()%50;
     temp->left = temp->right = NULL;
     temp->next_dim = NULL;
     strcpy(temp->filename,"NULL");
     return temp;
 }

 node* right_rotate(node* a )
 {
     node* b = a->left;
     node* temp = b->right;
     b->right = a;
     a->left = temp;
     return b;

 }

 node* left_rotate(node* a)
 {
    node* b = a->right;
    node* temp = b->left;
    b->left = a;
    a->right = temp;
    return b;

 }
 node* insert_node(node*,char key[][20],int,int,char*);
 node* insert_value(node* root,char key[][20],int dim,char rest[20])
 {
     int i;
     node* ptr = root;
     node* q = NULL;
     bool flag = 0;
     int tem_co = 0;
     for(i = 0;i<dim;i++)
     {

        flag = 0;
        while(ptr != NULL)
        {
            if(strcmp(ptr->key,key[i])==0)
            {

                flag = 1;
                break;
            }
            else if(strcmp(ptr->key,key[i])<0)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        if(flag)
        {
            tem_co++;
            q = ptr;
            ptr = ptr->next_dim;

        }
        else
            break;

     }
     if(tem_co == 0)
     {
         root = insert_node(root,key,0,dim,rest);
     }
     else if(tem_co==dim)
     {
         cout<<"here";
         char file[200];
         ofstream f;
         strcpy(file,key[0]);
         cout<<file<<endl;
         for(int k=1;k<dim;k++)
         {
             strcat(file,key[k]);
             cout<<file<<endl;
         }
         strcat(file,".txt");
         f.open(file,ios::app);
         f<<rest<<"\n";
         f.close();
     }
     else if(tem_co<dim)
     {
         cout<<tem_co;
         q->next_dim = insert_node(q->next_dim,key,tem_co,dim,rest);
     }
     return root;

 }
 node* insert_node (node* root, char key[][20],int st,int en,char rest[20])
 {
     int i;
     char file[200];
     if(!root)
     {

         node* temp = get_node(key[st]);
          node* ptr = temp;
         for(i = st+1;i<en;i++)
         {
             ptr->next_dim = get_node(key[i]);
             ptr = ptr->next_dim;
             if(i==en-1)
             {
                 ofstream f;
                 strcpy(file,key[0]);
              //   cout<<file<<endl;
                 for(int k=1;k<en;k++)
                {
                    strcat(file,key[k]);
                //    cout<<file<<endl;
                }
                strcat(file,".txt");
                f.open(file,ios::app);
                f<<rest<<"\n";
                f.close();
                strcpy(ptr->filename,file);

             }
         }

         return temp;
     }
     if(strcmp(key[st],root->key)<0)
     {
         root->left = insert_node(root->left,key,st,en,rest);
         if(root->left->priority > root->priority)
         {
             root = right_rotate(root);
         }

     }
     else
     {
            root->right = insert_node(root->right,key,st,en,rest);
            if(root->right->priority > root->priority)
            {
                root = left_rotate(root);
            }
     }
     return root;
 }

void inorder(node*ptr)
{
    if(ptr==NULL)
        return;
    else
    {
        inorder(ptr->left);

        cout<<ptr->key<<endl;

        inorder(ptr->right);
    }

}

node* bstsearch(node* root,char newkey[20])
{
    node*ptr=root;
    int flag=0;

    while(ptr!=NULL)
    {
        if(strcmp(ptr->key,newkey)==0)
        {
            cout<<"found"<<endl;
            flag=1;
            break;
        }

        else if(strcmp(newkey,ptr->key)<0)
        {
            ptr=ptr->left;
        }

        else
        {
            ptr=ptr->right;
        }
    }

    if(flag)
    {
        return ptr;
    }
}

void inorderkd1treap(node* root)
{
     char res[20];
     if(!root)
        return;
     else
     {
         inorderkd1treap(root->left);

         inorderkd1treap(root->next_dim);

         if(strcmp(root->filename,"NULL")!=0)
         {

                ifstream f;
                f.open(root->filename,ios::in);

                f>>res;
                while(!f.eof())
                {
                    cout<<res<<endl;
                    f>>res;
                }
                f.close();
         }

         inorderkd1treap(root->right);
     }
 }

void search(node* root,char key[][20],int dim1,int dim)
{
     int i;
     node* ptr = root;
     node* q = NULL;
     node*parent=NULL;
     bool flag = 0;
     int tem_co = 0;

     if(dim1==dim)
     {
     for(i=0;i<dim1;i++)
     {

        flag = 0;
        while(ptr != NULL)
        {
            if(strcmp(ptr->key,key[i])==0)
            {

                flag = 1;
                break;
            }
            else if(strcmp(ptr->key,key[i])<0)
            {
                parent=ptr;
                ptr = ptr->right;
            }
            else
            {
                parent=ptr;
                ptr = ptr->left;
            }
        }
        if(flag)
        {
            tem_co++;
            q = ptr;
            ptr = ptr->next_dim;
        }
        else
            break;
     }
     if(tem_co==dim1)
     {
         cout<<"Restaurants Found!"<<endl;
         char file[200];
         char rest[30]={0};
         ifstream f;
         strcpy(file,key[0]);
         for(int k=1;k<dim;k++)
         {
             strcat(file,key[k]);
         }
         strcat(file,".txt");
         cout<<file;

         f.open(file,ios::in);
         if(f)
         {


        f>>rest;
        while(!f.eof())
         {
             cout<<rest<<endl;
             f>>rest;

         }

         f.close();
         }
         else
         {
             cout<<"Error";
         }

     }
     else
     {
         cout<<tem_co;
         char newkey[20];
         cout<<"Not found!"<<endl;
         cout<<"Nearby suggestions for searching : "<<endl;
         inorder(parent);
         cout<<"Enter any one among them : ";
         cin>>newkey;

         node* ptr=parent;
         node* k=bstsearch(parent,newkey);

         if(k->next_dim==NULL)
         {

                 char file[200];
                 char rest[30];

                 ifstream f;
                 strcpy(file,key[0]);
                 for(int k=1;k<dim-1;k++)
                 {
                     strcat(file,key[i]);
                 }
                 strcat(file,newkey);
                 strcat(file,".txt");
                 f.open(file,ios::in);
                 f>>rest;

                 while(!f.eof())
                 {
                     cout<<rest<<endl;
                     f>>rest;
                 }

                 f.close();
         }

         else
         {
             cout<<k->next_dim->key;
             inorderkd1treap(k->next_dim);
         }
     }
     }
    return;
}

node* remove_node(node* ,char*);

node* remove_value(node* root, char key[][20],int st,int en)
{
    node* ptr = root;
    int i;
    if(root == NULL)
    {
        cout<<"Key not found ";
        return root;
    }
    else
    {
        while(ptr)
        {
            if(strcmp(ptr->key,key[st])==0)
            {
                if(!ptr->next_dim && st != en-1)
                {
                    cout<<"key not found";
                    return root;
                }
                else if(st == en-1)
                {
                    root = remove_node(root,key[st]);
                    return root;
                }
                else if(st < en)
                {
                    ptr->next_dim = remove_value(ptr->next_dim,key,st+1,en);
                    if(ptr->next_dim == NULL)
                    {
                        root = remove_node(root,key[st]);
                        return root;
                    }
                    return root;
                }
            }
            else if(strcmp(key[st],ptr->key)<0)
            {
                ptr = ptr->left;
            }
            else
                ptr = ptr->right;
        }
    }
    if(!ptr)
    {
         cout<<"key not found";
         return root;
    }


}
node* remove_node(node*root , char key[20])
{
    if(root == NULL)
        return root;
    else if(strcmp(key,root->key)<0)
    {
        root->left = remove_node(root->left,key);

    }
    else if(strcmp(key,root->key)>0)
        root->right = remove_node(root->right,key);
    else if(root->left == NULL)
    {
        node* temp = root->right;
        delete root;
        root = temp;
    }
    else if(root->right == NULL)
    {
        node* temp = root->left;
        delete root;
        root = temp;

    }
    else if(root->left->priority < root->right->priority)
    {
        root = left_rotate(root);
        root->left = remove_node(root->left,key);

    }
    else
    {
        root = right_rotate(root);
        root->right = remove_node(root->right,key);

    }
    return root;
 }

 void inorder_treap(node* root)
 {
     if(!root)
        return;
     else
     {
         inorder_treap(root->left);
         cout<<root->key<<"(";
         inorder_treap(root->next_dim);
         cout<<"),";

         inorder_treap(root->right);
     }
 }
int main()
{
    char c = 'y';
    char key[50][20]={0};
    char rest[20];
    int dim;
    int i;
    srand(time(NULL));
    node* root = NULL;
    cout<<"enter the no of dimensions";
    cin>>dim;
    while(c == 'y')
    {
        cout<<"enter the key";
        for(i =0;i<dim;i++)
        {
            cin>>key[i];

        }
        cout<<"Enter restaurant :";
        cin>>rest;

        root = insert_value(root,key,dim,rest);
        cout<<"root - ---"<<root->key;
        cout<<"do u want to continue (y/n) ?";
        cin>>c;
    }
    inorder_treap(root);
    int dim1;
    cout<<"Enter no. of dimensions :";
    cin>>dim1;
    cout<<"Enter key to be searched for : ";
    for(i =0;i<dim1;i++)
    {
            cin>>key[i];
    }
    search(root,key,dim1,dim);
    c = 'y';
    while(c == 'y')
    {
        cout<<"enter the key";
        for(i = 0;i<dim ; i++)
        {
            cin>>key[i];
        }
        root = remove_value(root,key,0,dim);
        inorder_treap(root);
        cout<<"do u want to continue (y/n) ??";
        cin>>c;
    }

}
