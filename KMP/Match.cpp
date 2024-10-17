#include <iostream>

char names[][16] = { "蛮力匹配S1", "蛮力匹配S2", "KMP 匹配S1", "KMP 匹配S2" };
int counters[4];
int results[4];

char S1[] = "74uowijernhklmnopqrsergergertuvwxyzabcdefghijklmnopqrstuvwx";
char S2[] = "zyxwvutsrqponmlkjihgfedcbazyxwvutsrqponmlkjihgfedcba";
char T[] = "abcdefghij";

static int matchHard(const char s[], const char t[], int counterIndex)
{
    for (int i = 0; i <= strlen(s) - strlen(t); i++)
    {
        int curPos = 0;
        for (curPos = 0; curPos < strlen(t); curPos++)
        {
            counters[counterIndex] += 1;
            if (s[i + curPos] != t[curPos]) break;
            if (curPos == strlen(t) - 1) return i;
        }
    }
    return -1;
}

static void findNextArray(const char t[], int r[], int counterIndex)
{
    int m = strlen(t);
    int j = 0;
    r[0] = 0;
    for (int i = 1; i < m; i++)
    {
        while (j > 0 && t[i] != t[j])
        {
            counters[counterIndex] += 1;
            j = r[j - 1];
        }

        if (t[i] == t[j])
        {
            counters[counterIndex] += 1;
            j++;
        }
        r[i] = j;
    }
}

static int matchKMP(const char s[], const char t[], int counterIndex)
{
    int n = strlen(s);
    int m = strlen(t);
    int *nexts = new int[m];
    findNextArray(t, nexts, counterIndex);
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        while (j > 0 && s[i] != t[j])
        {
            counters[counterIndex] += 1;
            j = nexts[j - 1];
        }
        if (s[i] == t[j])
        {
            counters[counterIndex] += 1;
            j++;
        }
        if (j == m)
        {
            return i - m + 1;
        }
    }
    return -1;
}

int main()
{
    results[0] = matchHard(S1, T, 0);
    results[1] = matchHard(S2, T, 1);
    results[2] = matchKMP(S1, T, 2);
    results[3] = matchKMP(S2, T, 3);
    printf("%-16s %-16s %-16s \n", "方法和组名", "比较次数", "结果");
    for (int i = 0; i < 4; i++) {
        printf("%-16s %-16d %-16d \n", names[i], counters[i], results[i]);
    }
}
