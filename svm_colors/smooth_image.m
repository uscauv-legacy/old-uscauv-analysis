function [iout, blurred] = smooth_image(iin, threshold, ksize, sigma)
g = fspecial('gaussian', [ksize, ksize], sigma);

blurred = conv2(iin, g);

%iout = im2bw(iout, graythresh(iin));
iout = im2bw(blurred, threshold);

end