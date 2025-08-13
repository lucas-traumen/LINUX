#include<filesat.h>

struct stat fileStat;

void infor_size_marktime_file(){
 printf("File Type: ");
    if (S_ISREG(fileStat.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("Symbolic Link\n");
    } else {
        printf("Other\n");
    }

    printf("Size: %lld bytes\n", (long long)fileStat.st_size);

    char timebuf[100];
    struct tm *tm_info = localtime(&fileStat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Last Modified: %s\n", timebuf);
}
