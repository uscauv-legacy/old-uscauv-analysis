function [fhull] = fillHull(img)
    
    % figure;
    %    imshow(img);
    %   hold on;                            

    fhull = img;
    
    hull_pts = wraphull(img);

    %scatter(hull_pts(:,1), hull_pts(:,2), 'MarkerFaceColor', 'b', ...
    %    'MarkerEdgeColor', 'b');

    [m,n] = size(img);

    %keyboard;

    for i=1:m
        for j = 1:n
            if inpolygon(j,i, hull_pts(:,1), hull_pts(:,2)) 
                fhull(i, j) = 1;
            end
        end
    end

    %    [a, b] = ind2sub([m,n], 1:(m*n));

    %    a = a'; b = b';

    %    [a, b] = meshgrid(1:m,1:n);



    %    in = inpolygon(b,a, hull_pts(:,1), hull_pts(:,2));

    %    indx = find(in);

  
    %   ai = a(indx); bi = b(indx);
    
    %    keyboard;
    %    idx = [b(indx); a(indx)]; 
    
    %    fhull(a(indx), b(indx)) = 0.5;
    
    %    imshow(fhull);                       
    %    hold on;
    %    scatter(b(indx), a(indx));
    %    keyboard;


     
end