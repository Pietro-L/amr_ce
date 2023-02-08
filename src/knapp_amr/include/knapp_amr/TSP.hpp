#ifndef TSP_H
#define TSP_H

/*
CLASS TO SOLVE Travelling Salesman Problem
Uses dynamic programming to obtain shortest path with adjacency matrix as input.
*/
#include<vector>
#include<iostream>
#include <limits>
class TSP {
public:
    TSP(std::vector<std::vector<float>> d) : n(d.size()), dp(1<<n, std::vector<float>(n, -1)), dist(d) {}

    float tsp(int u, int bitmask) {
        if (bitmask == (1<<n)-1) return dist[u][0];
        if (dp[bitmask][u] != -1) return dp[bitmask][u];
        float ans = std::numeric_limits<float>::max();
        for (int v=0; v<n; v++)
            if (!(bitmask & (1<<v)))
                ans = std::min(ans, dist[u][v] + tsp(v, bitmask|(1<<v)));
        return dp[bitmask][u] = ans;
    }
    
    void solvePath(int u, int bitmask) {
        path.push_back(u);
        if (bitmask == (1<<n)-1){path.push_back(path[0]);
        return;}
        float ans = std::numeric_limits<float>::max();
        int v_min = -1;
        for (int v=0; v<n; v++)
            if (!(bitmask & (1<<v))) {
                float cur = dist[u][v] + tsp(v, bitmask|(1<<v));
                if (cur < ans) {
                    ans = cur;
                    v_min = v;
                }
            }
        solvePath(v_min, bitmask|(1<<v_min));
    }

    std::vector<int> solve() {
        // for(auto i:dist){
        //     for(auto j : i)
        //         std::cout << j << '\t';
        //     std::cout << '\n';
        // }
        // float ans = tsp(0,1);
        // std::cout << "Minimum cost: " << ans << std::endl;
        solvePath(0,1);
        // for(auto i:path){
        //     std::cout << i << '\t';
        // }

        return path;
    }

private:
    int n;
    std::vector<std::vector<float>> dp;
    std::vector<std::vector<float>> dist;
    std::vector<int> path;
};


#endif