#include "main.h"

int validation(file_node **head, char *argv[])
{
    int i = 1,emty;
    int flag1 = 0;
    while(argv[i] != NULL)
    {
	//to check whether the file .txtx or not
	if(strstr(argv[i],".") != NULL && strcmp(strstr(argv[i],"."),".txt") == 0)
	{
            //fun call to check file empty or not	    
	    emty = FileEpty(argv[i]);
	    if(emty == FILE_NOT_AVAILABLE)
	    {
		printf("File: %s not found\n",argv[i]);
		//incrementing to acess next command line argument
		i++;                             
		continue;
	    }
	    else if(emty == FILE_EMPTY)
	    {
		printf("File: %s is not having any contents\n ",argv[i]);
		//incrementing to access next command line argument
		i++;		
		continue;
	    }
	    else
	    {
		file_node *temp1 = *head;
		file_node *prev = NULL;
		while( temp1 != NULL)
		{
		    //condition to check if its a duplicate file or not
		    if(strcmp(argv[i],temp1 -> filename) == 0)
		    {
			flag1 = 1;
			printf("File: %s repeated\n",argv[i]);
			break;
		    }
		    prev = temp1;
		    temp1 = temp1 -> link;	 
		}
		if(flag1 == 0)
		{
		    file_node *new = malloc(sizeof(file_node));
		    strcpy(new -> filename ,argv[i]);
		    //to check whether the file linkedlidt is empty or not
		    if(*head == NULL) 
		    {
			*head = new;
		        printf("File: %s insertes Successfully into file linked list\n",argv[i]);
		    }
		    else
		    {
		      prev -> link = new;
		      printf("File: %s insertes Successfully into file linked list\n",argv[i]);
		    }
		}
	    }
	}
	//to increment for next command line argument
	i++;	
    }
}
int FileEpty( char *file_name)
{
    //checking file is present or not
    FILE *fptr = fopen(file_name,"r");
    if(fptr == NULL)
    {
	return FILE_NOT_AVAILABLE;
    }
    //checking file is empty or not
    fseek(fptr,0,SEEK_END);
    if(ftell(fptr) == 0)
    {
	return FILE_EMPTY;
    }
}

