#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "config.h"
#include "shqh_leveldb.h"
#include "shqh_file.h"
#include "shqh_file.h"

void command_printer(char * command,char * command_line,char * description)
{
	printf("%-40s: %s\n",command_line,description);
}
struct option options [] = {
	{"help", no_argument, 0,'h'},
	{"online-dic", no_argument, 0,'O'},
	{"offline", no_argument, 0,'o'},
	{"dictionary", required_argument, 0,'d'},
	{0, 0, 0, 0},
};


void usage(char * pn)
{
	printf("Search examples for a specifed command \n");
	printf("Usage Example: \n");
	printf("\t\t%s tar \n",pn);
	printf("\nOptions \n");
	printf("\t-h,--help\t\t\tshow this help \n");
	printf("\t-O,--oneline-dict\t\tlookup for examples also on an online dictionary \n");
	printf("\t-o,--offline\t\t\tuse only offline dictionary \n");
	printf("\t-d,--dictionary dictionary\tspecify the dictionary to use \n");
	printf("\n\n");
}

int main(int argc, char **argv )
{
	int offline=0;
	char * dictionary=0;
	int opt;
	int opt_indx;
	while((opt = getopt_long(argc,argv,"?hOod:",options,&opt_indx))!= -1)
	{
		switch(opt)
		{
			//case '?':
			case 'h':
				usage(argv[0]);
				exit(1);
			case 'O':
				offline=0;
				break;
			case 'o':
				offline=1;
				break;
			case 'd':
				dictionary=optarg;
				break;
		}
	}
	if( argc -optind != 1)
	{
		printf("provide the name of an executable as argument\n");
		exit(1);
	}
	char *ex = argv[optind];
	file_find_commands(ex,command_printer);
	db_find_commands(ex,command_printer);
	return 0;
}

