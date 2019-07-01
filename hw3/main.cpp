#include <cstdio>
#include <vector>
#include <algorithm>
#include <chrono>

#include "hw3_cpp.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]){
    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen(argv[1], "r");
    fp2 = fopen("out.txt", "w");
    fp3 = fopen("out0.txt", "w");
    fp4 = fopen(argv[2], "r");

    int num_v, num_e;

    fscanf(fp1, "%d %d", &num_v, &num_e);

    printf("Number of vertexes: %d\n", num_v);
    printf("Number of edges: %d\n", num_e);

    std::vector < std::vector < int > > adj_list(num_v);
    std::vector < std::vector < int > > adj_mat(num_v);
    
    for(int i=0;i<num_v;i++){
        adj_mat[i].resize(num_v);
    }

    for(int i = 0 ; i < num_e ; i++) {
        int x, y;
        fscanf(fp1, "%d %d", &x, &y);
        adj_list[x].push_back(y);
        adj_mat[x][y] = 1;
    }

    std::vector < int > ans1(num_v);

    system_clock::time_point start1 = system_clock::now();

    int scc1 = find_scc_with_adj_list(adj_list,num_v,num_e,ans1);
    
    system_clock::time_point end1 = system_clock::now();

    duration<double> sec1 = end1 - start1;

    printf("Time progress for using list: %lf sec\n", sec1);

    for(int i = 0 ; i < num_v ; i++) {
        fprintf(fp2, "%d\n", ans1[i]);
    }

    std::vector < int > ans2(num_v);
    
    system_clock::time_point start2 = system_clock::now();

    int scc2 = find_scc_with_adj_mat(adj_mat,num_v,num_e,ans2);

    system_clock::time_point end2 = system_clock::now();

    duration<double> sec2 = end2 - start2;

    printf("Time progress for using matrix: %lf sec\n", sec2);

    for(int i = 0 ; i < num_v ; i++) {
        fprintf(fp3, "%d\n", ans2[i]);
    }

    bool check = false;

    for(int i = 0 ; i < num_v ; i++) {
        int temp;
        fscanf(fp4, "%d", &temp);
        if(temp != ans1[i] || temp != ans2[i]) {
            printf("algorithm incorrect\n");
            check = true;
        }
    }

    if(!check) {
        printf("algorithm correct\n");
    }

    return 0;
}
