/* __MC__ */ int C__12=0;
/* __MC__ */ char flag__0x400700=0;
/* __MC__ */ char flag__0x400310=0;
#define __COUNT_CODE(flag_mem_blk, conflict) {conflict+=(flag_mem_blk==0)?1:0; flag_mem_blk=1;}
#define __COUNT_MACRO(flag_mem_blk, conflict)	__COUNT_CODE(flag_mem_blk, conflict)
/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                           sslim@archi.snu.ac.kr       */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: qurt.c                                                         */
/*  SOURCE : Turbo C Programming for Engineering by Hyun Soo Ahn         */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Root computation of quadratic equations.                          */
/*     The real and imaginary parts of the solution are stored in the    */
/*     array x1[] and x2[].                                              */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/



/*
** Benchmark Suite for Real-Time Applications, by Sung-Soo Lim
**     
**    III-7. qurt.c : the root computation of a quadratic equation
**                 (from the book C Programming for EEs by Hyun Soon Ahn)
*/


double a[3], x1[2], x2[2];
int flag;

int  qurt();


double fabs(double n)
{
  double f;

  if (n >= 0) f = n;
  else f = -n;
  return f;
}

double sqrt(val)
double val;
{
  double x = val/10;

  double dx;

  double diff;
  double min_tol = 0.00001;

  int i, flag;

  flag = 0;
  if (val == 0 ) x = 0;
  else {
    for (i=1;i<4;i++)
      {
	if (!flag) {
	  dx = (val - (x*x)) / (2.0 * x);
	  x = x + dx;
	  diff = val - (x*x);
/* __MC__ */__COUNT_MACRO(flag__0x400310,C__12);
	  if (fabs(diff) <= min_tol) flag = 1;
	}
	else 
	  x =x;
      }
  }
  return (x);
}


void main()
{

	int flag;

   a[0] =  1.0;
	a[1] = -3.0;
	a[2] =  2.0;
	qurt();

   a[0] =  4.0;
	a[1] = -7.0;
	a[2] =  8.0;
	qurt();
   
	a[0] =  1.0;
	a[1] = -4.0;
	a[2] =  8.0;
	qurt();
/* __MC__ */__CPROVER_assert(C__12 <= 1, "conflict check");
}

int  qurt()
{
	double  d, w1, w2;

	if(a[0] == 0.0) return(999);
	d = a[1]*a[1] - 4 * a[0] * a[2];
	w1 = 2.0 * a[0];
	w2 = sqrt(fabs(d));
	if(d > 0.0)
	{
		 flag = 1;
		 x1[0] = (-a[1] + w2) / w1;
		 x1[1] = 0.0;
		 x2[0] = (-a[1] - w2) / w1;
		 x2[1] = 0.0;
		 return(0);
	}
	else if(d == 0.0)
	{
		 flag = 0;
/* __MC__ */__COUNT_MACRO(flag__0x400700,C__12);
		 x1[0] = -a[1] / w1;
		 x1[1] = 0.0;
		 x2[0] = x1[0];
		 x2[1] = 0.0;
		 return(0);
	}
	else
	{
		 flag = -1;
		 w2 /= w1;
		 x1[0] = -a[1] / w1;
		 x1[1] = w2;
		 x2[0] = x1[0];
		 x2[1] = -w2;
		 return(0);
	}
}
