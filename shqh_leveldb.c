#include <leveldb/c.h>
#include "config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shqh_leveldb.h"
#define LEVELDB_NAME "level.db"

void db_find_commands(char *command, void(*action)(char *, char * ,char  *))
{
	leveldb_options_t * options;
	leveldb_readoptions_t *roptions;
	leveldb_t *db;
	size_t res_size;
	char * result,*err=0,*old_res;
	options = leveldb_options_create();
	if(options == 0)
		return;
	db = leveldb_open(options,LEVELDB_NAME,&err);
	leveldb_options_destroy(options);
	if(db == 0) 
	{
#ifdef DEBUG
		printf("%s \n",err);
#endif
		free(err);
		return;
	}
	roptions = leveldb_readoptions_create();
	if(roptions == 0)
	{
		leveldb_close(db);
		return;
	}
	result = leveldb_get(db,roptions,command,strlen(command), &res_size,&err);
	leveldb_readoptions_destroy(roptions);
	if(result == 0)
	{
		free(err);
		leveldb_close(db);
		return;
	}
	old_res = result;
	result = strndup(result,res_size);
	char * cur=strtok(result,":");
	do
	{
		action(command,cur,strtok(0,"\n"));
	}
	while((cur =strtok(0,":"))!= 0);
	free(result);
	free(old_res);
	leveldb_close(db);

}

void db_add_command(char *command, char * command_line, char * description)
{
	char * result, *err=0;
	size_t res_size;
	leveldb_options_t * options;
	leveldb_t *db;
	leveldb_writeoptions_t *woptions;
	leveldb_readoptions_t *roptions;

	options = leveldb_options_create();
	if(options == 0)
		return;
	leveldb_options_set_create_if_missing(options, 1);
	db = leveldb_open(options,LEVELDB_NAME,&err);
	leveldb_options_destroy(options);
	if(db == 0)
	{
		free(err);
		return;
	}
	roptions = leveldb_readoptions_create();
	if(roptions == 0)
	{
		leveldb_close(db);
		return;
	}
	result = leveldb_get(db,roptions,command,strlen(command), &res_size,&err);
	leveldb_readoptions_destroy(roptions);
	int new_size = strlen(command_line) + strlen(description) + 4;
	if(result == 0)
	{
		free(err);
		result=malloc(new_size);
		if(result == 0)
		{ 
			leveldb_close(db);
			return;
		}
		result[0]=0;
	} else {
		char * ck=realloc(result,res_size+new_size+2);
		if(ck == 0)
		{
			free(result);
			leveldb_close(db);
			return;
		}
		result =ck;
		result[res_size]='\n';
		result[res_size+1]=0;
	}
	strcat(result,command_line);
	strcat(result,":");
	strcat(result,description);

	woptions = leveldb_writeoptions_create();
	if(woptions == 0)
	{
		leveldb_close(db);
		return;
	}
	leveldb_put(db,woptions,command,strlen(command),result,strlen(result),&err);
	leveldb_writeoptions_destroy(woptions);
	free(err);
	free(result);
	leveldb_close(db);
}



