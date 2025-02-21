#include <iostream>
#include <vector>

int find_element(const std::vector<int>& masive, int need_elem){
    int left = 0;
    int right = masive.size() - 1;
    if (need_elem == masive[left])
        return left;
    else if (need_elem == masive[right])
        return right;
    while (left <= right){
        int middle = (left + right) >> 1;
        if (need_elem == masive[middle])
            return middle;
        else if (masive[middle] < need_elem){
            if (masive[right] < need_elem)
                right = middle - 1;
            else
                left = middle + 1;
        }
        else{
            if (masive[right] > need_elem)
                right = middle - 1;
            else
                left = middle + 1;
        }
    }
    return -1;
}
