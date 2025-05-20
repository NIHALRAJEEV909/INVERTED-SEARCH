#include "main.h"

int save(hash_t *head)
{
    char *fname;
    //to print the message
    printf("Enter the file name\n");
    //to read the filename from the user
    scanf("%s",fname);		
    if(strcmp(strstr(fname,"."),".txt") == 0)
    {
	//to open file in write mode
    	FILE *fptr = fopen(fname, "w");  
	if(fptr == NULL)
	{
	    printf("ERROR:FILE FAILED TO OPEN\n");
	    return  FAILURE;
	}
	for( int i = 0 ; i < 28 ; i++ )
	{
	    //to check whether the index contain any element
	    if(head[i].link != NULL)	
	    {
		//temp pointer that pointing mainnode
		main_t *temp1 = head[i].link;
		//to traverse through the mainnode
		while(temp1)		
		{
		    fprintf( fptr,"#%d;%s;%d;", i, (temp1) -> word , (temp1) -> file_count);
		    sub_t *temp2 = temp1 -> slink;
		    //to traverse through the subnode
		    while(temp2)		
		    {
			fprintf(fptr,"%s;%d;", temp2 -> filename , temp2 -> word_count);
			temp2 = temp2 -> sublink;
		    }
		    fprintf(fptr,"#\n");
		    temp1 = temp1 -> mlink;
		}
	    }
	}
	return SUCCESS;
    }
    else
    {
	printf("ERROR: please pass filename with correct extension for %s usage :file.txt\n",fname);
	return FAILURE;
    }
}
