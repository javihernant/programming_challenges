#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Player
{
private:
    int m_id;
    int m_time;
    int m_num_problems;
    std::vector<int> m_time_problems; /* time spent for each problem */
    std::vector<int> m_problems; /* 9 positions, each refering to a problem.
    Value is 0 for not completed, or 1 for completed */

public:
    Player(int id=0)
    {
        m_id = id;
        m_time = 0;
        m_num_problems = 0;
        m_time_problems.assign(9, 0);
        m_problems.assign(9, 0);
    }

    void update(int L, int prob, int time)
    {
        if (L != 'R' && L != 'U' && L != 'E' && m_problems[prob-1] != 1){
            if (L == 'C'){
                m_time_problems[prob-1] += time;
                m_problems[prob-1] = 1;

            }

            if (L == 'I'){
                m_time_problems[prob-1] += 20;
            }
        }
    }

    void calculate_props(){
        for (int i{0}; i<m_problems.size(); i++){
            if (m_problems[i] == 1){
                m_time += m_time_problems[i];
                ++m_num_problems;
            }
        }
    }

    friend bool compare_pys(const Player& p1, const Player& p2);

    void printP(){
        std::cout << m_id << " " << m_num_problems << " " << m_time << "\n";
    }
};

bool compare_pys(const Player& p1, const Player& p2)
{
    if (p1.m_num_problems > p2.m_num_problems){
        return true;
    }else if (p1.m_num_problems == p2.m_num_problems){
        if (p1.m_time < p2.m_time){
            return true;
        }
        if (p1.m_time == p2.m_time){
            if (p1.m_id < p2.m_id){
                return true;
            }
        }

    }
    return false;
}

int main(){
    int tests;
    char c;
    int cont;
    int prob;
    int time;
    char L;
    std::cin >> tests;
    for (int i{0}; i<tests; i++){
        std::unordered_map<int, Player> pys_map;
        std::vector<Player> players;
        std::cin >> std::ws;
        while((c = std::cin.peek()) != '\n' && c != EOF){
            std::cin >> cont;
            std::cin >> prob;
            std::cin >> time;
            std::cin >> L;
            std::cin.ignore();

            if (pys_map.count(cont) == 0){
                pys_map[cont] = Player(cont); 
            }

            pys_map[cont].update(L, prob, time);

        }        

        for (auto& p : pys_map){
            p.second.calculate_props();
            players.push_back(p.second);
        }

        std::sort(players.begin(), players.end(), compare_pys);
        for (auto& py : players){
            py.printP();
        }
        if (i<tests-1){
            std::cout << "\n";
        }
    }
    return 0;
}