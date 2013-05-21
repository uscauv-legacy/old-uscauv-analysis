function mdata = getStats(v)

    mv = mean(v);

    vm = v - ones(length(v),1) * mv;

    kv = cov(v);
    
    [E, L] = eig(kv);

    cval = E(:, find(diag(L) == max(diag(L))));
    
    if cval(1) < 0
        cval = cval * -1;
        E = E * -1;
    end

    theta = atan2(cval(2), cval(1));

    mdata.mean = mv;
    mdata.cov = kv;
    mdata.pa = E;
    mdata.sv = sqrt(L);
    mdata.theta = theta;
    mdata.rmax = max(hypot(vm(:,1), vm(:,2)));

end