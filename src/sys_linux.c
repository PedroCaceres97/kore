#include <kore/kore.h>

#ifdef KORE_OS_LINUX

#include <kore/sys_null.h>

#include <unistd.h>
#include <dirent.h>
#include <termios.h>
#include <sys/stat.h>

u8 linux_init();
u8 linux_terminate();

u8 (*sys_init)() = linux_init;
u8 (*sys_terminate)() = linux_terminate;

void linux_kignore();
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
    tcflush(STDIN_FILENO, TCIFLUSH);
}
void linux_kwrite(const char* buffer, size_t count) {
    write(stdout, buffer, count);
}
void linux_kerror(const char* buffer) {
    write(stderr, buffer, count);
}

u8 linux_kore_is_dir(const char* path) {
    if (!(*path)) {
        return true;
    }
    
    struct stat s = {0};
    return (stat(path, &s) == 0) && (s.st_mode & S_IFDIR);
}
u8 linux_kore_is_file(const char* path, const char* file) {
    if (!kore_is_dir(path)) {
        return false;
    }
    
    DIR* dir = NULL

    if (!(*path)) {
        dir = opendir("./");
    } else {
        dir = opendir(path);
    }

    b8 found = false;

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, file) == 0) {
            found = true;
            break;
        }
    }

    closedir(dir);
    return found;
}
u8 linux_kore_make_dir(const char* path) {
    if (kore_is_dir(path)) {
        return true;
    }

    return mkdir(path, 0777) == 0;
}
u8 linux_kore_make_path(const char* path) {
    char* buffer = strdup(path);
    size_t length = strlen(path);

    for (size_t i = 0; i < length; i++) {
        if (buffer[i] == '/' || buffer[i] == '\\') {
            buffer[i] = '\0';

            if (!kore_make_dir(buffer)) {
                free(buffer);
                return false;
            }

            buffer[i] = '\\';
        }
    }

    b8 result = kore_make_dir(buffer);
    free(buffer);
    return result;
}

void linux_kore_console_clear() {
    const char* buffer = "\x1b[2J\x1b[0;0H"; 
    kwrite(buffer, strlen(buffer));
}
void linux_kore_console_reset() {
    const char* buffer = "\x1b[2J\x1b[0;0H"; 
    kwrite(buffer, strlen(buffer));
}
void linux_kore_console_set_color(KOREcolor fg, KOREcolor bg) {
    char buffer[256] = {0};
    sprintf(buffer, "\x1b[%u;%um", (fg & 0x7f) + 30 + (60 * !!(fg & 0x80)), (bg & 0x7f) + 40 + (60 * !!(bg & 0x80)));
    kwrite(buffer, strlen(buffer));
}
void linux_kore_console_set_foreground(KOREcolor fg) {
    char buffer[256] = {0};
    sprintf(buffer, "\x1b[%um", (fg & 0x7f) + 30 + (60 * !!(fg & 0x80)));
    kwrite(buffer, strlen(buffer));
}
void linux_kore_console_set_background(KOREcolor bg) {
    char buffer[256] = {0};
    sprintf(buffer, "\x1b[%um", (bg & 0x7f) + 40 + (60 * !!(bg & 0x80)));
    kwrite(buffer, strlen(buffer));
}

#endif // kore_linux