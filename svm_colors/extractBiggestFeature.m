function [iout] = extractBiggestFeature(iin)
    
    [smooth, ~] = smooth_image(iin, 0.9, 5, 5);

    iout = fillHull(biggestSegment(smooth));
    
end