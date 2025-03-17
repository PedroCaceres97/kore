#include <kore/kore.h>
#include <kore/memory.h>
#include <kore/string.h>

int main() {

    kore_init();

    const char* message = kstrdupf("Hola mundo! Copiando: %s", "Como tamos muchachos?");
    kprintf("%s\n", message);

    kore_terminate();
    return 0;
}