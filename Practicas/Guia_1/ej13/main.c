#include <stdio.h>
#define N 15

int main() {
    int i;

    for(i = 1; i <= N; i++) {
        if (i % 2 == 0)
            printf("%d ",i);
    }

    return 0;
}
