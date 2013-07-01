#include <stdio.h>

int time_to_second(int h, int m, int s);

int main(int argc, const char *argv[])
{

    int h1, m1, s1, h2, m2, s2;

    int n ;

    scanf("%d", &n);

    while (n--) {

        scanf("%d:%d:%d", &h1, &m1, &s1);
        scanf("%d:%d:%d", &h2, &m2, &s2);

        int time1 = time_to_second(h1, m1, s1);
        int time2 = time_to_second(h2, m2, s2);

        int seconds = time1 - time2;

        // printf("%d %d %d\n", time1, time2, seconds);
        if (seconds < 0)
            seconds += 24*60*60;

        printf("%02d:%02d:%02d\n", (seconds/3600) % 12, ( (seconds%3600) / 60), (seconds %60));
    }

    return 0;
}


int time_to_second(int h, int m, int s)
{
    h = h % 24;
    m = m % 60;
    s = s % 60;

    return h*3600 + m * 60 + s;
}

