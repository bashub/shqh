#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#define DICTIONARY_FILE "dictionary"


struct command_example 
{
	char command_line[1024];
	char description[1024];
};

void command_printer(struct command_example * example)
{
	printf("%-40s: %s\n",example->command_line,example->description);
}

void find_commands(char * command,void (*action)(struct command_example *))
{
	char buffer[1024];
	struct command_example comm_ex;
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
			sscanf(buffer,"\t%1024[^:]:%1024[^\n]\n",comm_ex.command_line,comm_ex.description);
			action(&comm_ex);
			ok =1;
		}
	}
	printf("no match found for %s \n",command);

}


int main(int argc, char **argv )
{
	if(argc != 2)
	{
		printf("provide the name of an executable as argument\n");
		exit(1);
	}
	char *ex = argv[1];
	find_commands(ex,command_printer);
	return 0;
}

