/*
Each installer has the same version number as the corresponding CUnit framework.
Thus, CUnit-msvc-2.1-3.exe installs the binary static libraries for CUnit 2.1-3.

The static libraries are provided for "Release" and "Debug" configurations on
platforms "Win32", "x86" and "x64" ("Win32" and "x86" are identical). The
installers can be used on 32-bit or 64-bit Windows. The libraries are installed
for both architectures.

After installation, the environment variable CUnitRoot points to the CUnit root,
typically C:\Program Files (x86)\CUnit or C:\Program Files\CUnit.

From Visual Studio, you can reference CUnit libraries using the CUnit property
sheet %CUnitRoot%\CUnit.props. In your Visual Studio project file, an XML file
ending in .vcxproj, add the following section.

  <ImportGroup Label="PropertySheets">
    <Import Project="$(CUnitRoot)\CUnit.props" />
  </ImportGroup>

From C source files of your application's unitary tests, use CUnit the same way
as on any platform. Namely, from any source file:

  #include <CUnit/CUnit.h>

Compiling and linking from Visual Studio is done transparently.

Sorced from here:
  https://sourceforge.net/projects/cunit-msvc/files/
*/
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"
#include <stdio.h>  // for printf

#include "max.h"

/* Test Suite setup and cleanup functions: */
int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/
void test_case_sample(void) {
	CU_ASSERT(CU_TRUE);
	CU_ASSERT_NOT_EQUAL(2, -1);
	CU_ASSERT_STRING_EQUAL("string #1", "string #1");
	CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

	CU_ASSERT(CU_FALSE);
	CU_ASSERT_EQUAL(2, 3);
	CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
	CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}

void max_test_1(void) {
	CU_ASSERT_EQUAL(max(1, 2), 2);
	CU_ASSERT_EQUAL(max(2, 1), 2);
}

void max_test_2(void) {
	CU_ASSERT_EQUAL(max(2, 2), 2);
	CU_ASSERT_EQUAL(max(0, 0), 0);
	CU_ASSERT_EQUAL(max(-1, -1), -1);
}

void max_test_3(void) {
	CU_ASSERT_EQUAL(max(-1, -2), -1);
}

/************* Test Runner Code goes here **************/
int main(void) {
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("max_test_suite", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if ((NULL == CU_add_test(pSuite, "max_test_1", max_test_1)) ||
		(NULL == CU_add_test(pSuite, "max_test_2", max_test_2)) ||
		(NULL == CU_add_test(pSuite, "max_test_3", max_test_3)) 
//		(NULL == CU_add_test(pSuite, "max_test_3", max_test_3)) ||
//		(NULL == CU_add_test(pSuite, "test_case_sample", test_case_sample))
		)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Run all tests using the basic interface
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	printf("\n");
	CU_basic_show_failures(CU_get_failure_list());
	printf("\n\n");

	// Pause to see results.
	int c = getchar();

	// Run all tests using the automated interface
//	CU_automated_run_tests();
//	CU_list_tests_to_file();
	// Run all tests using the console interface
//	CU_console_run_tests();

	/* Clean up registry and return */
	CU_cleanup_registry();
	return CU_get_error();
}
