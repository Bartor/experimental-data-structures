#include "cqa.h"

#include <stdlib.h>

CQA* new_cqa(int initial_size) {
    if (initial_size < 2) {
        return NULL;
    }

    CQA* q = malloc(sizeof(CQA));
    q->data = malloc(sizeof(int)*initial_size);
    q->nums = 0;
    q->size = initial_size;
    q->head = initial_size/2 - 1;
    q->tail = initial_size/2;

    return q;
}

void upsize(CQA* q) {
    int* new_data = malloc(sizeof(int) * q->size*2);
    for (int i = 0; i < q->size; i++) {
        new_data[q->size/2 + i] = q->data[(q->head + i + 1) % q->size];
    }
    q->head = q->size/2 - 1;
    q->tail = q->head + q->nums + 1;
    q->size *= 2;
    free(q->data);
    q->data = new_data;
}

void downsize(CQA* q) {
    int* new_data = malloc(sizeof(int) * q->size/2 + 1);
    for (int i = 0; i < q->nums; i++) {
        new_data[q->size/4 + i] = q->data[(q->head + i + 1) % q->size];
    }
    q->head = q->size/4 - 1;
    q->tail = q->head + q->nums + 1;
    q->size /= 2;
    free(q->data);
    q->data = new_data;
}

void push_head(CQA* q, int value) {
    if (q->nums == q->size) {
        upsize(q);
        push_head(q, value);
    } else {
        if (q->head > 0) {
            q->data[q->head--] = value;
        } else {
            q->data[q->head] = value;
            q->head = q->size - 1;
        }
        q->nums++;
    }
}

void push_tail(CQA* q, int value) {
    if (q->nums == q->size) {
        upsize(q);
        push_tail(q, value);
    } else {
        if (q->tail < q->size - 1) {
            q->data[q->tail++] = value;
        } else {
            q->data[q->tail] = value;
            q->tail = 0;
        }
        q->nums++;
    }
}

int pop_head(CQA* q) {
    if (q->nums == 0) {
        //this should be a null pointer really
        perror("empty");
        return -1;
    }
    if (q->nums == q->size/4) {
        downsize(q);
        return pop_head(q);
    } else {
        q->nums--;
        if (q->head < q->size - 1) {
            return q->data[++q->head];
        } else {
            return q->data[q->head = 0];
        }
    }
}

int pop_tail(CQA* q) {
    if (q->nums == 0) {
        //this should be a null pointer really
        perror("empty");
        return -1;
    }
    if (q->nums == q->size/4) {
        downsize(q);
        return pop_tail(q);
    } else {
        q->nums--;
        if (q->tail > 0) {
            return q->data[--q->tail];
        } else {
            return q->data[q->tail = q->size - 1];
        }
    }
}