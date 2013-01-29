
#include <iostream>
using namespace std;

void print_permutation(int n, int *A, int cur);
void print_permutation(int *a, int n, int *p, int cur);

int main(int argc, const char *argv[])
{

    const int nlen = 3;
    int a[3] = {1,1,2};
    int p[3] = {0};

    print_permutation(a, sizeof(a)/sizeof(int), p, 0);
    // print_permutation(sizeof(a)/sizeof(int), a, 0 );

    return 0;
}

//生成1到n上的全排列
void print_permutation(int n, int *p, int cur)
{
    if( cur == n ) {
        for(int i =0; i < n; ++i)
            cout << p[i] << " ";
        cout << endl;
    }
    else {


        for(int i = 1; i <= n; ++i) {

            int ok =1;

            for(int j =0; j < cur; ++j) {

                if( p[j] == i) {
                    ok = 0;
                    break;
                }
            }

            if(ok) {
                p[cur] = i;
                print_permutation(n,p, cur+1);
            }

        }

    }
}

//生成可重集合的全排列
//再琢磨琢磨
void print_permutation(int *a, int n, int *p, int cur)
{

    if( cur == n ) {
        for(int i =0; i < n; ++i)
            cout << p[i] << " ";
        cout << endl;
    }
    else {

        for(int i = 0; i < n; ++i) {

            if(i==0 || a[i] != a[i-1]) {

                int c1 = 0, c2 = 0;

                for(int j =0; j < n; ++j) {
                    if( a[i] == a[j])
                        ++c1;
                }

                for(int j =0; j < cur; ++j) {

                    if( p[j] == a[i])
                        ++c2;
                }

                if( c2 < c1) {

                    p[cur] = a[i];
                    print_permutation(a,n,p, cur+1);
                }
            }


        }

    }
}
