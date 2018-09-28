#include <iostream>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<graphics.h>
#include <stdlib.h>
int rypd;//rypd为冗余判断
int dushu[10000];
using namespace std;
template<class T>

class SLNode
{
public:
    T data;//数据域
    SLNode<T>* next;//指针域
    SLNode(SLNode* nextNode=NULL)//无数据域构造函数
    {
        next=nextNode;
    }
    SLNode(const T& item,SLNode* nextNode=NULL)//有数据域构造函数
    {
        data=item;
        next=nextNode;
    }
	T *left,*right;
	T *root;
};

template<class T>
class LQueue
{
private:
    SLNode<T>* Front;//指向队首的指针
    SLNode<T>* Rear;//指向队尾的指针
public:
    LQueue()
    {
        Front=Rear=NULL;   //构造函数
    }
    ~LQueue()
    {
        QClear();   //析构函数
    }
    void QInsert(const T& item);//队尾添加元素
    bool QDelete(T& item);//删除队首元素
    bool QFront(T& item)const;//存取队首元素
    bool IsEmpty() const
    {
        return Front==NULL;
    }
    void QClear();//清空队列
};


template<class T>
void LQueue<T>::QInsert(const T& item)
{
    if(IsEmpty())
    {
        Front=Rear=new SLNode<T>(item,NULL);//若为空则创建新节点并将首尾指针指向该新节点
    }
    else
    {
        Rear->next=new SLNode<T>(item,NULL);//若不为空则更新队尾指针
        Rear=Rear->next;
    }
}

template<class T>
bool LQueue<T>::QDelete(T& item)
{
    if(IsEmpty())//若为空则无法出列
    {
        cout<<"队列为空无法出队！"<<endl;
        return false;
    }
    SLNode<T>* temp=Front;//若不为空则将队首指针更新
    item=temp->data;
    Front=Front->next;
    delete temp;
    if(IsEmpty())//若删除队首后队列为空则将队尾指针置空
    {
        Rear=NULL;
    }
    return true;
}

template<class T>
bool LQueue<T>::QFront(T& item) const
{
    if(IsEmpty())//若队列为空则无法读取
    {
        cout<<"队列为空无法读取！"<<endl;
        return false;
    }
    item=Front->data;
    return true;
}
template<class T>
void LQueue<T>::QClear()
{
    while(!IsEmpty())//若不为空则从队首开始删除结点
    {
        Rear=Front;
        Front=Front->next;
        delete Rear;
    }
    Rear=NULL;
}


const int MaxGraphSize = 256;
const int MaxWeight = 1000;

/*边结点的结构体*/
struct Edge
{
    friend class Graph_List;
    int VerAdj;//邻接顶点序号，从0开始编号
    Edge *link;//指向下一个边结点的指针
};
/*顶点表中的结构体*/
struct Vertex
{
    friend class Graph_List;
    int VerName;//顶点的名称
	int du;
    Edge *adjacent;//边链表的头指针
};
/*采用邻接表存储的Graph_List类定义*/
class Graph_List
{
private:
    Vertex *Head;//顶点表头指针
    int graphsize;//图中当前顶点个数
public:
    Graph_List() {};
    virtual ~Graph_List();
    void Create();
    int GraphEmpty() const
    {
        return graphsize == 0;
    };//检测图是否为空
    void InsertEdge(const int &v1,const int &v2);//向图中插入一条边
	void InsertEdge2(const int &v1,const int &v2);
    int GetFirstNeighbor(const int v);//查找图中某顶点的第一个邻接顶点
    int GetNextNeighbor(const int v1,const int v2);//查找图中某顶点的第一个邻接顶点
    void DepthFisrtSearch(int v1,int v2);//图的深度优先遍历
	void bianli(const int v,int &i);
    void RDFS(int v,int *visited);
	void RDFS(const int v,int *visited,int &v2);//3变量重载
	void RDFS2(int v1,int *visited,int v2);//用于第一题的判断
	void deleteit(const int &v1,const int &v2);
	void deletepoint(const int &v1,const int &v2);//第三题的函数
	void jiaohuanji();
	int Isconect();
	int Isconect2();
	int Isconect3(const int v);

	void dierti(int e,int b[],int kekao[],int kekaopoint);
	void disanti(int graphsize,int sum[],int sumpoint);
	void huatu(int graphsize,int e,int aa[],int aapoint,int b[]);
	void wenjian(int sum[],int sumpoint,int kekao[],int kekaopoint);
};


	

void Graph_List::Create()//创建
{
	int a[10000];//随机生成的数
	int aa[10000];//创建成功的点，为第一题的最小支撑树
	int aapoint=0;
	int	b[10000];//储存网络个数,b[100]为第二题数组
	int kekao[10000];//可靠网络保存
	int kekaopoint=0;
	int sum[10000];//冗余项保存
	int sumpoint=0;//冗余项保存
	for(int j=0;j<10000;j++){
		b[j]=0;
		dushu[j]=0;
		sum[j]=0;
		aa[j]=0;
		kekao[j]=0;
	}
    int e,from,to;
    Head = new Vertex[MaxGraphSize+1];
    cout<<"请输入城市的个数: ";
    cin>>graphsize;
    for(int i=1; i<=graphsize; i++)
    {
        Head[i].VerName = i;
        Head[i].adjacent = NULL;
		Head[i].du=0;
    }
	Head[0].VerName= NULL;
	Head[0].adjacent=NULL;
	Head[0].du=0;
    cout<<"输入要随机生成的城市通讯网络的个数:";
    cin>>e;


	//随机数部分
    srand((unsigned)time(NULL)); 

    for (i=0; i<(e*2); i+=2)         
    {  
        a[i]=1 + (int)graphsize * rand() / (RAND_MAX + 1);
		a[i+1]=1 + (int)graphsize * rand() / (RAND_MAX + 1);
		cout<<"("<<a[i]<<","<<a[i+1]<<")  ";
		b[i]=a[i];  b[i+1]=a[i+1];
    }
	cout<<endl;
	//随机数部分

	                          /****************************第一题************************************/
    for(i=0; i<(e*2); i+=2)
    {
		from=a[i];
		to=a[i+1];
		rypd=0;
		if(from==to){
			cout<<"第"<<from<<"与第"<<to<<"个城市网络相同!无法构成通讯网络."<<endl;
			continue;
		}
		DepthFisrtSearch(from,to);
		if(rypd==1){
			cout<<from<<"与"<<to<<"冗余了!"<<endl;

			sum[sumpoint]=a[i];//记录冗余的边
			sum[sumpoint+1]=a[i+1];
			sumpoint+=2;
			continue;//有冗余边的暂时先删除
		}
		aa[aapoint]=a[i];//aa数组记录的是最小支撑树
		aa[aapoint+1]=a[i+1];
		aapoint+=2;
        InsertEdge(from,to);
		InsertEdge(to,from);
	}for(i=0;i<sumpoint;i+=2){//将冗余边加上，便于第二问的判断
		InsertEdge(sum[i],sum[i+1]);
		InsertEdge(sum[i+1],sum[i]);
	}
	cout<<"第一题剩余的边为:"<<endl;
	for(i=0;i<aapoint;i+=2)
		cout<<"("<<aa[i]<<","<<aa[i+1]<<") ";
	
	//第一遍创建
	                          /****************************第一题************************************/


	for(i=0;i<(e*2);i+=2){
		if(b[i]==b[i+1]){
			b[i]=0;
			b[i+1]=0;
			continue;
		}
			for(j=0;j<i;j+=2){
				if(b[i]==b[j])
					if(b[i+1]==b[j+1]){
					b[i]=0;
					b[i+1]=0;
				}
			}
			for(j=0;j<i;j+=2){
			 if(b[i]==b[j+1])
				if(b[i+1]==b[j]){
					b[i+1]=0;
					b[i]=0;
			}
			}
	}

	cout<<endl<<"城市的初始连通状态为:";
	i=Isconect();
	int nn;
	if(i==1){//网络不连通
		do{
		cout<<"随机生成的网络不连通!";
		cout<<"请输入操作: 1.查看图形  2.重新生成网络  "<<endl;
		cin>>nn;
		switch(nn){
		case 1:
			huatu(graphsize,e,aa,aapoint,b);
			break;
		case 2:
			Create();
		}
		}while(nn==1||nn==2);
	}
	else {//网络连通
		cout<<"连通"<<endl;
		do{
			cout<<"请输入操作: 1.检测网络的可靠性并将其保存到文件  2.将冗余边保存到文件  "<<endl;
			cout<<"            3.检测城市的交换机状况  4.查看图形  5.重新生成网络  "<<endl;
			cin>>nn;
			switch(nn){
			case 1:/****************************第二题************************************/
				dierti(e,b,kekao,kekaopoint);
				break;
			case 2:/***********将其存储**************/
				wenjian(sum,sumpoint,kekao,kekaopoint);
				cout<<"保存完毕!"<<endl;
				break;
			case 3:/****************************第三题************************************/
				disanti(graphsize,sum,sumpoint);
				break;
			case 4:/******************************画图************************************/
				huatu(graphsize,e,aa,aapoint,b);
				break;
			case 5:
				Create();
			}
		}while(nn == 1 || nn == 2 || nn == 3 || nn == 4||nn==5);
	}
}


Graph_List::~Graph_List()
{
    for(int i = 0; i<graphsize; i++)
    {
        Edge *p = Head[i].adjacent;
        while(p!=NULL)
        {
            Head[i].adjacent = p->link;
            delete p;
            p = Head[i].adjacent;
        }
    }
    delete[] Head;
}
void Graph_List::dierti(int e,int b[],int kekao[],int kekaopoint){
	cout<<"依次判断每两个城市的网络是否为可靠网络"<<endl<<endl;
	for(int i=0;i<(e*2);i+=2){
		if(b[i]==b[i+1])
			continue;
		deleteit(b[i],b[i+1]);
		deleteit(b[i+1],b[i]);
		cout<<"检测"<<b[i]<<"与"<<b[i+1];
		int kk=Isconect2();
		if(kk==0){
			kekao[kekaopoint]=b[i];
			kekao[kekaopoint+1]=b[i+1];
			kekaopoint+=2;
		}
		cout<<endl;
		InsertEdge2(b[i],b[i+1]);
		InsertEdge2(b[i+1],b[i]);
	}
	FILE *fp;
	fp=fopen("wenjian.txt","w");
	fprintf(fp,"可靠网络为:");
	fprintf(fp,"\n");
	for(i=0;i<kekaopoint;i+=2)
		fprintf(fp,"(%d,%d)\n",kekao[i],kekao[i+1]);
	fclose(fp);
}
void Graph_List::disanti(int graphsize,int sum[],int sumpoint){
	cout<<"请输入要检测哪一问的交换机情况:"<<endl;
	int shuru;
	cin>>shuru;
	if(shuru==1){
		for(int i=0;i<sumpoint;i+=2){
		deleteit(sum[i],sum[i+1]);
		deleteit(sum[i+1],sum[i]);
		}
	cout<<"需要配交换机的城市为:";
	for(i=0;i<graphsize;i++)
	{
		if(Head[i].du>1)
			cout<<Head[i].VerName<<" ";
	}
	for(i=0;i<sumpoint;i+=2){
		InsertEdge2(sum[i],sum[i+1]);
		InsertEdge2(sum[i+1],sum[i]);
		}
	cout<<endl;
	}
	else if(shuru==2)
		jiaohuanji();
	else cout<<"不要搞事情"<<endl;
}
void Graph_List::huatu(int graphsize,int e,int aa[],int aapoint,int b[]){
	cout<<"要显示哪一题的图形?(仅限1和2):";
		int dian1,dian2,bian1,bian2,bian3,bian4;
		int shuru2;
	cin>>shuru2;
	if(shuru2==1){//第一题图形
		initgraph(800,800);
		for(int i=0;i<(2*e);i++){
			dian1=400-250*cos((double)(2*3.14/graphsize)*i);
			dian2=400+250*sin((double)(2*3.14/graphsize)*i);
			solidcircle(dian1,dian2,2);
		}
		for(i=0;i<aapoint;i+=2){
			setcolor(GREEN);
			bian1=400-250*cos((double)(2*3.14/graphsize)*aa[i]);
			bian2=400+250*sin((double)(2*3.14/graphsize)*aa[i]);
			bian3=400-250*cos((double)(2*3.14/graphsize)*aa[i+1]);
			bian4=400+250*sin((double)(2*3.14/graphsize)*aa[i+1]);
			line(bian1,bian2,bian3,bian4);
		}
		getchar();getchar();
		closegraph();
	}
	else if(shuru2==2){//第二题图形
		initgraph(800,800);
		for(int i=0;i<(2*e);i++){
			dian1=400-250*cos((double)(2*3.14/graphsize)*i);
			dian2=400+250*sin((double)(2*3.14/graphsize)*i);
			solidcircle(dian1,dian2,2);
		}
		for(i=0;i<(2*e);i+=2){
			setcolor(GREEN);
			bian1=400-250*cos((double)(2*3.14/graphsize)*b[i]);
			bian2=400+250*sin((double)(2*3.14/graphsize)*b[i]);
			bian3=400-250*cos((double)(2*3.14/graphsize)*b[i+1]);
			bian4=400+250*sin((double)(2*3.14/graphsize)*b[i+1]);
			line(bian1,bian2,bian3,bian4);
		}
		getchar();getchar();
		closegraph();
	}
}
void Graph_List::wenjian(int sum[],int sumpoint,int kekao[],int kekaopoint){
	FILE *fp;
	fp=fopen("wenjian.txt","w");
	fprintf(fp,"冗余线路为:");
	fprintf(fp,"\n");
	for(int i=0;i<sumpoint;i+=2)
		fprintf(fp,"(%d,%d)\n",sum[i],sum[i+1]);
	fclose(fp);
}

int Graph_List::GetFirstNeighbor(const int v)//找第一个邻接顶点
{
    if(v == -1) return -1;
    Edge *p = Head[v].adjacent;
    if(p!=NULL) return p->VerAdj;
    else return -1;
}
int Graph_List::GetNextNeighbor(const int v1,const int v2)//找邻结点
{
    if(v1!=-1&&v2!=-1)
    {
        Edge *p = Head[v1].adjacent;
        while(p->VerAdj!=v2&&p!=NULL) p=p->link;
        if(p==NULL) return -1;
        p = p->link;
        if(p==NULL) return -1;
        return p->VerAdj;
    }
    return -1;
}
void Graph_List::RDFS(int v,int *visited)//从起点v开始深度优先遍历
{
    visited[v] = 1;
    int w = GetFirstNeighbor(v);
    while(w!=-1)
    {
        if(!visited[w]) RDFS(w,visited);
        w = GetNextNeighbor(v,w);
    }
}
void Graph_List::RDFS(const int v1,int *visited,int &v2)//从起点v开始深度优先遍历
{
	v2++;
    visited[v1] = 1;
     int w = GetFirstNeighbor(v1);
    while(w!=-1)
    {
        if(!visited[w]) RDFS(w,visited,v2);
        w = GetNextNeighbor(v1,w);
    }
}
void Graph_List::RDFS2(int v1,int *visited,int v2)//从起点v开始深度优先遍历
{
    visited[v1] = 1;
     int w = GetFirstNeighbor(v1);
    while(w!=-1)
    {
        if(!visited[w]) RDFS(w,visited);
        w = GetNextNeighbor(v1,w);
    }
}
void Graph_List::DepthFisrtSearch(int v1,int v2)//从序号v开始深度遍历
{
    int *visited = new int[graphsize+1];
    for(int k = 0; k<=graphsize; k++) visited[k] = 0;
    RDFS2(v1,visited,v2);
	if(visited[v2]==1)
		rypd=1;
    delete [] visited;
}
void Graph_List::bianli(const int v,int &i){
    int *visited = new int[graphsize+1];
    for(int k = 0; k<=graphsize; k++) visited[k] = 0;
    RDFS(v,visited,i);
    delete [] visited;
}

int Graph_List::Isconect()   //不带cout的测试
  {   
    int   i,x=0;   
    int   n=graphsize;   
    int*   visited=new int[graphsize];  
    for(i=1;i<=n;i++) visited[i]=0;

    for(i=1;i<=n;i++)  
		if(visited[i]==0)   {   
    RDFS(i,visited);   
    x++;   
    }
    if(x>1)   
	return   1;
    else    
    return   0;
	delete []visited;
  }


int Graph_List::Isconect2(){  //带cout的测试
	int   i,x=0;   
    int   n=graphsize;   
    int*   visited=new int[graphsize];  
    for(i=1;i<=n;i++) visited[i]=0;

    for(i=1;i<=n;i++)  
		if(visited[i]==0)   {   
    RDFS(i,visited);  
    x++;   
    }
    if(x>1)   
    {
	cout<<"城市网络不连通，为非可靠网络"<<endl;
	return   1;
	}   
    else   
    cout<<"城市网络连通，为可靠网络"<<endl;   
    return   0;
	delete []visited;
  }
int Graph_List::Isconect3(const int v)   //不带cout的测试
  {   
    int   i,x=0;   
    int   n=graphsize;   
    int*   visited=new int[graphsize];  
    for(i=1;i<n;i++) visited[i]=0;

    for(i=1;i<n;i++)  
		if(visited[i]==0&&i!=v)   {   
    RDFS(i,visited);   
    x++;   
    }
    if(x>1)   
	return   1;
    else    
    return   0;
	delete []visited;
  }


void Graph_List::InsertEdge(const int &v1,const int &v2)//第一遍插入的函数
{
    if(v1!=-1&&v2!=-1)
    {
        Edge *p = Head[v1].adjacent;
        Edge *q = p;
        if(p==NULL)
        {
            Head[v1].adjacent = new Edge;
            Head[v1].adjacent->link = NULL;
            Head[v1].adjacent->VerAdj = v2;
			Head[v1].du++;
            return;

        }
	
        while(q!=NULL)
        {
            if(q->VerAdj==v2)
				return;
            q = q->link;
        }
        while(p->link!=NULL)
        {
            p = p->link;
        }
        p->link = new Edge;
        (p->link)->link = NULL;
        (p->link)->VerAdj = v2;
		Head[v1].du++;
    }
    else
    {
        return;
    }
}

void Graph_List::InsertEdge2(const int &v1,const int &v2)//第二遍创建的函数
{
    if(v1!=-1&&v2!=-1)
    {
        Edge *p = Head[v1].adjacent;
        Edge *q = p;
        if(p==NULL)
        {
            Head[v1].adjacent = new Edge;
            Head[v1].adjacent->link = NULL;
            Head[v1].adjacent->VerAdj = v2;
            return;
        }
	
        while(q!=NULL)
        {
            if(q->VerAdj==v2)
				return;
            q = q->link;
        }
        while(p->link!=NULL)
        {
            p = p->link;
        }
        p->link = new Edge;
        (p->link)->link = NULL;
        (p->link)->VerAdj = v2;
    }
	return;
}



void Graph_List::deleteit(const int &v1,const int &v2){//正式删除
	Edge *q=NULL,*p = Head[v1].adjacent;
	if(p==NULL)
    {
        return;//边不存在
    }
    if(p->VerAdj==v2)
    {
        q = p->link;
        Head[v1].adjacent = q;
        delete p;//删除成功
		return;
    }
    if(p->link!=NULL)
    {
        while ((p->link->VerAdj != v2)&&(p->link != NULL))
        {
            p = p->link;
        }
        q = p->link;
        p->link = q->link;
        delete q;//删除成功
		return;
    }
}

void Graph_List::deletepoint(const int &v1,const int &v2){//第三题的删除函数
	Edge *q=NULL,*p = Head[v1].adjacent;
	if(p==NULL)
    {
        return;//边不存在
    }
    if(p->VerAdj==v2)
    {
        q = p->link;
        Head[v1].adjacent = q;
        delete p;
		Head[v1].du--;
		return;//删除成功
    }
    
	return;
}
void Graph_List::jiaohuanji(){
	int *R=new int[graphsize];
	int e=0;
	for(int i=1;i<=graphsize;i++)
	{
		int *dujihe=new int[Head[i].du];
		Edge *q=Head[i].adjacent;
		int m=0;
		while(q!=NULL)
		{
			dujihe[m]=q->VerAdj;
			q=q->link;
			m++;
		}
		for(int u=0;u<Head[i].du;u++)
		{
			deleteit(i,dujihe[u]);
			deleteit(dujihe[u],i);
		}
		int t=i+1;
		t=t%graphsize;
		int i_size=0;
		bianli(t,i_size);
		if(i_size<graphsize-1)
		{
			R[i]=i+1;
			e++;
		}
		for(int y=0;y<Head[i].du;y++)
		{
			InsertEdge2(i,dujihe[y]);
			InsertEdge2(dujihe[y],i);
		}
	}
	if(R[graphsize-1]==graphsize)
		R[graphsize-1]=-1;
	if(e)
	{
		cout<<"需要配备交换机的城市为:";
		for(int s=0;s<graphsize;s++)
		{
			if(R[s]>0)
			{
				cout<<R[s]-1<<" ";
			}
		}
	}
	else
	{
		cout<<"全都不用交换机!"<<endl;
	}
	cout<<endl;
}


int main()
{
    char n;
    Graph_List graph;
	cout<<"      *******************************************************************       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                   欢迎使用本组的城市网络构建程序                *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                                  by刘瀚霆 王晓楠 毕海嘉         *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *******************************************************************       ";
    cout<<"             -------------->请输入任意键创建城市网络<--------------             ";
    n=getchar();
    graph.Create();			
	return 0;
}