#ifndef PROJECT_LEARN_H
#define PROJECT_LEARN_H

//this function puts the binary tree in a countries file using pre-order traversal
void serialize(tree* root, FILE* fp)
{
    if (root == NULL)
    {
        fprintf(fp, "-1,");
        return;
    }
    fprintf(fp, "%s,", root->data);

    //in the recursion we first sent the left node to the function since we used pre-order traversal
    serialize(root->left, fp);
    serialize(root->right, fp);
}

//this function is used to add new country if the game couldn't guess it
void learn(tree* current,tree* root)
{
    char country[100];
    char question[100];

    printf("Enter the right country.\n");
    gets(country);
    //the fflush is used to clear the stdin buffer
    fflush(stdin);
    printf("Enter the question you would like to be asked for your country.\n");
    gets(question);

    //here we will add the new country
    current->right= newNode(current->data);
    current->data=question;
    current->left= newNode(country);

    //here we serialized the new binary tree in the countries text file
    FILE *fp=fopen("countries.txt","w");
    serialize(root,fp);
    fclose(fp);
}

#endif //PROJECT_LEARN_H