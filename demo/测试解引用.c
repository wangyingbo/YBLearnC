#include <stdio.h>

int main() {
    int arr[3] = {10, 20, 30};
    int *sp = arr;

    printf("Before increment: sp = %p, *sp = %d\n", (void*)sp, *sp);

    int result = *sp++;  // 解引用当前 sp 的值，然后 sp 自增

    printf("result: %d\n", result);
    printf("After increment: sp = %p, *sp = %d\n", (void*)sp, *sp);

    return 0;
}


// 输出
/*
Before increment: sp = 0x16b9d2f98, *sp = 10
result: 10
After increment: sp = 0x16b9d2f9c, *sp = 20
*/