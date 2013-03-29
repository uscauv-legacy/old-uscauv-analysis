function [] = plotsmoothing(predictions, trainingspace)

    fig1 = figure;
    fig2 = figure;
    fig3 = figure;
    
    for idx = 1:length(predictions.(trainingspace))

    img = predictions.(trainingspace){idx};

    [thresh_img, blur_img] = smooth_image(img, 0.9, 10, 5);

    plotc(fig1, img, [0, 1]);
    plotc(fig2, blur_img, [0, 1]);
    plotc(fig3, thresh_img, [0, 1]);

    %     plotc(fig1, img); plotc(fig2, blur_img); plotc(fig3, thresh_img);% 

    %    figure(fig1); clf; imshow(img); figure(fig2); clf; ...
    %        imshow(blur_img); figure(fig3); clf; imshow(thresh_img);
    
    
    waitforbuttonpress;
    
    end
end