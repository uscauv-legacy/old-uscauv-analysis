%classify;

img = predictions.rgbimage{8};

[simg, bimg] = smooth_image(img, 0.9, 10, 5);

fhull = fillHull(simg);