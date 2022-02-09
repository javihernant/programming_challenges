#include <iostream>
#include <vector>
#include <cctype>

int calc_check(std::vector<std::string>& tab, int id, int w_i, int w_j, int b_i, int b_j);

int main()
{
    std::vector<std::string> tab;
    int exit;
    char ch;
    int rc;
    int id = 0;
    int w_i, w_j; /* coords for white king */
    int b_i, b_j; /* coords for black king */

    while(true){
        id++;
        tab.clear();
        exit = 1;
        for (int i=0; i<8; i++){
            std::string row;
            for (int j=0; j<8; j++){
                std::cin >> ch;
                if (ch != '.'){
                    exit = 0;
                }
                if (ch == 'K'){
                    w_i = i;
                    w_j = j;
                }

                if (ch == 'k'){
                    b_i = i;
                    b_j = j;
                }
                row.push_back(ch);
            }
            tab.push_back(row);
        }

        if (exit){
            break;
        }
        calc_check(tab, id, w_i, w_j, b_i, b_j);
    }
    return 0;
}

int check_borq(std::vector<std::string>& tab, int k_i, int k_j, char en1, char en2);
int check_rorq(std::vector<std::string>& tab, int k_i, int k_j, char en1, char en2);
int check_n(std::vector<std::string>& tab, int k_i, int k_j, char en);
int check_p(std::vector<std::string>& tab, int k_i, int k_j, char en);

int calc_check(std::vector<std::string>& tab, int id, int w_i, int w_j, int b_i, int b_j)
{
    int rc;
    if(check_borq(tab, w_i, w_j, 'b', 'q') || check_rorq(tab, w_i, w_j, 'r', 'q') || check_n(tab,w_i, w_j, 'n') || check_p(tab, w_i, w_j, 'p')){
        std::cout << "Game #" << id << ": white king is in check.\n";
    }else if(check_borq(tab,b_i, b_j, 'B', 'Q') || check_rorq(tab, b_i, b_j, 'R', 'Q') || check_n(tab, b_i, b_j, 'N') || check_p(tab, b_i, b_j, 'P')){
        std::cout << "Game #" << id << ": black king is in check.\n";
    }else{
        std::cout << "Game #" << id << ": no king is in check.\n";
    }
    return rc;
}

int check_borq(std::vector<std::string>& tab, int k_i, int k_j, char en1, char en2)
{
    int i;
    int j;
    for (i = k_i-1, j = k_j-1; i>=0 && j>=0; i--, j--){
        if(tab[i][j] == en1 || tab[i][j] == en2){
            return 1;
        }else if(tab[i][j] != '.'){
            break;
        }
    }

    for (i = k_i+1, j = k_j+1; i<8 && j<8; i++, j++){
        if(tab[i][j] == en1 || tab[i][j] == en2){
            return 1;
        }else if(tab[i][j] != '.'){
            break;
        }
    }

    for (i = k_i+1, j = k_j-1; i<8 && j>=0; i++, j--){
        if(tab[i][j] == en1 || tab[i][j] == en2){
            return 1;
        }else if(tab[i][j] != '.'){
            break;
        }
    }

    for (i = k_i-1, j = k_j+1; i>=0 && j<8; i--, j++){
        if(tab[i][j] == en1 || tab[i][j] == en2){
            return 1;
        }else if(tab[i][j] != '.'){
            break;
        }
    }
    return 0;
}

int check_rorq(std::vector<std::string>& tab, int k_i, int k_j, char en1, char en2)
{
    int i;
    int j;
    for (i = k_i-1, j=k_j; i>=0; i--){
        if(tab[i][j] == en1 || tab[i][j] == en2){
            return 1;
        }else if(tab[i][j] != '.'){
            break;
        }
    }

    for (i = k_i+1, j = k_j; i<8; i++){
        if(tab[i][j] == en1 || tab[i][j] == en2){
            return 1;
        }else if(tab[i][j] != '.'){
            break;
        }
    }

    for (i = k_i, j = k_j-1; j>=0; j--){
        if(tab[i][j] == en1 || tab[i][j] == en2){
            return 1;
        }else if(tab[i][j] != '.'){
            break;
        }
    }

    for (i = k_i, j = k_j+1; j<8; j++){
        if(tab[i][j] == en1 || tab[i][j] == en2){
            return 1;
        }else if(tab[i][j] != '.'){
            break;
        }
    }
    return 0;
}

int check_n(std::vector<std::string>& tab, int k_i, int k_j, char en)
{
    std::vector<int> a{-2, 2};
    std::vector<int> b{-1, 1};
    int i, j, tmp;

    for (int off_a : a){
        for (int off_b : b){
            i = k_i+off_a;
            j = k_j+off_b;
            if (i < 8 && i >= 0 && j<8 && j >= 0 && tab[i][j] == en){
                return 1;
            } 

            i = k_i + off_b;
            j = k_j + off_a;
            if (i < 8 && i >= 0 && j<8 && j >= 0 && tab[i][j] == en){
                return 1;
            } 
        }
    }
    return 0;
}

int check_p(std::vector<std::string>& tab, int k_i, int k_j, char en)
{
    int search_up = std::islower(en);
    int i, j;

    if(search_up){
        i = k_i - 1;
        j = k_j - 1;
        if(i>=0 && j>=0){
            if(tab[i][j] == en){
                return 1;
            }
        }
        
        j = k_j + 1;
        if(i>=0 && j<8){
            if(tab[i][j] == en){
                return 1;
            }
        }
        
    }else{
        i = k_i + 1;
        j = k_j - 1;
        if(i<8 && j>=0){
            if(tab[i][j] == en){
                return 1;
            }
        }
        
        j = k_j + 1;
        if(i<8 && j<8){
            if(tab[i][j] == en){
                return 1;
            }
        }
    }
    return 0;
}