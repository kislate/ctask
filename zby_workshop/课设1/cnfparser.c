#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cnfparser.h"

Formula* parse_cnf(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { printf("无法打开文件\n"); return NULL; }
    Formula *F = (Formula*)malloc(sizeof(Formula));
    F->head = NULL;
    F->var_num = 0;
    F->clause_num = 0;
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == 'c') continue;
        if (line[0] == 'p') {
            sscanf(line, "p cnf %d %d", &F->var_num, &F->clause_num);
            continue;
        }
        int lits[1024], cnt = 0, x;
        char *p = line;
        while (sscanf(p, "%d", &x) == 1 && x != 0) {
            lits[cnt++] = x;
            while (*p && *p != ' ') p++;
            while (*p == ' ') p++;
        }
        if (cnt > 0) {
            Clause *cl = (Clause*)malloc(sizeof(Clause));
            cl->literals = (int*)malloc(cnt * sizeof(int));
            memcpy(cl->literals, lits, cnt * sizeof(int));
            cl->len = cnt;
            cl->next = F->head;
            F->head = cl;
        }
    }
    fclose(fp);
    return F;
}

void print_formula(Formula *F) {
    Clause *cl = F->head;
    int idx = 1;
    while (cl) {
        printf("Clause %d: ", idx++);
        for (int i = 0; i < cl->len; i++)
            printf("%d ", cl->literals[i]);
        printf("0\n");
        cl = cl->next;
    }
}

void free_formula(Formula *F) {
    Clause *cl = F->head;
    while (cl) {
        Clause *next = cl->next;
        free(cl->literals);
        free(cl);
        cl = next;
    }
    free(F);
}