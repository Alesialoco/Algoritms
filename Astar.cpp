#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <utility>


double distance_between_0_n(int n) {
    // расстояние по оси между центром нулевой клетки и клетки с номером по оси n
    return (2 - std::pow(0.5, n + 1)) - 0.5 - std::pow(0.5, n);
}

double Evrist(std::pair<int, int> from, std::pair<int, int> to) {
    double x_dist = std::abs(
        distance_between_0_n(from.first) 
        - distance_between_0_n(to.first));

    double y_dist = std::abs(
        distance_between_0_n(from.second) 
        - distance_between_0_n(to.second));

    return x_dist + y_dist;
}

double Astar(std::vector<std::vector<int>> matrix, int N, int M, std::pair<int, int> from, std::pair<int, int> to){
    auto comparator = [to](const std::pair<std::pair<int, int>, double>& a, 
        const std::pair<std::pair<int, int>, double>& b) {
            return a.second + Evrist(a.first, to) > b.second + Evrist(b.first, to);
    };

    std::priority_queue<std::pair<std::pair<int, int>, double>, 
        std::vector<std::pair<std::pair<int, int>, double>>, decltype(comparator)> pq(comparator);
    
    pq.push({from, 0});
    while(pq.size()){
        std::pair<std::pair<int, int>, double> current = pq.top();
        std::pair<int, int> point = current.first;
        pq.pop();
        if (matrix[point.first][point.second] == -1) 
            continue;
        matrix[point.first][point.second] = -1;
        if (point == to ) 
            return current.second;
        if (point.first - 1 >= 0 && matrix[point.first - 1][point.second] == 1){
            pq.push({{point.first - 1, point.second}, current.second + distance_between_0_n(point.first) - distance_between_0_n(point.first - 1)});
        }
        if (point.first + 1 < N && matrix[point.first + 1][point.second] == 1){
            pq.push({{point.first + 1, point.second}, current.second + distance_between_0_n(point.first + 1) - distance_between_0_n(point.first)});
        }
        if (point.second - 1 >= 0 && matrix[point.first][point.second - 1] == 1){
            pq.push({{point.first, point.second - 1}, current.second + distance_between_0_n(point.second) - distance_between_0_n(point.second - 1)});
        }
        if (point.second + 1 < M && matrix[point.first][point.second + 1] == 1){
            pq.push({{point.first, point.second + 1}, current.second + distance_between_0_n(point.second + 1) - distance_between_0_n(point.second)});
        }
    }  
    return INFINITY;
}
