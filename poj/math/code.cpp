
/*
 * poj 1850
 * memory: 728K
 * time: 0MS
 * code length: 1150B
 * date: 2012-10-29 12:14:28
 * */
#include <iostream>
#include <string>
using namespace std;

long long C[27][10];

int main(int argc, const char *argv[])
{

    for(int i = 0; i <= 26; ++i) {
        C[i][0] = 1;
        for(int j = 1; (j < i+1) && (j < 10); ++j) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    string str = "vwxyz";

    cin >> str;

    bool isOk = true;

    int nlen = str.length();
    for(int i = 1; i < nlen; ++i) {
        if( str[i-1] >= str[i] ) {
            isOk = false;
        }
    }

    if(!isOk){
        cout << 0 << endl;
        return 0;
    }

    int count = 0;
    char maxch = 'a' - 1;
    for(int i = 0; i < nlen; ++i) {


        for(char ch = maxch+1; ch < str[i]; ++ch) {
            int nleft = 'z' - ch;
            count += C[nleft][ nlen - i -1];

            // cout << ch << " " << nleft << " " << nlen - i -1 << endl;
        }
        // cout << i << " " << count << endl;

        if(maxch < str[i])
            maxch = str[i];
    }

    for(int i = 0; i < nlen; ++i) {
        count += C[26][i];
    }
    cout << count << endl;
    return 0;
}
