#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
#include<queue>
using namespace std;
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
const int N=300;
int _n,_m;
int n,k;
int t;
int a[N],c[N],d[N],e[N],b[N],vis[N];
int a2[N],c2[N];
int f[1<<5][N];
vector<int> g[N];
pii ans;
queue<pii> q1,q2,q3;
//priority_queue<pii,vector<pii>,greater<pii> > q;
int id(int x,int y)
{
	return (x-1)*_m+y;
}
vector<pii> h;
int check(int v)
{
	for(int i=1;i<=n;i++)
		if(a[i]<=v)
			a2[i]=100000-1;
		else
			a2[i]=100000+1;
	for(int i=0;i<1<<k;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=inf;
	for(int i=1;i<=n;i++)
		if(c2[i]!=-1)
			f[1<<(c2[i]-1)][i]=0;
	for(int i=1;i<1<<k;i++)
	{
		for(int j=(i-1)&i;j;j=(j-1)&i)
			for(int l=1;l<=n;l++)
				f[i][l]=min(f[i][l],f[j][l]+f[i^j][l]);
		h.clear();
		for(int j=1;j<=n;j++)
		{
			h.push_back(pii(f[i][j],j));
			vis[j]=0;
		}
		sort(h.begin(),h.end());
		for(int i=0;i<n;i++)
			q3.push(h[i]);
		while(!q1.empty()||!q2.empty()||!q3.empty())
		{
			pii x;
			if(!q1.empty()&&(q2.empty()||(q1.front()<=q2.front()))&&(q3.empty()||(q1.front()<=q3.front())))
			{
				x=q1.front();
				q1.pop();
			}
			else if(!q2.empty()&&(q1.empty()||(q2.front()<=q1.front()))&&(q3.empty()||(q2.front()<=q3.front())))
			{
				x=q2.front();
				q2.pop();
			}
			else
			{
				x=q3.front();
				q3.pop();
			}
			if(vis[x.second])
				continue;
			vis[x.second]=1;
			f[i][x.second]=min(f[i][x.second],x.first);
			x.first+=a2[x.second];
//			for(auto v:g[x.second])
			for(vector<int>::iterator it=g[x.second].begin();it!=g[x.second].end();it++)
			{
				int v=*it;
				if(!vis[v])
				{
					if(a2[x.second]==100000-1)
						q1.push(pii(x.first,v));
					else
						q2.push(pii(x.first,v));
				}
			}
		}
	}
	int res=inf;
	for(int i=1;i<=n;i++)
		if(c2[i]!=-1)
		{
			f[(1<<k)-1][i]+=a2[i];
			res=min(res,f[(1<<k)-1][i]);
		}
	return res;
}
void gao()
{
	for(int i=1;i<=n;i++)
		b[i]=rand()%k+1;
	for(int i=1;i<=n;i++)
		if(c[i]!=-1)
			c2[i]=b[c[i]];
		else
			c2[i]=-1;
	int l=1,r=t;
	int temp=check(1);
	if(temp==inf)
		return;
	int v=(int)round((db)temp/100000);
	if(v>ans.first)
		return;
	while(l<r)
	{
		int mid=(l+r)>>1;
		temp=check(mid);
		if(temp<=(int)round((db)temp/100000)*100000)
			r=mid;
		else
			l=mid+1;
	}
	ans=min(ans,pii(v,l));
}
void solve()
{
	scanf("%d%d%d",&_n,&_m,&k);
	n=_n*_m;
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		d[i]=a[i];
	}
	sort(d+1,d+n+1);
	t=unique(d+1,d+n+1)-d-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(d+1,d+t+1,a[i])-d;
	for(int i=1;i<=n;i++)
		g[i].clear();
	for(int i=1;i<=_n;i++)
		for(int j=1;j<=_m;j++)
			if(c[id(i,j)]!=-1)
			{
				if(i>1&&c[id(i-1,j)]!=-1)
					g[id(i,j)].push_back(id(i-1,j));
				if(i<_n&&c[id(i+1,j)]!=-1)
					g[id(i,j)].push_back(id(i+1,j));
				if(j>1&&c[id(i,j-1)]!=-1)
					g[id(i,j)].push_back(id(i,j-1));
				if(j<_m&&c[id(i,j+1)]!=-1)
					g[id(i,j)].push_back(id(i,j+1));
			}
	ans=pii(inf,inf);
	for(int times=200;times;times--)
		gao();
	if(ans.first==inf)
		printf("-1 -1\n");
	else
		printf("%d %d\n",ans.first,d[ans.second]);
}
int main()
{
	srand(19260817);
	open("chocolate");
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}
