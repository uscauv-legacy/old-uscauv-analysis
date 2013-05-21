function [] = scatterImage(v, dim)

    rows = dim(1); cols = dim(2);

    nv = length(v);
    
    kv = cov(v);
    
    [E, L] = eig(kv);

    if E(1, find(diag(L) == max(diag(L)))) < 0
        E = E * -1;
    end
    
    % Principal axes
    pc = E*sqrt(L);
    
    hold on;
    scatter(v(:,1), v(:,2));
    
    quiver(zeros(1,2), zeros(1,2), pc(1,:), pc(2,:));
    
    axis( [-cols/2 cols/2 -rows/2 rows/2] );

end