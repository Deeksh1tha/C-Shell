#define MAX_SIZE 15

struct dir_path
{
    char home_dir[1024];
    char cur_dir[1024];
    char pre_dir[1024];
};
typedef struct dir_path dir_path;
typedef struct {
    char items[MAX_SIZE][1024];
    int no_of_elems;
    int front, rear;
} CircularQueue;

