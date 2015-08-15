#include <stdlib.h>
#include <stdio.h>
#include "pipe.h"

struct Foo
{
    int a;
    int b;
    int c;
};

void test_draft()
{

    pipe_t* p = pipe_new(sizeof(struct Foo), 0);

    pipe_producer_t* producer = pipe_producer_new(p);
    pipe_consumer_t* consumer = pipe_consumer_new(p);


    printf("sizeof(Foo): %lu\n", sizeof(struct Foo));

    for(int i = 0; i < 22; ++i)
    {
        struct Foo f;
        pipe_push(producer, &f, 1);
    }

    for(int i = 0; i < 22; ++i)
    {
        struct Foo f;
        pipe_pop(producer, &f, 1);
    }

    for(int i = 0; i < 21; ++i)
    {
        printf("i: %d\n", i);
        struct Foo f;
        pipe_push(producer, &f, 1);
        pipe_pop(producer, &f, 1);
    }

    pipe_producer_free(producer);
    pipe_consumer_free(consumer);

    pipe_free(p);
}

int main()
{
    test_draft();
}
