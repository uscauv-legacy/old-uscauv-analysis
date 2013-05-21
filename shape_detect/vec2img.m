function img = vec2img(vec, dim)
%% Convert a vector of image coordinates to a binary image

img = zeros(dim);

img(sub2ind(dim, vec(:,2), vec(:,1))) = 1;

end