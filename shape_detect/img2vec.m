function vec = img2vec(img)
%% Convert a binary image to a vector of coordinates of points in
%% the image, ie a functional representation

[vec(:,2), vec(:,1)] = find(img);

end