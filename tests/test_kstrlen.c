#include <stdio.h>
#include <string.h>

extern size_t kstrlen(const char* src);

const char* testing = "size_t kstrlen(const char* src)";

typedef struct test_element {
    const char* alias;
    const char* string;
    size_t      first;
    size_t      second;
    size_t      expected;
} test_element;

void fill_elements(test_element* elements) {
    elements[0].alias = "Empty String";
    elements[0].string = "";

    elements[1].alias = "Single Character";
    elements[1].string = "a";

    elements[2].alias = "Single Space Character";
    elements[2].string = " ";

    elements[3].alias = "Short String 1";
    elements[3].string = "hello";

    elements[4].alias = "Short String 2";
    elements[4].string = "hello world!";

    elements[5].alias = "All Digits";
    elements[5].string = "1234567890";

    elements[6].alias = "All Letters";
    elements[6].string = "abcdefghijklmnopqrstuvwxyz\0";

    elements[7].alias = "Long String";
    elements[7].string = "A really long long string with spaces to qualify a function";

    elements[8].alias = "Special Characters";
    elements[8].string = "a\tb\tc";

    elements[9].alias = "Hidden Zero";
    elements[9].string = "zero\0hidden";
}

void test(test_element* element) {
    printf("test->string (%p) = \"%s\"\n", element->string, element->string);
    element->first = kstrlen(element->string);
    element->expected = strlen(element->string);
    element->second = kstrlen(element ->string);
}
void test_print(test_element* element) {
    printf("test->first = %llu\n", element->first);
    printf("test->second = %llu\n", element->second);
    printf("test->expected = %llu\n", element->expected);
}
int is_expected(test_element* element) {
    return element->first == element->expected;
}
int differ(test_element* element) {
    return element->first != element->second;
}

int main() {
    test_element tests[10] = {};
    fill_elements(tests);

    printf("\nTesting: %s\n", testing);

    for (int i = 0; i < 10; i++) {
        printf("\nTest [%i] = %s\n", i, tests[i].alias);
        test(&tests[i]);
        test_print(&tests[i]);
        if (is_expected(&tests[i])) {
            printf("The result is the EXPECTED!\n");
        } else {
            printf("The result is NOT the expected!\n");
        }
        if (differ(&tests[i])) {
            printf("The result DIFFERS!\n");  
        } else {
            printf("The result DON'T differs!\n");  
        }
    }

    return 0;
}