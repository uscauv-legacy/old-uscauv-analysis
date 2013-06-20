#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

# def predict():
    
# def update():



    
def main():

    # Constants
    T = 5
    D = T*50
    I = np.matrix(np.identity(2))
    predict_sigma = 1
    update_sigma = 10000
    real_sigma = .5
    initial_sigma = np.matrix([[10,0],[0,50000]])
     
    # Functions 
    t = np.linspace(0, T, D)
    x = np.sin(2*np.pi*t) 
    z = [y + np.random.normal(0, real_sigma) for y in x] 

    mu = [0]
    muv = [0]
    sigma = I*initial_sigma
    mus = np.matrix([mu,muv])

    A = np.matrix([[1,1],[0,1]])
    C = np.matrix([[1,0]])
    R = I*predict_sigma
    Q = np.matrix(update_sigma)

    sigmax = [0]
    sigmav = [0]
            
    for n in range(1, D):
        
        mu_prior = A*mus
        sigma_p = A*sigma*A.transpose() + R
     
        kalman_gain = sigma_p*C.transpose()*np.linalg.inv(C*sigma_p*C.transpose() + Q)
        z_vec = np.matrix(z[n])

        mus = mu_prior + kalman_gain*(z_vec - C*mu_prior)
        sigma = (I - kalman_gain*C)*sigma_p
        
        mu.append(mus[0])
        muv.append(mus[1])
        sigmax.append(sigma[0,0])
        sigmav.append(sigma[1,1])
        # mu.append(mu_prior + kalman_gain*(z[n] - mu_prior))
        # sigma.append((1 - kalman_gain)*sigma_prior)
        # TODO: Append to mu and muv
        
    f, (ax1, ax2) = plt.subplots(2,1)
    ax1.plot(t,x, 'b')
    ax1.plot(t,z, 'g')
    ax1.plot(t,mu, 'r')
    ax1.plot(t, muv, 'b')
    ax2.plot(t,sigmax, 'b')
    ax2.plot(t,sigmav, 'g')

    plt.show()
    


if __name__ == '__main__':
    main()

