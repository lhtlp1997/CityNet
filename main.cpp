#include <iostream>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<graphics.h>
#include <stdlib.h>
int rypd;//rypdΪ�����ж�
int dushu[10000];
using namespace std;
template<class T>

class SLNode
{
public:
    T data;//������
    SLNode<T>* next;//ָ����
    SLNode(SLNode* nextNode=NULL)//���������캯��
    {
        next=nextNode;
    }
    SLNode(const T& item,SLNode* nextNode=NULL)//���������캯��
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
    SLNode<T>* Front;//ָ����׵�ָ��
    SLNode<T>* Rear;//ָ���β��ָ��
public:
    LQueue()
    {
        Front=Rear=NULL;   //���캯��
    }
    ~LQueue()
    {
        QClear();   //��������
    }
    void QInsert(const T& item);//��β���Ԫ��
    bool QDelete(T& item);//ɾ������Ԫ��
    bool QFront(T& item)const;//��ȡ����Ԫ��
    bool IsEmpty() const
    {
        return Front==NULL;
    }
    void QClear();//��ն���
};


template<class T>
void LQueue<T>::QInsert(const T& item)
{
    if(IsEmpty())
    {
        Front=Rear=new SLNode<T>(item,NULL);//��Ϊ���򴴽��½ڵ㲢����βָ��ָ����½ڵ�
    }
    else
    {
        Rear->next=new SLNode<T>(item,NULL);//����Ϊ������¶�βָ��
        Rear=Rear->next;
    }
}

template<class T>
bool LQueue<T>::QDelete(T& item)
{
    if(IsEmpty())//��Ϊ�����޷�����
    {
        cout<<"����Ϊ���޷����ӣ�"<<endl;
        return false;
    }
    SLNode<T>* temp=Front;//����Ϊ���򽫶���ָ�����
    item=temp->data;
    Front=Front->next;
    delete temp;
    if(IsEmpty())//��ɾ�����׺����Ϊ���򽫶�βָ���ÿ�
    {
        Rear=NULL;
    }
    return true;
}

template<class T>
bool LQueue<T>::QFront(T& item) const
{
    if(IsEmpty())//������Ϊ�����޷���ȡ
    {
        cout<<"����Ϊ���޷���ȡ��"<<endl;
        return false;
    }
    item=Front->data;
    return true;
}
template<class T>
void LQueue<T>::QClear()
{
    while(!IsEmpty())//����Ϊ����Ӷ��׿�ʼɾ�����
    {
        Rear=Front;
        Front=Front->next;
        delete Rear;
    }
    Rear=NULL;
}


const int MaxGraphSize = 256;
const int MaxWeight = 1000;

/*�߽��Ľṹ��*/
struct Edge
{
    friend class Graph_List;
    int VerAdj;//�ڽӶ�����ţ���0��ʼ���
    Edge *link;//ָ����һ���߽���ָ��
};
/*������еĽṹ��*/
struct Vertex
{
    friend class Graph_List;
    int VerName;//���������
	int du;
    Edge *adjacent;//�������ͷָ��
};
/*�����ڽӱ�洢��Graph_List�ඨ��*/
class Graph_List
{
private:
    Vertex *Head;//�����ͷָ��
    int graphsize;//ͼ�е�ǰ�������
public:
    Graph_List() {};
    virtual ~Graph_List();
    void Create();
    int GraphEmpty() const
    {
        return graphsize == 0;
    };//���ͼ�Ƿ�Ϊ��
    void InsertEdge(const int &v1,const int &v2);//��ͼ�в���һ����
	void InsertEdge2(const int &v1,const int &v2);
    int GetFirstNeighbor(const int v);//����ͼ��ĳ����ĵ�һ���ڽӶ���
    int GetNextNeighbor(const int v1,const int v2);//����ͼ��ĳ����ĵ�һ���ڽӶ���
    void DepthFisrtSearch(int v1,int v2);//ͼ��������ȱ���
	void bianli(const int v,int &i);
    void RDFS(int v,int *visited);
	void RDFS(const int v,int *visited,int &v2);//3��������
	void RDFS2(int v1,int *visited,int v2);//���ڵ�һ����ж�
	void deleteit(const int &v1,const int &v2);
	void deletepoint(const int &v1,const int &v2);//������ĺ���
	void jiaohuanji();
	int Isconect();
	int Isconect2();
	int Isconect3(const int v);

	void dierti(int e,int b[],int kekao[],int kekaopoint);
	void disanti(int graphsize,int sum[],int sumpoint);
	void huatu(int graphsize,int e,int aa[],int aapoint,int b[]);
	void wenjian(int sum[],int sumpoint,int kekao[],int kekaopoint);
};


	

void Graph_List::Create()//����
{
	int a[10000];//������ɵ���
	int aa[10000];//�����ɹ��ĵ㣬Ϊ��һ�����С֧����
	int aapoint=0;
	int	b[10000];//�����������,b[100]Ϊ�ڶ�������
	int kekao[10000];//�ɿ����籣��
	int kekaopoint=0;
	int sum[10000];//�������
	int sumpoint=0;//�������
	for(int j=0;j<10000;j++){
		b[j]=0;
		dushu[j]=0;
		sum[j]=0;
		aa[j]=0;
		kekao[j]=0;
	}
    int e,from,to;
    Head = new Vertex[MaxGraphSize+1];
    cout<<"��������еĸ���: ";
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
    cout<<"����Ҫ������ɵĳ���ͨѶ����ĸ���:";
    cin>>e;


	//���������
    srand((unsigned)time(NULL)); 

    for (i=0; i<(e*2); i+=2)         
    {  
        a[i]=1 + (int)graphsize * rand() / (RAND_MAX + 1);
		a[i+1]=1 + (int)graphsize * rand() / (RAND_MAX + 1);
		cout<<"("<<a[i]<<","<<a[i+1]<<")  ";
		b[i]=a[i];  b[i+1]=a[i+1];
    }
	cout<<endl;
	//���������

	                          /****************************��һ��************************************/
    for(i=0; i<(e*2); i+=2)
    {
		from=a[i];
		to=a[i+1];
		rypd=0;
		if(from==to){
			cout<<"��"<<from<<"���"<<to<<"������������ͬ!�޷�����ͨѶ����."<<endl;
			continue;
		}
		DepthFisrtSearch(from,to);
		if(rypd==1){
			cout<<from<<"��"<<to<<"������!"<<endl;

			sum[sumpoint]=a[i];//��¼����ı�
			sum[sumpoint+1]=a[i+1];
			sumpoint+=2;
			continue;//������ߵ���ʱ��ɾ��
		}
		aa[aapoint]=a[i];//aa�����¼������С֧����
		aa[aapoint+1]=a[i+1];
		aapoint+=2;
        InsertEdge(from,to);
		InsertEdge(to,from);
	}for(i=0;i<sumpoint;i+=2){//������߼��ϣ����ڵڶ��ʵ��ж�
		InsertEdge(sum[i],sum[i+1]);
		InsertEdge(sum[i+1],sum[i]);
	}
	cout<<"��һ��ʣ��ı�Ϊ:"<<endl;
	for(i=0;i<aapoint;i+=2)
		cout<<"("<<aa[i]<<","<<aa[i+1]<<") ";
	
	//��һ�鴴��
	                          /****************************��һ��************************************/


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

	cout<<endl<<"���еĳ�ʼ��ͨ״̬Ϊ:";
	i=Isconect();
	int nn;
	if(i==1){//���粻��ͨ
		do{
		cout<<"������ɵ����粻��ͨ!";
		cout<<"���������: 1.�鿴ͼ��  2.������������  "<<endl;
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
	else {//������ͨ
		cout<<"��ͨ"<<endl;
		do{
			cout<<"���������: 1.�������Ŀɿ��Բ����䱣�浽�ļ�  2.������߱��浽�ļ�  "<<endl;
			cout<<"            3.�����еĽ�����״��  4.�鿴ͼ��  5.������������  "<<endl;
			cin>>nn;
			switch(nn){
			case 1:/****************************�ڶ���************************************/
				dierti(e,b,kekao,kekaopoint);
				break;
			case 2:/***********����洢**************/
				wenjian(sum,sumpoint,kekao,kekaopoint);
				cout<<"�������!"<<endl;
				break;
			case 3:/****************************������************************************/
				disanti(graphsize,sum,sumpoint);
				break;
			case 4:/******************************��ͼ************************************/
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
	cout<<"�����ж�ÿ�������е������Ƿ�Ϊ�ɿ�����"<<endl<<endl;
	for(int i=0;i<(e*2);i+=2){
		if(b[i]==b[i+1])
			continue;
		deleteit(b[i],b[i+1]);
		deleteit(b[i+1],b[i]);
		cout<<"���"<<b[i]<<"��"<<b[i+1];
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
	fprintf(fp,"�ɿ�����Ϊ:");
	fprintf(fp,"\n");
	for(i=0;i<kekaopoint;i+=2)
		fprintf(fp,"(%d,%d)\n",kekao[i],kekao[i+1]);
	fclose(fp);
}
void Graph_List::disanti(int graphsize,int sum[],int sumpoint){
	cout<<"������Ҫ�����һ�ʵĽ��������:"<<endl;
	int shuru;
	cin>>shuru;
	if(shuru==1){
		for(int i=0;i<sumpoint;i+=2){
		deleteit(sum[i],sum[i+1]);
		deleteit(sum[i+1],sum[i]);
		}
	cout<<"��Ҫ�佻�����ĳ���Ϊ:";
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
	else cout<<"��Ҫ������"<<endl;
}
void Graph_List::huatu(int graphsize,int e,int aa[],int aapoint,int b[]){
	cout<<"Ҫ��ʾ��һ���ͼ��?(����1��2):";
		int dian1,dian2,bian1,bian2,bian3,bian4;
		int shuru2;
	cin>>shuru2;
	if(shuru2==1){//��һ��ͼ��
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
	else if(shuru2==2){//�ڶ���ͼ��
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
	fprintf(fp,"������·Ϊ:");
	fprintf(fp,"\n");
	for(int i=0;i<sumpoint;i+=2)
		fprintf(fp,"(%d,%d)\n",sum[i],sum[i+1]);
	fclose(fp);
}

int Graph_List::GetFirstNeighbor(const int v)//�ҵ�һ���ڽӶ���
{
    if(v == -1) return -1;
    Edge *p = Head[v].adjacent;
    if(p!=NULL) return p->VerAdj;
    else return -1;
}
int Graph_List::GetNextNeighbor(const int v1,const int v2)//���ڽ��
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
void Graph_List::RDFS(int v,int *visited)//�����v��ʼ������ȱ���
{
    visited[v] = 1;
    int w = GetFirstNeighbor(v);
    while(w!=-1)
    {
        if(!visited[w]) RDFS(w,visited);
        w = GetNextNeighbor(v,w);
    }
}
void Graph_List::RDFS(const int v1,int *visited,int &v2)//�����v��ʼ������ȱ���
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
void Graph_List::RDFS2(int v1,int *visited,int v2)//�����v��ʼ������ȱ���
{
    visited[v1] = 1;
     int w = GetFirstNeighbor(v1);
    while(w!=-1)
    {
        if(!visited[w]) RDFS(w,visited);
        w = GetNextNeighbor(v1,w);
    }
}
void Graph_List::DepthFisrtSearch(int v1,int v2)//�����v��ʼ��ȱ���
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

int Graph_List::Isconect()   //����cout�Ĳ���
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


int Graph_List::Isconect2(){  //��cout�Ĳ���
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
	cout<<"�������粻��ͨ��Ϊ�ǿɿ�����"<<endl;
	return   1;
	}   
    else   
    cout<<"����������ͨ��Ϊ�ɿ�����"<<endl;   
    return   0;
	delete []visited;
  }
int Graph_List::Isconect3(const int v)   //����cout�Ĳ���
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


void Graph_List::InsertEdge(const int &v1,const int &v2)//��һ�����ĺ���
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

void Graph_List::InsertEdge2(const int &v1,const int &v2)//�ڶ��鴴���ĺ���
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



void Graph_List::deleteit(const int &v1,const int &v2){//��ʽɾ��
	Edge *q=NULL,*p = Head[v1].adjacent;
	if(p==NULL)
    {
        return;//�߲�����
    }
    if(p->VerAdj==v2)
    {
        q = p->link;
        Head[v1].adjacent = q;
        delete p;//ɾ���ɹ�
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
        delete q;//ɾ���ɹ�
		return;
    }
}

void Graph_List::deletepoint(const int &v1,const int &v2){//�������ɾ������
	Edge *q=NULL,*p = Head[v1].adjacent;
	if(p==NULL)
    {
        return;//�߲�����
    }
    if(p->VerAdj==v2)
    {
        q = p->link;
        Head[v1].adjacent = q;
        delete p;
		Head[v1].du--;
		return;//ɾ���ɹ�
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
		cout<<"��Ҫ�䱸�������ĳ���Ϊ:";
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
		cout<<"ȫ�����ý�����!"<<endl;
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
	cout<<"      *                   ��ӭʹ�ñ���ĳ������繹������                *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                                  by����� ����� �Ϻ���         *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *                                                                 *       ";
	cout<<"      *******************************************************************       ";
    cout<<"             -------------->�����������������������<--------------             ";
    n=getchar();
    graph.Create();			
	return 0;
}