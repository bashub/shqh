#include "shqh_file.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DICTIONARY_FILE "dictionary"

void file_find_commands(char * command,void (*action)(char * , char *,char *))
{
	char buffer[1024];
	FILE * dict_file = fopen(DICTIONARY_FILE,"r");
	if(dict_file == 0)
	{
		printf("failing to load the dictionary\n");
		exit(1);
	}
	int found = 0;
	int ok =0;
	while(fgets(buffer,1024,dict_file)!=0)
	{
		buffer[strlen(buffer)-1]=0;
		if(found == 0 )
		{
			if( strcmp(buffer,command)==0) found=1;
		}
		else 
		{
			if(buffer[0] != '\t')
				if(ok == 1)
					return;
				else 
					break;
			char * pos = strstr(buffer,":");
			if(pos != 0) {
				(*pos)= 0;
				action(command,buffer +1,pos+1);
				ok =1;
			}
		}
	}
	printf("no match found for %s \n",command);

}

