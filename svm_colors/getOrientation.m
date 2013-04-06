function [rot] = getOrientation(img)
    
    [rows, cols] = size(img);

    x_hist = sum(img, 1);
    y_hist = sum(img, 2);
    
    imean = [ (1:cols) * x_hist' /sum(x_hist), (1:rows) * y_hist/ ...
            sum(y_hist)];

    pos = [];
    [pos(:,1), pos(:,2)] = find(img == 1);

    icov = cov(pos);

    [v, d] = eig(icov);

    mag = v * sqrt(d);
    
    % Dot the biggest component with the x axis
    rot = [1,0] * v(:, find(diag(d) == max(diag(d)))) * 180 / pi;

    imshow(img);
    hold on;
    scatter(imean(1), imean(2));
    
    quiver(imean(1)*ones(1,2), imean(2)*ones(1,2), mag(2,:), mag(1,:)); % 
    
    
    
    
    
end
