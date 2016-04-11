#define MK_STRING0(smth) #smth
#define MK_STRING(smth)	MK_STRING0(smth)
#define MK_CAT_0(word, prefix, suffix) prefix##word suffix 
#define MK_CAT_(word, prefix, suffix) MK_CAT_0(word, prefix, suffix)
#define MK_MODULE_TEST(module) MK_CAT_(_test_main(), MK_CAT_(int, , module),)
#define MK_TEST_NAME(name) MK_CAT_(_test, name,)
#define MK_TEST(module, num) MK_CAT_(_test<num>(), MK_CAT_(template <> int, , module), )