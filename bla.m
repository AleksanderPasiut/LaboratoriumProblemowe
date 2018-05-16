clear all
close all

% kX = 0.2;
% kY = 0.2;
% eXscale = 3;
% eYscale = 3;
% alphaXscale = 2.5;
% alphaYscale = 2.5;

utx = [1 3 5 8];
ux = [0 0.2 -0.2 -0.2];

uty = [1 3 5 8];
uy = [0 0.2 -0.2 -0.2];
  
    
BasicTestFunction( 'GoHomeX', 0.5, 'Go Home !!!' );
BasicTestFunction( 'GoHomeY', 0.5, 'Go Home !!!' );
pause(10)
% set_param('Crane3D_DevDriv_READY', 'SimulationCommand', 'start')
set_param('Copy_of_Crane3D_DevDriv', 'SimulationCommand', 'start')

temp = exist('positions_and_angles');
while temp ~= 1
    temp = exist('positions_and_angles');
    pause(1)
end

figure;
plot(time, positions_and_angles)
legend('x','y','x angle','y angle')
title(alphaYscale);

% figure;
% plot(time, [eXplot, eYplot]);
% title(alphaYscale);
%     
formatSpec='%f %f %f %f %f %f %f %f \r\n';
size = 8000;

data_out(1,:) = time';
data_out(2:3,:) = control';
data_out(4:7,:) = positions_and_angles';
data_out(8,:) = z';

file = fopen('out.txt','w');
fprintf(file,formatSpec,data_out);
fclose(file);