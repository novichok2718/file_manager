#include "os_file.h"
#include "LinkedList.h"
#include <string.h>
#include <stdlib.h>
#define NODE_VALUE_MAX_LENGTH 32
#define ABSOLUTE_PATH_MAX_LEN 128

node *root = NULL;
node *cur_dir = NULL;
int SIZE = 0;

int create(int disk_size);
int destroy();
int create_dir(const char *path);
int create_file(const char *path, int file_size);
int remove(const char *path, int recursive);
int change_dir(const char *path);
void get_cur_dir(char *dst);
int list(const char *path, int dir_first);
void setup_file_manager(file_manager_t *fm);

int is_valid_path(char *path);
int createObject(const char *path, int size, int isDir);
int count(char *path);
char *get_abs_path(char *lhs, char *rhs);
char **parser(char *path, int size);
int set_cur_dir(char *path, int size);

int main()
{
    file_manager_t *fm;
    setup_file_manager(fm);
    fm->create(100);
    fm->create_dir("/Desktop");
    fm->create_dir("/Documents");
    fm->create_dir("/Downloads");
    fm->create_dir("/file_Manager");
    fm->change_dir("/Desktop");
    fm->create_dir("./lesson");
    fm->create_dir("./python_Course_Tinkoff");
    fm->change_dir("./lesson");
    fm->create_dir("./a.out");
    fm->create_file("./a.out", 1);
    fm->create_file("./FCFS", 1);
    fm->create_file("./input.txt", 1);
    fm->change_dir("../python_Course_Tinkoff");
    fm->create_file("./main.py", 1);
    fm->create_file("./taxis", 1);
    fm->create_file("./test.ipynb", 1);
    fm->change_dir("../../Downloads");
    fm->create_dir("/Telegram Desktop");
    fm->change_dir("./Telegram Desktop");
    fm->create_file("./Compiler Explorer code.cpp", 1);
    fm->create_file("./FileName(2).cpp", 1);
    fm->create_file("./makefile", 1);
    fm->create_file("./New_Sort", 1);
    fm->change_dir("..");
    fm->create_file("main.cpp", 1);
    fm->create_file("os_file.h", 1);
    fm->change_dir("../file_Manager");
    fm->create_file("./22_1_2task", 1);
    fm->create_file("./22_1_2task.c", 1);
    fm->create_file("./os_file", 1);
    return 0;
}

void setup_file_manager(file_manager_t *fm)
{
    fm->create = create;
    fm->destroy = destroy;
    fm->create_dir = create_dir;
    fm->create_file = create_file;
    fm->remove = remove;
    fm->change_dir = change_dir;
    fm->get_cur_dir = get_cur_dir;
    fm->list = list;
}

int is_valid_path(char *path)
{
    char arr[] = "!/\\,{}[]<>@#$%^&*()+|'\"?~`*+=";
    if (!path || strlen(path) > NODE_VALUE_MAX_LENGTH || !strcmp(path, ""))
    {
        return 0;
    }
    for (int i = 0; i != strlen(arr); ++i)
    {
        if (strchr(path, arr[i]))
        {
            return 0;
        }
    }
    return 1;
}

int count(char *path)
{
    int count = 0;
    for (int i = 0; i != strlen(path); ++i)
    {
        if (path[i] == '/')
        {
            ++count;
        }
    }
    return count;
}

char **parser(char *path, int size)
{
    char **lines = (char **)malloc(sizeof(char *) * size);
    lines[0] = strtok(path, "/");
    for (int i = 1; i < size; ++i)
    {
        lines[i] = strtok(NULL, "/");
    }
    return lines;
}

int set_cur_dir(char *path, int size)
{
    char **token = parser(path, size);
    cur_dir = root;
    for (int i = 0; i != size; ++i)
    {
        cur_dir = is_contains(cur_dir->child, token[i], 1);
        if (!is_valid_path(token[i]) && !cur_dir)
        {
            cur_dir = root;
            free(path);
            path = NULL;
            token = NULL;
            return 0;
        }
    }
    free(path);
    path = NULL;
    token = NULL;
    return 1;
}

char *get_abs_path(char *lhs, char *rhs)
{
    char *abs_path = malloc(ABSOLUTE_PATH_MAX_LEN);
    strcpy(abs_path, lhs);
    strcat(abs_path, rhs);
    return abs_path;
}

int createObject(const char *path, int size, int isDir)
{
    char *_path = strdup(path);
    int _size = count(_path);
    char **token = parser(_path, _size);
    node *iter = root;
    for (int i = 0; i != _size - 1; ++i)
    {
        iter = is_contains(iter->child, token[i], 1);
        if (!is_valid_path(token[i]) && !iter && iter->is_dir)
        {
            free(_path);
            _path = NULL;
            token = NULL;
            return 0;
        }
    }
    if (!is_contains(iter->child, token[_size - 1], isDir) && is_valid_path(token[_size - 1]))
    {
        node *tmp = (node *)malloc(sizeof(node));
        tmp->child = createLinkedList();
        tmp->is_dir = isDir;
        tmp->parent = iter;
        tmp->nodeValue = strdup(token[_size - 1]);
        tmp->absolutePath = strdup(path);
        pushBack(iter->child, tmp);
        SIZE -= size;
        free(_path);
        _path = NULL;
        token = NULL;
        if (!isDir && SIZE - size < 0)
        {
            return 0;
        }
        return 1;
    }
    free(_path);
    _path = NULL;
    token = NULL;
    return 0;
}

// implementation of main functions
int create(int disk_size)
{
    if (disk_size > 0)
    {
        root = (node *)malloc(sizeof(node));
        root->absolutePath = (char *)malloc(sizeof(char) * ABSOLUTE_PATH_MAX_LEN);
        root->child = createLinkedList();
        root->is_dir = 1;
        root->nodeValue = (char *)malloc(sizeof(char) * NODE_VALUE_MAX_LENGTH);
        root->parent = NULL;
        root->absolutePath = strdup("/");
        root->nodeValue = strdup("/");
        cur_dir = (node *)malloc(sizeof(node));
        cur_dir = root;
        SIZE = disk_size;
        return 1;
    }
    return 0;
}

int destroy()
{
    return 0;
}

int create_dir(const char *path)
{
    if (!path && !root)
    {
        return 0;
    }
    char *_path = strdup(path);
    if (*path == '/')
    {
        return createObject(path, 0, 1);
    }
    else if (*path == '.' && *(path + 1) == '/')
    {
        char *abs_path = get_abs_path(cur_dir->absolutePath, _path + 1);
        free(_path);
        _path = NULL;
        return createObject(abs_path, 0, 1);
    }
    else if (*path == '.' && *(path + 1) == '.' && *(path + 2) == '/')
    {
    }
    return 0;
}

int create_file(const char *path, int file_size)
{
    if (!path && !root)
    {
        return 0;
    }
    char *_path = strdup(path);
    if (*path == '/')
    {
        return createObject(path, file_size, 0);
    }
    else if (*path == '.' && *(path + 1) == '/')
    {
        char *abs_path = get_abs_path(cur_dir->absolutePath, _path + 1);
        free(_path);
        _path = NULL;
        return createObject(abs_path, file_size, 0);
    }
    return 0;
}

int remove(const char *path, int recursive)
{
    return 0;
}

int change_dir(const char *path)
{
    if (!root && !path)
    {
        return 0;
    }
    char *_path = strdup(path);
    if (*path == '/')
    {
        return set_cur_dir(_path, count(_path));
    }
    else if (*path == '.' && *(path + 1) == '/')
    {
        char *abs_path = get_abs_path(cur_dir->absolutePath, _path + 1);
        free(_path);
        _path = NULL;
        return set_cur_dir(abs_path, count(abs_path));
    }
    return 0;
}

void get_cur_dir(char *dst)
{
    if (dst && cur_dir)
    {
        dst = cur_dir->absolutePath;
    }
}

int list(const char *path, int dir_first)
{
    return 0;
}
