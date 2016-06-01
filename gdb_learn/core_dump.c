#include <stdio.h>
char *str = "test";
void core_test(){
    str[1] = 'T';
}

int main(){
    core_test();
    return 0;
}
