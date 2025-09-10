add_test([=[Security.ParsesData_TEST]=]  /home/john/local_repository/cs3021/Intermediate-Programming-and-Data-Structures/big_project/build/runSecurityTests [==[--gtest_filter=Security.ParsesData_TEST]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Security.ParsesData_TEST]=]  PROPERTIES WORKING_DIRECTORY /home/john/local_repository/cs3021/Intermediate-Programming-and-Data-Structures/big_project/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  runSecurityTests_TESTS Security.ParsesData_TEST)
