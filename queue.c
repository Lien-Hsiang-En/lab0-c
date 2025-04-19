#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    struct list_head head; /* 環狀鏈結哨兵 */
    size_t size;           /* 佇列長度，方便 O(1) 取值 */
} queue_t;

/* 方便透過 head 找回 queue_t */
static inline queue_t *to_queue(struct list_head *head)
{
    return container_of(head, queue_t, head);
}

/* ---------- 基本工具 ---------- */

static inline void list_swap_pair(struct list_head *first)
{
    struct list_head *second = first->next;
    list_del(second);
    list_add(second, first->prev); /* 插到 first 前面 */
}

/* 反轉 [first, last]（包含兩端），不包含 head。
 * 傳回反轉後的新起點（原本的 last）。 */
static struct list_head *reverse_segment(struct list_head *first,
                                         struct list_head *last)
{
    struct list_head *cur = first, *nxt;
    /* 迭代到 last (包含) 為止 */
    while (cur != last) {
        nxt = cur->next;
        list_move(cur, last); /* 每次把 cur 移到 last 之後 */
        cur = nxt;
    }
    return last; /* 此時 last 已變成 segment 新起點 */
}

element_t *create_new_element(char *s)
{
    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element)
        return NULL;
    new_element->value = strdup(s);
    if (!new_element->value) {
        free(new_element);
        return NULL;
    }
    return new_element;
}

/* Create an empty queue */
struct list_head *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    INIT_LIST_HEAD(&q->head);
    q->size = 0;
    return &q->head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;
    while (!list_empty(head)) {
        element_t *e = list_first_entry(head, element_t, list);
        list_del(&e->list);
        q_release_element(e);
    }
    free(to_queue(head));
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *new_element = create_new_element(s);
    if (!new_element)
        return false;
    list_add(&new_element->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *new_element = create_new_element(s);
    if (!new_element)
        return false;
    list_add_tail(&new_element->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    return NULL;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return NULL;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    return -1;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
