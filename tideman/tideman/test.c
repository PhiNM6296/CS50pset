#include <stdio.h>
#include <stdbool.h>

#define MAX 9

typedef struct
{
    int winner;
    int loser;
} pair;

int pair_count;
pair pairs[MAX * (MAX - 1) / 2];
bool locked[MAX][MAX];

void lock_pairs(void);

int main(void)
{
    printf("Enter pair count: ");
    scanf("%d", &pair_count);

    printf("Enter pairs (winner loser):\n");
    for (int i = 0; i < pair_count; i++)
    {
        scanf("%d %d", &pairs[i].winner, &pairs[i].loser);
    }

    lock_pairs();

    printf("Locked pairs:\n");
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser])
        {
            printf("(%d, %d)\n", pairs[i].winner, pairs[i].loser);
        }
    }

    printf("\nLocked matrix:\n");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", locked[i][j] ? 1 : 0);
        }
        printf("\n");
    }

    return 0;
}

void lock_pairs(void)
{
    for(int i = 0; i<pair_count; i++) {
        for(int j = 0; j<pair_cont; j++) {

        }
    }
}
bool check_cycle() {
    int visited[pair_count] = {100};
    int stack[pair_count] = {200};
    for(int i = 0; i<pair_count; i++) {
        
    }
}
