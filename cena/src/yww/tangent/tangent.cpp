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
const ldb eps=1e-6;
ldb DELTA[]={0,0.235,0.3746,0.1246,0.2153,0.364,0.1253,0.6124,0.164,0.7543,0.35476};
int n;
ldb a[20][20];
ldb r[20];
ldb ans[2100][20][20];
ldb b[20][20];
ldb c[20][20];
ldb e[20];
int cnt;
void gao(ldb d)
{
	for(int i=1;i<=n;i++)
		e[i]=c[i][n+1]*d+c[i][n+2];
	cnt++;
	for(int i=1;i<=n;i++)
	{
		ldb s=0;
		for(int j=1;j<=n;j++)
			s+=a[i][j]*e[j];
		s-=d;
		for(int j=1;j<=n;j++)
			ans[cnt][i][j]=a[i][j]-s*e[j];
	}
}
void calc()
{
	memcpy(c,b,sizeof b);
	int flag=0;
	for(int i=1;i<=n;i++)
	{
		int x=i;
		for(int j=i;j<=n;j++)
			if(fabs(c[j][i])>fabs(c[x][i]))
				x=j;
		if(fabs(c[x][i])<eps)
		{
			flag=1;
			continue;
		}
		if(x!=i)
			swap(c[x],c[i]);
		ldb v=1/c[i][i];
		for(int j=1;j<=n+2;j++)
			c[i][j]*=v;
		for(int j=1;j<=n;j++)
			if(j!=i)
			{
				ldb v=c[j][i];
				for(int k=1;k<=n+2;k++)
					c[j][k]-=c[i][k]*v;
			}
	}
	if(flag)
	{
//		ldb d;
//		for(int i=1;i<=n;i++)
//			if(!c[i][i])
//			{
//				if(flag)
//				{
//				}
//				else
//				{
//				}
		printf("error\n");
		return;
	}
	ldb A=0,B=0,C=0;
	for(int i=1;i<=n;i++)
	{
		A+=c[i][n+1]*c[i][n+1];
		B+=2*c[i][n+1]*c[i][n+2];
		C+=c[i][n+2]*c[i][n+2];
	}
	C-=1;
	if(fabs(A)<eps)
	{
		if(fabs(B)<eps)
		{
			return;
		}
		ldb d=-C/B;
		gao(d);
	}
	else
	{
		ldb delta=B*B-4*A*C;
		if(delta<-eps)
			return;
		else
			delta=max(delta,(ldb)0);
		if(delta<eps)
		{
			ldb d=-B/(2*A);
			gao(d);
		}
		else
		{
			ldb d1=(-B+sqrt(delta))/(2*A);
			gao(d1);
//			ldb d2=(-B+sqrt(delta))/(2*A);
//			gao(d2);
		}
	}
}
void dfs(int x)
{
	if(x>n)
	{
		calc();
		return;
	}
	for(int i=1;i<=n;i++)
		b[x][i]=a[x][i];
	b[x][n+1]=1;
	b[x][n+2]=r[x];
	dfs(x+1);
	if(fabs(r[x])<eps)
		return;
	b[x][n+2]=-r[x];
	dfs(x+1);
}
void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%Lf",&a[i][j]);
			a[i][j]-=DELTA[j];
		}
		scanf("%Lf",&r[i]);
	}
	cnt=0;
	dfs(1);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
				printf("%.20Lf ",ans[i][j][k]+DELTA[k]);
			printf("\n");
		}
}
int main()
{
//	freopen("tangent.in","r",stdin);
	int t;
	scanf("%d",&t);
	while(t--)
		solve();
	return 0;
}
