#include <stdio.h>
#include <string.h>

extern unsigned char kstrcmp(const char* src, const char* dst);

const char* testing = "unsigned char kstrcmp(const char* src, const char* dst)";

const char* boolstr(unsigned char value) {
    return (value) ? "true" : "false";
}

typedef struct test_element {
    const char* alias;
    const char* src;
    const char* dst;
    unsigned char      first;
    unsigned char      second;
    unsigned char      expected;
} test_element;

void fill_elements(test_element* elements) {
    elements[0].alias = "Empty String";
    elements[0].src = "";
    elements[0].dst = "";

    elements[1].alias = "Single Character 1";
    elements[1].src = "a";
    elements[1].dst = "a";

    elements[2].alias = "Single Character 2";
    elements[2].src = "a";
    elements[2].dst = "b";

    elements[3].alias = "Single Character 3";
    elements[3].src = "a";
    elements[3].dst = "";

    elements[4].alias = "Single Character 4";
    elements[4].src = "";
    elements[4].dst = "a";

    elements[5].alias = "Short String 1";
    elements[5].src = "abc";
    elements[5].dst = "abc";

    elements[6].alias = "Short String 2";
    elements[6].src = "abc";
    elements[6].dst = "abd";

    elements[7].alias = "Short String 3";
    elements[7].src = "abcd";
    elements[7].dst = "abc";

    elements[8].alias = "Long String 1";
    elements[8].src = "Hello World! There are papparazzis out here!";
    elements[8].dst = "Hello World! There are papparazzis out here!";

    elements[9].alias = "Long String 2";
    elements[9].src = "A beatiful long long string to qualify a function";
    elements[9].dst = "A beatiful long long string to grade a function";
}

void test(test_element* element) {
    printf("test->src (%p) = \"%s\"\n", element->src, element->src);
    printf("test->dst (%p) = \"%s\"\n", element->dst, element->dst);
    element->first = kstrcmp(element->src, element->dst);
    element->expected = strcmp(element->src, element->dst) == 0;
    element->second = kstrcmp(element->src, element->dst);
}
void test_print(test_element* element) {
    printf("test->first = %s\n", boolstr(element->first));
    printf("test->second = %s\n", boolstr(element->second));
    printf("test->expected = %s\n", boolstr(element->expected));
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