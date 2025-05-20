#include "main.h"

int update(hash_t hashtable[],file_node **bkhead,file_node **head)
{
    for(int c = 0 ; c <= 27 ; c++)
    {
	if(hashtable[c].link != NULL)
	{
	    printf("ERROR: Database is not empty . Can't update\n");
	    return FAILURE;
	}
    }
    char backup[200];
    printf("Enter the file to be updated in database: ");
    scanf("%s", backup);
    char char1,char2;
    //to validate part and txt and #
    if(strchr(backup, '.') == NULL) 
    {
	printf("ERROR: Please pass extension along with filename for %s\n", backup);
	return FAILURE;
    }
    else
    {
	if(strcmp(strstr(backup, "."),".txt")  != 0)
	{
	    printf("ERROR! Please pass file name with correct extension for %s Usage: file.txt\n", backup);
	    return FAILURE;	
	}
	else
	{
	    FILE *back_fptr = fopen(backup, "r");
	    fscanf(back_fptr,"%c", &char1);
	    fseek(back_fptr, -2, SEEK_END);
	    fscanf(back_fptr,"%c", &char2);
	    fseek(back_fptr, 0, SEEK_SET);
	    if(char1 == '#' && char2 == '#')
	    {
		char str[200];
		int index;
		//to read each line in backup file
		while(fscanf(back_fptr,"%s",str) != EOF)
		{
		    index = atoi(strtok(str + 1,";"));
		    if(hashtable[index].link == NULL)
		    {
			//to create mainnode
			main_t *mnew = malloc(sizeof(main_t));
			if(mnew == NULL)
			{
			    printf("ERROR: No space for dynamic memory allocation of mainnode\n");
			    return FAILURE;
			}
			//to update value
			strcpy(mnew -> word,strtok(NULL,";"));
			mnew -> file_count = atoi(strtok(NULL,";"));
			mnew -> mlink = NULL;
			for(int i = 1 ; i <= mnew -> file_count ; i++)
			{
			    //to create subnode
			    sub_t *snew = malloc(sizeof(sub_t));
			    if(snew == NULL)
			    {
				printf("ERROR: No space for dynamic memory allocation of subnode\n");
				return FAILURE;
			    }
			    sub_t * sptr;
			    sub_t *sprev = sptr;
			    sptr = snew;
			    strcpy(snew -> filename,strtok(NULL,";"));
			    if(duplicate(*bkhead, snew -> filename) == SUCCESS)
			    {
				insert_last(bkhead,snew -> filename);
			    }
			    //to create backup list
			    snew -> word_count = atoi(strtok(NULL,";"));
			    snew -> sublink = NULL;
			    if(i == 1)
			    {
				mnew -> slink = snew;
			    }
			    else
			    {
				sprev -> sublink = snew;
			    }
			}
			hashtable[index].link = mnew;
		    }
		    else
		    {
			//temp pointer to point main node
			main_t *main = hashtable[index].link;
			main_t *mprev = NULL;
			//to traverse through the main 
			while(main != NULL)
			{
			    mprev = main;
			    main = main -> mlink;
			}
			//to create mainnode
			main_t *mnew = malloc(sizeof(main_t));
			if(mnew == NULL)
			{
			    printf("ERROR: No space for dynamic memory allocation of mainnode\n");
			    return FAILURE;
			}
			//to update values
			strcpy(mnew -> word,strtok(NULL,";"));
			mnew -> file_count = atoi(strtok(NULL,";"));
			mnew -> mlink = NULL;
			for(int i = 1 ; i <= mnew -> file_count ; i++)
			{
			    //to create subnode
			    sub_t *snew = malloc(sizeof(sub_t));
			    if(snew == NULL)
			    {
				printf("ERROR: No space for dynamic memory allocation of subnode\n");
				return FAILURE;
			    }
			    sub_t *sptr;
			    sub_t *sprev = sptr;
			    sptr = snew;
			    strcpy(snew -> filename,strtok(NULL,";"));
			    if(duplicate(*bkhead, snew -> filename) == SUCCESS)
			    {
				insert_last(bkhead,snew -> filename);
			    }//to create backup list
			    snew -> word_count = atoi(strtok(NULL,";"));
			    snew -> sublink = NULL;
			    if(i == 1)
			    {
				mnew -> slink = snew;
			    }
			    else
			    {
				sprev -> sublink = sptr;
			    }
			}
			mprev -> mlink = mnew;
		    }
		}
		//to remove updated filenames of list
		file_node *temp1 = *head;
		file_node *prev = NULL;
		file_node *flist = *head;
		while(temp1 != NULL)
		{
		    file_node *temp2  = *bkhead;
		    int found = 0;
		    while(temp2 != NULL)
		    {
			if(strcmp(temp1 -> filename,temp2 -> filename) == 0)
			{
			    found = 1;
			    break;
			}
			temp2 = temp2 -> link;
		    }
		    if(found)
		    {
			if(prev == NULL)
			{
			    *head = (*head) -> link;
			    free(temp1);
			    temp1 = *head;
			}
			else
			{
			    prev -> link = temp1 -> link;
			    free(temp1);
			    temp1 = prev -> link;
			}
		    }
		    else
		    {
			prev = temp1;
			temp1 = temp1 -> link;
		    }
		}
	    }
	    else
	    {
		printf("ERROR: Please pass a correct backup file\n");
		return FAILURE;
	    }
	}
    }
}

//to insert at the last
int insert_last(file_node **head, char* argv)
{
    //to create the new node
    file_node *new = malloc(sizeof(file_node)); 
    //to check whether the memory is allocated or not
    if(new == NULL)
    {
	return FAILURE;
    }
    //to assign the data
    strcpy(new -> filename, argv);
    new -> link = NULL;
    //to check list empty or not 
    if(*head == NULL)
    {
	//head will be updated with new
	*head = new;
	return SUCCESS;
    }
    //to create the pointer
    file_node *temp1 = *head; 
    //to traverse to the last
    while(temp1 -> link != NULL)
    {
	temp1 = temp1 -> link;
    }
    //to assign new to the last
    temp1 -> link = new;
    return SUCCESS;
}

//to check for duplicates
int duplicate(file_node *head, char* argv)
{
    file_node *temp1 = head;
    //to travers
    while(temp1 != NULL)
    {
	if(strcmp(temp1 -> filename,argv) == 0)
	{
	    return FAILURE;
	}
	temp1 = temp1 -> link;
    }
    return SUCCESS;
}


