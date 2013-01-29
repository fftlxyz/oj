#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


/*
 * 这题其实不难啊。。。。
 * 可是我没想到～～
 * 多练习练习啊～～
 * 看了别人的状态转移方程。。。。
 * f(i)表示 前i个字符，最小删减数
 * f(i) = min(
 *        f(i-1)+1,                       不包含字符i
 *        f(j), + w(j+1,i);  0 <= j < i;   包含字符i
 *        )
 * */

bool mycompare(const string &a, const string &b);

int main(int argc, const char *argv[])
{
    const int MAXN = 300;
    int w, l;
    cin >> w >> l;

    string str, word;

    vector<string> words;
    vector<string>::iterator it;
    vector<string>::iterator itend;

    int dp[MAXN+1] = {0};

    cin >> str;
    for( int i =0; i < w; ++i) {
        cin >> word;
        words.push_back(word);
    }

    sort(words.begin(),words.end(),mycompare);

    // for(int i =0; i < words.size(); ++i)
        // cout << words[i] << endl;

    // dp[0] = MAXN;

    itend = words.end();
    for(int i = 1; i <= l; ++i) {

        int min = dp[i-1] + 1;
        for(int j = 0; j < i; ++j) {

            int nlen = i-j;

            for( it = words.begin(); it != itend; ++it) {
                word = *it;
                int wordsize = word.size();
                if( wordsize > nlen )
                    break;

                int ndelete = 0;
                int wi = 0;
                int k;
                //k表示
                for( k = j+1;  k <= i; ++k) {

                    if( str[k-1] == word[wi]) ++wi;
                    else ++ndelete;
                    if(wi== wordsize) break;
                }

                if( wi == wordsize)  ndelete += i-k;
                else ndelete = nlen;

                if( min > dp[j] + ndelete ) min = ndelete + dp[j];
            }
        }
        dp[i] = min;
        // cout << i <<  " " <<  dp[i] << endl;
    }

    cout << dp[l] << endl;

    return 0;
}

bool mycompare(const string &a, const string &b)
{
    return a.length() < b.length();
}
