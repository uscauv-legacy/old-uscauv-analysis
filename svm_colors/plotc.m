function [] = plotc(fig, img, scale)
    figure(fig); clf; imagesc(img, scale); colorbar;
end
