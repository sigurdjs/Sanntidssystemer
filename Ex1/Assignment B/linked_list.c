#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

list_t list_create()
{
    list_t new_list = (struct list*)malloc(sizeof(struct list));
    struct node *empty_node = (struct node*)malloc(sizeof(struct node));
    new_list->head = empty_node;
    new_list->tail = empty_node;
    new_list->length = 0;
    return new_list;
}

void list_delete(list_t list)
{
    free(list);
    list = NULL;
}

void list_insert(list_t list, int index, int data)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;

    int current_index = 0;
    struct node *current_node = list->head;
    while(current_index < index - 1) {
        current_node = current_node->next;
        current_index++;
    }
    new_node->prev = current_node;
    new_node->next = current_node->next;
    current_node->next->prev = new_node;
    current_node->next = new_node;
    list->length++;
}

void list_append(list_t list, int data)
{
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->next = NULL;
    new_node->data = data;
    if (list->length > 0) {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    } else {
        new_node->prev = NULL;
        new_node->next = NULL;
        list->head = new_node;
        list->tail = new_node;
    }
    list->length++;
}

void list_print(list_t list)
{
    struct node *current_node = list->head;
    for(int i = 0; i < list->length; i++) {
        printf("Node: %i, Data: %i  ",i,current_node->data);
        if (i % 5 == 0) {
            printf("\n");
        }
        current_node = current_node->next;
    }
    printf("\n");
}

long list_sum(list_t list)
{
    long sum = 0;
    struct node *current_node = list->head;
    for(int i = 0; i < list->length; i++) {
        sum = sum + current_node->data;
        current_node = current_node->next;
    }
    return sum;
}

int list_get(list_t list, int index)
{
    int current_index = 0;
    struct node *current_node = list->head;
    while(current_index < index) {
        current_node = current_node->next;
        current_index++;
    }
    return current_node->data;
}

int list_extract(list_t list, int index)
{
    int current_index = 0;
    struct node *current_node = list->head;
    while(current_index < index) {
        current_node = current_node->next;
        current_index++;
    }
    int data = current_node->data;
    if (index == 0) {
        list->head = current_node->next;
    }
    else if (index == list->length) {
        list->tail = current_node->prev;
    } else {
        current_node->prev->next = current_node->next;
        current_node->next->prev = current_node->prev;
    }
    free(current_node);
    list->length--;
    return data;
}

