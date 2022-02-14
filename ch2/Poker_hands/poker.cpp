#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define NUM_SUITS 4
#define NUM_VALUES 13
#define NUM_CARDS 5 /*Number of cards in a hand */


int compare(int a, int b);
void poker(int cards[][5]);
int high_comp(std::vector<int>& pr_cards_a, std::vector<int>& count_a, std::vector<int>& pr_cards_b, std::vector<int>& count_b, int c);
int pairs_cmp(std::vector<int> pr_cards_a, std::vector<int> count_a, std::vector<int> pr_cards_b, std::vector<int> count_b);
int get_rank(int cards[], std::vector<int>& pr, std::vector<int>& cnt);
bool comp (int i,int j);
void process(int cards[], std::vector<int>& pr, std::vector<int>& cnt);
void convert(int cards[]);
int get_hash(char val, char suit);
int get_value(int hash);
int get_suit(int hash);
int is_flush(int cards[]);
int is_straight(std::vector<int>& cards);
bool check_four(std::vector<int>& cnt);
bool check_pair(std::vector<int>& cnt);
bool check_three(std::vector<int>& cnt);
bool check_pairs(std::vector<int>& cnt);
int idx_of(std::vector<int>& cnt, int n);

std::string values("23456789TJQKA");
std::string suits("CDHS");

int main(){
    char val;
    char st;
    int cards[2][5]; /* cards' hashes */
    int i=0;
    while (true){
        i++;
        if (std::cin.peek() == EOF){
            break;
        }

        for (int i=0; i<2; ++i){
            for (int j=0; j<5; ++j){
                val = std::cin.get();
                st = std::cin.get();
                cards[i][j] = get_hash(val, st);
                std::cin.ignore();
            }       
        }       

        poker(cards);
        
    }

}

int compare(int a, int b)
{
    int cmp;
    if (a > b){
        cmp = 1;
    }else if (a < b){
        cmp = -1;
    }else{
        cmp = 0;
    }
    return cmp;
}

void poker(int cards[2][5])
{
    int rank_a, rank_b; 
    std::vector<int> pr_cards_a, pr_cards_b;
    std::vector<int> count_a, count_b;
    process(cards[0], pr_cards_a, count_a);
    process(cards[1], pr_cards_b, count_b);

    rank_a = get_rank(cards[0], pr_cards_a, count_a);
    rank_b = get_rank(cards[1], pr_cards_b, count_b);

    int cmp;
    int val_a, val_b;
    cmp = compare(rank_a, rank_b);

    if (cmp == 0){
        switch (rank_a)
        {
        case 1:
        case 6:
            cmp = high_comp(pr_cards_a, count_a, pr_cards_b, count_b, 1);
            break;
        case 2:
        case 3:
            cmp = high_comp(pr_cards_a, count_a, pr_cards_b, count_b, 2);
            if (cmp == 0){
                cmp = high_comp(pr_cards_a, count_a, pr_cards_b, count_b, 1);
            }
            break;
        case 4:
        case 7:
            {
                int i = idx_of(count_a,3);
                int j = idx_of(count_b,3);

                cmp = compare(pr_cards_a[i],pr_cards_b[j]);
                break;
            }
        case 5:
        case 9:
            cmp = compare(pr_cards_a[0],pr_cards_b[0]);
            break;
        case 8:
            {
                int i = idx_of(count_a,4);
                int j = idx_of(count_b,4);

                cmp = compare(pr_cards_a[i],pr_cards_b[j]);
                break;
            }
        }
    }

    if (cmp < 0){
        std::cout << "White wins.\n";
    }else if (cmp > 0){
        std::cout << "Black wins.\n";
    }else{
        std::cout << "Tie.\n";
    }
}

int idx_of(std::vector<int>& cnt, int n)
{
    int i = 0;
    for (; i<cnt.size(); i++){
        if (cnt[i] == n){
            break;
        }
    }
    return i;

}
int high_comp(std::vector<int>& pr_cards_a, std::vector<int>& count_a, std::vector<int>& pr_cards_b, std::vector<int>& count_b, int c)
{
    int cmp = 0;
    int i=0;
    int j=0;
    while (true){
        while (i<count_a.size() && count_a[i] != c){
            i++;
        }

        while (j<count_a.size() && count_b[j] != c){
            j++;
        }

        if (i>=count_a.size() || j>=count_a.size()){
            break;
        }

        cmp = compare(pr_cards_a[i], pr_cards_b[j]);
        if (cmp != 0){
            break;
        }else{
            i++;
            j++;
        }
    }
    return cmp;
}


int pairs_cmp(std::vector<int> pr_cards_a, std::vector<int> count_a, std::vector<int> pr_cards_b, std::vector<int> count_b)
{
    std::vector<int> pairs_a;
    std::vector<int> pairs_b;

    for (int i=0; i<count_a.size(); i++){
        if (count_a[i] == 2){
            pairs_a.push_back(i);
        }

        if (count_b[i] == 2){
            pairs_a.push_back(i);
        }
    }

    int max_a=0;
    int max_b=0;
    int val;

    for (int i:pairs_a){
        if ((val=pr_cards_a[i])>max_a){
            max_a = val;
        }        
    }

    for (int i:pairs_b){
        if ((val=pr_cards_b[i])>max_b){
            max_b = val;
        }        
    }

    return compare(max_a,max_b);
}

int get_rank(int cards[], std::vector<int>& pr, std::vector<int>& cnt)
{
    int rank;
    int flush;
    int straight;
    int pair;
    int three;
    
    straight = is_straight(pr);
    flush = is_flush(cards) && cnt.size() == 5;
    pair = check_pair(cnt);
    three =check_three(cnt);

    if (straight && flush){
        rank = 9;
    }else if (check_four(cnt)){
        rank = 8;
    }else if (pair && three){
        rank = 7;
    }else if (flush){
        rank = 6;
    }else if (straight){
        rank = 5;
    }else if (three){
        rank = 4;
    }else if (check_pairs(cnt)){
        rank = 3;
    }else if (pair){
        rank = 2;
    }else{
        rank = 1;
    }
    return rank;

}

bool comp (int i,int j) { return (get_value(i)>get_value(j)); }

void process(int cards[], std::vector<int>& pr, std::vector<int>& cnt)
{
    std::sort(cards, cards+5, comp);
    int val = get_value(cards[0]);
    int tmp;
    int c = 1;
    for (int i=1; i<5; i++){
        tmp = get_value(cards[i]);
        if(tmp != val){
            pr.push_back(val);
            cnt.push_back(c);
            val = tmp;
            c = 0;
        }
        c++;
        if (i == 4){
            pr.push_back(tmp);
            cnt.push_back(c);
        }
    }
}

void convert(int cards[])
{
    for (int i=0; i<5; i++){
        cards[i] = get_value(cards[i]);
    }
}

int get_hash(char val, char suit)
{
    int hash = 0;
    int i, j;
    for (int i=0; i<NUM_VALUES; i++){
        for (int j=0; j<NUM_SUITS; j++){
            if (val == values[i] && suit == suits[j]){
                hash = i*NUM_SUITS + j;
                break;
            }
        }
    }
    return hash;
}

int get_value(int hash){
    return hash/NUM_SUITS;
}

int get_suit(int hash){
    return hash%NUM_SUITS;
}

int is_flush(int cards[])
{
    int b = 1;
    int suit = get_suit(cards[0]);
    for (int i=1; i<NUM_CARDS; i++){
       if (get_suit(cards[i])!=suit){
           b =0;
           break;
       } 
    }
    return b;
}

int is_straight(std::vector<int>& cards)
{
    int b = 1;
    int val = (cards[0]);
    int tmp = -1;
    for (int card: cards){
        if (tmp == -1){
            tmp=card;
        }else{
            if (card == tmp-1){
                tmp = card;
            }else{
                b = 0;
                break;
            }
        }
    }
    return b && cards.size() == 5;
}

bool check_four(std::vector<int>& cnt)
{
    int is_four = 0;
    for (int c: cnt){
        if (c == 4){
            is_four = 1;
            break;
        } 
    }
    return is_four;
}

bool check_pair(std::vector<int>& cnt)
{
    int pair = 0;
    for (int c: cnt){
        if (c == 2){
            pair = 1;
            break;
        } 
    }
    return pair;
}

bool check_three(std::vector<int>& cnt)
{
    int three = 0;
    for (int c: cnt){
        if (c == 3){
            three = 1;
            break;
        } 
    }
    return three;
}

bool check_pairs(std::vector<int>& cnt)
{
    int pair = 0;
    for (int c: cnt){
        if (c == 2){
            pair++;
        } 
    }
    return pair == 2;
}
