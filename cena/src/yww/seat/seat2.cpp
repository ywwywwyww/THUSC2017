#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int inf=0x3fffffff;
const int N=3010;
ll a[N][N];
ll lx[N];
ll ly[N];
int link[N];
ll slack[N];
int pre[N];
int vis[N];
int n;
void aug(int s)
{
	memset(vis,0,sizeof vis);
	memset(slack,0x7f,sizeof slack);
	int now=0,next=0,i;
	link[0]=s;
	for(;link[now];now=next)
	{
		vis[now]=1;
		int x=link[now];
		ll t,d=0x7fffffffffffffffll;
		for(i=1;i<=n;i++)
			if(!vis[i])
			{
				if((t=lx[x]+ly[i]-a[x][i])<slack[i])
				{
					slack[i]=t;
					pre[i]=now;
				}
				if(slack[i]<d)
				{
					d=slack[i];
					next=i;
				}
			}
		if(!d)
			continue;
		for(i=0;i<=n;i++)
			if(vis[i])
			{
				lx[link[i]]-=d;
				ly[i]+=d;
			}
			else
				slack[i]-=d;
	}
	while(now)
	{
		int x=now;
		now=pre[now];
		link[x]=link[now];
	}
}
int l[1010][12];
int r[1010][12];
int _n,_m;
int id(int x,int y)
{
	return (x-1)*_m+y;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("seat.in","r",stdin);
	freopen("seat.out","w",stdout);
#endif
	scanf("%d%d",&_n,&_m);
	n=_n*_m;
	for(int i=1;i<=_n;i++)
		for(int j=1;j<=_m;j++)
		{
			scanf("%d",&l[i][j]);
			l[i][j]++;
		}
	for(int i=1;i<=_n;i++)
		for(int j=1;j<=_m;j++)
		{
			scanf("%d",&r[i][j]);
			r[i][j]++;
		}
	int i,j;
	int x,y;
	ll z;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			a[i][j]=-0x7fffffff;
	for(int i=1;i<=_n;i++)
		for(int j=1;j<=_m;j++)
			for(int k=1;k<=_n;k++)
				if(k>=l[i][j]&&k<=r[i][j])
					for(int l=1;l<=_m;l++)
						a[id(i,j)][id(k,l)]=inf-(2*abs(i-k)+min(abs(j-l),_m-abs(j-l)));
	for(i=1;i<=n;i++)
	{
		lx[i]=-0x7fffffff;
		for(j=1;j<=n;j++)
			lx[i]=max(lx[i],a[i][j]);
	}
	for(i=1;i<=n;i++)
		aug(i);
	ll ans=0;
	for(i=1;i<=n;i++)
		ans+=lx[i]+ly[i];
	printf("%lld\n",(ll)n*inf-ans);
	return 0;
}
