#ifndef SHDH_LEVELDB_H
#define SHDH_LEVELDB_H

void db_find_commands(char *command, void(*action)(char *, char * ,char*),char ** search,int search_size);

void db_add_command(char *command, char * command_line, char * description);

#endif
