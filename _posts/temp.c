#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int write_temp_file(char *buffer, size_t length) {
    int len = length;
    char filename_template[] = "/tmp/temp_file.XXXXXX";
    int fd = mkstemp(filename_template);
    unlink(filename_template);  // Unlink the file, then the file will be deleted when it is closed.
    printf("Template file name:%s\n", filename_template);
    write(fd, &len, sizeof(len));
    write(fd, buffer, len);
    return fd;
}

char *read_temp_file(int fd, size_t *length) {
    char *buffer;
    lseek(fd, 0, SEEK_SET);
    read(fd, length, sizeof(size_t));
    buffer = (char *) malloc(*length);
    read(fd, buffer, *length);
    close(fd); // Temp file will be deleted.
    return buffer;
}

int main(int argc, char **argv) {
    char buffer[] = "Test template files";
    int fd = write_temp_file(buffer, strlen(buffer));
    int len = 0;
    char *result = read_temp_file(fd, &len);
    printf("Len:%d\nContent:%s\n", len, result);
    free(result);
    return 0;
}
