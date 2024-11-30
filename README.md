# C program for numerical integration
## Algorithm
1. Print the given function - integrand
2. Read the ends of the integration interval and the desired accuracy from user
3. Ask user which method of integration to use: rectangle rule, trapezoidal rule or Simpson's rule
4. Calculate I2 at h = (b - a) / 2
5. Until the desired accuracy is reached:
   1. I1 = I2
   2. Reduce h by half
   3. Calculate I2
   4. Calculate integration error using Runge's rule
6. Print results (integral = I1)
