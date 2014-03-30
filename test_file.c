#include <check.h>
#include "shqh_file.h"
#include <stdio.h>
#include <stdlib.h>

int found = 0;
void command_found_handler(char * c,char *cl,char *d)
{
	if(strstr(cl,c) != 0)
		found = 1;
}

START_TEST(test_file_read)
{
	printf("start");
	file_find_commands("tar",command_found_handler);
	ck_assert_msg(found == 1,"fail to find entry in leveldb");
}
END_TEST

Suite * file_suite (void)
{
	Suite *s = suite_create ("file");
	TCase *tc_core = tcase_create ("read");
	tcase_add_test (tc_core, test_file_read);
	suite_add_tcase (s, tc_core);
	return s;
}

int main()
{
	printf("main");
	int number_failed;
	Suite *s = file_suite ();
	SRunner *sr = srunner_create (s);
	srunner_run_all (sr, CK_NORMAL);
	number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}


