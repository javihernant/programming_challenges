#include <iostream>
#include <vector>
#include <algorithm>

void hartals(std::vector<int>& hs, int sim_days);

int main()
{
    int num_ts; /* number of tests */
    int num_pys; /* number of parties */
    int sim_days; /* the simulation will work with this many days */ 
    int h;
    std::cin >> num_ts;
    for (int i=0; i<num_ts; i++){
        std::vector<int> hs;
        std::cin >> sim_days;
        std::cin >> num_pys;
        for (int p=0; p<num_pys; p++){
            std::cin >> h;
            hs.push_back(h);
        }
        hartals(hs, sim_days);

    }
    return 0;
}

void hartals(std::vector<int>& hs, int sim_days)
{
    int days; /* days we lose */
    int offset;
    int add;
    int day;
    int avoid;

    std::sort(hs.begin(), hs.end());
    days = 0;
    for (int i=0; i<hs.size(); i++){
        day = hs[i];
        offset = day;
            for (; day<=sim_days; day+=offset){
                add = 1;
                if (day%7 == 6 || day%7 == 0){
                    add = 0;
                }else{
                    for (int j=0; j<i; j++){
                        avoid = hs[j];
                        if (day%avoid == 0){
                            add = 0;
                            break;
                        }
                    }
                } 
                if (add){
                    days++;
                }
            }        
    }
    
    std::cout << days << "\n";
}

