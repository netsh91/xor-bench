# xor-bench

This project was supposed to become a file encryption program, 
but getting it run faster turned out to be much more exiting.

Given a naive algorithm:

```c
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
```

Which xor^s continuously a buffer with key,
how much faster can it get by optimizing the code?

Additionally see how different compilers and 
compiler optimizations affect performance.