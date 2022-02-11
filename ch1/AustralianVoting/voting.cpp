#include <iostream>
#include <vector>
#include <string>
#include <limits>

void print_winner(std::vector<std::string>& names, std::vector<std::vector<int>>& ballots);

int main()
{
    int num_tests;
    int num_candidates;
    int cand;
    int ch;
    std::vector<std::string> names;
    std::vector<std::vector<int>> ballots;

    std::cin >> num_tests;
    for (int i=0; i<num_tests; i++){
        ballots.clear();
        names.clear();
        std::cin >> num_candidates;
        std::cin >> std::ws;
        /* load names */
        for (int j=0; j<num_candidates; j++){
            std::string name;
            std::getline(std::cin, name);
            names.push_back(name);
        }
        /* load ballots */
        std::cin >> std::ws;
        while ((ch = std::cin.peek()) != '\n' && ch != EOF){
            std::vector<int> ballot(num_candidates, 0);
            for (int i=num_candidates-1; i>=0; i--){
                std::cin >> cand;
                ballot[i] = cand - 1;
            }            
            ballots.push_back(ballot);
            std::cin.ignore();
        }

        print_winner(names, ballots);
        if (i != num_tests-1){
            std::cout << "\n";
        }
    }

    return 0;
}

void update_votes(std::vector<int>& ballot, std::vector<int>& votes, std::vector<std::vector<int>>& bt_idxs, int bt_idx){
    int cand;
    while (!ballot.empty()){
        cand = ballot.back();
        ballot.pop_back();
        if(votes[cand] != -1){
            votes[cand]++;
            bt_idxs[cand].push_back(bt_idx);
            break;
        }
    }
}

int get_max(std::vector<int> votes){
    int amnt;
    int max = 0;
    for (int i=0; i<votes.size(); i++){
        amnt = votes[i];
        if (amnt != -1){
            return i;
        }
    }
    return -1;
}

void print_winner(std::vector<std::string>& names, std::vector<std::vector<int>>& ballots)
{
    int cand;
    int amnt;
    std::vector<int> losers;
    int winner = -1;
    int min; 
    int num_ballots = ballots.size();
    int num_candidates = names.size();
    int updated_num_cands; /* number of candidates in the current round; in each round one or more are discarded */
    std::vector<int>votes(num_candidates, 0);
    /* search what ballots (indices) vote for a specific candidate */
    std::vector<std::vector<int>>bt_idxs(num_candidates, std::vector<int>());

    /* update votes, first time */
    for (int i=0; i<num_ballots; i++){
        update_votes(ballots[i], votes, bt_idxs, i);
    }
    
    while(true){
        min = std::numeric_limits<int>::max();
        updated_num_cands = 0;
        for (int i=0; i<num_candidates; i++){
            amnt = votes[i];
            if (amnt != -1){
                updated_num_cands++;
                cand = i;

                if(amnt < min){
                    losers.clear();
                    losers.push_back(i);
                    min = amnt;
                }else if (amnt == min){
                    losers.push_back(i);
                }
            }
        }

        for (int loser : losers){
            votes[loser] = -1;
            updated_num_cands--;
            for (int bt: bt_idxs[loser]){
                update_votes(ballots[bt], votes, bt_idxs, bt);
            }
        } 

        if (updated_num_cands == 1){
            cand = get_max(votes);
            if (cand != -1){
                std::cout << names[cand] << "\n";
            }
            break;
        }else if(updated_num_cands == 0){
            for (int i : losers){
                std::cout << names[i] << "\n";
            }
            break;
        }
        losers.clear();
    }
}