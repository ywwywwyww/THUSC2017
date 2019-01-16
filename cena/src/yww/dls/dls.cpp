#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
#include<bitset>
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
const ll p=998244353;
const int N=10000010;
const int n=10000000;
const int sqrtn=3162;
const int size=446;
typedef bitset<500> arr;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}
int c[N],d[N],b[N],pri[N],cnt;
void sieve()
{
	c[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!b[i])
		{
			pri[++cnt]=i;
			d[i]=cnt;
			c[i]=i;
		}
		for(int j=1;j<=cnt&&i*pri[j]<=n;j++)
		{
			int v=i*pri[j];
			b[v]=1;
			c[v]=c[i];
			if(i%pri[j]==0)
				break;
		}
	}
}
void init()
{
	sieve();
}
arr get(int x)
{
	while(c[x]>sqrtn)
		x/=c[x];
	arr res;
	while(x>1)
	{
		res.flip(d[c[x]]-1);
		x/=c[x];
	}
	return res;
}
int len,tot,tot2;
void solve2(int l,int r)
{
	tot=0;
	len=r-l+1;
	for(int i=1;i<=cnt;i++)
		if(r/pri[i]!=(l-1)/pri[i])
			tot++;
	ll ans=fp(2,len-tot);
	printf("%lld\n",ans);
}
arr e[size];
int insert(arr v)
{
	for(int i=0;i<size;i++)
		if(v[i])
		{
			if(e[i][i])
				v^=e[i];
			else
			{
				e[i]=v;
				return 1;
			}
		}
	return 0;
}
pii a[10000];
arr pre;
int cmp(pii a,pii b)
{
	return a.second<b.second;
}
void solve()
{
	int l,r;
	scanf("%d%d",&l,&r);
	if(r-l>6000)
	{
		solve2(l,r);
		return;
	}
	tot=0;
	tot2=0;
	len=r-l+1;
	if(l==1)
		l++;
	int m=0;
	for(int i=0;i<size;i++)
		e[i].reset();
	for(int i=l;i<=r;i++)
		a[++m]=pii(i,c[i]);
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++)
		if(a[i].second<=sqrtn)
		{
			if(tot<size)
				if(insert(get(a[i].first)))
					tot++;
		}
		else if(i==1||a[i].second!=a[i-1].second)
		{
			tot2++;
			if(tot<size)
				pre=get(a[i].first);
		}
		else
		{
			if(tot<size)
				if(insert(get(a[i].first)^pre))
					tot++;
		}
	ll ans=fp(2,len-tot-tot2);
	printf("%lld\n",ans);
}
int main()
{
	open("dls");
	init();
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}
