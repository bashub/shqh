#include <check.h>
#include "shqh_file.h"
#include <stdio.h>
#include <stdlib.h>

int found = 0;
int found_count = 0;
void command_found_handler(char * c,char *cl,char *d)
{
	if(strstr(cl,c) != 0)
		found = 1;
}
void command_found_handler_count(char * c,char *cl,char *d)
{
	found_count++;	
}

START_TEST(test_file_read)
{
	printf("start");
	file_find_commands("tar",command_found_handler,0,0);
	ck_assert_msg(found == 1,"fail to find existing entry in the file");
}
END_TEST

START_TEST(test_file_search)
{
	printf("start");
	char * search[2];
	search[0]="compres";
	search[1]="folder";
	file_find_commands("tar",command_found_handler_count,search,2);
	ck_assert_msg(found_count == 1,"fail to find exinsting entry in the file by search");
}
END_TEST

Suite * file_suite (void)
{
	Suite *s = suite_create ("file");
	TCase *tc_core = tcase_create ("read");
	tcase_add_test (tc_core, test_file_read);
	tcase_add_test (tc_core, test_file_search);
	suite_add_tcase (s, tc_core);
	return s;
}

int main()
{
	int number_failed;
	Suite *s = file_suite ();
	SRunner *sr = srunner_create (s);
	srunner_run_all (sr, CK_NORMAL);
	number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}


