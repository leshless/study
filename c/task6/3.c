#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
    int x;
    struct list *next;
};

int main(void){
    FILE* in = fopen("input.txt", "r+");

    struct list* head = malloc(sizeof(struct list));
    struct list* cur = head;

    int n = 0;
    int x;
    
    while (fscanf(in, "%d", &x) != EOF){
        struct list *next = malloc(sizeof(struct list));
        next->x = x;
        next->next = NULL;

        cur->next = next;
        cur = next;

        n++;
    }

    fclose(in);

    while (n--){
        struct list* cur = head->next;

        while (cur->next != NULL){
            struct list* next = cur->next;

            if (cur->x > next->x){
                int t = cur->x;

                cur->x = next->x;
                next->x = t;
            }else {
                cur = cur->next;
            }
        }
    }

    FILE* out = fopen("output.txt", "w+");

    cur = head->next;
    free(head);
    
    while (cur != NULL){
        fprintf(out, "%d ", cur->x);

        struct list* next = cur->next;
        free(cur);        
        cur = next;    
    }


    fclose(out);


    return 0;
}   