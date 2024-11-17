# Mutual information calculator for residues in molecular dynamics simulation trajectories
## Introduction
Mutual information (MI) measures the independence of two random variables by its information theoretical background. Unlike other linear correlation coefficients, MI is sensitive also to dependences which do not manifest themselves in the covariance. MI equals to zero if and only if the two random variables are strictly independent. For a random variable $Z=(X,Y)$ with probability distribution function $f(x,y)$, (here $X$ and $Y$ can be multi-dimensional variables), the MI between variables $X$ and $Y$ is defined as:

$$
I(X, Y)=\iint d x d y f(x, y) \log \frac{f(x, y)}{f_x(x) f_y(y)}
$$


Correlated motions in biomolecules are often essential for allosteric signal transduction or thermodynamic energy transport. Since correlated motions are difficult to access experimentally, they are usually analyzed from molecular dynamics (MD) simulations trajectories via calculation of the covariance matrix. The research `PROTEINS: Structure, Function, and Bioinformatics 62:1053–1061 (2006)` found that linear correlations miss the nonlinear correlations, which were perfectly captured by MI. The definition of MI can be generalized to higher dimensions, which means that correlations between groups of atoms can also be quantified.

Regardless of such advantages of MI, estimating MI between two continuous variables from a set of discrete sample points is not easy. This program uses the algorithm proposed by Kraskov in 2005:

$$
I(X, Y)=\psi(k)-\left\langle\psi\left(n_x+1\right)+\psi\left(n_y+1\right)\right\rangle+\psi(N)
$$

The details of the algorithm can be found in `PHYSICAL REVIEW E 69, 066138 (2004)`.

## How to use this program?
This program is written by C++. To compile this program, one should make sure the boost library (https://www.boost.org/) has already been installed.
```
g++
```
