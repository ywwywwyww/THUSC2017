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
const int N=270000;
const int p=998244353;
struct mat
{
	int a[5][5];
	int n,m;
	mat(int _n=0,int _m=0):n(_n),m(_m)
	{
		memset(a,0,sizeof a);
	}
	int *operator [](int x)
	{
		return a[x];
	}
	const int *operator [](int x) const
	{
		return a[x];
	}
};
void add(const mat &a,const mat &b,mat &c)
{
	static mat d;
	d.n=a.n;
	d.m=a.m;
	for(int i=1;i<=a.n;i++)
		for(int j=1;j<=b.m;j++)
			d[i][j]=(a[i][j]+b[i][j])%p;
	c.n=d.n;
	c.m=d.m;
	for(int i=1;i<=c.n;i++)
		for(int j=1;j<=c.m;j++)
			c[i][j]=d[i][j];
}
void mul(const mat &a,const mat &b,mat &c)
{
	static mat d;
	d.n=a.n;
	d.m=b.m;
	for(int i=1;i<=c.n;i++)
		for(int j=1;j<=c.m;j++)
			d[i][j]=0;
	if(d.n==1&&d.m==4)
		for(int i=1;i<=a.n;i++)
			for(int j=1;j<=b.m;j++)
			{
	//			ll s=0;
	//			for(int k=1;k<=a.m;k++)
	//				s+=(ll)a[i][k]*b[k][j];
	//			c[i][j]=s%p;
				d[i][j]=((ll)a[i][1]*b[1][j]+(ll)a[i][2]*b[2][j]+(ll)a[i][3]*b[3][j]+(ll)a[i][4]*b[4][j])%p;
			}
	else
	{
		for(int i=1;i<=4;i++)
			for(int j=1;j<=3;j++)
			{
	//			ll s=0;
	//			for(int k=1;k<=a.m;k++)
	//				s+=(ll)a[i][k]*b[k][j];
	//			c[i][j]=s%p;
				d[i][j]=((ll)a[i][1]*b[1][j]+(ll)a[i][2]*b[2][j]+(ll)a[i][3]*b[3][j]+(ll)a[i][4]*b[4][j])%p;
			}
		d[4][4]=1;
	}
	c.n=d.n;
	c.m=d.m;
	for(int i=1;i<=c.n;i++)
		for(int j=1;j<=c.m;j++)
			c[i][j]=d[i][j];
}
int a[N],b[N],c[N];
mat ans;
namespace seg
{
	mat s[2*N];
	mat t[2*N];
	int _t[2*N];
#define lc (cur<<1)
#define rc ((cur<<1)|1)
#define mid ((L+R)>>1)
	void mt(int cur)
	{
		add(s[lc],s[rc],s[cur]);
	}
	void build(int cur,int L,int R)
	{
		s[cur].n=1;
		s[cur].m=t[cur].n=t[cur].m=4;
		t[cur][1][1]=t[cur][2][2]=t[cur][3][3]=t[cur][4][4]=1;
		if(L==R)
		{
			s[cur][1][1]=a[L];
			s[cur][1][2]=b[L];
			s[cur][1][3]=c[L];
			s[cur][1][4]=1;
			return;
		}
		build(lc,L,mid);
		build(rc,mid+1,R);
		mt(cur);
	}
	void add(int cur,mat &v)
	{
		if(!_t[cur])
		{
			_t[cur]=1;
			t[cur]=v;
		}
		else
			mul(t[cur],v,t[cur]);
		mul(s[cur],v,s[cur]);
	}
	void push(int cur)
	{
		if(_t[cur])
		{
			add(lc,t[cur]);
			add(rc,t[cur]);
			_t[cur]=0;
//			t[cur]=mat(4,4);
//			t[cur][1][1]=t[cur][2][2]=t[cur][3][3]=t[cur][4][4]=1;
		}
	}
	void modify(int cur,int l,int r,mat &v,int L,int R)
	{
		if(l<=L&&r>=R)
		{
			add(cur,v);
			return;
		}
		push(cur);
		if(l<=mid)
			modify(lc,l,r,v,L,mid);
		if(r>mid)
			modify(rc,l,r,v,mid+1,R);
		mt(cur);
	}
	void query(int cur,int l,int r,int L,int R)
	{
		if(l<=L&&r>=R)
		{
			add(ans,s[cur],ans);
			return;
		}
		push(cur);
		if(l<=mid)
			query(lc,l,r,L,mid);
		if(r>mid)
			query(rc,l,r,mid+1,R);
	}
}
int n,m;
int main()
{
	open("magic");
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
//		scanf("%d%d%d",&a[i],&b[i],&c[i]);
	{
		a[i]=rd();
		b[i]=rd();
		c[i]=rd();
	}
	seg::build(1,1,n);
	scanf("%d",&m);
	int op,l,r,v;
	for(int i=1;i<=m;i++)
	{
//		scanf("%d%d%d",&op,&l,&r);
		op=rd();
		l=rd();
		r=rd();
		mat t(4,4);
		if(op==1)
		{
			t[1][1]=1;
			t[2][2]=1;
			t[3][3]=1;
			t[4][4]=1;
			t[2][1]=1;
			seg::modify(1,l,r,t,1,n);
		}
		else if(op==2)
		{
			t[1][1]=1;
			t[2][2]=1;
			t[3][3]=1;
			t[4][4]=1;
			t[3][2]=1;
			seg::modify(1,l,r,t,1,n);
		}
		else if(op==3)
		{
			t[1][1]=1;
			t[2][2]=1;
			t[3][3]=1;
			t[4][4]=1;
			t[1][3]=1;
			seg::modify(1,l,r,t,1,n);
		}
		else if(op==4)
		{
//			scanf("%d",&v);
			v=rd();
			t[1][1]=1;
			t[2][2]=1;
			t[3][3]=1;
			t[4][4]=1;
			t[4][1]=v;
			seg::modify(1,l,r,t,1,n);
		}
		else if(op==5)
		{
//			scanf("%d",&v);
			v=rd();
			t[1][1]=1;
			t[2][2]=v;
			t[3][3]=1;
			t[4][4]=1;
			seg::modify(1,l,r,t,1,n);
		}
		else if(op==6)
		{
//			scanf("%d",&v);
			v=rd();
			t[1][1]=1;
			t[2][2]=1;
			t[4][4]=1;
			t[4][3]=v;
			seg::modify(1,l,r,t,1,n);
		}
		else
		{
			ans=mat(1,4);
			seg::query(1,l,r,1,n);
			printf("%d %d %d\n",ans[1][1],ans[1][2],ans[1][3]);
		}
	}
	return 0;
}
