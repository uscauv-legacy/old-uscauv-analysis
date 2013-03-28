function [predictions] = predict(svm_struct, trainingexamples, ...
                                 trainingspace)
    for j=1:length(trainingexamples)
        cimage = imresize(trainingexamples(j).(trainingspace), 0.5);
        csize = size(cimage);
        cin = double(squeeze(reshape(cimage, [], 1, 3)));
        tic
        cout = svmclassify(svm_struct, cin);
        toc
        cout = reshape(cout, csize(1), csize(2));
        figure(1); clf;
        imshow(cimage);
        figure(2); clf;
        imshow(cout);

        predictions{j} = cout;

        keyboard;
    end
    
end