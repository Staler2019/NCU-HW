function bino = binomial(k,n,p)
    bino = binomial_coefficients(n,k) * p^k * (1-p)^(n-k);
end