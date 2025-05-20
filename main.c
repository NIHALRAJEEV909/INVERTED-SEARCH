#include "main.h"
int main(int argc, char *argv[])
{
    //to declare head pointer
    file_node *head = NULL;
    int count = 0;
    int choice;
    char str[30];
    if(argc == 1)
    {
	printf("ERROR : Please pass the sufficient command line argument, usage:./a.out file.txt \n");
	return 0;
    }
    else
    {
	//fun call to validate
	validation(&head,argv);   
    }

    hash_t hashtable[28];
    //for loop to enter into index of hashtable
    for( int i = 0 ; i < 28 ; i++ )	
    {
	hashtable[i].index = i;
	hashtable[i].link = NULL;
    }

    //to initialize main and backup list pointers
    file_node *backuplist = NULL; 
   
    //to display the menu

    printf("1.Create Database\n2.Display Database\n3.Search word\n4.Save database\n5.Update database\n6.Exit\n");
    while(1)
    {
	printf("Enter the choice\n");
	scanf("%d",&choice);
	switch(choice)
	{		
	    //to create the database using the files in the linkedlist
	    case 1 : if(!count)
		     {
			 if(create_database(head, hashtable)== SUCCESS)
		         {
		     	     count=1;
			     //to print the message if the data base is created
			     printf("INFO: creating database is succesfully done\n");
			 }
			 else
			 {
			     //to print the message if data base is not created
			     printf("ERROR: creaing database is unsuccesfull\n");
			 }
		     
		     }
		     else
		     {
			 //to print the message if data base is already created
			 printf("Database already created\n");
		     }
		     break;
		     //to display database
	    case 2: if(display(hashtable) == FAILURE)	
		    {
			printf("database empty\n");
		    }
		    break;
		    //to search
	    case 3: printf("Enter the word\n");
		    scanf("%s",str);
		    //Search for a word in the database
		    if(search(hashtable, str) == FAILURE)
		    {	
			printf("ERROR : Word not found\n");
		    }
		    break;
		    //to save
	    case 4: if(save(hashtable) == SUCCESS)
		    {
			//to print the message
			printf("INFO:Database saved successfully\n");
		    }
		    else
		    {
			printf("Database saving failed\n");
		    }
		    break;	    
		    //to update the database
	    case 5: if(update(hashtable,&backuplist,&head) != FAILURE)	 
		    {
			//to print the successfull messsge
			printf("INFO:Update success\n");
		    }
		    else
		    {
			printf("ERROR:Update unsuccessful\n");
		    }
		    break;
                    //to exit from the prgm
	    case 6: exit(1); 
		    return SUCCESS;
		    break;
	    default:
		    printf("Invalid choice\n");


	}

    }
}
