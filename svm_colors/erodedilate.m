function [output] = erodedilate(img, se)
    ime = imerode(img, se);

    figure; imshow(ime);

    output = imdilate(ime, se);

    figure;imshow(output);


end


