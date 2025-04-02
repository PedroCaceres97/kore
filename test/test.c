#include <kore/kore.h>
#include <kore/memory.h>
#include <kore/string.h>
#include <kore/logger.h>

int main() {   
    kore_init();

    if (kore_is_dir("test")) {
        kprint("test is a dir\n");
    } else {
        kprint("test is not a dir\n");
    }

    if (kore_is_file("test", "test.c")) {
        kprint("test/test.c is a file\n");
    } else {
        kprint("test/test.c is not a file\n");
    }

    kore_memory_print();
    kore_memory_register("STRING", 0);
    const char* string = kore_memory_alloc(50, 0);
    if (kore_memory_leak() > 0) {
        kore_info("String allocated: %s:%s", "test.c", "25");
        kore_memory_print();
    } else {
        kore_fatal("Unable to allocate string");
    }

    char* hola = kstrdup("Hello World!\n");
    kwrite(hola, kstrlen(hola));
    kstrncpy(&hola[6], "Mundo", 5);
    kwrite(hola, kstrlen(hola));
    kore_free(hola);

    kprint("Press a key to continue...");
    kignore();

    kore_memory_free(string, 0);
    kore_terminate();
    return 0;
}