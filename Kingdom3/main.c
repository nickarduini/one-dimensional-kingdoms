/*
 Nick Arduini
 
 N one dimensional kingdoms are represented as intervals of the form [ai , bi] on the real line.
 A kingdom of the form [L, R] can be destroyed completely by placing a bomb at a point x on the real line if L
 ≤ x ≤ R.
 Your task is to determine minimum number of bombs required to destroy all the one dimensional kingdoms.
 Input
 
 First line of the input contains T denoting number of test cases.
 For each test case, first line contains N denoting the number of one dimensional kingdoms.
 For each next N lines, each line contains two space separated integers ai and bi.
 Output
 
 For each test case , output an integer denoting the minimum number of bombs required.
 Constraints
 
 Subtask 1 (20 points) : 1 ≤ T ≤ 100 , 1 ≤ N ≤ 100 , 0 ≤ ai ≤ bi ≤500
 Subtask 2 (30 points) : 1 ≤ T ≤ 100 , 1 ≤ N ≤ 1000 , 0 ≤ ai ≤ bi ≤ 1000
 Subtask 3 (50 points) : 1 ≤ T ≤ 20 , 1 ≤ N ≤ 105, 0 ≤ ai ≤ bi ≤ 2000
 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct kingdom
{
    int left;
    int right;
    int on;
} kingdom;

static inline int cmpfuncLeft (const void * a, const void * b)
{
    return (*(kingdom*)a).left - (*(kingdom*)b).left;
}

int main(void) {
    
    int cases, kingNum, left, right, i, j, k;
    kingdom arr[2000];
    scanf("%d", &cases);
    for (i = 0; i < cases; ++i)
    {
        scanf("%d", &kingNum);
        scanf("%d%d", &left, &right);
        arr[0].left = left;
        arr[0].right = right;
        arr[0].on = 1;
        int counter = 1;
        for (j = 1; j < kingNum; ++j)
        {
            scanf("%d%d", &left, &right);
            int goodOne = 1;
            for (k = 0; k < counter; k++) {
                if (arr[k].left <= left && arr[k].right >= right) {
                    arr[k].on = 0;
                } else if (left <= arr[k].left && right >= arr[k].right) {
                    goodOne = 0;
                    break;
                }
            }
            if (goodOne) {
                int index = -1;
                for (k = 0; k < counter; k++) {
                    if (arr[k].on == 1) continue;
                    index = k;
                    break;
                }
                if (index == -1) {
                    index = counter++;
                }
                arr[index].left = left;
                arr[index].right = right;
                arr[index].on = 1;
            }
                
        }
        
        qsort(arr, counter, sizeof(kingdom), cmpfuncLeft);
        
        int bombs = 0;
        for (j = 0; j < counter; ++j) {
            if (arr[j].on != 1) continue;
            bombs++;
            for (k = j + 1; k < kingNum && arr[k].left <= arr[j].right; ++k) {
                arr[k].on = 0;
            }
        }



        printf("%d\n", bombs);
        
    }
    return 0;
}
