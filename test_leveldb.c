#include <check.h>
#include "shqh_leveldb.h"
#include <stdio.h>
#include <stdlib.h>

int found = 0;
void command_found_handler(char * c,char *cl,char *d)
{
	found = 1;
}

START_TEST(test_leveldb_read)
{
	db_add_command("tar","tar -xvf","extract files from the archive");
	db_find_commands("tar",command_found_handler);
	ck_assert_msg(found == 1,"fail to find entry in leveldb");
}
END_TEST

Suite * leveldb_suite (void)
{
	Suite *s = suite_create ("levledb");
	TCase *tc_core = tcase_create ("read");
	tcase_add_test (tc_core, test_leveldb_read);
	suite_add_tcase (s, tc_core);
	return s;
}

int main()
{
	int number_failed;
	Suite *s = leveldb_suite ();
	SRunner *sr = srunner_create (s);
	srunner_run_all (sr, CK_NORMAL);
	number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}


