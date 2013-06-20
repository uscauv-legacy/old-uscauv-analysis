#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

# def predict():
    
# def update():
    
def main():

    # Constants
    T = 4
    D = T*50
    predict_sigma = .1 
    update_sigma = .1
    real_sigma = 1
     
    # Functions 
    t = np.linspace(0, T, D)
    x = 2*np.pi*t
    z = [y + np.random.normal(0, real_sigma) for y in x] 
    
    mu = [0]
    sigma = [1]

    # print len(z)
        
    for n in range(1, D):
        mu_prior = mu[n-1]
        sigma_prior = sigma[n-1] + predict_sigma
        kalman_gain = sigma_prior/(sigma_prior + update_sigma)
        mu.append(mu_prior + kalman_gain*(z[n] - mu_prior))
        sigma.append((1 - kalman_gain)*sigma_prior)

        
    f, (ax1, ax2) = plt.subplots(2,1)
    ax1.plot(t,x, 'b')
    ax1.plot(t,z, 'g')
    ax1.plot(t,mu, 'r')
    ax2.plot(t, sigma, 'b')

    plt.show()
    


if __name__ == '__main__':
    main()

