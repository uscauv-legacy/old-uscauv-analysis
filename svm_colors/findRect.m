rect_img = zeros(size(ii));    
rect_img(70:200, 50:270) = 1;

[rn, rx] = radialHist(rect_img, 30);

[in, ix] = radialHist(ii, 30);

diff = rn - in;

mse = diff * diff';

figure;
bar(rx, diff);