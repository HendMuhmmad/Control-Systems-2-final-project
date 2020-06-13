function generate_C()

% to generate simulate.h
fileID = fopen('simulate.h','w');
fprintf(fileID,'#ifndef simulate_H_\n');
fprintf(fileID,'#define simulate_H_\n');
fprintf(fileID,'void control_system(float r[],float u[],float c[],const float numcr[],const float dencr[],const float numur[],const float denur[]);\n');
fprintf(fileID,'#endif\n');
fclose(fileID);

% to generate simulate.c
fileID = fopen('simulate.c','w');
fprintf(fileID,'#include "simulate.h"\n');
fprintf(fileID,'#include "output_tf.h"\n');
fprintf(fileID,'void control_system(float r[],float u[],float c[],const float numcr[],const float dencr[],const float numur[],const float denur[])\n{\n');
fprintf(fileID,'int i;\n');
fprintf(fileID,'for(i = 0;i<size_ncr;i++)\n');
fprintf(fileID,'{\n');
fprintf(fileID,'c[0] += numcr[i]*r[i];\n');
fprintf(fileID,'}\n');
fprintf(fileID,'for(i = 1;i<size_ncr;i++)\n');
fprintf(fileID,'{\n');
fprintf(fileID,'c[0] -= dencr[i]*c[i];\n');
fprintf(fileID,'}\n');
fprintf(fileID,'c[0] /= dencr[0];\n');

fprintf(fileID,'for(i = 0;i<size_nur;i++)\n');
fprintf(fileID,'{\n');
fprintf(fileID,'u[0] += numur[i]*r[i];\n');
fprintf(fileID,'}\n');
fprintf(fileID,'for(i = 1;i<size_nur;i++)\n');
fprintf(fileID,'{\n');
fprintf(fileID,'u[0] -= denur[i]*u[i];\n');
fprintf(fileID,'}\n');
fprintf(fileID,'u[0] /= denur[0];\n');
fprintf(fileID,'}\n');
fclose(fileID);

% to generate main.c
fileID = fopen('main.c','w');
fprintf(fileID,'#include"simulate.h"\n#include"output_tf.h"\n#include"uart.h"\n#include<stdlib.h>\n');
fprintf(fileID,'int main(void)\n{\nUART_init();\n');
fprintf(fileID,'int n_samples = 100;\nfloat Ts = 0.1;\nr[0] = 1;\nint k = 0;');
fprintf(fileID,'for (; k < size_ncr; k++)\n{\n c[k] = 0;\n}\n');
fprintf(fileID,'k = 1;\nr[0] = 1;\nfor (; k < size_r; k++)\n{\nr[k] = 0;\n}\n');
fprintf(fileID,'k = 0;\nfor (; k < n_samples; ++k)\n{\ncontrol_system(r, u, c, num_cr, den_cr, num_ur, den_ur);\n');
fprintf(fileID,'UART_sendString("\\r\\n\\r\\nk = ");\nUART_sendNumber(k);\nUART_sendString(" ,t = ");\nUART_sendFloatNumber(k*Ts);\nUART_sendString(" ,u = ");\nUART_sendFloatNumber(u[0]);\nUART_sendString(" ,c = ");\nUART_sendFloatNumber(c[0]);\n');
fprintf(fileID,'int i  = size_ncr - 1;\nfor (; i > 0; i--)\n{\nc[i] = c[i - 1];\n}\nc[i] = 0;\n');
fprintf(fileID,'i = size_nur - 1;\nfor (; i > 0; i--)\n{\nu[i] = u[i - 1];\n}\nu[i] = 0;\n');
fprintf(fileID,'i = size_r - 1;\nfor (; i > 0; i--)\n{\nr[i] = r[i- 1];\n}\nr[i] = 1;\n}\n}\n');
fclose(fileID);
end