function [data] = data_serial(s,Num_datos)
    data = 0;
    clear i 
    for i = 1:1000
        if s.NumBytesAvailable >= Num_datos
            [data] = read(s,Num_datos,"uint8"); %% Finish RD
            break; 
        end
    end
end
