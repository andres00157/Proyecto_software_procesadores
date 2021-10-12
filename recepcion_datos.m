% se limpia matlab
clear all % se borran las variables
close all % se cierra las ventanas 
clc % se borra el comand windows
% se configura el puerto seria a usar
if ~isempty(instrfind) % se preg
    unta si hay puertos abiertos
    fclose(instrfind); % se cierran los puertos abiertos
    delete(instrfind); % se borran los puertos abiertos
end
s = serialport("COM4",1000000,"Parity", "none", "DataBits" , 8, "StopBits", 1, "TimeOut", 2);
dato = 0;
while(length(dato)==1)
    [dato] = data_serial(s,512);
end

%clear all % se borran las variables
close all % se cierra las ventanas 
clc % se borra el comand windows
