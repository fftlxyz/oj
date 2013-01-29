#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
 * 这个题目，值得我写一个解题报告
 * poj:3267
 * memory:808K
 * time: time exceed->735MS->500MS->485MS
 * 这个时间不行啊 好多0MS的
 * code length:1524B
 * date: 2012-10-28 17:07:11
 **/

bool mycompare(const string &a, const string &b);

int main(int argc, const char *argv[])
{
    const int MAXN = 300;
    int w, l;
    cin >> w >> l;

    string str, word;

    vector<string> words;

    int dp[MAXN+1] = {0};

    cin >> str;
    for( int i =0; i < w; ++i) {
        cin >> word;
        words.push_back(word);
    }

    sort(words.begin(),words.end(),mycompare);

    // for(unsigned i =0; i < words.size(); ++i)
        // cout << words[i] << endl;

    for(int i = 1; i <= l; ++i) {

        int min = dp[i-1] + 1;

        for(int j = 0; j < w; ++j) {
            word = words[j];

            int wordsize = word.size();
            int wi = wordsize-1;

            //不可能构成
            if( wordsize > i )
                break;

            if(str[i-1] != word[wi])
                continue;

            int k;
            for( k = i-1;  k >=0 && wi >=0 ; --k) {
                if( str[k] == word[wi]) --wi;

                if( k < wi )
                    break;
            }
            int ndelete;
            if( wi == -1)  ndelete = i- (k + 1) -wordsize;
            else ndelete = i;

            if( min > dp[k+1] + ndelete ) min = ndelete + dp[k+1];
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
