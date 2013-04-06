function [N, X] = radialHist(img, bins)
    
    [pos(:,1), pos(:,2)] = find(img == 1);

    ctr = mean(pos);
    
    edges = edge(img, 'canny');

    [edge_pts(:,1), edge_pts(:,2)] = find(edges == 1);

    edge_pts_ctr = edge_pts - ones(length(edge_pts), 1) * ctr;

    dists = hypot(edge_pts_ctr(:,1), edge_pts_ctr(:,2));
    
    % Normalize so that max dist is 1
    dists = dists / max(dists);

    [N, X] = hist(dists, bins);
    
    figure;
    bar(X,N);

    figure;
    imshow(edges);
    hold on;
    scatter(ctr(2), ctr(1), 'd', 'MarkerFaceColor', 'w');

end