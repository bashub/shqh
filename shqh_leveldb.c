#include <leveldb/c.h>
#include "config.h"
#include "shqh_leveldb.h"


void db_find_commands(char *command, void(*action)(char *, char * ,char  *))
{
	leveldb_options_t * options;
	leveldb_t *db;

	//leveldb_open();

}



