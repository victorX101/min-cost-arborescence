/*i declare that i have done this code on my own 
himanshu
2018meb1152

sample input output cases
3
6 1
9
1 2 10
1 3 2
1 4 10
2 3 1
3 4 4
4 5 2
2 6 8
5 2 2
4 6 4
8 1
13 
1 2 5
1 5 11
5 2 6
6 5 10
6 2 2 
2 3 3
2 7 13
7 6 7
3 7 9
3 4 12
4 8 1
8 3 4
7 8 8
7 7
8
1 2 3
2 3 4
3 1 5
3 4 16
4 5 10
5 6 11
6 4 12
7 1 20
14 0 10 2 6 8 10 # 0 5 1 3 4 4 
47 0 5 8 20 34 24 17 21 # 0 1 2 3 6 7 3 4 
64 20 23 27 43 53 64 0 # 7 1 2 3 4 5 0 
Time taken by program is : 0.000529 sec





NOTE that it shows a message when all the vertices are not reachable from source
*/
#include<iostream>
#include<bits/stdc++.h>
#include <sys/time.h>
using namespace std;
#define MAX 999999
#define M 99990
#define N 200
int parent[N];
int reachable[N]={0};
int cnum = -1;
int s,n;
void givefinal(int arr[][N])
{
	int i;
	while(cnum!=-1)
	{
		int i,j,min;
		min = 0;
		for(i=1;i<n+cnum;i++)
		{
			if(arr[min][n+cnum]>arr[i][n+cnum])
			min = i;
		}
		for(i=0;i<n+cnum;i++)
		{
			if(arr[i][n+cnum]==M && arr[min][i]==arr[min][n+cnum])
			break;
		}
		arr[parent[i]][i]=MAX;
		parent[i]=min;
		
		
		
		for(j=0;j<n+cnum;j++)
		if(arr[n+cnum][j]<MAX)
		{
			for(i=0;i<n+cnum;i++)
			if(arr[i][j]==arr[n+cnum][j] && arr[i][n+cnum]==M)
			{
				if(arr[i][j]<=arr[parent[j]][j])
				parent[j]=i;
			}
		}
		cnum--;
	}
	
}
void dfs(int arr[][N],int t)
{
	int j;
	reachable[t]=1;
	for(j=0;j<n;j++)
	if(arr[t][j]<MAX)
	{
		if(reachable[j]==0)
		{
			reachable[j]=1;
			dfs(arr,j);
		}
	}
}
void finalans(int arr[][N])
{
	int i,d;
	d=0;
	int dist[n]={0};
	for(i=0;i<n;i++)
	{
		if(reachable[i]==0)
		continue;
		if(i!=s-1)
		d=d+arr[parent[i]][i];
	}
	cout<<d<<" ";
	for(i=0;i<n;i++)
	{
		if(i==s-1)
		{dist[i]=0;
		continue;}
		int temp = i;
		while(parent[temp]!=-1)
		{
			dist[i]=dist[i]+arr[parent[temp]][temp];
			temp=parent[temp];
		}
	}
	for(i=0;i<n;i++)
	cout<<dist[i]<<" ";
	cout<<"#"<<" ";
	for(i=0;i<n;i++)
	cout<<parent[i]+1<<" ";
	cout<<endl;
	return;
}
// It is a recursive function which keeps on making new suernodes as long as their are new cycles in graph and as soon as we reach a graph in which their is no cycle
// we call function giveanswer() which opens the supernodes one by one
void mincostarbor(int arr[][N],int vert[],int en)
{
	int min = 0;
	int i,j,k;
	for(j=0;j<en;j++)
	{
		min = vert[0];
		if(vert[j]==s-1)
		{parent[vert[j]]=-1;
		continue;}
		for(i=1;i<en;i++)
		if(arr[min][vert[j]]>arr[vert[i]][vert[j]])
		min = vert[i];
		parent[vert[j]]=min;
	}
		
		int visited[N]={0};
		int a[N];
		int temp=vert[0];
		i=1;k=-1;
		int flag;
		while(visited[temp]!=i)
		{
			flag=0;
			k++;
			a[k]=temp;
			visited[temp]=i;
			temp = parent[temp];
			
			if(temp==-1)
			{
				i++;
				for(j=0;j<en;j++)
				{
					if(visited[vert[j]]==0)
					{temp=vert[j];
					flag=1;
					break;
					}
				}
				if(flag==0)
				break;
			}
		}
		if(visited[temp]==i)
		{
			unordered_set<int> cycle;
			cycle.insert(temp);
			while(a[k]!=temp)
			{
				cycle.insert(a[k]);
				k--;
			}
			int z = 0;
			cnum++;
			
			unordered_set<int> :: iterator itr;
			int min1;
			for(i=0;i<n+cnum;i++)
			arr[n+cnum][i]=MAX;
			for(i=0;i<=n+cnum;i++)
			arr[i][n+cnum]=MAX;
			for(j=0;j<en;j++)
			{
				if(cycle.find(vert[j])==cycle.end())
				{
					min = arr[vert[j]][*(cycle.begin())];
					min1 = arr[*(cycle.begin())][vert[j]];
					for(itr=cycle.begin();itr!=cycle.end();itr++)
					{
						if(min > arr[vert[j]][(*itr)])
						min = arr[vert[j]][(*itr)];
						if(min1 >  arr[(*itr)][vert[j]])
						min1 = arr[(*itr)][vert[j]];
					}
					arr[vert[j]][n+cnum]=min;
					arr[n+cnum][vert[j]]=min1;
				}
				else if(cycle.find(vert[j])!=cycle.end())
				arr[vert[j]][n+cnum]=M;
			}
			for(i=0;i<en;i++)
			{
				if(cycle.find(vert[i])==cycle.end())
				vert[z++]=vert[i];
			}
			vert[z]=n+cnum;
			en = z+1;
			mincostarbor(arr,vert,en);
		}
		else if(flag==0)
		{
			givefinal(arr);
			finalans(arr);
		}
		return;
}
int main()
{
	struct timeval start, end; 
	gettimeofday(&start, NULL);
	int t;
	cin>>t;
	while(t>0)
	{
		cnum = -1;
		cin>>n>>s;
		int arr[N][N];
		int m,i,j,flag;
		cin>>m;
		vector<int> vec[n];
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		arr[i][j]=MAX;
		for(i=0;i<N;i++)
		reachable[i]=0;
		int u,v,w; 
		for(i=0;i<m;i++)
		{
			cin>>u>>v>>w;
			arr[u-1][v-1]=w;
			vec[u-1].push_back(w-1);
		}
		int vert[N];
		j=0;
		dfs(arr,s-1);
		for(i=0;i<n;i++)
		if(reachable[i]==1)
		vert[j++]=i;
		if(j!=n)
		{cout<<"some of the vertices are unreachable"<<endl;
		t=t-1;
		continue;}
		mincostarbor(arr,vert,j);
		t=t-1;
	}
	gettimeofday(&end, NULL);
	double time_taken; 
          time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
    	  time_taken = (time_taken + (end.tv_usec -  start.tv_usec)) * 1e-6; 
  
         cout << "Time taken by program is : " << fixed << time_taken << setprecision(6); 
         cout << " sec" << endl;
	return 0;
}
		
