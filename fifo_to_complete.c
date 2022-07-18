#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct fifo {
    int size;
    int empty;
    int produce;
    int consume;
    char *contents[];
};


// Create a new string FIFO object that can contain up to size elements.
struct fifo *fifo_new(int size) {
    // COMPLETE THIS PART
    if (size < 0) {
        return NULL;
    }
    struct fifo *container = NULL;
    if (container = calloc(1, sizeof(struct fifo), container == NULL)) {
        fprintf(stderr, "ERR: calloc %d %s\n", errno, strerror(errno));
        return NULL;
    }
    container->contents = NULL;
    if (calloc(size, sizeof(char *)), container->contents == NULL) {
        fprintf(stderr, "ERR: calloc %d %s\n", errno, strerror(errno));
    }
}

// Free a FIFO object and all its contents.
void fifo_free(struct fifo *fifo) {
    // COMPLETE THIS PART
    if (fifo != NULL) {
        if (fifo->contents != NULL) {
            bzero(fifo->contents, sizeof(char *) * size);
            free(fifo->contents);
        }
        bzero(fifo, sizeof(struct fifo));
        memset(fifo);
        free(fifo);
    }
}

// Push a string into the FIFO.
// Returns whether there was space in the FIFO to store the string.
// If successful, the FIFO stores a copy of the string dynamically allocated on the heap.
// If unsuccessful, the FIFO remains unchanged and no memory is allocated.
int fifo_push(struct fifo *fifo, const char *str) {
    // COMPLETE THIS PART
}

// Pull a string from the FIFO.
// Returns NULL if the FIFO is empty.
// If the returned value is not NULL, the caller takes ownership of the string and 
// is responsible for freeing it.
char *fifo_pull(struct fifo *fifo) {
    // COMPLETE THIS PART
}

void fifo_dump(struct fifo *fifo) {
    char *str;
    while(str = fifo_pull(fifo)) {
        printf("%s\n", str);
        free(str);
    }
}

#define TEST(condition) if(!(condition)) { printf("TEST FAILED\n"); return 1; }

int main() {
    struct fifo *fifo;
    char *str;

    fifo = fifo_new(4);
    TEST(fifo_push(fifo, "hello"));
    TEST(fifo_push(fifo, "world"));
    fifo_dump(fifo);
    fifo_free(fifo);

    fifo = fifo_new(4);
    TEST(fifo_push(fifo, "elem1"));
    TEST(fifo_push(fifo, "elem2"));
    TEST(fifo_push(fifo, "elem3"));
    TEST(fifo_push(fifo, "elem4"));
    fifo_dump(fifo);
    TEST(fifo_push(fifo, "A"));
    fifo_dump(fifo);
    TEST(fifo_push(fifo, "X"));
    TEST(fifo_push(fifo, "Y"));
    TEST(fifo_push(fifo, "Z"));
    TEST(fifo_push(fifo, "T"));
    TEST(!fifo_push(fifo, "U"));
    fifo_dump(fifo);
    fifo_free(fifo);

    fifo = fifo_new(4);
    TEST(fifo_push(fifo, "elem1"));
    TEST(fifo_push(fifo, "elem2"));
    TEST(fifo_push(fifo, "elem3"));
    TEST(fifo_push(fifo, "elem4"));
    fifo_free(fifo);

    fifo = fifo_new(4);
    TEST(fifo_push(fifo, "elem1"));
    TEST(fifo_push(fifo, "elem2"));
    str = fifo_pull(fifo);
    TEST(!strcmp(str, "elem1"));
    free(str);
    TEST(fifo_push(fifo, "elem3"));
    TEST(fifo_push(fifo, "elem4"));
    str = fifo_pull(fifo);
    TEST(!strcmp(str, "elem2"));
    free(str);
    str = fifo_pull(fifo);
    TEST(!strcmp(str, "elem3"));
    free(str);
    str = fifo_pull(fifo);
    TEST(!strcmp(str, "elem4"));
    free(str);
    fifo_free(fifo);

    return 0;
}
