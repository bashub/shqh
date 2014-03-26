#include <stdio.h>
#include <stdlib.h>
#include "config.h"

struct command_example 
{
	char * command_line;
	char * description;
};

void command_printer(struct command_example * example)
{
	printf("%-30s: %s\n",example->command_line,example->description);
}

void find_commands(char * command,void (*action)(struct command_example *))
{
	struct command_example examples [] = {
		{"test -xvd something", "Do something"},
		{"test -rst something", "Do something else"},
		{"test -h", "show help"},
	};
	int i;
	for( i = 0 ; i < 3; i++ ) action(&examples[i]);
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

