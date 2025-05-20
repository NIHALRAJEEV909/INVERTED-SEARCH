#include "main.h"

char *fname;
int create_database(file_node *head, hash_t *hashtable)
{
    if(head == NULL)
    {
	printf("ERROR: Database is already created\n");
	return FAILURE;
    }

    //while loop to access files linkedlist
    while(head)
    {
	if(read_file(head ,hashtable,head -> filename) == SUCCESS)
	{
	    //to store next file address to head
	    head = head -> link;		
	}
	else
	{
	    return FAILURE;
	}
    }
    return SUCCESS;

}
int read_file(file_node *file, hash_t *head, char *filename)
{
    fname = filename;
    char word[100];
    int flag1 = 1, index;
    //to open file in the reading mode
    FILE *fptr = fopen(filename, "r");
    //while loop to access word
    while(fscanf(fptr,"%s",word) != EOF)   
    {
	//to find index of alphabet
	if(isalpha(word[0]))
		{
		    index = tolower(word[0] - 97); 
		}
	//index is 27 if it is digit
	else if(isdigit(word[0]))
	{	    
	    index = 27;
	}
	//index is 26 if its aspecial chara
	else
	{
	    index = 26;	
	}	    
	if(head[index].link != NULL)
	{
	    main_t *temp1 = head[index].link;
	    while(temp1)
	    {
		//to compare the words
		if(strcmp(temp1 -> word,word)== 0)	
		{
		    //fun call to update the word count
		    update_word_count(&temp1,filename );
		    flag1 = 0;
		    break;
		}
		temp1 = temp1 -> mlink;

	    }

	}
	if(flag1 == 1)
	{
	    //fun call to create the main node if words are not present
	    create_main_node(&head[index],word);    
	}   
    }
    return SUCCESS;
}

int create_main_node( hash_t *head,char *data)  
{ 
    //to create a new main node
    main_t *new = malloc(sizeof(main_t));
    //to check whether the memory is allocated or not
    if(new == NULL)
    {
	return FAILURE;
    }
    new -> file_count = 1;
    strcpy(new -> word, data);
    new -> slink = NULL;
    new -> mlink = NULL;
    //fun call to create main node
    create_subnode(&new);  
    //if hashtable is empty 
    if(head -> link == NULL)
    {
	//head will be updated with new node
	head -> link = new;
	return SUCCESS;
    }
    else
    {
	main_t *temp1 = head->link;
	//while loop to traverse
	while( temp1 -> mlink != NULL)	
	{
	    temp1 = (temp1) -> mlink;
	}
	(temp1) -> mlink = new;
	return SUCCESS;

    }

}

//fun to create sub node
int create_subnode( main_t **head)		
{   
    //to create new sub node
    sub_t *Snew = malloc(sizeof(sub_t));
    //to check whether the memory is allocated or not
    if(Snew == NULL)
    {
	return FAILURE;
    }
    Snew -> word_count = 1;
    strcpy(Snew -> filename ,fname);
    Snew -> sublink = NULL;
    (*head) -> slink = Snew;
    return SUCCESS; 
}

int update_word_count(main_t **head, char * filename)
{
    sub_t *temp = (*head) -> slink;
    while(temp)
    {
	//to compare the file name are same or not
	if(strcmp(temp -> filename,filename)== 0)	
	{
	    //to increment the word count
	    (temp -> word_count)++;
	    return 1;
	}
	temp = temp -> sublink;
    }
    temp = (*head) -> slink;
    while(temp -> sublink)
    {
	temp = temp -> sublink;
    }
    //to create the new sub node
    sub_t *new = malloc(sizeof(sub_t));
    new -> sublink = NULL;
    strcpy(new -> filename,filename);
    temp -> sublink = new;
    //to increment the filecount
    ((*head) -> file_count)++;
    return 1;

}

