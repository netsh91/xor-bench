#include "_helper.c"


int main(int argc, char **argv)
{
    struct TestSetup *test_setup = test_init(argc, argv);

    clock_t start = clock();

    encrypt(test_setup->buffer1, test_setup->buffer1_size, test_setup->buffer2, test_setup->buffer2_size);

    clock_t  end = clock();

    test_end(start, end, test_setup);

    return 0;
}


void encrypt(uint8_t* data_buffer, size_t data_size, uint8_t* key_buffer, size_t key_size)
{
    size_t key_index = 0;
    size_t buffer_index = 0;

    for (buffer_index = 0; buffer_index < data_size; buffer_index++) {
        if (key_index >= key_size) {
            key_index = 0;
        }
        data_buffer[buffer_index] ^= key_buffer[key_index];
        key_index++;
    }
}