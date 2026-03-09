#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"



linked_list* create_linked_list(){
	linked_list *newList = (linked_list *)malloc(sizeof(linked_list));
	if (newList != NULL) {
		newList->size = 0;
		newList->head = NULL;
		newList->tail = NULL;
	}
	return newList;
}

bool insert_in_order(
    linked_list *list, void *data, int (*cmp)(const void*, const void*)){
        //Edge cases:
        //1. List is NULL, return false
        if (list == NULL) {return false;}

        //create the node, (the create_node does not account for a failed malloc)
        node *insert = create_node(data);
        if (insert == NULL) {return false;}

        //2. Head is NULL (list is empty)
        if(list->head == NULL) {
                //set head and tail as insert. prev and next are already NULL
                list->head = insert;
                list->tail = insert;
                list->size++;
                return true;
        }

        //3. the data is greater than or equal to tail
        if(cmp(data,list->tail->data) >= 0){
                //set the dummy to tail, insert's prev is tail, tail's next is insert
                // and tail is now insert.
                node *dummy = list->tail;
                if(dummy == NULL) {return false;}

                insert->prev = dummy;
                dummy->next = insert;
                list->tail = insert;
                list->size++;
                return true;
        }

        //4. the data is less than or equal to the head
        if(cmp(data,list->head->data) < 0){
                node *dummy = list->head;
                if(dummy == NULL) {return false;}

                insert->next = dummy;
                dummy->prev = insert;
                list->head = insert;
                list->size++;
                return true;
        }

        //traverse to the end until the data is smaller than the current
        node *dummy = list->head;
        if(dummy == NULL) {return false;}
        while(dummy->next != NULL && cmp(data,dummy->data) >= 0){
                dummy = dummy->next;
        }
        //For all else:
        // ->insert<-
        //prev(<->)dummy<->next
        insert->next = dummy;
        insert->prev = dummy->prev;
        dummy->prev->next = insert;
        dummy->prev = insert;
        list->size++;
        return true;
}

void print_list(linked_list *list, void (*print_function)(void*)) {
    putchar('[');
    node *cur = list->head;
    if (cur != NULL) {
        print_function(cur->data);
        cur = cur->next;
    }
    for ( ; cur != NULL; cur = cur->next) {
        printf(", ");
        print_function(cur->data);
    }
    printf("]\n{length: %lu, head->data: ", list->size);
    list->head != NULL ? print_function(list->head->data) :
                         (void)printf("NULL");
    printf(", tail->data: ");
    list->tail != NULL ? print_function(list->tail->data) :
                         (void)printf("NULL");
    printf("}\n\n");
}

void free_list(linked_list *list, void (*free_data)(void *)){
	if (list == NULL) {return;}
	node *dummy = list->head;
	while(dummy != NULL) {
		node *toFree = dummy->next;
		free_node(dummy, free_data);
		dummy = toFree;
	}
	free(list);
}
