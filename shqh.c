#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"
#include "shqh_leveldb.h"
#include "shqh_file.h"
#include "shqh_file.h"

void command_printer(char * command,char * command_line,char * description)
{
	printf("%-40s: %s\n",command_line,description);
}

void usage(char * pn)
{
	printf("Search examples for a specifed command \n");
	printf("\tUsage Example: \n");
	printf("\t\t%s tar \n",pn);
	printf("\n\tOptions \n");
	printf("\t-h\tshow this help \n");
}

int main(int argc, char **argv )
{
	int opt;
	while((opt = getopt(argc,argv,"?hv"))!= -1)
	{
		switch(opt)
		{
			//case '?':
			case 'h':
				usage(argv[0]);
				exit(1);
		}
	}
	if(argc != 2)
	{
		printf("provide the name of an executable as argument\n");
		exit(1);
	}
	char *ex = argv[1];
	file_find_commands(ex,command_printer);
	db_find_commands(ex,command_printer);
	return 0;
}

