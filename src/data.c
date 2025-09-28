#include "data.h"

struct gap_buffer
{
    int  size;
    char buffer[BUFFER_MAX_SIZE];
    int  start_gap;
    int  end_gap;
};

struct linked_gap_buffer
{
    struct* gap_buffer cell;
    struct* gap_buffer next;
};
