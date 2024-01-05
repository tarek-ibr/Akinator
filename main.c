#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "play.h"
#include "learn.h"

int main()
{
    char choice;

    printf("\t\t\t\t welcome to Country guessing game \n");

    //we open the file to get the data
    FILE *fp=fopen("countries.txt","r");
    struct tree* root=deserialize(fp);
    //we close the file
    fclose(fp);

    //we call the play function to start the game
    tree* current;

    beginning:

    //if he wants to play again we go back to the beginning of the function
    current=play(root);

    printf("Is it right?(y/n)\n");
    confirming_country:
    scanf(" %c",&choice);
    fflush(stdin);

    if(choice=='y'||choice=='Y')
    {
        printf("Thank you for playing.\n");
    }
    else if(choice=='n'||choice=='N')
    {
        //we call the learn function to add a new country with its question
        learn(current, root);
    }
    else
    {
        //if the input is invalid we go back to the scanf part
        printf("Invalid input!\nPlease try again.\n");
        goto confirming_country;
    }

    printf("Do you want to play again?(y/n)\n");
    playing_again:
    scanf("%c",&choice);
    fflush(stdin);
    if(choice=='y'||choice=='Y')
    {
        //we get the binary tree from the countries text file
        FILE *fp=fopen("countries.txt","r");
        root= deserialize(fp);
        fclose(fp);
        goto beginning;
    }
    else if(choice=='n'||choice=='N')
    {
        printf("Hope you enjoyed the game.");
    }
    else
    {
        //if the input is invalid we go back to the scanf part
        printf("Invalid input!\nPlease try again.\n");
        goto playing_again;
    }

    //we call the cleanup function to free up the allocated memory
    cleanUp(root);

    return 0;
}
