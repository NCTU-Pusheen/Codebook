//gcc專用
//unsigned int ffs
//unsigned long ffsl
//unsigned long long ffsll
unsigned int x; scanf("%u",&x)
printf("右起第一個1:的位置");
printf("%d\n",__builtin_ffs(x));
printf("左起第一個1之前0的個數:");
printf("%d\n",__builtin_clz(x));
printf("右起第一個1之後0的個數:");
printf("%d\n",__builtin_ctz(x));
printf("1的個數:");
printf("%d\n",__builtin_popcount(x));
printf("1的個數的奇偶性:");
printf("%d\n",__builtin_parity(x));