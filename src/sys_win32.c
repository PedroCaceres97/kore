#include <kore/kore.h>

#ifdef KORE_OS_WINDOWS

#include "kore_sys.h"

#include <windows.h>
#include <direct.h>

u8 win32_init();
u8 win32_terminate();

DWORD console_mode = 0;
HANDLE handle_stdin = NULL;
HANDLE handle_stdout = NULL;
HANDLE handle_stderr = NULL;

u8 (*sys_init)() = win32_init;
u8 (*sys_terminate)() = win32_terminate;

void win32_kread(char* buffer, size_t count);
void win32_kignore();
void win32_kwrite(const char* buffer, size_t count);
void win32_kerror(const char* buffer);

u8 win32_kore_is_dir(const char* path);
u8 win32_kore_is_file(const char* path, const char* file);
u8 win32_kore_make_dir(const char* path);
u8 win32_kore_make_path(const char* path);

void win32_kore_console_clear();
void win32_kore_console_reset();
void win32_kore_console_set_color(KOREcolor fg, KOREcolor bg);
void win32_kore_console_set_foreground(KOREcolor fg);
void win32_kore_console_set_background(KOREcolor bg);

static void report(const char* message) {
    fprintf(stderr, "(win32 system report)\n[KORE]: %s\n", message);
}

u8 win32_init() {
    handle_stdin = GetStdHandle(STD_INPUT_HANDLE);
    handle_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    handle_stderr = GetStdHandle(STD_ERROR_HANDLE);
    if (!handle_stdin) {
        report("Failed to get std input handle");
        return false;
    }
    if (!handle_stdout) {
        report("Failed to get std output handle");
        return false;
    }
    if (!handle_stderr) {
        report("Failed to get std error handle");
        return false;
    }
    if (!GetConsoleMode(handle_stdout, &console_mode)) {
        report("Failed to get console mode");
        return false;
    }
    if (!SetConsoleMode(handle_stdout, console_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
        report("Failed to set console mode");
        return false;
    }

    kread                       = win32_kread;
    kignore                     = win32_kignore;              
    kwrite                      = win32_kwrite;    
    kerror                      = win32_kerror;     

    kore_is_dir                 = win32_kore_is_dir;              
    kore_is_file                = win32_kore_is_file;     
    kore_make_dir               = win32_kore_make_dir;   
    kore_make_path              = win32_kore_make_path;          

    kore_console_clear          = win32_kore_console_clear;
    kore_console_reset          = win32_kore_console_reset;
    kore_console_set_color      = win32_kore_console_set_color;
    kore_console_set_foreground = win32_kore_console_set_foreground;  
    kore_console_set_background = win32_kore_console_set_background;        

    return true;
}
u8 win32_terminate() {
    u8 value = true;
    kore_console_reset();
    if (!SetConsoleMode(handle_stdout, console_mode)) {
        report("Failed to restore console mode");
        value = false;
    }

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

    return value;
}

void win32_kignore() {
#if defined(KORE_USE_STD) || defined(KORE_SYS_USE_STD)
    char c = getc();
    while(c != '\n' && c != EOF) {
        c = getc();
    }
#else
    char c;
    win32_kread(&c, 1);
    FlushConsoleInputBuffer(handle_stdin);
#endif
}
void win32_kread(char* buffer, size_t count) {
    DWORD readed;
    ReadFile(handle_stdin, buffer, count, &readed, NULL);
}
void win32_kwrite(const char* buffer, size_t count) {
#if defined(KORE_USE_STD) || defined(KORE_SYS_USE_STD)
    const char temp[count] = {0};
    snprintf(temp, count, "%s", buffer);
    fprintf(stdout, temp);
#else
    DWORD writen; 
    WriteFile(handle_stdout, buffer, count, &writen, NULL);
#endif
}
void win32_kerror(const char* buffer) {
#if defined(KORE_USE_STD) || defined(KORE_SYS_USE_STD)
    fprintf(stderr, buffer);
#else
    DWORD writen; 
    WriteFile(handle_stderr, buffer, __sys_strlen__(buffer), &writen, NULL);
#endif
}

u8 win32_kore_is_dir(const char* path) {
    if (!(*path)) {
        return true;
    }
    
    DWORD attrib = GetFileAttributes(path);
    return attrib != INVALID_FILE_ATTRIBUTES && attrib & FILE_ATTRIBUTE_DIRECTORY;
}
u8 win32_kore_is_file(const char* path, const char* file) {
    if (!win32_kore_is_dir(path)) {
        return false;
    }
    
    const u16 sizepath = 512;
    char buffer[sizepath] = {0};

    if (!(*path)) {
        snprintf(buffer, sizepath, "./*.*");
    } else {
        snprintf(buffer, sizepath, "%s/*.*", path);
    }

    WIN32_FIND_DATA ffd;
    HANDLE hFind;

    u8 found = false; 

    hFind = FindFirstFile(buffer, &ffd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (__sys_strcmp__(ffd.cFileName, file)) {
                found = true;
                break;
            } 
        } while (FindNextFile(hFind, &ffd));
    }
    
    FindClose(hFind);
    return found;
}
u8 win32_kore_make_dir(const char* path) {
    if (win32_kore_is_dir(path)) {
        return true;
    }

    return _mkdir(path) == 0;
}
u8 win32_kore_make_path(const char* path) {
    char* buffer = __sys_strdup__(path);
    size_t length = __sys_strlen__(path);

    for (size_t i = 0; i < length; i++) {
        if (buffer[i] == '/' || buffer[i] == '\\') {
            buffer[i] = '\0';

            if (!win32_kore_make_dir(buffer)) {
                free(buffer);
                return false;
            }

            buffer[i] = '\\';
        }
    }

    u8 created = win32_kore_make_dir(buffer);
    free(buffer);
    return created;
}

void win32_kore_console_clear() {
    const char* buffer = "\x1b[2J\x1b[0;0H"; 
    win32_kwrite(buffer, __sys_strlen__(buffer));
}
void win32_kore_console_reset() {
    const char* buffer = "\x1b[0m"; 
    win32_kwrite(buffer, __sys_strlen__(buffer));
}
void win32_kore_console_set_color(KOREcolor fg, KOREcolor bg) {
    char buffer[256] = {0};
    sprintf(buffer, "\x1b[%u;%um", (fg & 0x7f) + 30 + (60 * !!(fg & 0x80)), (bg & 0x7f) + 40 + (60 * !!(bg & 0x80)));
    win32_kwrite(buffer, __sys_strlen__(buffer));
}
void win32_kore_console_set_foreground(KOREcolor fg) {
    char buffer[256] = {0};
    sprintf(buffer, "\x1b[%um", (fg & 0x7f) + 30 + (60 * !!(fg & 0x80)));
    win32_kwrite(buffer, __sys_strlen__(buffer));
}
void win32_kore_console_set_background(KOREcolor bg) {
    char buffer[256] = {0};
    sprintf(buffer, "\x1b[%um", (bg & 0x7f) + 40 + (60 * !!(bg & 0x80)));
    win32_kwrite(buffer, __sys_strlen__(buffer));
}

#endif