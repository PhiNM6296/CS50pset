#include <cs50.h>
#include <stdio.h>
#include<string.h>

// Max number of candidates
#define MAX 9

bool check_cycle(int start, int end);

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count = 0;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs and matrix of preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        if(strcmp(candidates[i],name) ==0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

void record_preferences(int ranks[])
{
    // Iterate over each candidate in the ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        // For each candidate i, iterate over candidates ranked after i
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Increment preference count for candidate ranks[i] over candidate ranks[j]
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i = 0; i < candidate_count; i++) {
        for(int j = 0; j < candidate_count; j++) {
            // only need this since it does include those [j][i] cases. When you try to add "<" codition for the [j][i], it will count double the pairs.
            if(preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        int max_index = i;
        for (int j = i + 1; j < pair_count; j++) {
            int diff_i = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            int diff_max = preferences[pairs[max_index].winner][pairs[max_index].loser] - preferences[pairs[max_index].loser][pairs[max_index].winner];
            if (diff_i > diff_max) {
                max_index = j;
            }
        }
        if (max_index != i) {
            pair temp = pairs[i];
            pairs[i] = pairs[max_index];
            pairs[max_index] = temp;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // 'locked' makes directed graph
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (check_cycle(pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

// cycle = start-node connected to end-node
bool check_cycle(int start, int end)
{
    if (start == end)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i] == true)
        {
            if (check_cycle(start, i) == true)
            {
                return true;
            }
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the current candidate has all false values in their column
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                // If any edge points to the candidate, they are not the winner
                is_winner = false;
                break;
            }
        }

        // If the candidate has no incoming edges, print their name
        if (is_winner)
        {
            printf("%s\n", candidates[i]);
            return; // Only one winner, so exit the function after printing
        }
    }
}

