typedef struct ti {
    int n;
    int first;
    int out_flag;
    int result;
} thread_info_t;

int generate_n_queens_serial(int n, int print_flag);
int next_permutation(int *list, int n);
void get_array_string(int *list, int n, char *s);
int check_diagonal(int *list, int n);
int generate_n_queens_serial_one(int n, int out_flag, int first);
void *queens_thread(void *infopointer);

pthread_mutex_t mutex;
