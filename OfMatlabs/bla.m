clear all
close all
BasicTestFunction( 'GoHomeXYZ', 0.5, 'Go Home !!!' );
set_param('Crane3D_DevDriv', 'SimulationCommand', 'start')

temp = exist('positions_and_angles');
while temp ~= 1
    temp = exist('positions_and_angles');
    pause(1)
end

plot(time,positions_and_angles)

formatSpec='%d %d';
% size = 

data_out_ctrl = fopen('control.txt','w');
data_out_pa = fopen('pa.txt','w');
data_out_pa_dev = fopen('pa_dev.txt','w');
fprintf(data_out_ctrl,formatSpec,sizeA);
fprintf(data_out_pa,formatSpec,sizeA);
fprintf(data_out_pa_dev,formatSpec,sizeA);
fclose(data_out);
