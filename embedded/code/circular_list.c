    #include<stdio.h>

    typedef struct _node{
        int data;
        struct _node * next;
    }node;

    node*head;

    void init(int k) {
        node *t;
        int i;
        t = (node*)calloc(1, sizeof(node));
        t->data = 0;
        head = t;
        for (i = 1; i <= k; i++) {
            t->next = (node*)malloc(sizeof(node));
            t = t->next;
            t->data = i;
        }
        t->next = head;
    }

    void del_after(node*t) {
        node *s;
        s = t->next;
        t->next = t->next->next;
        free(s);
    }

    void josep(int n, int m) {// n = last value = # of peopel   m = interval = 건너뛰는 횟수
        node *t;
        int i;
        init(n);
        t = head;
        printf("\nAnswer : ");
        while (t != t->next) {
            for (i = 0; i < m - 1; i++)
                t = (t->next == head) ? head->next : t->next;
            if (t->next == head) t = head;
            printf("%d ", t->next->data);
            del_after(t);
        }

        printf("\n\ndata of head : ");
        printf("%d", t->data);
    }

    void main() {
        int m, n;
        printf("m & n :");
        scanf_s("%d %d",&m,&n);
        josep(10, 4);
        while (1);
    }