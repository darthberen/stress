#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define USAGE \
"Usage:\n" \
"    memory_stressor [seconds] [size]\n" \
"Options:\n" \
"    seconds: the time interval in seconds that the memory coordinator will \n" \
"             malloc memory\n" \
"    size: the size in bytes to be allotted in memory each interval\n"

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

    byte_size = atoi(argv[1]);
    if (byte_size <= 0) {
        fprintf(stderr, "Invalid value '%lu' for byte size\n", byte_size);
        return EXIT_FAILURE;
    }

    return stress(interval_seconds, byte_size);
}

int stress(int interval_seconds, unsigned long byte_size) {
    while (true) {
        malloc(byte_size);
        sleep(interval_seconds);
    }

    return EXIT_SUCCESS;
}
