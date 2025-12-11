#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int x, deg, mark;
    struct Node *par, *ch, *lc, *rc;
} Node;

typedef struct Heap {
    Node *min;
    int n;
} Heap;

Node* create_node(int x) {
    Node *node = malloc(sizeof(Node));
    node->x = x;
    node->deg = node->mark = 0;
    node->par = node->ch = NULL;
    node->lc = node->rc = node;
    return node;
}

Heap* build() {
    Heap* heap = malloc(sizeof(Heap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

void insert(Heap *h, Node *node) {
    if (h->min == NULL) {
        h->min = node;
    } else {
        node->lc = h->min;
        node->rc = h->min->rc;
        h->min->rc->lc = node;
        h->min->rc = node;
        if (node->x < h->min->x)
            h->min = node;
    }
    h->n += 1;
}

void print_tree(Node *rt) {
    if (rt == NULL) return;
    Node **nodes = malloc(sizeof(Node*) * 100);
    int head = 0, tail = 1;
    nodes[0] = rt;
    while (head < tail) {
        Node *node = nodes[head++];
        printf("%d ", node->x);
        if (node->ch != NULL) {
            Node *ch = node->ch, *start = node->ch;
            do {
                nodes[tail++] = ch;
                ch = ch->rc;
            } while (ch != start);
        }
    }
}

bool compare_degree(Node *n1, Node *n2) {
    return (n1->deg < n2->deg || (n1->deg == n2->deg && n1->x < n2->x));
}

bool compare_key(Node *n1, Node *n2) {
    return n1->x < n2->x;
}

void merge_sort(Node **nodes, int l, int r, bool cmp_func(Node*, Node*)) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    merge_sort(nodes, l, mid, cmp_func);
    merge_sort(nodes, mid + 1, r, cmp_func);
    Node **tmp = malloc(sizeof(Node*) * (r - l + 1));
    int pl = l, pr = mid + 1, id = 0;
    while (pl <= mid && pr <= r) {
        if (cmp_func(nodes[pl], nodes[pr]))
            tmp[id++] = nodes[pl++];
        else
            tmp[id++] = nodes[pr++];
    }
    while (pl <= mid)
        tmp[id++] = nodes[pl++];
    while (pr <= r)
        tmp[id++] = nodes[pr++];
    for (int i = l; i <= r; i++)
        nodes[i] = tmp[i - l];
}

int get_all_siblings(Node *node, Node **rts) {
    if (node == NULL) return 0;
    int rt_cnt = 0;
    rts[0] = node;
    for (int i = 1; ; i++) {
        rts[i] = rts[i - 1]->rc;
        if (rts[i] == rts[0]) {
            rt_cnt = i;
            break;
        }
    }
    return rt_cnt;
}

void print_nodes_with_degree(Heap *h) {
    Node **rts;
    rts = malloc(sizeof(Node*) * 100);
    int rt_cnt = get_all_siblings(h->min, rts);
    if (rt_cnt == 0) return;
    merge_sort(rts, 0, rt_cnt - 1, compare_degree);
    for (int i = 0; i < rt_cnt; i++) {
        print_tree(rts[i]);
        printf("\n");
    }
} 

void consolidate(Heap *h) {
    Node **rts;
    rts = malloc(sizeof(Node*) * 100);
    int rt_cnt = get_all_siblings(h->min, rts);
    merge_sort(rts, 0, rt_cnt - 1, compare_key);
    Node **deg_node;
    deg_node = malloc(sizeof(Node*) * 100);
    for (int i = 0; i < 100; i++) deg_node[i] = NULL;
    for (int i = 0; i < rt_cnt; i++) {
        Node *cur = rts[i];
        int deg = cur->deg;
        while (deg_node[deg] != NULL) {
            Node *son = deg_node[deg];
            deg_node[deg] = NULL;
            if (cur->x > son->x) {
                Node *tmp = cur;
                cur = son;
                son = tmp;
            }
            if (deg == 0) {
                son->lc = son->rc = son;
                son->par = cur;
                cur->lc = cur->rc = cur;
                cur->ch = son;
            } else {
                son->lc = cur->ch->lc;
                son->rc = cur->ch;
                cur->ch->lc->rc = son;
                cur->ch->lc = son;
                son->par = cur;
            }
            deg += 1;
            cur->deg = deg;
            // sort child by degree
            Node **childs;
            childs = malloc(sizeof(Node*) * 100);
            int child_cnt = get_all_siblings(cur->ch, childs);
            merge_sort(childs, 0, child_cnt - 1, compare_key);
            cur->ch = childs[0];
            for (int i = 1; i < child_cnt; i++) {
                childs[i - 1]->rc = childs[i];
                childs[i]->lc = childs[i - 1];
            }
            childs[0]->lc = childs[child_cnt - 1];
            childs[child_cnt - 1]->rc = childs[0];
        }
        deg_node[deg] = cur;
    }
    h->min = NULL;
    Node *start = NULL, *lst = NULL;
    for (int i = 0; i < 100; i++) {
        if (deg_node[i] != NULL) {
            if (start == NULL)
                start = deg_node[i];
            if (h->min == NULL) {
                h->min = lst = deg_node[i];
            } else {
                if (deg_node[i]->x < h->min->x)
                    h->min = deg_node[i];
                lst->rc = deg_node[i];
                deg_node[i]->lc = lst;
                lst = deg_node[i];
            }
        }
    }
    start->lc = lst;
    lst->rc = start;
}

Node *extract_min(Heap *h) {
    Node *del = h->min;
    if (del != NULL) {
        Node *child = del->ch;
        if (child != NULL) {
            Node *start_child = child, *last_child = child->lc;
            do {
                child->par = NULL;
                child = child->rc;
            } while (child != start_child);
            del->lc->rc = start_child;
            start_child->lc = del->lc;
            del->rc->lc = last_child;
            last_child->rc = del->rc;
        } else {
            del->lc->rc = del->rc;
            del->rc->lc = del->lc;
        }
        if (del == del->rc) {
            h->min = NULL;
        } else {
            h->min = del->rc;
            consolidate(h);
        }
        h->n -= 1;
    }
    return del;
}

void cut(Heap *h, Node *node, Node *par) {
    if (node->rc == node) {
        par->ch = NULL;
    } else {
        par->ch = node->rc;
        node->lc->rc = node->rc;
        node->rc->lc = node->lc;
    }
    par->deg -= 1;
    node->lc = h->min;
    node->rc = h->min->rc;
    h->min->rc->lc = node;
    h->min->rc = node;
    node->par = NULL;
    node->mark = 0;
}

void put_tag(Heap *h, Node *node) {
    Node *par = node->par;
    if (par != NULL) {
        if (node->mark == 0) {
            node->mark = 1;
        } else {
            cut(h, node, par);
            put_tag(h, par);
        }
    }
}

void decrease_key(Heap *h, Node *node, int x) {
    node->x -= x;
    Node *parent = node->par;
    if (parent != NULL && node->x < parent->x) {
        cut(h, node, parent);
        put_tag(h, parent);
    }
    if (node->x < h->min->x)
        h->min = node;
}

void delete_key(Heap* heap, Node* node) {
    decrease_key(heap, node, 1000000);
    Node* min_node = extract_min(heap);
    if (min_node) free(min_node);
}

Node *find_value(Node *node, int x) {
    if (node == NULL) return NULL;
    Node *start = node;
    do {
        if (node->x == x) return node;
        if (node->ch != NULL) {
            Node *res = find_value(node->ch, x);
            if (res != NULL) return res;
        }
        node = node->rc;
    } while (node != start);
    return NULL;
}

int main() {
    Heap *h = build();
    char s[15];
    while (scanf("%s", s) != EOF) {
        if (s[0] == 'e' && s[1] == 'x' && s[2] == 'i')
            break;
        if (s[0] == 'i') {
            int x;
            scanf("%d", &x);
            insert(h, create_node(x));
        } else if (s[0] == 'd' && s[1] == 'e' && s[2] == 'l') {
            int x;
            scanf("%d", &x);
            Node *node = find_value(h->min, x);
            if (node != NULL) delete_key(h, node);
        } else if (s[0] == 'd' && s[1] == 'e' && s[2] == 'c') {
            int x, y;
            scanf("%d %d", &x, &y);
            Node *node = find_value(h->min, x);
            if (node != NULL) decrease_key(h, node, y);
        } else if (s[0] == 'e' && s[1] == 'x' && s[2] == 't') {
            extract_min(h);
        }
    }
    print_nodes_with_degree(h);
}
