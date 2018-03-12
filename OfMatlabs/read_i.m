data = fopen('input.txt','r');
formatSpec='%f %f'
sizeA=[2 Inf];
A = fscanf(data,formatSpec,sizeA)
A=A'
fclose(data);
