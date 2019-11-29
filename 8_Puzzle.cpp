#include <iostream>
#include <vector>
#include <iterator> 
#include <map> 
#include <string>
#include <bits/stdc++.h>
#include <functional>
#include <utility>
#include <queue>
#include <fstream>

using namespace std;

map<vector<vector<int> > , bool> visited; //declaring a map named "visited" that takes vector(which stores vectors that takes integer values) as its key, and a boolean as its value
map<vector<vector<int> > , vector<vector<int> > > parent; //declaring a map named "parent" that takes vectors as its both key and value to keep track of the nodes
vector<vector<int> > goal(3,vector<int> (3)); 

bool visit(vector<vector<int> > a)  //boolean to see if node is visited
{
	if(visited[a]==true)
		return true;
	
	return false;
}


//Manhattan or A*(A-star) search to find the distance 
int manhattan (vector<vector<int> > a , int moves)
{
	int dist = moves;
	for (int i=0; i<3; i++) //for loop to go through each row and column (like matrices). [00,01,02,10,11,12,20,21,22] We'll be using this i,j loop more.
	{
		for (int j=0; j<3; j++)
		{
			if(a[i][j] != 0)
			{
				for (int k=0; k<3; k++)
				{
					for (int l=0; l<3; l++)
					{
						if(a[i][j]==goal[k][l])
							dist+=abs(i-k)+abs(j-l); //absolute value since it may be negative
					}
				}
			}
		}
	}
	return dist;	
}

bool isGoal (vector<vector<int> > a){  //boolean to see if we've reached our goal state
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(a[i][j] != goal[i][j]) return 0; //if our puzzle tiles aren't same with the goal position. For eg. we want a[0][0] = 1, a[0][1] = 2, a[2][2] = 0, etc.
			
		}
	}
	
	return 1;	
}

bool safe(int i,int j) //boolean safe to see if grid is 3x3
{
	if(i>=0 && i<=2 && j>=0 && j<=2)
		return true;
	
	return false;
}


int dx[]={-1,1,0,0}; //array named "dx", with 4 length
int dy[]={0,0,1,-1};

vector<vector<vector<int> > > neighbours(vector<vector<int> > a) 
{
	pair<int,int> pos; //vector of pairs named "pos" (pairs an integer to another integer)
	for (int i=0; i<3; i++)
	{
		for (int j=0; j<3; j++){
			if(a[i][j] == 0) 
			{
				pos.first=i;
				pos.second=j;
				break;
			 } 												
		}		
		
	}
	
	vector<vector<vector<int> > > ans; //"answer" vector to add the correct values by pushing back
	for (int k=0; k<4; k++) // 4, not 3, since our dx and dy arrays have 4 length
	{
		int cx = pos.first; //to keep track of the "i" values
		int cy = pos.second; //to keep track of the "j" values
		vector<vector<int> > n = a;
		if(safe(cx+dx[k], cy+dy[k]))
		{
			swap(n[cx+dx[k]][cy+dy[k]], n[cx][cy]); //swap tiles(or we can say swap arrays)
			ans.push_back(n);			
		}
	}
		
	return ans; //result vector
		
}

typedef pair<vector<vector<int> > , int> state; // new type defined named "state" that's a vector of pairs (which is a vector to integer pair)
	
struct cmp 
{
	bool operator() (state &a, state &b) // overloading the unary operator "()"
	{
		int am = manhattan(a.first,a.second);
		int bm = manhattan(b.first,b.second);
		return am<bm;		
	}	
};

void print_path(vector<vector<int> > s)
{
	if(parent.count(s)) //to see if our vector s is present in our map named "parent" which takes vectors in it for both key and value, and if it is present
	print_path(parent[s]); //then print the path
	
    for(int i=0;i<3;i++)
    {
 	  for(int j=0;j<3;j++)
	  {
		 printf("%d ",s[i][j]);
	  }
	 cout<<endl;
    }
   cout<<endl;
   
 return;
}

void print(vector<vector<int> > s)
{
	for(int i=0;i<3;i++)
   {
	 for(int j=0;j<3;j++)
	 {
		printf("%d ",s[i][j]);
	 }
	cout<<endl;
   }
}


void solve(vector<vector<int> > a, int moves)
{
	
	priority_queue<state, vector<state>, cmp> Q; //Priority queue named "Q". 
	Q.push(state(a,moves));
	while(!Q.empty())
	{
		vector<vector<int> > s = Q.top().first;
		Q.pop();
		visited[s]=true;
		if(s==goal) //print(s)
		{
			print_path(s);
			break;
		}
		vector<vector<vector<int> > > ns = neighbours(s);
		vector<vector<vector<int> > >::iterator it;
		for(it=ns.begin();it!=ns.end();it++)
		{
			vector<vector<int> > temp = *it;
			if(!visit(temp))
			{
				parent.insert(pair<vector<vector<int> > , vector<vector<int> > >(temp,s));
				Q.push(state(temp,moves+1));
			}
		}
	}
	return;
}

int main()
{

  string line;
  ifstream myFile("prog1_input.txt");
  if (myFile.is_open())
  {
    while ( getline( myFile, line))
    {
     // cout << line << '\n';d
    }
    myFile.close();
  }


	cout<<"Please enter your 8 Puzzle as a string! \n";
	cout<<"\nFor example => 0 1 3 4 2 5 7 8 6\n";
	vector<vector<int> > a(3,vector<int> (3));	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>a[i][j];	
		}
	}
	cout<<"\nPlease wait while the puzzle is solving...\n";
	goal[0][0] = 1;
	goal[0][1] = 2;
	goal[0][2] = 3;
	goal[1][0] = 4;
	goal[1][1] = 5;
	goal[1][2] = 6;
	goal[2][0] = 7;
	goal[2][1] = 8;
	goal[2][2] = 0;
	solve(a,0);

	ofstream outFile;
	outFile.open("prog1_output.txt");

}

