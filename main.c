#include"simulate.h"
#include"output_tf.h"
#include"uart.h"
#include<stdlib.h>
int main(void)
{
UART_init();
int n_samples = 100;
float Ts = 0.1;
r[0] = 1;
int k = 0;for (; k < size_ncr; k++)
{
 c[k] = 0;
}
k = 1;
r[0] = 1;
for (; k < size_r; k++)
{
r[k] = 0;
}
k = 0;
for (; k < n_samples; ++k)
{
control_system(r, u, c, num_cr, den_cr, num_ur, den_ur);
UART_sendString("\r\n\r\nk = ");
UART_sendNumber(k);
UART_sendString(" ,t = ");
UART_sendFloatNumber(k*Ts);
UART_sendString(" ,u = ");
UART_sendFloatNumber(u[0]);
UART_sendString(" ,c = ");
UART_sendFloatNumber(c[0]);
int i  = size_ncr - 1;
for (; i > 0; i--)
{
c[i] = c[i - 1];
}
c[i] = 0;
i = size_nur - 1;
for (; i > 0; i--)
{
u[i] = u[i - 1];
}
u[i] = 0;
i = size_r - 1;
for (; i > 0; i--)
{
r[i] = r[i- 1];
}
r[i] = 1;
}
}
