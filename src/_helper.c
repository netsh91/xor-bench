#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <time.h>


struct TestSetup {
    uint8_t* buffer1;
    size_t buffer1_size;
    uint8_t* buffer2;
    size_t buffer2_size;
};


void encrypt(uint8_t* data_buffer, size_t data_size, uint8_t* key_buffer, size_t key_size);


struct TestSetup *test_init(int argc, char **argv)
{
    if(argc != 3) {
        printf ("Usage: buffer_size_1 buffer_size_1 \n");
        return 0;
    }

    size_t buffer1_size = (size_t)strtol(argv[1], NULL, 10);
    size_t buffer2_size = (size_t)strtol(argv[2], NULL, 10);
    // size_t buffer1_size = 1024 * 1024 * 1024;
    // size_t buffer2_size = 1024 * 1024 * 1024;

    struct TestSetup *test_setup = aligned_alloc(32, sizeof(struct TestSetup));
    if (test_setup == NULL) {
        printf ("Failed to allocate memory \n");
        return 0;
    }

    test_setup->buffer1 = aligned_alloc(32, buffer1_size);
    test_setup->buffer1_size = buffer1_size;
    // buffer1 warm-up/fill
    for(size_t ii = 0; ii < buffer1_size; ii++) {
        test_setup->buffer1[ii] = 1;
    }

    test_setup->buffer2 = aligned_alloc(32, buffer2_size);
    test_setup->buffer2_size = buffer2_size;
    // buffer2 warm-up/fill
    for(size_t ii = 0; ii < buffer2_size; ii++) {
        test_setup->buffer2[ii] = 1;
    }


    if (test_setup->buffer1 == NULL || test_setup->buffer2 == NULL) {
        printf ("Failed to allocate memory \n");
        return 0;
    }

    return test_setup;
}


void test_end(clock_t start, clock_t end, struct TestSetup *test_setup)
{
    printf("time %Lf \n", (long double)(end - start));
    printf("file size %lu \n", test_setup->buffer1_size);
    printf("%f Mb/s\n\n", ((((float)test_setup->buffer1_size/((float)(end - start)/(float)1000000))/(float)1024)/(float)1024));
}