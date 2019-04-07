// Implements a dictionary's functionality

#include <stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

#include "dictionary.h"
typedef struct node
{
    char word[46];
    struct node *next;
}node;
node *buck[26][45];
int y[45];





// Returns true if word is in dictionary else false
bool check( char *word1)
{
    int c;

    int k=strlen(word1);
    for(int i=0;i<k;i++)
    {
        if isalpha(word1[i])
        {
            if isupper(word1[i])
            {
                word1[i]=tolower(word1[i]);
            }
        }

    }

    //used this loop to convert the word into lowercase

    // used to check th word
    int v=(int)word1[0]-97;

    node *cursor=buck[v][k];
    while(cursor!=NULL)
    {
        c=strcmp(cursor->word,word1);
        if(c==0)
        {
            return true;
        }
        cursor=cursor->next;
    }
    return false;
}
//buck=bucket
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file=fopen(dictionary,"r");
    char phrase[46];
    int x;
    for(int a=0;a<45;a++)
    {
    y[a]=a;
    }
    for(int j=0;j<45;j++)
    {
        for(int i=0;i<26;i++)
        {
            buck[i][j]=NULL;
        }
    }
    while (fscanf(file,"%s",phrase)!=EOF)
    {
        node *newword=malloc(sizeof(node));
        x=strlen(phrase);
        if(newword==NULL)
        {
            return false;
        }
        for(int j=0;j<45;j++)
        {
            if(x==y[j])
            {
                for(int i=0;i<26;i++)
                {
                    if(((int)(phrase[0]))==97+i)
                    {
                        strcpy(newword->word,phrase);
                        newword->next=buck[i][j];
                        buck[i][j]=newword;

                    }

                }
                j=46;
            }
        }

    }


    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int c=0;
    for(int j=0;j<45;j++)
    {
        for(int i=0;i<26;i++)
        {
            node *cursor=buck[i][j];
            while(cursor!=NULL)
            {
               c++;
               cursor=cursor->next;
            }
        }
    }
    return c;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node*cursor=NULL;
    for(int j=0;j<45;j++)
    {
        for(int i=0;i<26;i++)
        {
            cursor=buck[i][j];
            while(cursor!=NULL)
            {
                node *tmp=cursor;
                cursor=cursor->next;
                free(tmp);
            }
        }
    }
    return true;
}
