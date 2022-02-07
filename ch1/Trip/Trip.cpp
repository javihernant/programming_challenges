#include <iostream>
#include <vector>

std::string get_cents(int);

int main()
{
    int num_students;
    int total; /* total cents spent */
    int avg_floor, avg_ceil; /* average in cents */
    int remainings; /* remainings after dividing all cents into all the students */
    int money; /* all cents spent by current student */
    int dollars, cents; /*dollars and cents of current student */
    int more, less; /* difference between money spent and the average. 
    more holds the difference from the people who payed more than avg; less for those who payed less. */
    int res;
    int is_rounded;
    std::vector<int> v;

    while(scanf("%d", &num_students) != EOF){
        
        if(num_students==0){
            break;
        }
        v.clear();
        

        total = 0;
        for(int i=0; i<num_students; i++){
            scanf("%d.%d", &dollars, &cents);
            money = dollars*100 + cents;
            v.push_back(money);
            total += money;
        }

        avg_floor = total/num_students;
        is_rounded = (total % num_students) != 0;

        more = 0;
        less = 0;

        for(int i=0; i<num_students; i++){
            if(is_rounded && v[i] >= avg_floor+1){
                more += v[i] - (avg_floor + 1);
            }else if(!is_rounded && v[i] > avg_floor){
                more += v[i] - avg_floor;
            }else{
                less += avg_floor - v[i];
            }    
        }
        
        res = more > less ? more : less;
        std::cout << "$" << res/100 <<".";
        if (res%100 < 10){
            std::cout << '0';
        }
        std::cout << res%100 << std::endl;
   
    }

    return 0;
}