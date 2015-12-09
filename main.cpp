
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

struct Node
{
	int x,y;
	int f;
	int g;
	int h;
	int pass;
	bool isPath;
	Node* parent;
	Node(int x=0, int y=0):x(x), y(y),f(0),g(0),h(0), parent(NULL),pass(1),isPath(false){};
	
};
bool CmpF (Node* n1, Node* n2)
{
	return n1->f < n2->f;
}

class Solution {
public:
	vector<Node*> OPEN;
	vector<Node*> CLOSE;
	const static int SIZE=6;
	int m_end[2];
	int Dist(int sX, int sY)
	{
		return abs(m_end[0] - sX) + abs(m_end[1] - sY);
	}
	vector<Node*> getChild(const vector<Node*>& NodeMap, const Node* node)
	{
		vector<pair<int,int>> dir;
		dir.push_back(pair<int,int>(1,0));
		dir.push_back(pair<int,int>(1,1));
		dir.push_back(pair<int,int>(1,-1));
		dir.push_back(pair<int,int>(0,1));
		dir.push_back(pair<int,int>(0,-1));
		dir.push_back(pair<int,int>(-1,0));
		dir.push_back(pair<int,int>(-1,1));
		dir.push_back(pair<int,int>(-1,-1));
		vector<Node*> v;
		int x;
		int y;
		
		for(int i=0; i<dir.size(); ++i)
		{
			x = node->x + dir[i].first;
			y = node->y + dir[i].second;
			if ( (x>=0 && x<SIZE) && (y>=0 && y<SIZE) && (NodeMap[x*SIZE+y]->pass!=0) )
			{
				v.push_back(NodeMap[x*SIZE+y]);
			}
		}
		return v;
	}
	void SetPass(int x, int y, bool bPass, vector<Node*>& NodeMap)
	{
		NodeMap[x*SIZE+y]->pass = 0;
	}
	void Astar(int sX, int sY, int eX, int eY)
	{
		m_end[0] = eX;
		m_end[1] = eY;
		vector<Node*> NodeMap(SIZE*SIZE);
		for(int i=0; i<NodeMap.size(); ++i)
		{
			NodeMap[i] = new Node();
			NodeMap[i]->x = i/SIZE;
			NodeMap[i]->y = i%SIZE;
		}
		SetPass(1,0,false, NodeMap);
		OPEN.push_back(NodeMap[sX*SIZE + sY]);
		while(!OPEN.empty())		
		{
			Node* cur = OPEN[0];
			if(cur->x == eX && cur->y == eY)
				break;
			CLOSE.push_back(cur);
			OPEN.erase(OPEN.begin());			
			vector<Node*> v = getChild(NodeMap, cur);
			for(auto x : v)
			{
				int h = Dist(x->x, x->y);
				int g = cur->g + 1;
				int f = h + g;
				if(std::find(OPEN.begin(), OPEN.end(), x) != OPEN.end())
				{
					if(f < x->f)
					{
						x->h = h;
						x->g = g;
						x->f = f;
						x->parent = cur;
					}
				}
				else if(std::find(CLOSE.begin(), CLOSE.end(), x) != CLOSE.end())
					continue;
				else
				{
					x->h = h;
					x->g = g;
					x->f = f;
					x->parent = cur;
					OPEN.push_back(x);
				}
			}
			std::sort(OPEN.begin(), OPEN.end(), CmpF);
		}
		int m[SIZE][SIZE];
		Node* n = NodeMap[eX*SIZE+eY];
		while(n)
		{
			n->isPath = true;
			n = n->parent;
		}
		for(auto n : NodeMap)
		{
			if(n->isPath)
			{
				cout<<"o";
			}
			else if(!n->pass)
			{
				cout<<"X";
			}
			else
				cout<<" ";
			if(n->y == SIZE-1)
				cout<<endl;
		}
	}
};
int main()
{
	//vector<TreeNode*> v;
	//v.push_back(new TreeNode(1));
	//v.push_back(new TreeNode(2));
	//v.push_back(new TreeNode(3));
	//v.push_back(new TreeNode(4));
	//v.push_back(new TreeNode(5));
	//v[0]->left = v[1];
	//v[0]->right = v[2];
	//v[1]->right = v[4];

	//vector<string> v;
	//v.push_back("aaaccc");
	//v.push_back("");
	//v.push_back("aaddd");
	/*vector<ListNode*> v1;
	v1.push_back(new ListNode(5));

	
	
	for(int i=0; i<(int)v1.size()-1; ++i)
		v1[i]->next = v1[i+1];
	vector<ListNode*> v2;
	v2.push_back(new ListNode(1));
	v2.push_back(new ListNode(2));
	v2.push_back(new ListNode(4));
	for(int i=0; i<v2.size()-1; ++i)
		v2[i]->next = v2[i+1];*/
//	s.uniquePaths(2,3);
	Solution s;
	s.Astar(0,0, 1,5);
	system("pause");
	return 0;
}

