#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

void shuffle(std::vector<int>& deck, std::unordered_map<int,int>& shf);
void print_name(int n);

int main()
{
    int tests;
    int num_shfs;
    int i;
    int s;
    std::cin >> tests;
    for (int t{0}; t<tests; t++){
        std::cin >> num_shfs;
        std::vector<std::unordered_map<int, int>> shfs(num_shfs, std::unordered_map<int, int>());
        for (s=0; s<num_shfs; s++){
            for (int j{0}; j<52; j++){
                std::cin >> i;
                --i;
                shfs[s][i] = j;
            }
        }

        std::vector<int> initial(52);
        for (int i{0}; i<52; i++){
            initial[i] = i;
        }
    
        std::cin.ignore();
        char c;
        while((c = std::cin.peek())!='\n' && c!=EOF){
            std::cin >> s;
            --s;
            shuffle(initial, shfs[s]);
            std::cin.ignore();
        }
    
        for (const int& c: initial){
            print_name(c);
        }
        if (t < tests-1){
            std::cout << "\n";
        }
                
    }
    return 0;
}

void shuffle(std::vector<int>& deck, std::unordered_map<int,int>& shf)
{
    std::vector<int> deck_cpy(deck);
    int j;
    for (std::size_t i{0}; i<deck_cpy.size(); i++){
        j = shf[i];
        deck[j] = deck_cpy[i];
    }
}


void print_name(int n)
{
    static std::vector<std::string> values {
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10",
        "Jack",
        "Queen",
        "King",
        "Ace"
    };
    static std::vector<std::string> suits= {
        "Clubs",
        "Diamonds",
        "Hearts",
        "Spades"
    };

    int s = n/13;
    int v = n%13;
    std::cout << values[v] << " of " << suits[s] << "\n";
}