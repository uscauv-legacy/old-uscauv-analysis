function [hull] = wraphull(img)
%% Assumes that the input image is binary on [0, 1]
    
    pointsin = [];

    [pointsin(:, 2) pointsin(:,1)] = find(img == 1);

    %    keyboard;

    [hull] = pointsin( convhull(pointsin(:,1), pointsin(:,2)), :);

end