#include <iostream>
#include <vector>

void st_digit(std::vector<std::vector<char>>& arr, char d, int offset, int s);
void st_segment(int seg, std::vector<std::vector<char>>& arr, int offset, int s);

int main()
{
    std::vector<int> v;
    int sz; /* size of the output. Number of -/| that are printed in each segment */
    std::string num; /* number to print */
    int num_digits; /* number of digits that the number has */
    int rows, cols;
    int col_offset;
    int is_zero;

    while(std::cin >> sz >> num){
        is_zero = 1;
        for(char d :num){
            if(d != '0'){
                is_zero = 0;
                break;
            }
        }

        if(sz == 0 && is_zero){
            break;
        }

        rows = 2*sz + 3;
        cols = 2+sz;

        num_digits = num.size();  

        std::vector<std::vector<char>> arr(rows,std::vector<char>((cols+1)*(num_digits-1)+cols, ' '));

        for(int i=0; i<num_digits; i++){
            col_offset = i*(cols+1);
            st_digit(arr, num[i], col_offset, sz);
        }

        for (int i=0; i<rows; i++){
            for (char c: arr[i]){
                std::cout << c;
            }
            std::cout << std::endl;
        }        
        std::cout << std::endl;
    }

    return 0;
}

void st_digit(std::vector<std::vector<char>>& arr, char d, int offset, int s)
{
    switch(d){
        case '0':
            st_segment(0, arr, offset, s);
            st_segment(1, arr, offset, s);
            st_segment(2, arr, offset, s);
            st_segment(3, arr, offset, s);
            st_segment(4, arr, offset, s);
            st_segment(5, arr, offset, s);
            break;
        case '1':
            st_segment(1, arr, offset, s);
            st_segment(2, arr, offset, s);
            break;
        case '2':
            st_segment(0, arr, offset, s);
            st_segment(1, arr, offset, s);
            st_segment(6, arr, offset, s);
            st_segment(4, arr, offset, s);
            st_segment(3, arr, offset, s);
            break;
        case '3':
            st_segment(0, arr, offset, s);
            st_segment(6, arr, offset, s);
            st_segment(3, arr, offset, s);
            st_segment(1, arr, offset, s);
            st_segment(2, arr, offset, s);
            break;
        case '4':
            st_segment(5, arr, offset, s);
            st_segment(1, arr, offset, s);
            st_segment(6, arr, offset, s);
            st_segment(2, arr, offset, s);
            break;
        case '5':
            st_segment(0, arr, offset, s);
            st_segment(5, arr, offset, s);
            st_segment(6, arr, offset, s);
            st_segment(2, arr, offset, s);
            st_segment(3, arr, offset, s);
            break;
        case '6':
            st_segment(0, arr, offset, s);
            st_segment(5, arr, offset, s);
            st_segment(4, arr, offset, s);
            st_segment(3, arr, offset, s);
            st_segment(2, arr, offset, s);
            st_segment(6, arr, offset, s);
            break;
        case '7':
            st_segment(0, arr, offset, s);
            st_segment(1, arr, offset, s);
            st_segment(2, arr, offset, s);
            break;
        case '8':
            st_segment(0, arr, offset, s);
            st_segment(1, arr, offset, s);
            st_segment(2, arr, offset, s);
            st_segment(3, arr, offset, s);
            st_segment(4, arr, offset, s);
            st_segment(5, arr, offset, s);
            st_segment(6, arr, offset, s);
            break;
        case '9':
            st_segment(0, arr, offset, s);
            st_segment(1, arr, offset, s);
            st_segment(5, arr, offset, s);
            st_segment(6, arr, offset, s);
            st_segment(2, arr, offset, s);
            st_segment(3, arr, offset, s);
            break;
    }
    
    
}

void st_segment(int seg, std::vector<std::vector<char>>& arr, int offset, int s)
{
    int i = 0;
    int j = offset;

    if(seg == 0 || seg == 6 || seg == 3){
        j+=1;
    }

    if(seg == 1 || seg == 2){
        j+=1 + s;
    }

    if(seg == 1 || seg == 5){
        i+=1;
    }

    if(seg == 4 || seg == 2){
        i+=s+2;
    }
    
    if(seg == 6){
        i+=s+1;
    }

    if(seg == 3){
        i+= 2*s+2;
    }
    
    int horizontal = (seg == 0 || seg == 6 || seg == 3); 
    while(s--){
        arr[i][j] = horizontal ? '-' : '|';
        if(horizontal){
            j++;
        }else{
            i++;
        }
    }


}