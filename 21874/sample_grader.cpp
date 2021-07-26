#include <stdio.h>
#include <vector>
#include "hat.h"
using namespace std;

static int n,te,p;

int main()
{
	scanf("%d%d",&n,&te);
	init(n);
	for(int tn=0;tn<te;tn++)
	{
		vector<int> F(n),B(n),OF(n);
		for(int i=0;i<n-1;i++)
			scanf("%d",&F[i]);
		bool check=true;
		for(int i=n-1;i>=0;i--)
		{
			int nans=F[i];
			F[i]=0;
			int c=call(F,B,i);
			B[i]=c;
			if(c<0 || c>63 || (i!=n-1 && nans!=c))
			{
				check=false;
				break;
			}
		}
		if(check) printf("1\n");
		else printf("0\n");
	}
}
