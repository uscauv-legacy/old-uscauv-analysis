function contour = radialContour(img, nb)
%% Assumes that the image is centered at zero. nb is number of
%% histogram bins

    if size(img,3) == 3
        img = rgb2gray(img);
    end
    
    [rows, cols] = size(img);
    
    v = img2vec(img);
    
    nd = size(v,1);

    mdata = getStats(v);
    
    % Edge Detection ------------------------------------
    img_contour = edge(img, 'canny');

    vc = img2vec( img_contour);

    % Normalize ------------------------------------

    vc = vc - ones(length(vc),1)*mdata.mean; 

    % Rotate the data so that its most principal axis is aligned with
    % the x axis of the world frame
    theta = -mdata.theta;
    
    fprintf('Theta is %f degrees.\n', mdata.theta*180/pi);

    rot = [cos(theta) -sin(theta); sin(theta) cos(theta)];

    sc = [1/mdata.rmax 0 ; 0 1/mdata.rmax];

    vc = (sc * rot * vc')';    

    % Contour histogram ------------------------------------

% Convert the data from cartesian to polar coordinates, with angle
% sorted in ascending order in range [-pi, pi]
    vr = [atan2(vc(:,2), vc(:,1)), hypot(vc(:,1), vc(:,2))];
    vr = sortrows(vr,1);

    theta = uint32(linspace(1, length(vr), nb+1));
    
    contour = zeros(length(theta)-1,1);

    for i = 1:(length(theta)-1)
        % Take the mean radius of a specific segment of the theta space
        contour(i) = mean( vr(theta(i):theta(i+1), 2) );
    end

    figure; scatterImage(vc, [rows cols]*sc);
    
    figure; bar(contour);

end