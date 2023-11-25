#include "os_file.h"
#include "LinkedList.h"
#include <string.h>
#include <stdlib.h>
#define NODE_VALUE_MAX_LENGTH 32
#define ABSOLUTE_PATH_MAX_LEN 128

node *root = NULL;
char *cur_dir = NULL;
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
    fm->create_file("a.out", 1);
    fm->create_file("FCFS", 1);
    fm->create_file("input.txt", 1);
    fm->change_dir("../python_Course_Tinkoff");
    fm->create_file("main.py", 1);
    fm->create_file("taxis", 1);
    fm->create_file("test.ipynb", 1);
    fm->change_dir("../../Downloads");
    fm->create_dir("/Telegram Desktop");
    fm->change_dir("./Telegram Desktop");
    fm->create_file("Compiler Explorer code.cpp", 1);
    fm->create_file("FileName(2).cpp", 1);
    fm->create_file("makefile", 1);
    fm->create_file("New_Sort", 1);
    fm->change_dir("..");
    fm->create_file("main.cpp", 1);
    fm->create_file("os_file.h", 1);
    fm->change_dir("../file_Manager");
    fm->create_file("22_1_2task", 1);
    fm->create_file("22_1_2task.c", 1);
    fm->create_file("os_file", 1);
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
        cur_dir = (char *)malloc(sizeof(char) * ABSOLUTE_PATH_MAX_LEN);
        cur_dir = strdup("/");
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
    return 0;
}

int create_file(const char *path, int file_size)
{
    return 0;
}

int remove(const char *path, int recursive)
{
    return 0;
}

int change_dir(const char *path)
{
    return 0;
}

void get_cur_dir(char *dst)
{
    if (dst && cur_dir)
    {
        dst = strdup(cur_dir);
    }
}

int list(const char *path, int dir_first)
{
    return 0;
}
