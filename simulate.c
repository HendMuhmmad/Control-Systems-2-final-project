#include "simulate.h"
#include "output_tf.h"
void control_system(float r[],float u[],float c[],const float numcr[],const float dencr[],const float numur[],const float denur[])
{
int i;
for(i = 0;i<size_ncr;i++)
{
c[0] += numcr[i]*r[i];
}
for(i = 1;i<size_ncr;i++)
{
c[0] -= dencr[i]*c[i];
}
c[0] /= dencr[0];
for(i = 0;i<size_nur;i++)
{
u[0] += numur[i]*r[i];
}
for(i = 1;i<size_nur;i++)
{
u[0] -= denur[i]*u[i];
}
u[0] /= denur[0];
}
