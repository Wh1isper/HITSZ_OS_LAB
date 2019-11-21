#include <cstdio>
#include "Producer_Consumers_thread.h"

void *print_usage(int argc, char *argv[]) {
    printf("Usage: %s M(docs) N(seat) P(patients)\n", argv[0]);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 4)
        print_usage(argc, argv);
    int M = atoi(argv[1]);  // 医生
    int N = atoi(argv[2]);  // 椅子
    int P = atoi(argv[3]);  // 患者
    if (M < 0 || N < 0 || P < 0)
        print_usage(argc, argv);
    else
        printf("%d个医生, %d个座位, %d个病人\n", M, N, P);
    Producer_Consumers_thread mission(M, N, P);
    mission.start();
    return 0;
}