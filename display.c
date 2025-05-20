#include "main.h"

int display(hash_t *head)
{ 
    printf("[Index]\tWord\tFile count\tFile name\twordcount\n");
    //for loop to run till last of hash table
    for(int i = 0 ; i < 28 ; i++)	
    {
	//to check if the index contain any data
	if(head[i].link != NULL)	
	{
	    print(head[i].link);
	}
    }
    return SUCCESS;
}
int print(main_t * head)
{
    //loop for traversing main node
    while(head != NULL)		
    {
	printf(" [%d]\t%s\t %d\t", tolower((head) -> word[0]) - 97, (head) -> word , (head) -> file_count);
	sub_t *temp1 = head -> slink;
	//Loop for traversing sub node
	while(temp1)		
	{
	    //to print the filename and the word count
	    printf("\t%s\t %d\t", temp1 -> filename , temp1 -> word_count);
	    temp1 = temp1 -> sublink;
	}
	head = head -> mlink;
	printf("\n");
    }
    return SUCCESS;
}

