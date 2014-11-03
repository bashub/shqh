#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "config.h"
#include "shqh_leveldb.h"
#include "shqh_file.h"
#include "shqh_file.h"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"


void command_printer(char * command,char * command_line,char * description)
{
	printf( KBLU "# %s\n"RESET"%s\n\n",description,command_line);
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
	printf("\t-O,--online-dict\t\tlookup for examples also on an online dictionary \n");
	printf("\t-o,--offline\t\t\tuse only offline dictionary \n");
	printf("\t-d,--dictionary=dictionary\tspecify the dictionary to use \n");
	printf("\n\n");
}

int main(int argc, char **argv )
{
	int offline=0;
	char ** searchArgs;
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
	if( argc - optind == 0)
	{
		printf("provide the name of an executable as argument\n");
		exit(1);
	}
	char *ex = argv[optind];
	int searchSize= argc - optind-1;
	searchArgs= argv + optind+1;
	int cur;
	for(cur = 0;cur< searchSize;cur++){
		//printf("%s",searchArgs[cur]);
	}
	file_find_commands(ex,command_printer);
	db_find_commands(ex,command_printer);
	return 0;
}

