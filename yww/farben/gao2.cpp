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
const int N=10010;
//const int n=10000;
int n;
ll fp(ll a,ll b)
{
	ll s=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)
			s=s*a%p;
	return s;
}

ll f[N],c[N],cur[N],ls[N];
int clen,curlen,lslen,l;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&f[i]);
	cur[0]=1;
	curlen=0;
	for(int i=1;i<=n;i++)
	{
		ll s=0;
		for(int j=0;j<=curlen;j++)
			s=(s+f[i-j]*cur[j])%p;
		if(!s)
			continue;
		ll invs=fp(s,p-2);
		if(!curlen)
		{
			curlen=i;
			lslen=0;
			ls[0]=invs;
			l=i;
			continue;
		}
		clen=max(curlen,i-l);
		for(int j=0;j<=clen;j++)
			c[j]=0;
		for(int j=0;j<=curlen;j++)
			c[j]=cur[j];
		for(int j=0;j<=lslen;j++)
			c[i-(l+lslen-j)]=(c[i-(l+lslen-j)]-ls[j]*s)%p;
		if(i-curlen>l)
		{
			l=i-curlen;
			lslen=curlen;
			for(int j=0;j<=curlen;j++)
				ls[j]=cur[j]*invs%p;
		}
		curlen=clen;
		for(int j=0;j<=clen;j++)
			cur[j]=c[j];
	}
	
	printf("%d\n",curlen);
	for(int i=0;i<=curlen;i++)
		printf("%lld ",(cur[i]+p)%p);
	
//	printf("{%d",curlen);
//	for(int i=1;i<=curlen;i++)
//		printf(",%lld",(-cur[i]+p)%p);
//	printf("},\n");

//	printf("{0");
//	for(int i=1;i<=500;i++)
//		printf(",%lld",(f[i]+p)%p);
//	printf("},\n");
	return 0;
}
