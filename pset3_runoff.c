#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct //definindo o candidato
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES]; //cria um array com os candidatos

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name); //id se voto é válido; se for, id qual o rank de cada voto
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name) //ok
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(name, candidates[k].name) == 0)
        {
            preferences[voter][rank] = k; //if valid, store the votes
            return true;
        }
    }
    return false; // if not valid, return false
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++) //conta linha
    {
        for (int j = 0; j < candidate_count; j++) //conta a primeira coluna
        {
            int pos = preferences[i][j]; //cria uma int pos pra ser mais fácil pra identificar o candidato
            if (candidates[pos].eliminated == false) //se o candidato não estiver eliminado, vai contar o voto
            {
                candidates[pos].votes++; //conta um voto se o id na matriz for a id do candidato
                break; //ele não conta a segunda coluna
            }

        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) //para ciclar por todos os candidatos
    {
        if (candidates[i].votes > (voter_count / 2)) //se a quantidade de votos do candidato for > que a metade do total, ja ganhou
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false; //caso não, então return false e vamos de novo
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int counter = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes <  counter)
            {
                counter = candidates[i].votes;
            }
        }
    }
    return counter;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int keeps = 0;
    int istie = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min) //se a quantidade de votos do candidato for a quantidade minima, então...
            {
                keeps++; //duas var para ter meio de comparação
                istie++;
            }
            else //se não for a quantidade minima
            {
                keeps++; //apenas uma var
            }
        }
    } //encerra o ciclo

    if (keeps == istie) //aqui a comparação
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
    return;
}
