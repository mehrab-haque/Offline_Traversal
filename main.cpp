#include<iostream>
#include <vector>
#include<queue>

using namespace std;

int C,R,L,F;
int *currPieceList;
vector<int> *adj_list;
bool *isVisited;
int collected;

void bfs(int startV){
	queue<int> queue;
	isVisited[startV]=true;
	queue.push(startV);
	while(!queue.empty()){
		int currV=queue.front();
		queue.pop();
		collected+=currPieceList[currV];
		currPieceList[currV]=0;
		for(int i=0;i<adj_list[currV].size();i++){
			if(!isVisited[adj_list[currV][i]]){
				isVisited[adj_list[currV][i]]=true;
				queue.push(adj_list[currV][i]);
			}
		}	
	}
}

void dfs(int currV){
	isVisited[currV]=true;
	collected+=currPieceList[currV];
	currPieceList[currV]=0;
	for(int i=0;i<adj_list[currV].size();i++){
		if(!isVisited[adj_list[currV][i]])
			dfs(adj_list[currV][i]);
	}
}

int main(){
	int i=-1;
	cin>>C>>R>>L>>F;
	adj_list=new vector<int>[C];
	isVisited=new bool[C];
	int *originalPieceList=new int[C];
	currPieceList=new int[C];
	for(int j=0;j<C;j++)
		originalPieceList[j]=0;
	int friendsList[F];
	int collectionList[F];
	for(int j=0;j<F;j++){
		friendsList[j]=0;
		collectionList[j]=0;
	}
	while(++i<R){
		int C1,C2;
		cin>>C1>>C2;
		adj_list[C1].push_back(C2);
		adj_list[C2].push_back(C1);
	}
	i=-1;
	int nPieces=0;
	while(++i<L){
		int Cx,Px;
		cin>>Cx>>Px;
		originalPieceList[Cx]=Px;
		nPieces+=Px;
	}
	i=-1;
	while(++i<F){
		int Cy,Fy;
		cin>>Cy>>Fy;
		friendsList[Fy]=Cy;
	}
	int totalCollected;
	
	//bfs
	for(int i=0;i<C;i++)
		isVisited[i]=false;
	cout<<endl<<"########BFS########"<<endl;
	for(int j=0;j<C;j++)
		currPieceList[j]=originalPieceList[j];
	totalCollected=0;
	for(int j=0;j<F;j++){
		collected=0;
		bfs(friendsList[j]);
		collectionList[j]=collected;
		totalCollected+=collectionList[j];
	}
	if(totalCollected==nPieces)
		cout<<"Mission Accomplished"<<endl;
	else
		cout<<"Mission Impossible"<<endl;
	cout<<totalCollected<<" out of "<<nPieces<<" pieces are collected"<<endl;
	for(int j=0;j<F;j++)
		cout<<j<<" collected "<<collectionList[j]<<" pieces"<<endl;
	
	
	//dfs
	for(int i=0;i<C;i++)
		isVisited[i]=false;
	cout<<endl<<"########DFS########"<<endl;
	for(int j=0;j<C;j++)
		currPieceList[j]=originalPieceList[j];
	totalCollected=0;
	for(int j=0;j<F;j++){
		collected=0;
		dfs(friendsList[j]);
		collectionList[j]=collected;
		totalCollected+=collectionList[j];
	}
	if(totalCollected==nPieces)
		cout<<"Mission Accomplished"<<endl;
	else
		cout<<"Mission Impossible"<<endl;
	cout<<totalCollected<<" out of "<<nPieces<<" pieces are collected"<<endl;
	for(int j=0;j<F;j++)
		cout<<j<<" collected "<<collectionList[j]<<" pieces"<<endl;
	
	
	return 0;
}
