#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
int find_min(deque<int> q){
  int min = q.front();
  q.pop_front();
  while(!q.empty()){
    if(q.front() < min){
      min= q.front();
    }
    q.pop_front();
  }
  return min;
}
deque<int> merge_q(deque<int> a, deque<int> b){
  deque<int> c = a;
  while(!b.empty()){
    c.push_back(b.front());
    b.pop_front();
  }
  return c;
}
int main(int argc,char* argv[]){
  deque<int> labels = {};
  string line;
  deque< deque<int> > all_q;all_q.push_back(labels);
  deque<int> Empty = {};
  deque<int> Ans = {};;
  ifstream fin1, fin2, fin3;
  fin1.open(argv[1]); 
  fin2.open(argv[2]); 
  fin3.open(argv[3]); 
  while (getline(fin2, line)) {
    int e = line.length()-2;
    labels.push_back(stoi(line.substr(1, e)));
  }
  int run_num = labels.size()-10;
  for(int i = 0; i < run_num; ++i){
    getline(fin1, line);
    int n1, n2;
    deque<int> a_q, b_q, c_q;
    n1 = stoi(line.substr(0,line.find_first_of(",")));
    n2 = stoi(line.substr(line.find_first_of(",")+1));
    if(n1 < 0){
      a_q.push_back(labels[(n1+1)*(-1)]);
    }else{
      a_q = all_q[n1];
      all_q[n1] = Empty;
    }
    if(n2 < 0){
      b_q.push_back(labels[(n2+1)*(-1)]);
    }else{
      b_q = all_q[n2];
      all_q[n2] = Empty;
    }
    c_q = merge_q(a_q, b_q);
    all_q.push_back(c_q);
  }
  while(!all_q.empty()){
    if(all_q.front().size()>0){
      Ans.push_back(find_min(all_q.front()));
    }
    all_q.pop_front();
  }
  sort(Ans.begin(),Ans.end());
  while(!Ans.empty()){
    if(Ans.size() == 1){
      cout << Ans.front();
      break;
    }
    cout << Ans.front() << " ";
    Ans.pop_front();
  }
  fin1.close();
  fin2.close();
  fin3.close();
}
