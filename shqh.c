#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "shqh_leveldb.h"
#include "shqh_file.h"
#include "shqh_file.h"

void command_printer(char * command,char * command_line,char * description)
{
	printf("%-40s: %s\n",command_line,description);
}

int main(int argc, char **argv )
{
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

