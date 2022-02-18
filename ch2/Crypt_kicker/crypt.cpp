#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>

int match(std::string& word1, std::string& word2, std::unordered_map<char,char>& trans, std::unordered_map<char,char>& trans_rev, std::vector<char>& added);
int max_repeated(std::string str);
int decypher(std::vector<std::string>& words, std::size_t i, std::unordered_map<char,char>& trans,std::unordered_map<char,char>& trans_rev, std::unordered_map<int, std::unordered_map<int, std::vector<std::string>>>& dic);

int main(){

    int rc;
    std::unordered_map<int, std::unordered_map<int, std::vector<std::string>>> dic;
    int num_dic_ws;
    std::string word;
    std::cin >> num_dic_ws;
    for (int i=0; i<num_dic_ws; i++){
        std::cin >> word;
        int size = word.size();
        int reps = max_repeated(word);
        dic[size][reps].push_back(word);
    }

    std::cin >> std::ws;
    for (std::string line; std::getline(std::cin,line);){
        std::stringstream strm(line);
        std::vector<std::string> words;
        std::unordered_map<char, char> trans;
        std::unordered_map<char, char> trans_rev;
        for (std::string word; strm>>word;){
            words.push_back(word);
        }

        int rc = decypher(words,0, trans, trans_rev, dic);
        for (size_t i=0; i<words.size(); i++){
            for (auto& ch : words[i]){
                if (rc == 0){
                    ch = '*';
                }else{
                    ch = trans[ch];
                }
            }
            std::cout << words[i];
            if (i < words.size()-1){
                std::cout << " ";
            }else{
                std::cout << "\n";
            }
        }

    }

    return 0;
}

int max_repeated(std::string str)
{
    std::sort(str.begin(), str.end());

    int max=0;
    
    for (int i=0;i<str.size();){
        int j=i;
        for (; j<str.size() && str[j]==str[i]; j++);
        if (j-i > max){
            max = j-i;
        }
        i = j;
    }

    return max;
}

int decypher(std::vector<std::string>& words, std::size_t i, std::unordered_map<char,char>& trans,std::unordered_map<char,char>& trans_rev, std::unordered_map<int, std::unordered_map<int, std::vector<std::string>>>& dic)
{
    if (i>=words.size()){
        return 1;
    }
    int rc {0};
    int num_rep = max_repeated(words[i]);
    std::size_t w_size = words[i].size();
    auto& list = dic[w_size][num_rep];
    for (auto &word: list){
        std::vector<char> added;
        if (match(words[i], word, trans, trans_rev, added)){
            rc = decypher(words, i+1, trans, trans_rev, dic);
            if (rc == 0){
                int tmp;
                for (char ch : added){
                    tmp = trans[ch];
                    trans.erase(ch);
                    trans_rev.erase(tmp);
                }
            }else{
                break;
            }
        }
    }

    return rc;
    
}

int match(std::string& word1, std::string& word2, std::unordered_map<char,char>& trans, std::unordered_map<char,char>& trans_rev, std::vector<char>& added)
{
    int match{1};
    char c;
    for (std::size_t i{0}; i<word1.size(); i++){
        c = word1[i];
        if (trans.count(c)){
            if(trans[c] != word2[i]){
                match = 0;
                break;
            } 
        }else{
            if (trans_rev.count(word2[i]) == 0){
                added.push_back(c);
                trans[c] = word2[i];
                trans_rev[word2[i]] = c;
            }else{
                match = 0;
                break;
            }
        }
    }

    char tmp;
    if (match==0){
        for (char ch : added){
            tmp = trans[ch];
            trans.erase(ch);
            trans_rev.erase(tmp);
        }
        added.clear();
    }
    return match;

}