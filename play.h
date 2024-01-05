#ifndef PROJECT_PLAY_H
#define PROJECT_PLAY_H

//this is our binary tree node that includes data(questions or answers) and two pointers to other two nodes
typedef struct tree
{
    char *data;
    struct tree *right;
    struct tree *left;
}tree;

//this function create new node in the binary tree
tree* newNode(const char* data)
{
    //we allocate memory for the node
    tree* newNode = (tree*)malloc(sizeof(tree));

    //strdup is used to copy the data and return a pointer to the copied data
    newNode->data = strdup(data);

    newNode->left = newNode->right = NULL;

    return newNode;
}

//this function gets the text from the countries file and convert it to a binary tree
tree* deserialize(FILE* fp)
{
    char buffer[100];

    // the format specifier %[^\,]%*c is used with the fscanf function to read a string that can contain spaces or any character until a comma (',') character is encountered.
    if (fscanf(fp,"%[^,]%*c",buffer))
    {
        //strcmp function compare two strings and return 0 if they are the same and 1 if not
        //using recursive function to  deserialize smaller sub-trees until we reach the leaf then we return NULL
        if (!(strcmp(buffer, "-1")))
        {
            return NULL;
        }
        tree* root = newNode(buffer);
        root->left = deserialize(fp);
        root->right = deserialize(fp);

        //returns the root node since we will need to use it later
        return root;
    }
    return NULL;
}

//this function is used to start the game
tree* play(tree* root)
{
    char choice;
    tree * current=root;

    printf("____________________________________________________________________________________________\n");

    //this loop iterate over the tree till it finds a leaf
    while(current->left!=NULL&&current->right!=NULL)
    {
        printf("%s(y/n)\n",current->data);
        fflush(stdin);
        k:
        scanf(" %c",&choice);
        fflush(stdin);

        if(choice=='y'||choice=='Y')
        {
            current = current->left;
        }
        else if(choice=='n'||choice=='N')
        {
            current = current->right;
        }
        else
        {
            //if the input is invalid we go back to the scanf part
            printf("Invalid input!\nPlease try again.\n");
            goto k;
        }
    }
    printf("Your answer is %s.\n",current->data);
    return current;

}

//this function is to free up all the allocated pointers in the memory in the program and it works in recursion
void cleanUp(tree* root)
{
    //this is the base case
    if (root==NULL)
    {
        return;
    }

    cleanUp(root->left);
    cleanUp(root->right);

    free(root->data);
    free(root);
}

#endif //PROJECT_PLAY_H