imagenames = {
'orange_tape/orange_tape-0000000000.png',
'orange_tape/orange_tape-0000000001.png',
'orange_tape/orange_tape-0000000002.png',
'orange_tape/orange_tape-0000000003.png',
'orange_tape/orange_tape-0000000004.png',
'orange_tape/orange_tape-0000000005.png',
'orange_tape/orange_tape-0000000006.png',
'orange_tape/orange_tape-0000000007.png',
'orange_tape/orange_tape-0000000008.png'};

masknames = {
'orange_tape/orange_tape-0000000000_mask.png',
'orange_tape/orange_tape-0000000001_mask.png',
'orange_tape/orange_tape-0000000002_mask.png',
'orange_tape/orange_tape-0000000003_mask.png',
'orange_tape/orange_tape-0000000004_mask.png',
'orange_tape/orange_tape-0000000005_mask.png',
'orange_tape/orange_tape-0000000006_mask.png',
'orange_tape/orange_tape-0000000007_mask.png',
'orange_tape/orange_tape-0000000008_mask.png'};

trainingexamples = struct();

labTransform = makecform('srgb2lab');   % 

scale         = 0.0625;  
trainingspaces= {'rgbimage', 'hsvimage', 'labimage'};

% trainingspace = 'hsvimage';             
% trainingspace = 'labimage';             
trainingspace = 'rgbimage';             

for idx = 1:length(imagenames)
  
  trainingexamples(idx).rgbimage = imread(imagenames{idx});
  trainingexamples(idx).labimage = applycform(trainingexamples(idx).rgbimage, labTransform);
  trainingexamples(idx).mask     = imread(masknames{idx});
  trainingexamples(idx).hsvimage = rgb2hsv(trainingexamples(idx).rgbimage);

  % These two images will be used by the labeler
  trainingexamples(idx).mask          = trainingexamples(idx).mask(:,:,1);
  %  trainingexamples(idx).trainingimage = imresize(trainingexamples(idx).(trainingspace), scale);
end

% [positiveexamples, negativeexamples] = labeldata(trainingexamples); 

predictions = struct();

%% Plot labeled data in each color space
for i = 1:length(trainingspaces)
    [positiveexamples, negativeexamples] = labeldata(trainingexamples, ...
                                                     trainingspaces{i}, ...
                                                     scale);
    %    plotimages(positiveexamples, negativeexamples, trainingspaces{i});

    tic
    allexamples = [positiveexamples; negativeexamples];
    alllabels = [ones(length(positiveexamples), 1); ...
                 zeros(length(negativeexamples), 1)];

    %    keyboard;
    
    svm_opts = statset('Display', 'iter', 'MaxIter', 50000);
    
    svm_struct = svmtrain(allexamples, alllabels, 'kernel_function', ...
                          'linear', 'options', svm_opts);

    toc
    
    predictions.(trainingspaces{i}) = predict(svm_struct, trainingexamples, ...
                                             trainingspaces{i});
%    
%    for j=1:length(trainingexamples)
%        cimage = trainingexamples(j).(trainingspaces{i});
%        csize = size(cimage);
%        cin = double(resize(squeeze(reshape(cimage, [], 1, 3)), 0.5));
%        keyboard;
%        cout = svmclassify(svm_struct, cin);
%        cout = reshape(cout, csize(1), csize(2));
%        figure(1); clf;
%        imshow(cimage);
%        figure(2); clf;
%        imshow(cout);
%        keyboard;
%    end
%        
end


% tic
% allexamples = [positiveexamples; negativeexamples];
% alllabels = [ones(length(positiveexamples), 1); zeros(length(negativeexamples), 1)];
% nb = NaiveBayes.fit(allexamples, alllabels, 'Prior', 'uniform');
% toc

% imsize = size(trainingexamples(1).(trainingspace));
% tic
% predictions = predict(nb, reshape(trainingexamples(1).(trainingspace), [], 3));
% toc
% labels = reshape(predictions, imsize(1:2));
% imshow(labels);                         % 
% 

