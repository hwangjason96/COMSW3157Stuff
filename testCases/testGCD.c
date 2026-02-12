#include <stdio.h>


int gcd_iterative(int m, int n){
        int dummy;
        // gcd(a,b) = gcd(b, a mod b)
        while( n != 0 ){
                printf("m = %d\nn = %d\n",m,n);
		dummy = m % n;
                m = n;
		n = dummy;
        }
        return m;
}

int gcd_recursive(int m, int n){
        if (n == 0){
                return m;
        }
        return gcd_recursive(n, m % n);

}
int main() {
	printf("%d\n",gcd_iterative(1234560,987840));
	printf("%d\n",gcd_recursive(1234560,987840));
	return 0;
}
