#include "main.h"// the procedure we used for computing the first 10 moments:double moment_function(int m, int i, double a[], double b[], double zai[], double vai[], double x){	double s;	s = pow(x,i)*f_Z(m,a,b,zai,vai,x);	return 2*s;}double qfunction(int n, double a[], double b[], double zai[], double vai[], double x, double u){	double s;	s = F_Z(n,a,b,zai,vai,x)-u;	return s;}	double moment(int m, int i, double a[], double b[], double zai[], double vai[]){	double s;	double e[7];	e[1]=e[2]=1.0e-9;	s=integral_moment(m,i,a,b,zai,vai,0,1,moment_function,e,1,0);	return s;}double F_Z(int m, double a[], double b[], double zai[], double vai[], double x){	double s;	double e[7];	e[1]=e[2]=1.0e-9;	if (x>=0)	{		if (x<=1)			s = 0.5+integral1(m,a,b,zai,vai,0,x,f_Z,e,1,1);		else			s = 1-integral1(m,a,b,zai,vai,x,x+1,f_Z,e,1,0);	}	else	{		x=-x;		if (x<=1)			s = 0.5+integral1(m,a,b,zai,vai,0,x,f_Z,e,1,1);		else			s = 1-integral1(m,a,b,zai,vai,x,x+1,f_Z,e,1,0);	}	return s;}double f_Z(int m, double a[], double b[], double zai[], double vai[], double x){	double s,x1,x2,x3,y,y1,y2,y3;	double e[7];	e[1]=e[2]=1.0e-9;		if (x<0) x =-x;		x1= integral(m,a,b,zai,x,0,1,p1,e,1,0)/sqrt(2*pi);	x2= integral2(x,0,1,p2,e,1,0)*2*sqrt(2/pi);	x3= 2*x-x1+x2;			y = -x;	y1= integral(m,a,b,zai,y,0,1,p1,e,1,0)/sqrt(2*pi);	if (y>=-1)	{		y2= integral2(y,0,1,p2,e,1,0)*2*sqrt(2/pi);		y3= 2*y-y1+y2;	}	else y3= p3(m,zai,vai,y);			s = x3*y3/2;		return s;}					 	 double	quantile_function(int n, double a[], double b[], double zai[], double vai[], double u){	int result;	double s,v=0,below,above,tolx=1.0e-10;		below=0.5;	above=2.0;		if ((u<=0)||(u>=1))    {        printf("Choose a value strictly between 0 and 1");    }			if (u<0.5) v=1-0.5;	if (u>=0.5)		result=zeroinder(n,a,b,zai,vai,u,&below,&above,qfunction,f_Z,tolx);	else		result=zeroinder(n,a,b,zai,vai,v,&below,&above,qfunction,f_Z,tolx);			s=(below+above)/2;		if (u>=0.5)		return s;	else		return -s;}	double px(int m, double aa[], double bb[], double Aizero[], double x){	int i;	double sum=0,y,z,c;	double sqrt_pi1= sqrt(pi/2);	double sqrt_pi2= 2*sqrt(2*pi);			if ((0<x) && (x<=1))	{		sum=-sqrt_pi1;		for (i=1;i<=m;i++)			sum+=-sqrt_pi1*aa[i]*exp(3*i*log(x))+bb[i]*exp(3*(i-0.5)*log(x));	}	else	{		if (x>1)		{			sum=0;			c=exp(log(2)/3);			y=-exp(-1.5*log(x));			z = sqrt_pi2*exp(-x*SQR(x)/6);			for (i=1;i<=m;i++)				sum+= exp(c*Aizero[i]*x);			sum = y+z*sum;		}	}	return sum;}//	The following function computes the integrand of the first integral in (3.8)double p1(int m, double aa[], double bb[], double Aizero[], double x, double y){	double s;		s= px(m,aa,bb,Aizero,x)*exp(-0.5*x*SQR(2*y+x));		return s;}//	The following function computes the integrand of the second integral in (3.8)double p2(double x, double y){	double s,z1,z2;		z1=2*y+SQR(x);	z2=SQR(x);		s=(z1*z2+0.5*SQR(z1))*exp(-0.5*SQR(z1)*z2);		return s;}//	The following function computes the function g, given by (3.9)double p3(int m, double zai[], double vai[], double x){	int i;	double s,c1,c2;		c1= exp(log(2)/3);	c2=SQR(c1);		s=0;		for (i=1;i<=m;i++)		s += exp(-c1*zai[i]*x)/vai[i];	s = c2*exp(2*SQR(x)*x/3)*s;		return s;}				//	Recursive computation of coefficients a[i] and b[i], as in (3.6) and (3.7)	void ComputeCoefficients(int n, double a[], double b[]){	int i,k,j;	double sum1,sum2,*c;        c = new double[n+1];		a[0]=1.0;	b[0]=0.0;	c[0]=1;		a[1]=7.0/48;	b[1]=2.0/3;	c[1]= 3.0/16;		for (i=2;i<=n;i++)	{		c[i]=-(2*i-3)*(2*i+1)*c[i-1]/(16*i*i*(2*i-1));				sum1=0;		sum2=0;				for (j=0;2*j-1<i;j++)		{			k=2*j-1;			if (k>0)				sum2 += a[i-k-1]*beta(3*i-2*k-2,k+1.5)/(gamma1(k+1)*pow(2,k+1));			k=2*j;			if (k<i)				sum2 -= a[i-k-1]*beta(3*i-2*k-2,k+1.5)/(gamma1(k+1)*pow(2,k+1));		}		b[i] =  sum2;				for (j=0;2*j-1<i;j++)		{			k=2*j-1;			if (k>0)				sum1 -= b[i-k]*beta(3*i-2*k-0.5,k+1.5)/(pi*gamma1(k+1)*pow(2,k));			k=2*j;			if (k<i)				sum1 += b[i-k]*beta(3*i-2*k-0.5,k+1.5)/(pi*gamma1(k+1)*pow(2,k));		}				a[i] = c[i] - sum1;	}        delete[] c;}			int main (){	int i,n;	double *xcoor,*quantile,*a,*b,*zai,*vai,*Moment;	double e[3];	FILE *output=NULL;		e[1]=e[2]=1.0e-10;		//printf("Number of terms in series?\n");		// here one can choose the number of terms, used in the series in (3.5) and (3.9)		//scanf("%d",&n);        n=100;    a = new double[n+1];    b = new double[n+1];    zai = new double[n+1];    vai = new double[n+1];        xcoor = new double[7];    quantile = new double[7];    Moment = new double[11];	ComputeCoefficients(n,a,b);	// coefficients a and b are computed		airyzeros(n,0,zai,vai);	// zeros of Ai and value of Ai' at the zeros are computed		// As an example we compute the quantiles, given in Table 2 of the paper		xcoor[1]=0.9;	quantile[1]=quantile_function(n,a,b,zai,vai,xcoor[1]);    printf("quantiles\n\n");	printf("%8.3f	%15.10f\n",xcoor[1],quantile[1]);	xcoor[2]=0.95;	quantile[2]=quantile_function(n,a,b,zai,vai,xcoor[2]);	printf("%8.3f	%15.10f\n",xcoor[2],quantile[2]);	xcoor[3]=0.975;	quantile[3]=quantile_function(n,a,b,zai,vai,xcoor[3]);	printf("%8.3f	%15.10f\n",xcoor[3],quantile[3]);	xcoor[4]=0.99;	quantile[4]=quantile_function(n,a,b,zai,vai,xcoor[4]);	printf("%8.3f	%15.10f\n",xcoor[4],quantile[4]);	xcoor[5]=0.995;	quantile[5]=quantile_function(n,a,b,zai,vai,xcoor[5]);	printf("%8.3f	%15.10f\n",xcoor[5],quantile[5]);	xcoor[6]=0.999;	quantile[6]=quantile_function(n,a,b,zai,vai,xcoor[6]);	printf("%8.3f	%15.10f\n",xcoor[6],quantile[6]);    printf("\n\n");		for (i=1;i<=10;i++)	{		Moment[i] = moment(n,i,a,b,zai,vai);		printf("%3d-th moment = %15.10f\n",i,Moment[i]);	}		output=fopen("results.txt","w");	for (i=1;i<=6;i++)		fprintf(output,"%8.3f	%15.10f\n",xcoor[i],quantile[i]);        fprintf(output,"\n\n");        for (i=1;i<=10;i++)        fprintf(output,"%3d-th moment = %15.10f\n",i,Moment[i]);		fclose(output);		printf("\n\n");		printf("ready\n");        delete[] a; delete[] b; delete[] zai; delete[] vai; delete[] xcoor;    delete[] quantile; delete[] Moment;        return 0;	}