function [iout] = biggestSegment(iin)
    
    [iout, ~, mass] = segmentBFS(iin);

    max_class = find(mass == max(mass));

    iout(iout ~= max_class) = 0;
    iout(iout == max_class) = 1;
    
    
end