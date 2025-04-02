#include <kore/kore.h>

#ifdef KORE_OS_LINUX

#include "kore_sys.h"

#include <unistd.h>
#include <dirent.h>
#include <termios.h>
#include <sys/stat.h>

u8 linux_init();
u8 linux_terminate();

u8 (*sys_init)() = linux_init;
u8 (*sys_terminate)() = linux_terminate;

void linux_kignore();
void linux_kread(char* buffer, size_t count);
void linux_kwrite(const char* buffer, size_t count);
void linux_kerror(const char* buffer);

u8 linux_kore_is_dir(const char* path);
u8 linux_kore_is_file(const char* path, const char* file);
u8 linux_kore_make_dir(const char* path);
u8 linux_kore_make_path(const char* path);

void linux_kore_console_clear();
void linux_kore_console_reset();
void linux_kore_console_set_color(KOREcolor fg, KOREcolor bg);
void linux_kore_console_set_foreground(KOREcolor fg);
void linux_kore_console_set_background(KOREcolor bg);

static void report(const char* message) {
    fprintf(stderr, "(linux system report)\n[KORE]: %s\n", message);
}

u8 linux_init() {
    kread                       = linux_kread;
    kignore                     = linux_kignore;              
    kwrite                      = linux_kwrite;    
    kerror                      = linux_kerror;     

    kore_is_dir                 = linux_kore_is_dir;              
    kore_is_file                = linux_kore_is_file;     
    kore_make_dir               = linux_kore_make_dir;   
    kore_make_path              = linux_kore_make_path;          

    kore_console_clear          = linux_kore_console_clear;
    kore_console_reset          = linux_kore_console_reset;
    kore_console_set_color      = linux_kore_console_set_color;
    kore_console_set_foreground = linux_kore_console_set_foreground;  
    kore_console_set_background = linux_kore_console_set_background;        

    return true;
}
u8 linux_terminate() {
    kread                       = null_kread;
    kignore                     = null_kignore;              
    kwrite                      = null_kwrite;    
    kerror                      = null_kerror;     

    kore_is_dir                 = null_kore_is_dir;              
    kore_is_file                = null_kore_is_file;     
    kore_make_dir               = null_kore_make_dir;   
    kore_make_path              = null_kore_make_path;          

    kore_console_clear          = null_kore_console_clear;
    kore_console_reset          = null_kore_console_reset;
    kore_console_set_color      = null_kore_console_set_color;
    kore_console_set_foreground = null_kore_console_set_foreground;  
    kore_console_set_background = null_kore_console_set_background;        

    return true;
}

void linux_kignore() {
#if defined(KORE_USE_STD) || defined(KORE_SYS_USE_STD)
    char c = getchar();
    while(c != '\n' && c != EOF) {
        c = getchar();
    }
#else
    char c;
    linux_kread(&c, 1);
    tcflush(STDIN_FILENO, TCIFLUSH);
#endif
}
void linux_kread(char* buffer, size_t count) {
    read(STDIN_FILENO, buffer, count);
}
void linux_kwrite(const char* buffer, size_t count) {
    write(STDOUT_FILENO, buffer, count);
}
void linux_kerror(const char* buffer) {
    write(STDERR_FILENO, buffer, __sys_strlen__(buffer));
}

u8 linux_kore_is_dir(const char* path) {
    if (!(*path)) {
        return true;
    }
    
    struct stat s = {0};
    return (stat(path, &s) == 0) && (s.st_mode & S_IFDIR);
}
u8 linux_kore_is_file(const char* path, const char* file) {
    if (!linux_kore_is_dir(path)) {
        return false;
    }
    
    DIR* dir = NULL;

    if (!(*path)) {
        dir = opendir("./");
    } else {
        dir = opendir(path);
    }

    u8 found = false;

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (__sys_strcmp__(entry->d_name, file)) {
            found = true;
            break;
        }
    }

    closedir(dir);
    return found;
}
u8 linux_kore_make_dir(const char* path) {
    if (linux_kore_is_dir(path)) {
        return true;
    }

    return mkdir(path, 0777) == 0;
}
u8 linux_kore_make_path(const char* path) {
    char* buffer = __sys_strdup__(path);
    size_t length = __sys_strlen__(path);

    for (size_t i = 0; i < length; i++) {
        if (buffer[i] == '/' || buffer[i] == '\\') {
            buffer[i] = '\0';

            if (!linux_kore_make_dir(buffer)) {
                free(buffer);
                return false;
            }

            buffer[i] = '\\';
        }
    }

    u8 result = linux_kore_make_dir(buffer);
    free(buffer);
    return result;
}

void linux_kore_console_clear() {
    const char* buffer = "\x1b[2J\x1b[0;0H"; 
    linux_kwrite(buffer, __sys_strlen__(buffer));
}
void linux_kore_console_reset() {
    const char* buffer = "\x1b[0m"; 
    linux_kwrite(buffer, __sys_strlen__(buffer));
}
void linux_kore_console_set_color(KOREcolor fg, KOREcolor bg) {
    char buffer[256] = {0};
    sprintf(buffer, "\x1b[%u;%um", (fg & 0x7f) + 30 + (60 * !!(fg & 0x80)), (bg & 0x7f) + 40 + (60 * !!(bg & 0x80)));
    linux_kwrite(buffer, __sys_strlen__(buffer));
}
void linux_kore_console_set_foreground(KOREcolor fg) {
    char buffer[256] = {0};
    sprintf(buffer, "\x1b[%um", (fg & 0x7f) + 30 + (60 * !!(fg & 0x80)));
    linux_kwrite(buffer, __sys_strlen__(buffer));
}
void linux_kore_console_set_background(KOREcolor bg) {
    char buffer[256] = {0};
    sprintf(buffer, "\x1b[%um", (bg & 0x7f) + 40 + (60 * !!(bg & 0x80)));
    linux_kwrite(buffer, __sys_strlen__(buffer));
}

#endif // kore_linux