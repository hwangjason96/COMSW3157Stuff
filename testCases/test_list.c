#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "linked_list.h"

// Portable strdup replacement (POSIX strdup isn't guaranteed)
static char *my_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy != NULL) {
        memcpy(copy, s, len);
    }
    return copy;
}

static int cmp_str(const void *a, const void *b) {
    const char *sa = (const char *)a;
    const char *sb = (const char *)b;
    return strcmp(sa, sb);
}

static void free_str(void *p) {
    free(p);
}

static void check_invariants(linked_list *list) {
    assert(list != NULL);

    if (list->size == 0) {
        assert(list->head == NULL);
        assert(list->tail == NULL);
        return;
    }

    assert(list->head != NULL);
    assert(list->tail != NULL);

    // For a well-formed doubly linked list:
    assert(list->head->prev == NULL);
    assert(list->tail->next == NULL);

    // Forward walk: verify prev links and count
    size_t count = 0;
    node *prev = NULL;

    for (node *cur = list->head; cur != NULL; cur = cur->next) {
        assert(cur->prev == prev);
        prev = cur;
        count++;
        // guard against cycles
        assert(count <= list->size + 2);
    }

    assert(count == list->size);
    assert(prev == list->tail);

    // Backward walk: verify next links and count
    count = 0;
    node *next = NULL;

    for (node *cur = list->tail; cur != NULL; cur = cur->prev) {
        assert(cur->next == next);
        next = cur;
        count++;
        assert(count <= list->size + 2);
    }

    assert(count == list->size);
    assert(next == list->head);
}

static void check_sorted(linked_list *list) {
    if (list == NULL) return;

    // First pass: verify ordering
    for (node *cur = list->head; cur != NULL && cur->next != NULL; cur = cur->next) {
        const char *a = (const char *)cur->data;
        const char *b = (const char *)cur->next->data;

        if (strcmp(a, b) > 0) {
            fprintf(stderr, "NOT SORTED: '%s' then '%s'\n", a, b);
            assert(0);
        }
    }

    // If we reach here, list is sorted → print it once
    printf("Sorted! Current list: [");
    for (node *cur = list->head; cur != NULL; cur = cur->next) {
        printf("%s", (char *)cur->data);
        if (cur->next != NULL) printf(", ");
    }
    printf("]\n");
}

static void snapshot(linked_list *list, const char **out, size_t cap) {
    assert(list != NULL);
    assert(list->size <= cap);

    size_t i = 0;
    for (node *cur = list->head; cur != NULL; cur = cur->next) {
        out[i++] = (const char *)cur->data;
    }
}

int main(void) {
    puts("=== linked_list tests (strings, no print_list) ===");

    linked_list *list = create_linked_list();
    assert(list != NULL);
    assert(list->size == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    check_invariants(list);
    puts("[OK] create_linked_list");

    // Insert out-of-order, including duplicates
    const char *inputs[] = {"delta", "alpha", "charlie", "bravo", "bravo", "echo", "alpha"};
    const size_t n_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < n_inputs; i++) {
        char *s = my_strdup(inputs[i]);
        assert(s != NULL);

        bool ok = insert_in_order(list, s, cmp_str);
        assert(ok == true);

        // After each insert, size should match i+1
        assert(list->size == i + 1);

        check_invariants(list);
        check_sorted(list);
    }
    puts("[OK] insert_in_order maintains invariants + sorted order");

    // Expected final sorted order (duplicates after existing equals)
    const char *expected[] = {"alpha", "alpha", "bravo", "bravo", "charlie", "delta", "echo"};
    const size_t n_exp = sizeof(expected) / sizeof(expected[0]);
    assert(list->size == n_exp);

    const char *got[32] = {0};
    snapshot(list, got, 32);

    for (size_t i = 0; i < n_exp; i++) {
        assert(strcmp(got[i], expected[i]) == 0);
    }
    puts("[OK] final order matches expected");

    free_list(list, free_str);
    puts("[OK] free_list");

    puts("=== ALL TESTS PASSED ===");
    return 0;
}
