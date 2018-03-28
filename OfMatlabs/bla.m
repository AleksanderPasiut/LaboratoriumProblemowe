clear all
close all

% there and back again
% utx = [0.8 2 3];
% ux = [0.2 -0.4 0.2];
% 
% uty = [0.8 2 3];
% uy = [0.2 -0.4 0.2];

% utx = [1 2 3];
% ux = [0 0 0];

% there and stop
utx = [0.8 2 0];
ux = [0.2 0 0];

% uty = [0.8 2 0];
% uy = [0.2 0 0];

uty = [1 2 3];
uy = [0 0 0];



BasicTestFunction( 'GoHomeXYZ', 0.5, 'Go Home !!!' );
pause(30)
set_param('Crane3D_DevDriv', 'SimulationCommand', 'start')

temp = exist('positions_and_angles');
while temp ~= 1
    temp = exist('positions_and_angles');
    pause(1)
end

plot(time,positions_and_angles)
legend('x','y','x angle','y angle')

formatSpec='%f %f %f %f %f %f %f %f \r\n';
size = 3000;

data_out(1,:) = time';
data_out(2:3,:) = control';
data_out(4:7,:) = positions_and_angles';
data_out(8,:) = z';

file = fopen('out.txt','w');
fprintf(file,formatSpec,data_out);
fclose(file);
