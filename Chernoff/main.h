#include <iostream>#include <sstream>#include <fstream>#include <iomanip>#include <stdio.h>#include <stdlib.h>#include <stddef.h>#include <chrono>#include <time.h>#include <math.h>#include <string.h>#include "gamma.h"#include "integral.h"#include "airy.h"using namespace std;#define SQR(x) ((x)*(x))#define pi 3.141592653589793double moment_function(int m, int i, double a[], double b[], double zai[], double vai[], double x);double qfunction(int n, double a[], double b[], double zai[], double vai[], double x, double u);double moment(int m, int i, double a[], double b[], double zai[], double vai[]);double F_Z(int m, double a[], double b[], double zai[], double vai[], double x);double f_Z(int m, double a[], double b[], double zai[], double vai[], double x);double    quantile_function(int n, double a[], double b[], double zai[], double vai[], double u);double px(int m, double aa[], double bb[], double Aizero[], double x);double p1(int m, double aa[], double bb[], double Aizero[], double x, double y);double p2(double x, double y);double p3(int m, double zai[], double vai[], double x);void ComputeCoefficients(int n, double a[], double b[]);double moment_function(int m, int i, double a[], double b[], double zai[], double vai[], double x);double moment(int m, int i, double a[], double b[], double zai[], double vai[]);int zeroinder(int n, double aa[], double bb[], double zai[], double vai[], double u, double *x, double *y,				 double (*fx)(int,double *,double *,double *,double *,double,double),					double (*dfx)(int,double *,double *,double *,double *,double),					 double tolx);double 	qfunction(int n, double a[], double b[], double zai[], double vai[], double x, double u);double	quantile_function(int n, double a[], double b[], double zai[], double vai[], double u);double tolx(double x);double integral_moment(int m, int i, double aa[], double bb[], double Aizero[], double vai[], double a, 				double b, double (*fx)(int,int,double *,double *,double *,double *, double),				double e[], int ua, int ub);double gamma1(double x);double beta(double z, double w);