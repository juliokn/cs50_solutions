# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    with open(sys.argv[1]) as file:
        # we read each row of the file as a dictionary
        reader = csv.DictReader(file)
        for team in reader:
            team["rating"] = int(team["rating"])
            # we're appending values (dictionaries) to a list, so we have a list of dictionaries
            teams.append(team)          
            
    counts = {}
    for i in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1
            
    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            # if return True, team 1 won
            winners.append(teams[i])
        else:
            # if return False, team 2 won
            winners.append(teams[i + 1])            
    # returns a list with all winners
    return winners                                  


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # inside this loop we will simulate tournaments 
    # in each round the list of teams will be filled with only the winners
    while len(teams) > 1:                           
        teams = simulate_round(teams)              
    # after all rounds, we end up with one winner, and return it
    # we say the "["team"]" thing to access only the value for the team key inside the dictionary
    return teams[0]["team"]                         
                                                    
                                                                    
if __name__ == "__main__":
    main()
