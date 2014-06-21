#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int a, b;
    
    scanf("%d %d", &a, &b);
    printf("%d\n", a + b);
    // open("asdf", O_CREAT);
    
    return 0;
}
