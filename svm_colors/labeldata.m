function [positiveexamples, negativeexamples] = labeldata(trainingexamples, ...
                                                      trainingspace, ...
                                                      scale)
  positiveexamples = [];
  negativeexamples = [];
  
  for idx=1:length(trainingexamples)
      tr_image = imresize(trainingexamples(idx).(trainingspace), scale);
      mask = imresize(trainingexamples(idx).mask, scale);
      
    masksize  = size(mask);
    imagesize = size(tr_image);

    pos = [];
    [goodpixeli, goodpixelj] = ind2sub(masksize(1:2), find(mask ~= 0));
    pos(:, 1) = tr_image(sub2ind(imagesize, goodpixeli, goodpixelj, repmat(1, length(goodpixeli),1)));
    pos(:, 2) = tr_image(sub2ind(imagesize, goodpixeli, goodpixelj, repmat(2, length(goodpixeli),1)));
    pos(:, 3) = tr_image(sub2ind(imagesize, goodpixeli, goodpixelj, repmat(3, length(goodpixeli),1)));

    
    neg = [];
    [badpixeli, badpixelj] = ind2sub(masksize(1:2), find(mask == 0));
    neg(:, 1) = tr_image(sub2ind(imagesize, badpixeli, badpixelj, repmat(1, length(badpixeli),1)));
    neg(:, 2) = tr_image(sub2ind(imagesize, badpixeli, badpixelj, repmat(2, length(badpixeli),1)));
    neg(:, 3) = tr_image(sub2ind(imagesize, badpixeli, badpixelj, repmat(3, length(badpixeli),1)));
    
    positiveexamples = [positiveexamples; pos];
    negativeexamples = [negativeexamples; neg];
  end

    positiveexamples = single(positiveexamples);
    negativeexamples = single(negativeexamples);
  
end

