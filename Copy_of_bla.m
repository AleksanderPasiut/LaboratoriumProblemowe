clear all
close all

% trzy_palce = 0.5*0.8354;
% 
% % there and back again
% utx = [0.8 4 7 10];
% ux = [0 0.2 -0.4 0.2];
% 
% uty = [0.8 4 7 10];
% uy = [0 0.2 -0.4 0.2];

% uty = [0.8 2 3];
% uy = [0.2 -0.4 0.2];

% utx = [1 2 3];
% ux = [0 0 0];

% there and stop
% utx = [1 3 10];
% ux = [0.5 -0.5 0];
% 
% uty = [1 3 10];
% uy = [0.5 -0.5 0];

% uty = [1 2 3];
% uy = [0 0 0];

% utx = [1 2 3];
% ux = [0 0 0];



% BasicTestFunction( 'GoHomeX', 0.5, 'Go Home !!!' );
% BasicTestFunction( 'GoHomeY', 0.5, 'Go Home !!!' );
% pause(10)
% set_param('Copy_of_Crane3D_DevDriv', 'SimulationCommand', 'start')
% 
% temp = exist('positions_and_angles');
% while temp ~= 1
%     temp = exist('positions_and_angles');
%     pause(1)
% end

plot(time,positions_and_angles)
legend('x','y','x angle','y angle')

formatSpec='%f %f %f %f %f %f %f %f \r\n';
size = 8000;

data_out(1,:) = time';
data_out(4:7,:) = positions_and_angles';
data_out(8,:) = z';

file = fopen('out.txt','w');
fprintf(file,formatSpec,data_out);
fclose(file);
