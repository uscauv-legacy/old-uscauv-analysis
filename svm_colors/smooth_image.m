function [iout] = smooth_image(iin, threshold, ksize, sigma)
g = fspecial('gaussian', [ksize, ksize], sigma);

iout = conv2(iin, g);

%iout = im2bw(iout, graythresh(iin));
iout = im2bw(iout, threshold);

end