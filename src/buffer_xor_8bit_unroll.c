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

    size_t const unroll_factor = 16;
    size_t fast_loop_limit = ((size_t)data_size / (1 * unroll_factor)) * unroll_factor;

    for (buffer_index = 0; buffer_index < fast_loop_limit; buffer_index += unroll_factor) {
        if (key_index >= key_size) {
            key_index = 0;
        }
        data_buffer[buffer_index+0] ^= key_buffer[key_index+0];
        data_buffer[buffer_index+1] ^= key_buffer[key_index+1];
        data_buffer[buffer_index+2] ^= key_buffer[key_index+2];
        data_buffer[buffer_index+3] ^= key_buffer[key_index+3];
        data_buffer[buffer_index+4] ^= key_buffer[key_index+4];
        data_buffer[buffer_index+5] ^= key_buffer[key_index+5];
        data_buffer[buffer_index+6] ^= key_buffer[key_index+6];
        data_buffer[buffer_index+7] ^= key_buffer[key_index+7];
        data_buffer[buffer_index+8] ^= key_buffer[key_index+8];
        data_buffer[buffer_index+9] ^= key_buffer[key_index+9];
        data_buffer[buffer_index+10] ^= key_buffer[key_index+10];
        data_buffer[buffer_index+11] ^= key_buffer[key_index+11];
        data_buffer[buffer_index+12] ^= key_buffer[key_index+12];
        data_buffer[buffer_index+13] ^= key_buffer[key_index+13];
        data_buffer[buffer_index+14] ^= key_buffer[key_index+14];
        data_buffer[buffer_index+15] ^= key_buffer[key_index+15];
        key_index += unroll_factor;
    }

    key_index = fast_loop_limit / key_size;
    for (buffer_index = fast_loop_limit; buffer_index < data_size; buffer_index++) {
        if (key_index >= key_size) {
            key_index = 0;
        }
        data_buffer[buffer_index] ^= key_buffer[key_index];
        key_index++;
    }
}