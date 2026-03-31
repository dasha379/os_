#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

bool growing_pos(int i, int j, const std::vector<int> a){
    for (int k = i; k < j; ++k){
        if (a[k] >= a[k + 1])
            return false;
    }
    return true;
}

int main(){
    int i;
    std::vector<int> arr;
    
    while (std::cin >> i){
        arr.push_back(i);
    }
    int n = arr.size();

    int max_len = 0;
    int max_sum = INT_MIN;
    std::vector<int> pref = {n};
    pref[0] = arr[0];
    for (int i = 1; i < n; ++i){
        pref[i] = pref[i - 1] + arr[i];
    }

    int cur_len = 1;
    int cur_sum = 0;
    int st, end;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < i; ++j){
            cur_sum = pref[i] - pref[j];
            cur_len = i - j + 1;
            if (growing_pos(j, i, arr)){
                if (cur_sum > max_sum && cur_len >= max_len){
                    max_len = cur_len;
                    max_sum = cur_sum;
                    st = j;
                    end = i;
                }
            }
        }
    }

    std::cout << '\n';
    for (int i = st; i <= end; ++i){
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}