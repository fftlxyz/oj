#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

const int MAXN = 5;
int perm[MAXN + 1];

//算出p指向的排列是第几个排列
int cantor(int *p)
{
    int h = 0;
    //找全排列的hash方法
    for(int i =0; i < MAXN; ++i)
    {
        int count =0;
        for(int j = i+1 ;j < MAXN ; ++j) {
            if( p[i] > p[j])
                ++count;
        }
        h += perm[ MAXN - i - 1] * count;
    }
    return h;
}


//返回code 对应的全排列
void reverse_cantor(int code, int *p)
{
    for(int i = 0; i < MAXN; ++i) {
        p[i] = i+1;
    }

    int t1;

    for(int i = 0; i < MAXN ; ++i){

        t1 = code / perm[ MAXN - 1 - i];
        int j = i + t1;
        // cout << code << " " << perm[ MAXN - 1 - i] << " " << t1 << " " << j << endl;
        // for(int i = 0; i < MAXN; ++i) {
          // cout << p[i] << " ";
        // }
        // cout << endl;

        int tmp = p[j];
        for( ; j > i; j--)
            p[j] = p[j-1];

        p[i] = tmp;

        code = code % perm[MAXN - 1 - i];
    }


}

int main(int argc, const char *argv[])
{

    perm[0] = 1;
    for(int i = 1; i< MAXN ; ++i){
        perm[i] =  i *perm[i-1];
    }

    int pArray[] = {3,2,4,5,1};

    cout << cantor(pArray) << endl;

    memset(pArray, 0, sizeof(pArray));

    reverse_cantor(57,pArray);

    for(int i = 0; i < MAXN; ++i)
        cout << pArray[i] << " ";
    cout << endl;


    for(int i = 0; i < MAXN; ++i) {
        pArray[i] = i+1;
    }
    int code = 0;
    do{
        int code2 = cantor(pArray);

        assert(code == code2);

        code++;
        // cout << code++ << endl;
        // for(int i = 0; i < MAXN; ++i)
            // cout << pArray[i] << " ";
         // cout << endl;

    } while( next_permutation(pArray, pArray + sizeof(pArray)/ sizeof(int)) );


    int p2Array[MAXN];
    for(int i = 0; i < MAXN; ++i) {
        p2Array[i] = i+1;
    }

    for(int i = 0; i < perm[MAXN]; ++i) {

        reverse_cantor(i,pArray);

        for(int i = 0; i < MAXN; ++i) {
            assert( pArray[i] == p2Array[i]);
        }
        next_permutation(p2Array, p2Array + sizeof(p2Array)/ sizeof(int));
    }



    return 0;
}

// void decimal_to_varycode(int n)
// {

    // int num = n;

    // vector<int> varycode;

    // bool isOk = false;

    // for(int i = MAXN -1; i >= 0; i--) {

        // int t1 = num/ perm[i];
        // if( t1 ) {
            // isOk = true;
        // }

        // num = num % perm[i];
        // if(isOk)
            // varycode.push_back(t1);
    // }

    // reverse(varycode.begin(), varycode.end());
    // for(unsigned i = 0; i < varycode.size(); ++i )
        // cout <<  varycode[i] << " ";
    // cout << endl;
// }

// //生成1到n上的全排列
// void print_permutation(int n, int *p, int cur)
// {
    // if( cur == n ) {
        // for(int i =0; i < n; ++i)
            // cout << p[i] << " ";
        // cout << endl;
        // int hashcode =hash_code(p,n);
        // cout <<  "hashcode " <<  hashcode << endl;
    // }
    // else {


        // for(int i = 1; i <= n; ++i) {

            // int ok =1;

            // for(int j =0; j < cur; ++j) {

                // if( p[j] == i) {
                    // ok = 0;
                    // break;
                // }
            // }

            // if(ok) {
                // p[cur] = i;
                // print_permutation(n,p, cur+1);
            // }

        // }

    // }
// }


