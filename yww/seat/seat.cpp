#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
//using namespace std;
using std::min;
using std::max;
using std::swap;
using std::sort;
using std::reverse;
using std::random_shuffle;
using std::lower_bound;
using std::upper_bound;
using std::unique;
using std::vector;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
void open(const char *s){
#ifndef ONLINE_JUDGE
	char str[100];sprintf(str,"%s.in",s);freopen(str,"r",stdin);sprintf(str,"%s.out",s);freopen(str,"w",stdout);
#endif
}
void open2(const char *s){
#ifdef DEBUG
	char str[100];sprintf(str,"%s.in",s);freopen(str,"r",stdin);sprintf(str,"%s.out",s);freopen(str,"w",stdout);
#endif
}
int rd(){int s=0,c,b=0;while(((c=getchar())<'0'||c>'9')&&c!='-');if(c=='-'){c=getchar();b=1;}do{s=s*10+c-'0';}while((c=getchar())>='0'&&c<='9');return b?-s:s;}
void put(int x){if(!x){putchar('0');return;}static int c[20];int t=0;while(x){c[++t]=x%10;x/=10;}while(t)putchar(c[t--]+'0');}
int upmin(int &a,int b){if(b<a){a=b;return 1;}return 0;}
int upmax(int &a,int b){if(b>a){a=b;return 1;}return 0;}
const int inf=0x3fffffff;
namespace flow
{
	int cnt;
	int v[1000010];
	int t[1000010];
	int c[1000010];
	int w[1000010];
	int h[1000010];
	int vis[12000];
	void add(int x,int y,int _c,int _w)
	{
		cnt++;
		v[cnt]=y;
		t[cnt]=h[x];
		c[cnt]=_c;
		w[cnt]=_w;
		h[x]=cnt;
	}
	int len,cost,flow;
	int num;
	int S,T;
	int ti;
	int op(int x)
	{
		return ((x-1)^1)+1;
	}
	int aug(int x,int fl)
	{
		if(x==T)
		{
			flow+=fl;
			cost+=len*fl;
			return fl;
		}
		vis[x]=ti;
		int s=0;
		for(int i=h[x];i;i=t[i])
			if(c[i]&&!w[i]&&vis[v[i]]!=ti)
			{
				int d=aug(v[i],min(fl,c[i]));
				c[i]-=d;
				c[op(i)]+=d;
				s+=d;
				fl-=d;
				if(!fl)
					break;
			}
		return s;
	}
	int gao()
	{
		int s=inf;
		for(int i=1;i<=num;i++)
			if(vis[i]==ti)
				for(int j=h[i];j;j=t[j])
					if(c[j]&&vis[v[j]]!=ti)
						s=min(s,w[j]);
		if(s==inf)
			return 0;
		for(int i=1;i<=num;i++)
			if(vis[i]==ti)
				for(int j=h[i];j;j=t[j])
				{
					w[j]-=s;
					w[op(j)]+=s;
				}
		len+=s;
		return 1;
	}
	void solve()
	{
		flow=cost=len=0;
		do
			do
				ti++;
			while(aug(S,inf));
		while(gao());
	}
}
void add(int x,int y,int c,int w)
{
	flow::add(x,y,c,w);
	flow::add(y,x,0,-w);
}
int nodecnt;
int n,m;
int id(int x,int y)
{
	return (x-1)*m+y;
}
struct seg
{
#define lc (p<<1)
#define rc ((p<<1)|1)
#define mid ((L+R)>>1)
	int s1[10000];
	int s2[10000];
	void build(int p,int k,int L,int R)
	{
		if(L==R)
		{
			s1[p]=s2[p]=id(L,k)+n*m;
			return;
		}
		s1[p]=++nodecnt;
		s2[p]=++nodecnt;
		build(lc,k,L,mid);
		build(rc,k,mid+1,R);
		add(s1[p],s1[lc],inf,(R-mid)*2);
		add(s1[p],s1[rc],inf,0);
		add(s2[p],s2[lc],inf,0);
		add(s2[p],s2[rc],inf,(mid-L+1)*2);
	}
	void gao1(int p,int l,int r,int x,int y,int L,int R)
	{
		if(l<=L&&r>=R)
		{
			add(y,s1[p],inf,(x-R)*2);
			return;
		}
		if(l<=mid)
			gao1(lc,l,r,x,y,L,mid);
		if(r>mid)
			gao1(rc,l,r,x,y,mid+1,R);
	}
	void gao2(int p,int l,int r,int x,int y,int L,int R)
	{
		if(l<=L&&r>=R)
		{
			add(y,s2[p],inf,(L-x)*2);
			return;
		}
		if(l<=mid)
			gao2(lc,l,r,x,y,L,mid);
		if(r>mid)
			gao2(rc,l,r,x,y,mid+1,R);
	}
}
seg[11];
int l[1010][12];
int r[1010][12];
int main()
{
	open("seat");
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&l[i][j]);
			l[i][j]++;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&r[i][j]);
			r[i][j]++;
		}
	nodecnt=2*n*m;
	for(int i=1;i<=m;i++)
		seg[i].build(1,i,1,n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(l[i][j]<=i)
				seg[j].gao1(1,l[i][j],min(r[i][j],i),i,id(i,j),1,n);
			if(r[i][j]>=i)
				seg[j].gao2(1,max(l[i][j],i),r[i][j],i,id(i,j),1,n);
		}
	flow::S=++nodecnt;
	flow::T=++nodecnt;
	flow::num=nodecnt;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			add(n*m+id(i,j),n*m+id(i,j%m+1),inf,1);
			add(n*m+id(i,j),n*m+id(i,(j-2+m)%m+1),inf,1);
		}
	for(int i=1;i<=n*m;i++)
	{
		add(flow::S,i,1,0);
		add(i+n*m,flow::T,1,0);
	}
	flow::solve();
	if(flow::flow<n*m)
		printf("no solution\n");
	else
		printf("%d\n",flow::cost);
	return 0;
}
