#include <iostream>
#include<vector>
#include<queue>
#include<functional>//用于greater
#include<algorithm>//用于 sort（内置是“<")
using namespace std;
typedef int Elemtype;
const int INF = 1e9;
//重点在于用path回溯
//Kruskal 用边
struct Edge
{ 
	int start;
	int end;
	int weight;
	bool operator<(const Edge& others) const
	{
		return weight < others.weight;
		}
};
//Kruskal辅助类
//用来快速判断两个点是否已经属于同一个集合，从而判断加边会不会成环。
class Unionfind
{
	vector<int> parent;
	vector<int> rank;
public:
	Unionfind(int n)
	{
		parent.resize(n);
		rank.resize(n, 0);
		for (int i = 0;i < n;i++) parent[i] = i;
	}
	int findroot(int elem)
	{
		if (parent[elem] != elem)
		{
			parent[elem] = findroot(parent[elem]);
		}
		return parent[elem];
	}
	bool Unit(int x, int y)
	{
		int rootx = findroot(x);
		int rooty = findroot(y);
		if (rootx == rooty) return false;//成环了
		if (rank[rootx] < rank[rooty])//小树接到大树上
		{
			parent[rootx] = rooty;
		}
		else if (rank[rootx] > rank[rooty])
		{
			parent[rooty] = rootx;
		}
		else {
			parent[rooty] = rootx;
			rank[rootx]++;
		}
		return true;
	}
};
class Graph
{
	Elemtype  vertexnum;
	vector<vector <int> > adjMatrix;//vector<元素类型, 分配器类型(可选)>  变量名;

public:
	Graph(Elemtype v) : vertexnum(v), adjMatrix(v, vector<int>(v, INF)) {
		for (int i = 0; i < vertexnum;i++)
		{
			adjMatrix[i][i] = 0;
		}
	}
	void addEdge(Elemtype i, Elemtype j, bool directed, int weight)
	{
		if (i < 0 || i >= vertexnum || j < 0 || j >= vertexnum) return;
		adjMatrix[i][j] = weight;
		if (directed == false) adjMatrix[j][i] = weight;
	}
	void  Print()
	{
		cout << "=========================================" << endl;
		cout << " ";
		for (int i = 0;i < vertexnum;i++)
		{
			for (int j = 0; j < vertexnum; j++)
			{
				cout << adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	//-------------------------------------------------知parent反向输出正确的所有路径--------------------------------------------------------------------------------------------------------------------------------------------
	void Path_pre(int cur, vector<vector<int>>& parent, vector<int>& path)
	{
		path.push_back(cur);
		if (parent[cur].empty())
		{
			for (int i = path.size() - 1; i >= 0; i--)
			{
				cout << path[i];
				if (i != 0)
				{
					cout << " -> ";
				}
			}
			cout << endl;
		}
		else
		{
			for (int pre : parent[cur])
			{
				Path_pre(pre, parent, path);
			}
		}
		path.pop_back();
	}//path 是先存，一直走到一条路的尽头，反向打印然后逐步删除，退回到分叉点，再走另一条路，再反向打印。---------------------------------------------------------------------------------------------------------------
	void Path_next(int thing, vector<vector<int>>& next, vector<int>& path)
	{
		path.push_back(thing);
		if (next[thing].empty())
		{
			for (int i =0;i<path.size();i++)
			{
				cout << path[i];
				if (i != path.size() - 1)
				{
					cout << "->";
				}
			}
			cout << endl;
		}
		else {
			for (int kid : next[thing])
			{
				Path_next(kid, next, path);
			}
		}
		path.pop_back();
	}
	void BFS(int start)//无权和有权
		//从一个点开始，一层一层往外扩散，用队列实现
	{
		if (start >= vertexnum) return;
		queue<Elemtype> q;
		q.push(start);
		vector<bool> visited(vertexnum, false);
		visited[start] = true;
		while (!q.empty())
		{
			Elemtype v = q.front();
			q.pop();
			cout << v << endl;
			for (int i = 0; i < vertexnum; i++)
			{
				if (i!=v&&adjMatrix[v][i] != INF && visited[i] == false)
				{
					visited[i] = true;
					q.push(i);
				}
			}
		}
		cout << endl;
		return;
	}
	void  DFS(int start)//无权和有权
		//从一个点开始，一条路走到底，走不动再回退，用递归或栈实现
	{
		if (start < 0 || start >= vertexnum) return;
		vector<bool> visited(vertexnum, false);
		cout << "DFS 的顺序为：" << endl;
		DFStuil(start, visited);
	}
	void DFStuil(int start, vector<bool>& visited)
	{
		visited[start] = true;
		cout << start << " ";
		for (int i = 0; i < vertexnum;i++)
		{
			if (i != start&&adjMatrix[start][i] != INF && visited[i] == false)
			{
				DFStuil(i, visited);
			}
		}
	}
	//-------------------------------------------------------------------------Prim-----------------------------------------------------------------------------------------------------------------------------------------
	//从一个点出发，每次选择“当前树连接外部点的最小边” 重点在于：minweight的比较
	void   Prim(Elemtype start)
	{
		if (start < 0 || start >= vertexnum) return;
		cout << "最小生成树的路径为：" << endl;
		vector<bool> visited(vertexnum, false);
		vector<int> minweight(vertexnum, INF);
		vector<int> parent(vertexnum, -1);
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		//pair 是 C++ 标准库（位于 <utility> 头文件）中定义的一个类模板。它的作用极其简单：将两个可能不同类型的值打包成一个整体
		//pair< frist ,second > 比较规则； 先比frist ,再比second 。返回 bool
		//priority_queue 默认是大顶堆，greater<T> 是一个预定义的函数对象（仿函数），它重载了 operator()，执行的操作是 a > b
		//priority_queue 的模板参数是 <数据类型, 底层容器, 比较器>
		minweight[start] = 0;
		int totalweight = 0;
		pq.push({ 0,start });
		cout << "Prim的最小生成树为:" << " ";
		while (!pq.empty())
		{
			auto [w, u] = pq.top();pq.pop();
			if (visited[u]) continue;//防止旧数据点 U 重新加入 树 
			visited[u] = true;
			totalweight += w;//先加入树再加
			if (parent[u] != -1) {
				cout << " 边" << parent[u] << " - " << u << "  权值 " << w << endl;
			}
			for (int i = 0;i < vertexnum;i++)
			{
				if (i != u && adjMatrix[u][i] != INF && visited[i] == false && adjMatrix[u][i] < minweight[i])
				{
					minweight[i] = adjMatrix[u][i];
					parent[i] = u;
					pq.push({ minweight[i], i });
				}
			}
		}
		cout << "总权重为：" << totalweight << endl;

	}
	// Prim重点在于广，考虑到许多情况
	//---------------------------------------------------------------------------------------------Kruskal---------------------------------------------------------------------------------------------------------------------
	//把所有边按权重排序，从小到大选，只要不成环就加入
	void Kruskal()
	{
		vector<Edge> edge;
		for (int i = 0;i < vertexnum;i++)
		{
			for (int j = i + 1;j < vertexnum;j++)
			{
				if (adjMatrix[i][j] != INF)
					edge.push_back({ i, j, adjMatrix[i][j] });//先将{i，j，adjMartix}打包成临时对象，ps：push_back只能加一个对象
			}
		}
		int totalWeight = 0;
		int edgeCount = 0; // 记录已选边数（n个顶点，MST有 n-1 条边）
		cout << "Kruskal 最小生成树边集：" << endl;
		sort(edge.begin(), edge.end());
		Unionfind uf(vertexnum);//别忘了创造类
		for (Edge e : edge)
		{
			if (uf.Unit(e.start, e.end))
			{
				cout << "边" << e.start << "-" << e.end << "权重：" << e.weight << " ";
				totalWeight += e.weight;
				edgeCount++;
			}
			if (edgeCount == vertexnum - 1)		 break;
		}
		cout << endl;
		if (edgeCount == vertexnum - 1) cout << "Kruskal的总权重为：" << totalWeight;
		else cout << "非连通图，找不到最小生成树";
	}
	//--------------------------------------------------------------------------------------------------------Dijkstra--------------------------------------------------------------------------------------------------------
	//与Prim类似，用pq来实现小栈堆。单源最短路径，核心是 dist[i] > dist[cur] + edge(cur,i)
	//在于贪心。O(E log V)
	void Dijkstra(int start,int v)
	{
		if (start < 0 || start >= vertexnum || v < 0 || v >= vertexnum) return;
		vector<int> parent(vertexnum, -1);	
		vector<int>d(vertexnum,INF);
		d[start] = 0;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		pq.push({ 0,start });
		while (!pq.empty())
		{
			auto [distance, cur] = pq.top();
			pq.pop();
			if (distance != d[cur]) continue;//一如既往，防污染
			for (int i = 0;i < vertexnum;i++)
			{
				if (i != cur && adjMatrix[cur][i] != INF && d[cur] != INF)
				{
					if (d[i] > d[cur] + adjMatrix[cur][i])//重点在于更新从出发点到cur的距离，实现贪心，进而追求最优解。
					{
						d[i] = d[cur] + adjMatrix[cur][i];
						parent[i] = cur;
						pq.push({ d[i], i });
					}
				}
			}
		}
		if (d[v] == INF)
		{
			cout << start << " 到 " << v << " 不可达" << endl;
			return;
		}
		cout << "点v : Dijkstra的最短距离" << d[v]<<endl;
		cout << "路径为：" << endl;
		vector<int> path;
		int cur = v;
		while (cur != -1)
		{
			path.push_back(cur);
			if (cur == start) break;
			cur = parent[cur];
		}
		reverse(path.begin(), path.end());

		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i];
			if (i != path.size() - 1) cout << " -> ";
		}
		cout << endl;
	}
	//-------------------------------------------------------------------------------------------Floyd-------------------------------------------------------------------------------------------------------
	//Floyd.Floyd：多源最短路径，核心是 dist[i][j] > dist[i][k] + dist[k][j],注意next的更新
	//动态规划。O(n³)
	void Floyd(int v1 ,int v2,vector<vector<int>> &dist, vector<vector<int>>& next)
	{
		if (v1 >=vertexnum|| v1<0)
		{
			cout << "起点不合规" << endl;
			return;
		}	
		if (v2 >= vertexnum || v2 < 0)
		{
			cout << "终点不合规" << endl;
			return;
		}
		dist.assign(vertexnum, vector<int>(vertexnum, INF));
		next.assign(vertexnum, vector<int>(vertexnum, -1));
		for (int i = 0;i < vertexnum;i++)
		{
			for (int j = 0;j < vertexnum;j++)
			{
				dist[i][j] = adjMatrix[i][j];
				// 初始化 next：若 i->j 直接可达（且不是自身），则 next[i][j] = j
				if (i != j && adjMatrix[i][j] != INF) {
					next[i][j] = j;
				}
			}
		}
		for (int k = 0; k < vertexnum; k++)
		{
			for (int i = 0; i < vertexnum; i++)
			{
				for (int j = 0; j < vertexnum; j++)
				{
					if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
						next[i][j] = next[i][k];
		//举例：(1->4) >(1->2->3->4), 则next[1][4]=2=next[1][2]
					}		
				}
			}
		 }
	}
	void Floydshow(int v1, int v2)
	{
		vector<vector<int>> dist;
		vector<vector<int>> next;
		Floyd(v1, v2, dist, next);
		if (dist[v1][v2] == INF)
		{
			cout << " 到不了" << endl;
			return;
		}
		cout << "点；" << v1 << "->" << v2 << "的最短路径为" << dist[v1][v2] << endl;
		cout << "路径为:";
		int cur = v1;
		cout << cur;
		while (cur != v2)//没走到
		{
			cur = next[cur][v2];
			cout << " -> " << cur;
		}
		cout << endl;
	}
// -----------------------------------------------------------------------------------拓扑排序---------------------------------------------------------------------------------------------------------------------------
//用入度来表示前置事件的个数，个数为零就可以开始了
	void TopologicalSort()
	{
		vector<int> indegree(vertexnum,0);//入度
		vector<vector<int>> dist(vertexnum, vector<int>(vertexnum, INF));
		queue<int> q;	
		for (int i = 0;i < vertexnum;i++)
		{
			for (int j = 0;j < vertexnum;j++)
			{
				if (adjMatrix[j][i] != INF)
				{
					indegree[i]++;
				}
			}
		}
		for (int i = 0; i < vertexnum; i++)
		{
			if (indegree[i] == 0)
			{
				q.push(i);
			}
		}
		vector<int> result;
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();
			for (int i = 0;i < vertexnum;i++)
			{
				if (i != cur && adjMatrix[cur][i] != INF)
				{
					indegree[i]--;
					result.push_back(cur);
					if (indegree[i] == 0)
					{
						q.push(i);
					}
				}
			}
		}
		if (result.size() != vertexnum)
		{
			cout << "该有向图存在环，不能进行拓扑排序" << endl;
			return;
		}
		for (int i = 0; i < result.size();i++)
		{
			cout << result[i] << " ";
		}
		cout << endl;
	}
//—————————————————————————————————————————————————————————————AOE————————————————————————————————————————————————
//AOE图
//先拓扑
//再写ve（从前往后，更新parent）
//逆向输出topo来 完成vl（从后往前，更新next)
	void AOE(int thing)
	{
		vector<int>indegree(vertexnum, 0);
		for (int i = 0;i < vertexnum;i++)
		{
			for (int j = 0;j < vertexnum; j++)
			{
				if (i != j && adjMatrix[i][j] != INF)
				{
					indegree[j]++;
				}
			}
		}
		queue<int> q;
		for (int i = 0;i < vertexnum;i++)
		{
			if (indegree[i] == 0)
			{
				q.push(i);
			}
		}
		vector<int> ve(vertexnum, 0);
		vector<int> topo;
		vector<vector<int>> parent(vertexnum);
		int count = 0;
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();
			count++;
			topo.push_back(cur);
			for (int i = 0;i < vertexnum;i++)
			{
				if (adjMatrix[cur][i] != INF && cur != i)
				{
			
					indegree[i]--;
					if (ve[i]<ve[cur]+adjMatrix[cur][i])
					{
						ve[i] = ve[cur] + adjMatrix[cur][i];
						parent[i].clear();
						parent[i].push_back(cur);
					}
					else if (ve[i] == ve[cur] + adjMatrix[cur][i])
					{
						parent[i].push_back(cur);
					}
					if (indegree[i] == 0)
					{
						q.push(i);
					}//出错一次，有时候会看叉括号，记得检查 入队条件，eg：应该在入度--里面检查，防止一个零入度的点重复添加
				}
			}
		}
		if (count < vertexnum)
		{
			cout << "失败，原因：AOE网成环" << endl;
			return;
		}
		vector<int> vepath;
		cout << "事件：" << thing << "最早发生的时间" << ve[thing] << endl;
		cout << "ve的路线为" << endl;
		Path_pre(thing, parent, vepath);
		int projectTime = 0;
		for (int i = 0; i < vertexnum; i++)
		{
			projectTime = max(projectTime, ve[i]);
		}//找到最大的工作时间

		vector<int> vl(vertexnum, projectTime);
		vector<vector<int>> next(vertexnum);
		for (int k = topo.size() - 1; k >= 0; k--)
		{
			int cur = topo[k];//出错一次，注意角标和具体值的区别
			for (int i = 0; i < vertexnum; i++)
			{
				if (cur != i && adjMatrix[cur][i] != INF)
				{
					int newLateTime = vl[i] - adjMatrix[cur][i];
					if (vl[cur] > newLateTime)
					{
						vl[cur] = newLateTime;
						next[cur].clear();
						next[cur].push_back(i);
					}
					else if (vl[cur] == newLateTime)
					{
						next[cur].push_back(i);
					}
				}
			}
		}
		cout << "事件：" << thing << "的最晚发生时间(vl)为：" << vl[thing] << endl; 
		vector<int> vlpath;
		cout << "到汇点的路线" << endl;
		Path_next(thing, next, vlpath);
	}
};
int main()
{
	Graph g(6);
	g.addEdge(0, 1, false, 6);
	g.addEdge(0, 2, false, 1);
	g.addEdge(0, 3, false, 5);
	g.addEdge(1, 2, false, 5);
	g.addEdge(1, 4, false, 3);
	g.addEdge(2, 3, false, 5);
	g.addEdge(2, 4, false, 6);
	g.addEdge(2, 5, false, 4);
	g.addEdge(3, 5, false, 2);
	g.addEdge(4, 5, false, 6);
	g.Prim(0);
	g.Kruskal();
	g.Dijkstra(0, 5);
	g.Dijkstra(0, 6);//检查是否考虑到了错误
	for (int i = 0;i < 6;i++)
	{
		for (int j = 0;j < 6;j++)
		{
			g.Floydshow(i, j);
		}
	}
	//有向：
	Graph to(6);
	to.addEdge(0, 1, true, 6);
	to.addEdge(0, 2, true, 1);
	to.addEdge(0, 3, true, 5);
	to.addEdge(1, 4, true, 3);
	to.addEdge(2, 4, true, 6);
	to.addEdge(3, 5, true, 2);
	to.addEdge(4, 5, true, 6);
	to.AOE(5);//看ve;
	to.AOE(0);//看vl
}
//| 算法       | 解决什么       | 核心结构             | 关键判断             |
//| --------   | ---------- | ---------------- | ---------------- |
//| BFS        | 层次遍历 / 无权最短路 | queue + visited | 未访问就入队           |
//| DFS        | 深度遍历 | 递归 / 栈 + visited | 未访问就递归           |
//| Prim       | 最小生成树 | minweight + pq | 比较边权             |
//| Kruskal    | 最小生成树 | 边集排序 + 并查集 | 不成环就选            |
//| Dijkstra   | 单源最短路径 | dist + pq | dist[cur] + edge |
//| Floyd      | 多源最短路径 | dist二维数组 | 经过k是否更短  k,i,j,其中k为中转点        |
//| 拓扑排序   | 有向无环图排序 | indegree + queue | 入度为0 |
//|AOE(ve)     |有向无环图排序 | ve[],parent[]   正向思维  |   ve[i] =max{ve[i],ve[j]+adjMartex[j][i]} 以此来更新ve[] 和 parent[]
// |AOE(vl)    |有向无环图排序|  vl[] ,next[] ,逆拓扑     |   vl[i] =  min{ vl[i], vl[j]- adjMartex[i][j]  
