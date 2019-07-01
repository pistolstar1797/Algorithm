#ifndef HW3CPP_H
#define HW3CPP_H

#include <vector>
#include <stack>

using namespace std;

//parameters
//adj : adjacent list of graph where the smallest element is the 0th element.
	//in array adj[i], neighbors of the ith vertecies are inserted.
//num_v : the number of vertecies.
//num_e : the number of edges.
//ans : ans[i] means that ith vertex is included in the ans[i]th strongly connected component.
	//ans[i] should be non-negative integer.
	//if there are multiple answers, please find the lexicoraphically smallest sequence.

//This function should return the number of strongly connnected components.

void listdfs2(const vector<vector<int>>&adj, int num_v, int cur_v, bool visited[], int cnt, vector<int>&ans) 
{ 
    visited[cur_v] = true;
	ans[cur_v] = cnt;
  
    for(int i = 0 ; i < adj[cur_v].size() ; i++) {
		if(!visited[adj[cur_v][i]]) {
			listdfs2(adj, num_v, adj[cur_v][i], visited, cnt, ans);
		}
	}
} 

void listdfs(const vector<vector<int>>&adj, int num_v, int cur_v, bool visited[], stack<int> &Stack) {
	visited[cur_v] = true; 
	
	for(int i = 0 ; i < adj[cur_v].size() ; i++) {
		if(!visited[adj[cur_v][i]]) {
			listdfs(adj, num_v, adj[cur_v][i], visited, Stack);
		}
	}
	
	Stack.push(cur_v);
}

int find_scc_with_adj_list(const vector<vector<int>>&adj,int num_v,int num_e,vector<int>&ans){
	stack<int> dfsStack; 
  
    bool *visited = new bool[num_v]; 
    for(int i = 0; i < num_v; i++) 
        visited[i] = false; 
  
    for(int i = 0; i < num_v; i++) {
        if(!visited[i]) {
            listdfs(adj, num_v, i, visited, dfsStack); 
		}
	}
	
	vector<vector<int>>adj_r(num_v);

	for(int i = 0 ; i < num_v ; i++) {
		for(int j = 0 ; j < adj[i].size() ; j++) {
			adj_r[adj[i][j]].push_back(i);
		}
	}
    
	for(int i = 0; i < num_v; i++) 
        visited[i] = false; 
	
	int cnt = 0;

    while (dfsStack.empty() == false) 
    { 
        int v = dfsStack.top();
        dfsStack.pop(); 

        if (visited[v] == false) {
            listdfs2(adj_r, num_v, v, visited, cnt, ans);
			cnt++;
        } 
    }

	int *wrap = new int[cnt];

	for(int i = 0; i < cnt; i++) 
        wrap[i] = 0;

	int check = 1;

	for(int i = 0 ; i < num_v ; i++) {
		if(wrap[ans[i]] == 0) {
			wrap[ans[i]] = check;
			check++;
		}

		ans[i] = wrap[ans[i]] - 1;
	}

	return cnt;
}

//adj : num_v x num_v dimension adjacency matrix of the given graph

//the other parameters have same as above function.

void matdfs2(const vector<vector<int>>&adj, int num_v, int cur_v, bool visited[], int cnt, vector<int>&ans) 
{ 
    visited[cur_v] = true;
	ans[cur_v] = cnt;
  
    for(int i = 0 ; i < num_v ; i++) {
		if(adj[cur_v][i] == 1 && !visited[i]) {
			matdfs2(adj, num_v, i, visited, cnt, ans);
		}
	}
} 

void matdfs(const vector<vector<int>>&adj, int num_v, int cur_v, bool visited[], stack<int> &Stack) {
	visited[cur_v] = true; 
	
	for(int i = 0 ; i < num_v ; i++) {
		if(adj[cur_v][i] == 1 && !visited[i]) {
			matdfs(adj, num_v, i, visited, Stack);
		}
	}
	
	Stack.push(cur_v);
}

int find_scc_with_adj_mat(const vector<vector<int>>&adj,int num_v,int num_e,vector<int>&ans){
	stack<int> dfsStack; 

	
    bool *visited = new bool[num_v]; 
    for(int i = 0; i < num_v; i++) 
        visited[i] = false; 
  
    for(int i = 0; i < num_v; i++) {
        if(!visited[i]) {
            matdfs(adj, num_v, i, visited, dfsStack); 
		}
	}
	
	vector<vector<int>>adj_r(num_v);

	for(int i=0;i<num_v;i++){
        adj_r[i].resize(num_v);
    }

	for(int i = 0 ; i < num_v ; i++) {
		for(int j = 0 ; j < num_v ; j++) {
			adj_r[i][j] = adj[j][i];
		}
	}
    
	for(int i = 0; i < num_v; i++) 
        visited[i] = false; 
	
	int cnt = 0;

    while (dfsStack.empty() == false) 
    { 
        int v = dfsStack.top();
        dfsStack.pop(); 

        if (visited[v] == false) 
        {
            matdfs2(adj_r, num_v, v, visited, cnt, ans);
			cnt++;
        } 
    }

	int *wrap = new int[cnt];

	for(int i = 0; i < cnt; i++) 
        wrap[i] = 0;

	int check = 1;

	for(int i = 0 ; i < num_v ; i++) {
		if(wrap[ans[i]] == 0) {
			wrap[ans[i]] = check;
			check++;
		}

		ans[i] = wrap[ans[i]] - 1;
	}

	return cnt;
}


#endif
