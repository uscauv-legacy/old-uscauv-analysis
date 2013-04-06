function [N, X] = plotHist(img)
    
    tsize = @(x) prod(size(x));
    serialize = @(x) reshape(x, [], 1);

    [N, X] = hist(serialize(img), 4096);

    figure;
    hold on;
    bar(X,N);

end
