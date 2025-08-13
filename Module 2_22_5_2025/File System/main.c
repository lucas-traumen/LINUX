#include<filesat.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    if (lstat(argv[1], &fileStat) == -1) {
        perror("lstat");
        return 1;
    }
    printf("File Path: %s\n", argv[1]);

    infor_size_marktime_file();

    return 0;
}
