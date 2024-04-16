#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#define node struct Node

static int counter = 0;

struct Node
{
    char* key;
    int value;
    node* left;
    node* right;
};


double wtime()
{
 struct timeval t;
 gettimeofday(&t, NULL);
 return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
 return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}


node* Create_Node(char* key, int value)
{
    node* new_node = (node*)malloc(sizeof(node));

    if (new_node != NULL)
    {
        new_node->key = key;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

void add(node* tree, char* key, int value)
{
    
    node* parrent = NULL;
    while(tree != NULL)
    {
        parrent = tree;

        if(strcmp(key, tree->key) < 0)
            tree = tree->left;
        

        else if(strcmp(key, tree->key) > 0)
            tree = tree->right;

        else
        {
            counter++;
            return;
        }
    }
    

    node* new_node = Create_Node(key, value);
    
    if(strcmp(key, parrent->key) > 0)
        parrent->right = new_node; 

    else
        parrent->left = new_node;


}

node* LookUp(node* tree, char* key)
{
    while(tree != NULL)
    {
        if(strcmp(key, tree->key) > 0)
            tree = tree->right;
        else if(strcmp(key, tree->key) < 0)
            tree = tree->left;
        return tree;
    }

    return NULL;
}

node* tree_min(node* tree)
{
    while(tree->left != NULL)
    {
        tree = tree->left;
    }

    return tree;
}

node* tree_max(node* tree)
{
    while(tree->right != NULL)
    {
        tree = tree->right;
    }

    return tree;
}


node* successor(node* tree, char* key)
{
    node* successor = NULL;

    while(tree != NULL)
    {
        
        if(strcmp(key, tree->key) > 0)
        {
            tree = tree->right;
        }

        else if(strcmp(key, tree->key) < 0)
        {
            successor = tree;
            tree = tree->left;
        }

        else
        {
            if(tree->right != NULL)
                return tree_min(tree->right);
            return successor;
        }

    }

    return NULL;


}

node* predecessor(node* tree, char* key)
{
    node* predecessor = NULL;

    while(tree != NULL)
    {
        
        if(strcmp(key, tree->key) > 0)
        {
            predecessor = tree;
            tree = tree->right;
        }

        else if(strcmp(key, tree->key) < 0)
        {   
            tree = tree->left;
        }

        else
        {
            if(tree->left != NULL)
                return tree_max(tree->left);
            return predecessor;
        }
    }

    return NULL;
}
void REPLACE_NODE(node* parent, node* current, node* child)
{
    if(parent != NULL)
    {
        if(current->key < parent->key)
        {
            parent->left = child;
        }

        else 
        {
            parent->right = child;
        }
    }
}

node* DELETE(node* tree, node* current,node* parent)
{
    if(current->left != NULL)
    {
        REPLACE_NODE(parent, current, current->right);
        if(parent == NULL)
        {
            tree = current->right;
        }
    }

    else if(current->right != NULL)
    {
        REPLACE_NODE(parent, current, current->left);
        if(parent == NULL)
        {
            tree = current->left;
        }
    }

    else
    {
        node* min = current->right;
        node* minparent = min;

        while(min->left != NULL)
        {
            minparent = min;
            min = min->left;
        }

        REPLACE_NODE(parent, current, min);
        if(parent = NULL)
            tree = min;
        if(current->right != min)
        {
            minparent->left = min->right;
            min->left = current->left;
            min->right = current->right;
        }

        else
        {
            min->left = current->left;
        }

        free(current);
    }

    return tree;

}

node* delete(node* tree, char* key)
{
    node* parent = NULL;
    node* current = tree;
    while(current != NULL && strcmp(key, current->key) != 0)
    {
        parent = current;

        if(strcmp(key, current->key))
        {
            
            current = current->left;
        }

        else
        {
            current = current->right;
        }
    }

    if(current == NULL)
    {
        return tree;
    }

    return DELETE(tree, current, parent);
}

int main()
{

    FILE* file = fopen("unsorted.txt", "r");

    srand(time(0));

    printf("Enter count of words: ");

    int count;

    scanf("%d", &count);

    char** words = (char**)malloc(sizeof(char*) * (count + 1));


    words[count] = '\0';

    for(int i = 0; i < count; i++)
    {
        words[i] = (char*)malloc(sizeof(char) * 32);
    }

    int k = 0;
    int m = 0;

   while ((words[k][m] = fgetc(file)) != EOF && k < count -1) {
        if (words[k][m] == '\n') {
            words[k][m] = '\0';
            k++;
            m = 0;
        }
        else m++;
    }

    fclose(file);

    node* tree = Create_Node(words[0], rand() % 1000);

    for(int i = 1; i < count-1; i++)
    {
        add(tree, words[i], i);
    }

    node* tmp;

    for(int i = 0; i <= 200000; i+=10000)
    {
        double start = wtime();

        tmp = tree_max(tree);

        double end = wtime();

        printf("%lf\n", end - start);
    }

    //printf("%lf\n", end - start);
    
    printf("%d\n", counter);

    return 0;
}