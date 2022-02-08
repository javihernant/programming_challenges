#include <iostream>
#include <vector>
#include <limits>

void create_tab(std::vector<std::vector<char>>& sc, int m, int n);
void color_px(std::vector<std::vector<char>>& sc, int m, int n);
void save_sc(std::vector<std::vector<char>>& sc);
void v_draw(std::vector<std::vector<char>>& sc, int m, int n);
void h_draw(std::vector<std::vector<char>>& sc, int m, int n);
void draw_rect(std::vector<std::vector<char>>& sc, int m, int n);
void fill_reg(std::vector<std::vector<char>>& sc, int m, int n);
void ignoreLine();

int main(){
    char cmd;
    int m=0;
    int n=0;
    std::vector<std::vector<char>> sc;
    while(true){
        std::cin >> cmd;
        switch(cmd){
            case 'I':
                std::cin >> n;
                std::cin >> m;
                create_tab(sc, m, n);
                break;
            case 'C':
                create_tab(sc, m, n);
                break;
            case 'L':
                color_px(sc, m, n);
                break;
            case 'V':
                v_draw(sc, m, n);
                break;
            case 'H':
                h_draw(sc, m, n);
                break;
            case 'K':
                draw_rect(sc, m, n);
                break;
            case 'F':
                fill_reg(sc, m, n);
                break;
            case 'S':
                save_sc(sc);
                break;
            case 'X':
                return 0;
            default:
                ignoreLine();
                continue;
        }

    }
    return 0;
}

void create_tab(std::vector<std::vector<char>>& sc, int m, int n)
{
    sc.clear();
    for(int i{0}; i<m; ++i){
        sc.push_back(std::vector<char>(n, 'O'));
    }

}

void color_px(std::vector<std::vector<char>>& sc, int m, int n)
{
    int x, y;
    char col;

    std::cin >> x;
    x -= 1;
    std::cin >> y;
    y -= 1;
    std::cin >> col;
    if(x>=0 && x<n && y >= 0 && y < m){
        sc[y][x] = col;
    }
}

void save_sc(std::vector<std::vector<char>>& sc)
{
    std::string name;
    std::cin >> name;
    std::cout << name << '\n';

    for(auto row : sc){
        for(char val: row){
            std::cout << val;
        }
        std::cout << std::endl;
    }
}

void v_draw(std::vector<std::vector<char>>& sc, int m, int n)
{
    int x;
    int y1, y2;
    int temp;
    char col;
    std::cin >> x;
    x -= 1;
    std::cin >> y1;
    y1 -= 1;
    std::cin >> y2;
    y2 -= 1;
    std::cin >> col;

    if(y1>y2){
        temp = y1;
        y1 = y2;
        y2 = temp;
    }


    for( ; y1 <= y2; y1++){
        if(x>=0 && x<n && y1 >= 0 && y1 < m){
            sc[y1][x] = col;
        }
    }

}

void h_draw(std::vector<std::vector<char>>& sc, int m, int n)
{
    int x1, x2; 
    int y;
    int temp;
    char col;

    std::cin >> x1;
    x1 -= 1;
    std::cin >> x2;
    x2 -= 1;
    std::cin >> y;
    y -= 1;
    std::cin >> col;

    if(x1>x2){
        temp = x1;
        x1 = x2;
        x2 = temp;
    }

    for( ; x1 <= x2; x1++){
        if(x1>=0 && x1<n && y >= 0 && y < m){
            sc[y][x1] = col;
        }
    }

}

void draw_rect(std::vector<std::vector<char>>& sc, int m, int n)
{
    int x1, y1; 
    int x2, y2;

    char col;
    std::cin >> x1;
    x1 -= 1;
    std::cin >> y1;
    y1 -= 1;
    std::cin >> x2;
    x2 -= 1;
    std::cin >> y2;
    y2 -= 1;
    std::cin >> col;

    int y = y1 < y2 ? y1 : y2;
    int x = x1 < x2 ? x1 : x2;

    int max_y = y1 > y2 ? y1 : y2;
    int max_x = x1 > x2 ? x1 : x2;

    for(; y <= max_y; y++){
        for(int xx{x}; xx <= max_x; xx++){
            if(xx>=0 && xx<n && y >= 0 && y < m){
                sc[y][xx] = col;
            }
        }
    }
}

void rec_fill_reg(std::vector<std::vector<char>>& sc, int x, int y, int m, int n, int col, int new_col);

void fill_reg(std::vector<std::vector<char>>& sc, int m, int n)
{
    int x, y; 
    char new_col;
    char col;
    
    std::cin >> x;
    x -= 1;
    std::cin >> y;
    y -= 1;
    std::cin >> new_col;
    if(x>=0 && x<n && y >= 0 && y < m){
        col = sc[y][x];

        if(col != new_col){
            rec_fill_reg(sc, x, y, m, n, col, new_col);
        }
    }

}

void rec_fill_reg(std::vector<std::vector<char>>& sc, int x, int y, int m, int n, int col, int new_col){
    int n_x;
    int n_y;
    for (int i{-1}; i <= 1; i++){
        for (int j{-1}; j <= 1; j++){
            n_x = x + j;
            n_y = y + i;
            if(n_x >= 0 && n_x < n && n_y >= 0 && n_y < m && sc[n_y][n_x] == col){
                sc[n_y][n_x] = new_col;
                rec_fill_reg(sc, n_x, n_y, m, n, col, new_col);
            }
        }
    }
}

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}