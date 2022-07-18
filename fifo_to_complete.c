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
} fifo;


// Create a new string FIFO object that can contain up to size elements.
struct fifo *fifo_new(int size) {
    /* TODO: COMPLETE THIS PART */
    struct fifo *container = NULL;

    if (size < 0) {
        return NULL;
    }
    if (container = calloc(1, sizeof(struct fifo) + (sizeof(char *) * (unsigned long)size)), container == NULL) {
        fprintf(stderr, "ERR: calloc %d %s\n", errno, strerror(errno));
        return NULL;
    }
    container->size = size;
    container->empty = 1;
    return container;
}

// Free a FIFO object and all its contents.
void fifo_free(struct fifo *fifo) {
    /* TODO: COMPLETE THIS PART */
    if (fifo != NULL) {
        if (fifo->contents != NULL) {
            for (int i = 0; i < fifo->size; ++i) {
                if (fifo->contents[i] != NULL) {
                   free(fifo->contents[i]);
                }
            }
            bzero(fifo->contents, sizeof(char *) * fifo->size);
        }
        bzero(fifo, sizeof(struct fifo));
        free(fifo);
    }
}

// Push a string into the FIFO.
// Returns whether there was space in the FIFO to store the string.
// If successful, the FIFO stores a copy of the string dynamically allocated on the heap.
// If unsuccessful, the FIFO remains unchanged and no memory is allocated.
int fifo_push(struct fifo *fifo, const char *str) {
    /* TODO: COMPLETE THIS PART */
    int str_sz = 0;
    char *str_cpy = NULL;
    int space = 0;

    if (fifo == NULL || fifo->contents == NULL) return 0;
    space = (fifo->size - fifo->produce) + fifo->consume;
    if (str == NULL) return space;
    if (space <= 0 || ((space == fifo->size) && (fifo->empty == 0))) return 0;

    str_sz = strlen(str);
    str_cpy = calloc(str_sz, sizeof(char));
    memcpy(str_cpy, str, str_sz);
    fifo->contents[fifo->produce] = str_cpy;
    fifo->produce = (fifo->produce + 1) % fifo->size;
    fifo->empty = 0;
    return space;
}

// Pull a string from the FIFO.
// Returns NULL if the FIFO is empty.
// If the returned value is not NULL, the caller takes ownership of the string and 
// is responsible for freeing it.
char *fifo_pull(struct fifo *fifo) {
    /* TODO: COMPLETE THIS PART */
    char *str = NULL;
    int space = 0;

    if (fifo == NULL || fifo->contents == NULL) return NULL;

    if (fifo->produce < fifo->consume) {
        space = fifo->consume - fifo->produce;
    } else if (fifo->consume < fifo->produce) {
        space = fifo->produce - fifo->consume;
    } else if (fifo->empty == 0) {
        space = fifo->size;
    } else if (fifo->empty != 0) {
        return NULL;
    }
    if (space <= 0) {
        return NULL;
    }
    str = fifo->contents[fifo->consume];
    fifo->contents[fifo->consume] = NULL;
    fifo->consume = (fifo->consume + 1) % fifo->size;
    if (fifo->consume == fifo->produce) {
        fifo->empty = 1;
    }
    return str;
}

void fifo_dump(struct fifo *fifo) {
    char *str;
    while(str = fifo_pull(fifo), str) {
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
