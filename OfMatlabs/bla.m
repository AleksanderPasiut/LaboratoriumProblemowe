clear all
close all

kX = 0.2;
kY = 0.2;

eXscale = 2;
eYscale = 2;
alphaXscale = 1;

for alphaYscale = 1:3
    
    BasicTestFunction( 'GoHomeXYZ', 0.5, 'Go Home !!!' );
    pause(10)
    set_param('Crane3D_DevDriv', 'SimulationCommand', 'start')

    temp = exist('positions_and_angles');
    while temp ~= 1
        temp = exist('positions_and_angles');
        pause(1)
    end

    figure;
    plot(time, positions_and_angles)
    legend('x','y','x angle','y angle')
    title(alphaYscale);

    figure;
    plot(time, [eXplot, eYplot]);
    title(alphaYscale);
    
    clear positions_and_angles
    
end


