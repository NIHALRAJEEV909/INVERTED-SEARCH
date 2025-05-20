#include "main.h"

int search( hash_t *head,char *word)
{
    //to find the index to be searched
    int i = tolower(word[0]) - 97;
    //to check whether the index is empty or not    
    if(head[i].link == NULL)	
    {
	printf("searching is not possible,list empty\n");
	return FAILURE;
    }
    //to create the mainnode pointer
    main_t *temp1 = head[i].link;
    while(temp1)
    {
	//to check if the word is present
	if(!strcmp((temp1) -> word , word))
	{
	      printf("Word %s found at %dth index and in %d files \n" , word,i , (temp1) -> file_count);
	      //to create the subnode pointer
	      sub_t *temp2 = (temp1) -> slink;	
	      while(temp2)
	      {
		  printf("In file : %s  %d time \n" , (temp2) -> filename , temp2 -> word_count);
		  temp2 = (temp2) -> sublink;
	      }
	      return 1;
	}
	temp1 = temp1 -> mlink;
    }
    printf("Search word is not present\n");
}

