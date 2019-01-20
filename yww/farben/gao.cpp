#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<stack>
#include<bitset>
#include<assert.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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
template <class T>
int upmin(T &a, const T &b){return (b<a?a=b,1:0);}
template <class T>
int upmax(T &a, const T &b){return (b>a?a=b,1:0);}
namespace io
{
	const int SIZE=(1<<20)+1;
	char ibuf[SIZE],*iS,*iT;
	char obuf[SIZE],*oS=obuf,*oT=oS+SIZE-1;
	int getc()
	{
		(iS==iT?iS=ibuf,iT=ibuf+fread(ibuf,1,SIZE,stdin):0);
		return iS==iT?EOF:*(iS++);
	}
	int f;
	char c;
	template <class T>
	void get(T &x)
	{
		f=1;
		for(c=getc();(c<'0'||c>'9')&&c!='-';c=getc());
		(c=='-'?f=-1,c=getc():0);
		x=0;
		for(;c>='0'&&c<='9';c=getc())
			x=x*10+c-'0';
		x*=f;
	}
	void flush()
	{
		fwrite(obuf,1,oS-obuf,stdout);
		oS=obuf;
	}
	void putc(char x)
	{
		*(oS++)=x;
		if(oS==oT)
			flush();
	}
	int a[55],t;
	template <class T>
	void put(T x)
	{
		if(!x)
			putc('0');
		x<0?putc('-'),x=-x:0;
		while(x)
		{
			a[++t]=x%10;
			x/=10;
		}
		while(t)
			putc(a[t--]+'0');
	}
	void space()
	{
		putc(' ');
	}
	void enter()
	{
		putc('\n');
	}
	struct flusher
	{
		~flusher()
		{
			flush();
		}
	}
	io_flusher;
}
const ll p=1000000007;
const int N=1010;
const int n=1000;
//const int m=5;
int m;

ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}


const int MA=2100000;

int e[MA];
int ban[MA];
vector<int> g[N];
int pw[N];
int ma;

namespace gao1
{
	int a[N],b[N],c[N];
	void dfs(int x)
	{
		if(x>m)
		{
			for(int i=1;i<=m;i++)
				b[i]=0;
			int tot=0;
			int s=0;
			int s2=0;
			int first=0;
			for(int i=1;i<=m;i++)
			{
				if(!b[a[i]])
					b[a[i]]=++tot;
				c[i]=b[a[i]];
				s+=c[i]*pw[i-1];
				s2+=a[i]*pw[i-1];
				if(c[i]<=c[i-1]&&!first)
					first=i-1;
			}
			if(tot==m)
				ban[s2]=1;
			else
				g[first].push_back(s);
			return;
		}
		for(int i=1;i<=m;i++)
		{
			a[x]=i;
			dfs(x+1);
		}
	}
	void gao()
	{
		dfs(1);
	}
}

namespace gao2
{
	int a[N],b[N],c[N];
	void dfs(int x)
	{
		if(x>m)
		{
			for(int i=1;i<=m;i++)
				b[i]=0;
			for(int i=m;i>=1;i--)
				if(!a[i]||!b[a[i]])
				{
					c[i]=a[i];
					b[a[i]]=1;
				}
				else
					c[i]=0;
			int s=0,s1=0;
			for(int i=1;i<=m;i++)
				s+=c[i]*pw[i-1];
			for(int i=1;i<=m;i++)
				s1+=a[i]*pw[i-1];
			e[s1]=s;
			return;
		}
		for(int i=0;i<=m;i++)
		{
			a[x]=i;
			dfs(x+1);
		}
	}
	void gao()
	{
		dfs(1);
	}
}

int f[N];
int h[2][MA];
int d[MA];

void add(int &a,int b)
{
	a=(a+b)%p;
}

int append(int a,int b)
{
	return a/(m+1)+b*pw[m-1];
}

namespace gao3
{
	void gao(int x)
	{
		memset(d,0,sizeof d);
		
		for(int i=0;i<=ma;i++)
		{
			int flag=1;
			for(int y=i,j=1;j<=x;j++)
			{
				y=append(y,j);
				if(ban[y])
				{
					flag=0;
					break;
				}
			}
			d[i]=flag;
		}
		
		memset(h,0,sizeof h);
		int cur=0;
		for(auto v:g[x])
			h[cur][e[v]]++;
		for(int i=m;i<=n;i++)
		{
			fprintf(stderr,"%d %d %d\n",m,x,i);
			memset(h[cur^1],0,sizeof h[cur^1]);
			for(int j=0;j<=ma;j++)
				if(h[cur][j]&&!ban[j])
				{
					add(f[i],d[j]*h[cur][j]);
					for(int k=1;k<=m;k++)
						add(h[cur^1][e[append(j,k)]],h[cur][j]);
				}
			cur^=1;
		}
	}
}

int main(int argc,char **argv)
{
//	freopen("farben2.txt","w",stdout);
	sscanf(argv[1],"%d",&m);
	ma=fp(m+1,m);
	pw[0]=1;
	for(int i=1;i<=m;i++)
		pw[i]=pw[i-1]*(m+1);
	gao1::gao();
	gao2::gao();
	
	for(int i=1;i<m;i++)
		f[i]=fp(m,i);
	
	for(int i=1;i<m;i++)
		gao3::gao(i);
	
	for(int i=1;i<=n;i++)
		printf("%d\n",f[i]);
	return 0;
}
