//
//  main.cpp
//  laba4algopart2
//
//  Created by Guryanova Dasha on 01.03.18.
//  Copyright © 2018 Guryanova Dasha. All rights reserved.
//

#include <iostream>
#include<vector>

using namespace std;
double max=1e9;

struct node{
    node * left;
    node * right;
    int data;
    node(int data): data(data),left(nullptr),right(nullptr) {}
};
struct optimal_tree{
    node *root;
    void add(int data);
    bool search(int data);
    
    optimal_tree(): root(nullptr) {}
};

void optimal_tree::add(int data){//function that add ellement to tree
    if(!root){
        root=new node(data);
        return;
    }
    node *pointer=root;
    node *parent=nullptr;
    while(pointer){
        parent=pointer;
        if(pointer->data > data){
            pointer=pointer->left;
        }else{
            pointer=pointer->right;
        }
    }
    if(parent->data >data){
        parent->left=new node(data);
    }
    else{
        parent->right=new node(data);
    }
}

bool optimal_tree::search (int data){//function which finds  element
    if(!root){
        return false;
    }
    node *pointer=root;
    while(pointer){
        if(pointer->data==data){
            return true;
        }
        if(pointer->data < data){
            pointer=pointer->right;
        }
        else{
            pointer=pointer->left;
        }
    }
    return false;
}

// utility function which adds elements to the tree by root array
node *  add_optimal(int l, int r, vector<int> & keys, vector<vector<int> > & root){
    if(l>r) return nullptr;
    
    int m = root[l][r];
  
    if(l==r) return new node(keys[m]);
    
    node * tmp = new node(keys[m]);
    tmp -> left = add_optimal(l,m-1, keys, root);
    tmp -> right = add_optimal(m+1,r, keys, root);
    return tmp;
}



optimal_tree optimal_binary_tree(vector <int> & keys,vector <double > & p,vector <double> & q,int n){  //p-probbility of real keys ,q-probability of dummy keys
    double e[n+2][n+1];//array for calculating mathematical expectation
    vector<vector<int> > root(n+1, vector<int>(n+1));
    double w[n+2][n+1];//aray for calculating
    
    for (int i=1;i<=n+1;i++){
        e[i][i-1]=q[i-1];
        w[i][i-1]=q[i-1];
        
    }
    for(int l = 1; l <= n ; l++ ){
        for( int i = 1 ; i <= n - l + 1 ; i++ ){
            int j=i+l-1;
            e[i][j]=100000;
            w[i][j]=w[i][j-1]+p[j]+q[j];
            for(int r=i;r<=j;r++){
                double k=e[i][r-1]+e[r+1][j]+w[i][j];//formula which help us calculating math expactation
                
                if(k<e[i][j]){
                    e[i][j]=k;
                    root[i][j]=r;
                }
            }
        }
       
    }
    cout << "root array:" << endl;
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j ++){
            cout << root[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "mathematical expectation array:" << endl;
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j ++){
            cout << e[i][j] << " ";
        }
        cout << endl;
    }
    optimal_tree result;
    result.root = add_optimal(1, n, keys, root);
    return result;
}
    
int main(int argc, const char * argv[]) {
    vector<int> keys = {0,1,2,3,4,5};
    vector<double> p = {0,0.15,0.1,0.05,0.1,0.2};
    vector<double> q = {0.05,0.1,0.05,0.05,0.05,0.1};
    optimal_tree my_tree = optimal_binary_tree(keys, p, q, 5);
    
    return 0;
}
