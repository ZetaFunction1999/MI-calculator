
# Mutual information calculator for residues in molecular dynamics simulation trajectories
## Preface
The initial version of this program was developed in May 2021. At the time, I was an undergraduate student working on a research project to explore the allosteric effects of thrombin. I wanted to calculate the amount of mutual information between residues in the MD trajectories for interaction analysis. However, no open source program could be found to calculate MI between variables of arbitrary dimension, which meant that only the MI of Cα atoms could be calculated. This program was developed in order to calculate the number of all-atom mutual information between two residues. After several versions of the improvement, the efficiency of the core algorithm has been optimized to the extreme. Given the limited energy and ability of the developers, the usability of the program for the public is not good. Feedback is welcome.

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

The details of the algorithm can be found in `PHYSICAL REVIEW E 69, 066138 (2004)`. The time complexity of the algorithm is $O(N^2)$.

## How to use this program?
This program is written by C++. To compile this program, one should make sure the boost library (https://www.boost.org/) has already been installed.
```
g++ -o MIcalc calculate.cpp data_structure.h MIA.h main.cpp mutual_information.cpp readin.cpp -lboost_system -w -fopenmp
```
This program is based on OpenMP to achieve multi-core parallelization. The number of parallel threads can be set in the following ways:
```
export OMP_NUM_THREADS=10
```
Before the calculation, the MD trajectory needs to be split into mutiple pdb files. Each pdb file refers a single frame and its name should be *{Number of frame}.pdb*. (See the example folder). After the preparation, run the following command to start the calculation:
```
./MIcalc -i example/pdbs/1.pdb -d example/pdbs/ -o test.out -rgA 33,136,190,215,38,145 -rgB 50,20,221,223,307,78 -rgC 46,320,110 -bf 10 -ef 1000 -fs 10
```
One can check the MI results in *test.out*.

## The meaning of each parameter
- ```example/pdbs/1.pdb```: The name of the index file. The index file should have exactly the same atom name and atom number of those of data files.
- ```-d example/pdbs/```: The directory of data files. Data files should be spilt from MD trajectories.
- ```-o test.out```: Name of the output file.
- ```-rgA 1,4,7,10-12```: Residues contained in Group A.
- ```-rgB 2,5,8,13-15```: Residues contained in Group B. MI between two members of group A and group B will be caculated.
- ```-rgC 3,6,9,16-18```: Residues contained in Group C. If specified, ternary mutual information of group A, B and C will be caculated.
- ```-bf 10```: Start frame.
- ```-ef 1000```: End frame.
- ```-fs 10```: Frame step. The calculation time is proportional to the square of the total number of frames.
- ```-fm 1```: File format. 0 refers to *pdb.{Number of frame}*, while 1 refers to *{Number of frame}.pdb*.
