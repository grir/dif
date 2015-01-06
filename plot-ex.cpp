#include <cstdio>

int main(){
 std::FILE *f = popen("gnuplot", "w");
 std::fputs("plot sin(x)\n", f);
 std::fflush(f);
 //int a;
 //scanf("%d", &a);
 getchar();
 std::fclose(f);

 return 0;
}

