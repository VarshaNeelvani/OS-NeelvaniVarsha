#include <stdio.h>

int p, r;

void avai(int all[p][r], int tot[r], int avail[r]) {
    for (int j = 0; j < r; j++) {
        avail[j] = 0;
        for (int k = 0; k < p; k++) {
            avail[j] += all[k][j];
        }
    }
    for (int j = 0; j < r; j++) {
        avail[j] = tot[j] - avail[j];
    }
}

void need1(int all[p][r], int max[p][r], int needmat[p][r]) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            needmat[i][j] = max[i][j] - all[i][j];
        }
    }
}

void safety(int p, int r, int all[p][r], int avail[r], int needmat[p][r], int seq[p]) {
    int f[p], c, count = 0, h = 0;
    for (int i = 0; i < p; i++) {
        f[i] = 0;
    }
    while (count < p && h < p) {
        for (int i = 0; i < p; i++) {
            if (f[i] == 0) {
                c = 0;
                for (int j = 0; j < r; j++) {
                    if (needmat[i][j] <= avail[j]) {
                        c++;
                    }
                }
                if (c == r) {
                    printf("P%d is visited(\t",i);
                    for (int k = 0; k < r; k++) {
                        avail[k] += all[i][k];
                        printf("%d",avail[k]);
                        printf("\t");

                    }
                    printf(")\n");
                    f[i] = 1;
                    count++;
                    seq[h] = i;
                    h++;

                }
            }
        }
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &p);
    printf("Enter the number of resources: ");
    scanf("%d", &r);

    int tot[r], needmat[p][r], avail[r], seq[p];
    printf("Enter the total instances of each resource: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &tot[i]);
    }

    int all[p][r], max[p][r];
    printf("Enter the details of each process (allocation matrix):\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &all[i][j]);
        }
    }

    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    avai(all, tot, avail);
    need1(all, max, needmat);

    printf("Need matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            printf("%d\t", needmat[i][j]);
        }
        printf("\n");
    }

    safety(p, r, all, avail, needmat, seq);

    printf("Safe sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("P%d\t", seq[i]);
    }
    return 0;
}
