#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

const size_t BUF_SIZE = 32;  

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("The source and target file names should be provided\n");
        exit(1);
    }
    if (strcmp(argv[1], argv[2]) == 0) {
        printf("The source and target file names should differ\n");
        exit(1);
    }

    printf("Opened source file for reading\n");

    int source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("Failed to open source file");
        exit(1);
    }

    struct stat source_stat;

    int f = fstat(source_fd, &source_stat);
    if (f == -1) {
        perror("Failed to stat source file");
        exit(1);
    }

    int perm = source_stat.st_mode & 0777;
    printf("Source file mode is %o\n", perm);

    int target_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, perm);
    if (target_fd < 0) {
        perror("Failed to open target file");
        exit(1);
    }

    printf("Opened target file for writing\n");

    char* buf = malloc(BUF_SIZE);
    int n_total = 0;

    while (1) {
        int n = read(source_fd, buf, BUF_SIZE);
        if (n == 0) {
            printf("Finished reading bytes from source file\n");
            break;
        }
        if (n == -1) {
            printf("Failed to read bytes from source file (error %d)\n", errno);
            break;
        }
        printf("Read %d bytes from source file\n", n);

        n = write(target_fd, buf, n);
        if (n == -1) {
            printf("Failed to write bytes to target file (error %d)\n", errno);
            break;
        }

        printf("Written %d bytes to target file\n", n);

        n_total += n;
    }

    free(buf);
    close(source_fd);
    close(target_fd);

    printf("Written total %d bytes to target file\n", n_total);

    return 0;
}