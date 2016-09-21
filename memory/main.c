#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define USAGE \
"Usage:\n" \
"    memory_stressor [seconds] [size]\n" \
"Options:\n" \
"    seconds: the time interval in seconds that the memory coordinator will \n" \
"             malloc memory\n" \
"    size: the size in bytes to be allotted in memory each interval\n"

#define MB (1024 * 1024)
#define GB (1024 * 1024 * 1024)

int stress(int interval_seconds, unsigned long byte_size);

int main(int argc, char **argv) {
    int interval_seconds;
    unsigned long byte_size;

    if (argc != 3) {
        puts(USAGE);
        return 1;
    }

    interval_seconds = atoi(argv[1]);
    if (interval_seconds <= 0) {
        fprintf(stderr, "Invalid value '%d' for interval seconds\n", interval_seconds);
        return EXIT_FAILURE;
    }

    byte_size = strtol(argv[2], NULL, 10);
    if (byte_size <= 0) {
        fprintf(stderr, "Invalid value '%lu' for byte size\n", byte_size);
        return EXIT_FAILURE;
    }

    printf("Writing %lu bytes every %d seconds\n", byte_size, interval_seconds);
    return stress(interval_seconds, byte_size);
}

int stress(int interval_seconds, unsigned long byte_size) {
    char * b;
    unsigned long long total;

    while (true) {
        b = malloc(byte_size);
        memset(b, 0, byte_size);
        for (int i = 0; i < byte_size; i++) {
            b[i] = 'x';
        }
        total += byte_size;
        printf("Total written to memory: %llu (%lluMiB or %lluGiB)\n", total, total/MB, total/GB);
        sleep(interval_seconds);
    }

    return EXIT_SUCCESS;
}
