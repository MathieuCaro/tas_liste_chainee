#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../fonctions.h"

void test_init(void){

	init();
	CU_ASSERT(tas[0]==127);
    CU_ASSERT(tas[1]==-1);
    for(int i=2;i<SIZE_TAB;i++){
        CU_ASSERT(tas[i]==0);
    }
    char* p1 = tas_malloc(10);
    CU_ASSERT(p1-1 == tas);
    CU_ASSERT(*(p1+1) != FREE_BLOCK);
    CU_ASSERT(libre == 10+1);
    CU_ASSERT(*(tas + libre) == 116);
    printf("tas+libre %d\n",*(tas+libre));
    afficher_tas();
    CU_ASSERT(*(tas + libre + 1) == FREE_BLOCK);
    char* p2 = tas_malloc(9);
    CU_ASSERT(p2 == tas+12);
    CU_ASSERT(*(p2-1) == 9);
    CU_ASSERT(libre == 21);
    char* p3 = tas_malloc(5);
    CU_ASSERT(p3 == tas + 22);
    CU_ASSERT(*(p3-1) == 5);
    CU_ASSERT(libre == 27);
    char* p4 = tas_malloc(101);
    CU_ASSERT(p4 == NULL);
}

void test_free(void){
    init();
    char* p1 = tas_malloc(10);
    char* p2 = tas_malloc(10);
    char* p3 = tas_malloc(10);
    char* p4 = tas_malloc(10);

    strcpy(p1,"tp1");
    strcpy(p2,"tp2");
    strcpy(p3,"tp3");
    strcpy(p4,"tp4");

    tas_free(p2);
    CU_ASSERT(*(p2-1) == 10);
    CU_ASSERT(*(p2) == FREE_BLOCK);
    CU_ASSERT(libre == p2 - 1 - tas);

    tas_free(p3); // testing merge left

    CU_ASSERT(*(p3) == FREE_BLOCK);
    //CU_ASSERT(*(p2-1) == 21);
}

void test_full_example(){
    init();

    char* p1 = tas_malloc(10);
    char* p2 = tas_malloc(9);
    char* p3 = tas_malloc(5);

    strcpy(p1,"tp 1");
    strcpy(p2,"tp 2");
    strcpy(p3,"tp 3");

    tas_free(p2);

     // That verifies that in case we have 1 byte left we actually malloc size+1
    char* p4 = tas_malloc(8);
    strcpy(p4,"systeme");

    //print_heap();

    CU_ASSERT(*(p1-1) == 10);
    CU_ASSERT(*(p4-1) == 9);
    CU_ASSERT(*(p3-1) == 5);
    CU_ASSERT(libre == 27);
    CU_ASSERT(tas[27] == 100);
    CU_ASSERT(tas[28] == -1);

    CU_ASSERT(strcmp(p1,"tp 1") == 0);
    CU_ASSERT(strcmp(p3,"tp 3") == 0);
    CU_ASSERT(strcmp(p4,"systeme") == 0);
    afficher_tas();
}

void test_empty_heap(void)
{

    char *p1;

    init();
    p1 = (char*)tas_malloc(127);
    strcpy(p1, "ab");

    CU_ASSERT(tas[0] == 127 && tas[127] == 0);
    CU_ASSERT(libre == -1);
}

void test_add_to_empty_heap(void)
{

    char *p1,*p2;

    init();
    p1 = (char* )tas_malloc(125);
    strcpy(p1, "ab");

    p2 = (char*)tas_malloc(3);

    CU_ASSERT(p2 == NULL);
    CU_ASSERT(libre == 126);
}


int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int main()
{
	CU_pSuite pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add a suite to the registry */
	pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* add the tests to the suite */
	if (
		NULL == CU_add_test(pSuite, "test initialisation", test_init)||
        NULL == CU_add_test(pSuite, "test free", test_free) ||
        NULL == CU_add_test(pSuite, "test full example", test_full_example) ||
        NULL == CU_add_test(pSuite, "test empty tas", test_empty_heap) ||
        NULL == CU_add_test(pSuite, "test add to empty tas", test_add_to_empty_heap) 

	)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}