#include <kore/kore.h>
#include <kore/memory.h>

typedef struct KORElayout {
    u8 registered;
    size_t size;
    const char* alias;
} KORElayout;

static size_t kore_layout = 0;
static KORElayout layouts[256] = {};

static const char* title = "[Kore Memory Layout]";
static KOREcolor foreground = KORE_COLOR_WHITE | KORE_COLOR_INTENSITY;
static KOREcolor background = KORE_COLOR_BLACK;

static u8* ptr_base(kore_ptr ptr) {
    return ptr - sizeof(size_t);
}
static u8* ptr_start(kore_ptr ptr) {
    return ptr + sizeof(size_t); 
}

static void ptr_set_size(kore_ptr ptr, size_t size) {
    *((size_t*)ptr_base(ptr)) = size;
}
static size_t ptr_get_size(kore_ptr ptr) {
    return *((size_t*)ptr_base(ptr));
}

static void ptr_free(kore_ptr ptr) {
    free(ptr_base(ptr));
}
static kore_ptr ptr_alloc(size_t size) {
    size_t* ptr = calloc(size + sizeof(size_t), 1);
    *ptr = size + sizeof(size_t);
    return ptr_start(ptr);
}
static kore_ptr ptr_realloc(kore_ptr ptr, size_t size) {
    ptr_set_size(ptr, size + sizeof(size_t));
    return ptr_start(realloc(ptr_base(ptr), size + sizeof(size_t)));
}

void kore_free(kore_ptr ptr) {
    kore_layout -= ptr_get_size(ptr);
    ptr_free(ptr);
}
kore_ptr kore_alloc(size_t size) {
    u8* ptr = ptr_alloc(size);
    kore_layout += ptr_get_size(ptr);
    return ptr;
}
kore_ptr kore_realloc(kore_ptr ptr, size_t size) {
    kore_ptr new = ptr_realloc(ptr, size);
    kore_layout += ptr_get_size(new);
    return new;
}

size_t kore_leak() {
    return kore_layout;
}
size_t kore_size(kore_ptr ptr) {
    return ptr_get_size(ptr);
}

void kore_memory_register(const char* alias, u8 layout){
    layouts[layout].alias = alias;
    layouts[layout].registered = true;
}
size_t kore_memory_unregister(u8 layout) {
    if (layouts[layout].size > 0) {
        return layouts[layout].size;
    }
    layouts[layout].alias = 0;
    layouts[layout].registered = false;
    return 0;
}

void kore_memory_free(kore_ptr ptr, u8 layout) {
    if (!layouts[layout].registered) {
        kerror("[KORE MEMORY]: Unable to free memory in an unregistered layout");
    }
    size_t* ptr64 = (size_t*)ptr_base(ptr);
    layouts[layout].size -= ptr64[0];
    free(ptr64);
}
kore_ptr kore_memory_alloc(size_t size, u8 layout) {
    if (!layouts[layout].registered) {
        kerror("[KORE MEMORY]: Unable to allocate memory in an unregistered layout");
    }

    size += sizeof(size_t);
    layouts[layout].size += size;

    size_t* ptr = calloc(sizeof(u8), size);
    *ptr = size;
    return ptr_start((u8*)ptr);
}
kore_ptr kore_memory_realloc(kore_ptr ptr, size_t size, u8 layout) {
    kore_ptr new = ptr_realloc(ptr, size);
    layouts[layout].size += ptr_get_size(new);
    return new;
}

void kore_memory_print() {
    kprintf("\n%s\n", title);
    
    for (u16 i = 0; i < 256; i++) {
        if (!layouts[i].registered) {
            continue;
        }
    
        f32 size = 0;
        const char* sufix = NULL;
        if (layouts[i].size >= KORE_GB(1)) {
            size = (f32)layouts[i].size / (f32)KORE_GB(1);
            sufix = "GB";
        } else if (layouts[i].size >= KORE_MB(1)) {
            size = (f32)layouts[i].size / (f32)KORE_MB(1);
            sufix = "MB";
        } else if (layouts[i].size >= KORE_KB(1)) {
            size = (f32)layouts[i].size / (f32)KORE_KB(1);
            sufix = "KB";
        } else {
            size = layouts[i].size;
            sufix = "B";
        }
    
        kprintf_color(foreground, background, "[%s]: %.2f %s\n", layouts[i].alias, size, sufix);
    }

    f32 size = 0;
    const char* sufix = NULL;
    if (kore_layout >= KORE_GB(1)) {
        size = (f32)kore_layout / (f32)KORE_GB(1);
        sufix = "GB";
    } else if (kore_layout >= KORE_MB(1)) {
        size = (f32)kore_layout / (f32)KORE_MB(1);
        sufix = "MB";
    } else if (kore_layout >= KORE_KB(1)) {
        size = (f32)kore_layout / (f32)KORE_KB(1);
        sufix = "KB";
    } else {
        size = kore_layout;
        sufix = "B";
    }
    kprintf_color(foreground, background, "[KORE]: %.2f %s\n", size, sufix);
}
size_t kore_memory_leak() {
    size_t size = 0;

    for (u16 i = 0; i < 256; i++) {
        if (!layouts[i].registered || layouts[i].size == 0) {
            continue;
        }

        size += layouts[i].size;
    }

    return size;
}

void kore_memory_set_title(const char* _title) {
    title = _title;
}
void kore_memory_set_color(KOREcolor fg, KOREcolor bg) {
    foreground = fg;
    background = bg;
}