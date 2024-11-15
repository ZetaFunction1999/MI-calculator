#include "data_structure.h"
#include "MIA.h"
#include <boost/math/special_functions/digamma.hpp>
#include <boost/math/special_functions/gamma.hpp>

struct sorted_point
{
	int order;
	int d;
	int up_or_down;
	char type;
};


double Kraskov_n(int* n_x, int* n_y, int no, double** sample_x, double** sample_y, int** index_x, int** order_x, int** index_y, int** order_y, int dimension_x, int dimension_y, int sample_size, int k)
{
	*n_x = 0;
	*n_y = 0;
	double epsilon = 0;
	int counts = 0;
	double value = 0;
	
	priority_queue<double, sorted_point> delta_list(2*(dimension_x+dimension_y));
	for (int i = 0; i < dimension_x; i++)
	{
		int order_x_tmp = order_x[i][no];
		if (order_x_tmp != 0)
		{
			int index_up = index_x[i][order_x_tmp-1];
			sorted_point st_up;
			st_up.type = 'x';
			st_up.d = i;
			st_up.up_or_down = -1;
			st_up.order = order_x_tmp - 1;
			value = -fabs(sample_x[i][no] - sample_x[i][index_up]);
			delta_list.come(value, st_up);
		}
		if (order_x_tmp != sample_size-1)
		{
			int index_down = index_x[i][order_x_tmp+1];
			sorted_point st_down;
			st_down.type = 'x';
			st_down.d = i;
			st_down.up_or_down = 1;
			st_down.order = order_x_tmp + 1;
			value = -fabs(sample_x[i][no] - sample_x[i][index_down]);
			delta_list.come(value, st_down);
		}
	}
	for (int i = 0; i < dimension_y; i++)
	{
		int order_y_tmp = order_y[i][no];
		if (order_y_tmp != 0)
		{
			int index_up = index_y[i][order_y_tmp-1];
			sorted_point st_up;
			st_up.type = 'y';
			st_up.d = i;
			st_up.up_or_down = -1;
			st_up.order = order_y_tmp - 1;
			value = -fabs(sample_y[i][no] - sample_y[i][index_up]);
			delta_list.come(value, st_up);
		}
		if (order_y_tmp != sample_size-1)
		{
			int index_down = index_y[i][order_y_tmp+1];
			sorted_point st_down;
			st_down.type = 'y';
			st_down.d = i;
			st_down.up_or_down = 1;
			st_down.order = order_y_tmp + 1;
			value = -fabs(sample_y[i][no] - sample_y[i][index_down]);
			delta_list.come(value, st_down);
		}
	}
	
	int* hits_x = (int*)malloc(sample_size*sizeof(int));
	int* hits_y = (int*)malloc(sample_size*sizeof(int));
	for (int i = 0; i < sample_size; i++)
	{
		hits_x[i] = 0;
		hits_y[i] = 0;
	}
	
	sorted_point outcome;
	
	while (counts < k)
	{
		delta_list.leave(&epsilon, &outcome);
		if (outcome.type == 'x')
		{
			int i = outcome.d;
			int index_hits;
			index_hits = index_x[i][outcome.order];
			if (outcome.up_or_down == -1)
			{
				outcome.order--;
				if (outcome.order != -1)
				{
					int index_up = index_x[i][outcome.order];
					value = -fabs(sample_x[i][no] - sample_x[i][index_up]);
					delta_list.come(value, outcome);
				}
			}
			if (outcome.up_or_down == 1)
			{
				outcome.order++;
				if (outcome.order != sample_size)
				{
					int index_down = index_x[i][outcome.order];
					value = -fabs(sample_x[i][no] - sample_x[i][index_down]);
					delta_list.come(value, outcome);
				}
			}
			
			hits_x[index_hits]++;
			if ((hits_x[index_hits] == dimension_x))
			{
				(*n_x) = (*n_x) + 1;
				if (hits_y[index_hits] == dimension_y)
				{
					counts++;
				}
			}
		}
		if (outcome.type == 'y')
		{
			int i = outcome.d;
			int index_hits;
			index_hits = index_y[i][outcome.order];
			if (outcome.up_or_down == -1)
			{
				outcome.order--;
				if (outcome.order != -1)
				{
					int index_up = index_y[i][outcome.order];
					value = -fabs(sample_y[i][no] - sample_y[i][index_up]);
					delta_list.come(value, outcome);
				}
			}
			if (outcome.up_or_down == 1)
			{
				outcome.order++;
				if (outcome.order != sample_size)
				{
					int index_down = index_y[i][outcome.order];
					value = -fabs(sample_y[i][no] - sample_y[i][index_down]);
					delta_list.come(value, outcome);
				}
			}
			
			hits_y[index_hits]++;
			if ((hits_y[index_hits] == dimension_y))
			{
				(*n_y) = (*n_y) + 1;
				if (hits_x[index_hits] == dimension_x)
				{
					counts++;
				}
			}
		}
	}
	
	if (outcome.type == 'y') (*n_x) = (*n_x) + 1;
	if (outcome.type == 'x') (*n_y) = (*n_y) + 1;

	free(hits_x);  
	free(hits_y);
	
	return -epsilon;
};

double mutual_information(double** sample_x, double** sample_y, int dimension_x, int dimension_y, int sample_size, int k)
{
	double MI = 0;
	double HX = 0;
	double HY = 0;
	
	double log_e = 0;
	
	double* sorted = (double*)malloc(sample_size*sizeof(double));
	int* index = (int*)malloc(sample_size*sizeof(int));
	
	int** index_x = (int**)malloc(dimension_x*sizeof(int*));
	int** order_x = (int**)malloc(dimension_x*sizeof(int*));
	for (int i = 0; i < dimension_x; i++)
	{
		index_x[i] = (int*)malloc(sample_size*sizeof(int));
		double* copy_x = (double*)malloc(sample_size*sizeof(double));
		for (int j = 0; j < sample_size; j++) copy_x[j] = sample_x[i][j];
		for (int j = 0; j < sample_size; j++) index[j] = j;
		sort_merge<double>(copy_x, 0, sample_size-1, sorted, index, index_x[i]);
		order_x[i] = (int*)malloc(sample_size*sizeof(int));
		for (int j = 0; j < sample_size; j++)
		{
			int no = index_x[i][j];
			order_x[i][no] = j;
		}
		free(copy_x);
	}
	
	int** index_y = (int**)malloc(dimension_y*sizeof(int*));
	int** order_y = (int**)malloc(dimension_x*sizeof(int*));
	for (int i = 0; i < dimension_y; i++)
	{
		index_y[i] = (int*)malloc(sample_size*sizeof(int));
		double* copy_y = (double*)malloc(sample_size*sizeof(double));
		for (int j = 0; j < sample_size; j++) copy_y[j] = sample_y[i][j];
		for (int j = 0; j < sample_size; j++) index[j] = j;
		sort_merge<double>(copy_y, 0, sample_size-1, sorted, index, index_y[i]);
		order_y[i] = (int*)malloc(sample_size*sizeof(int));
		for (int j = 0; j < sample_size; j++)
		{
			int no = index_y[i][j];
			order_y[i][no] = j;
		}
		free(copy_y);
	}
	
	for (int iii = 0; iii < sample_size; iii++)
	{
		printf("#%3d %3.3f %3.3f %3d %3d\n",iii,
		sample_x[0][iii], sample_x[0][index_x[0][iii]], index_x[0][iii], order_x[0][iii]);
	}
	HX = quick_H(sample_x, index_x, order_x, dimension_x, sample_size, k);
	printf("HX=%f k=%d\n", HX, k);
	
	for (int iii = 0; iii < sample_size; iii++)
	{
		printf("#%3d %.3f %.3f %3d %3d\n",iii,
		sample_y[0][iii], sample_y[0][index_y[0][iii]], index_y[0][iii], order_y[0][iii]);
	}
	HY = quick_H(sample_y, index_y, order_y, dimension_y, sample_size, k);
	printf("HY=%f k=%d\n", HY, k);
	
	double** ss = (double**)malloc(2*sizeof(double*));
	int** ii = (int**)malloc(2*sizeof(int*));
	int** oo = (int**)malloc(2*sizeof(int*));
	ss[0]=sample_x[0];
	ss[1]=sample_y[0];
	ii[0]=index_x[0];
	ii[1]=index_y[0];
	oo[0]=order_x[0];
	oo[1]=order_y[0];
	double XY = quick_H(ss, ii, oo, 2, sample_size, k);
	printf("XY=%f HX+HY-XY=%f k=%d\n", XY, HX+HY-XY, k);
	//getchar();
	
	double digamma_nx = 0;
	double digamma_ny = 0;
	int* n_x = (int*)malloc(sample_size*sizeof(int));
	int* n_y = (int*)malloc(sample_size*sizeof(int));
	for (int i = 0; i < sample_size; i++)
	{
		int tmp_x = 0;
		int tmp_y = 0;
		
		double epsilon = Kraskov_n(&tmp_x, &tmp_y, i, sample_x, sample_y, index_x, order_x, index_y, order_y, dimension_x, dimension_y, sample_size, k);
		n_x[i] = tmp_x;
		n_y[i] = tmp_y;
		printf("n_x=%d n_y=%d\n", tmp_x, tmp_y);
		
		log_e += log(epsilon);
		
		digamma_nx += boost::math::digamma(n_x[i]);
		digamma_ny += boost::math::digamma(n_y[i]);
	}
	
	MI = boost::math::digamma(k) + boost::math::digamma(sample_size) - digamma_nx/sample_size - digamma_ny/sample_size;
	//HX = boost::math::digamma(sample_size) - digamma_nx/sample_size + log_e*dimension_x/sample_size;
	//HY = boost::math::digamma(sample_size) - digamma_ny/sample_size + log_e*dimension_y/sample_size;
	
	printf("+>~$# HX=%f HY=%f #$~>+\n", HX, HY);

	free(n_x);
	free(n_y);
	
	for (int i = 0; i < dimension_x; i++)
	{
		free(index_x[i]);
		free(order_x[i]);
	}
	free(index_x);
	free(order_x);
	for (int i = 0; i < dimension_y; i++)
	{
		free(index_y[i]);
		free(order_y[i]);
	}
	free(index_y);
	free(order_y);
	
	free(sorted);
	free(index);

	return MI;
}

double quick_MI(double** sample_x, int** index_x, int** order_x, double** sample_y, int** index_y, int** order_y, int dimension_x, int dimension_y, int sample_size, int k)
{
	double MI = 0;
	
	double digamma_nx = 0;
	double digamma_ny = 0;
	int* n_x = (int*)malloc(sample_size*sizeof(int));
	int* n_y = (int*)malloc(sample_size*sizeof(int));
	
	
	#pragma omp parallel for
	for (int i = 0; i < sample_size; i++)
	{
		int tmp_x = 0;
		int tmp_y = 0;
		
		Kraskov_n(&tmp_x, &tmp_y, i, sample_x, sample_y, index_x, order_x, index_y, order_y, dimension_x, dimension_y, sample_size, k);
		n_x[i] = tmp_x;
		n_y[i] = tmp_y;
	}
	
	for (int i = 0; i < sample_size; i++)
	{
		digamma_nx += boost::math::digamma(n_x[i]);
		digamma_ny += boost::math::digamma(n_y[i]);
	}
	
	MI = boost::math::digamma(k) + boost::math::digamma(sample_size) - digamma_nx/sample_size - digamma_ny/sample_size;
	
	free(n_x);
	free(n_y);

	return MI;
}

double quick_NMI(double** sample_x, int** index_x, int** order_x, double** sample_y, int** index_y, int** order_y, int dimension_x, int dimension_y, int sample_size, int k)
{	
	double MI = 0;
	double HX = 0;
	double HY = 0;
	
	double NMI = 0;
	
	double digamma_nx = 0;
	double digamma_ny = 0;
	double log_e = 0;
	int* n_x = (int*)malloc(sample_size*sizeof(int));
	int* n_y = (int*)malloc(sample_size*sizeof(int));
	double* epslion = (double*)malloc(sample_size*sizeof(double));
	
	for (int i = 0; i < sample_size; i++)
	{
		int tmp_x = 0;
		int tmp_y = 0;
		
		epslion[i] = Kraskov_n(&tmp_x, &tmp_y, i, sample_x, sample_y, index_x, order_x, index_y, order_y, dimension_x, dimension_y, sample_size, k);
		n_x[i] = tmp_x;
		n_y[i] = tmp_y;
		
		digamma_nx += boost::math::digamma(n_x[i]);
		digamma_ny += boost::math::digamma(n_y[i]);
		log_e += log(epslion[i]);
	}
	
/* 	double pi = 3.1415926535898;
	double cx = pow(pi, dimension_x/2)/pow(2, dimension_x/2);
	cx /= boost::math::tgamma(1 + dimension_x/2);
	double cy = pow(pi, dimension_y/2)/pow(2, dimension_y/2);
	cy /= boost::math::tgamma(1 + dimension_y/2); */
	
	MI = boost::math::digamma(k) + boost::math::digamma(sample_size) - digamma_nx/sample_size - digamma_ny/sample_size;
	HX = boost::math::digamma(sample_size) - digamma_nx/sample_size + log_e*dimension_x/sample_size;
	HY = boost::math::digamma(sample_size) - digamma_ny/sample_size + log_e*dimension_y/sample_size;

	free(n_x);
	free(n_y);
	free(epslion);
	
	return 2*MI/(HX+HY);
}

double get_epsilon(int no, double** sample, int** index, int** order, int dimension, int sample_size, int k)
{
	double epsilon = 0;
	int counts = 0;
	double value = 0;
	
	priority_queue<double, sorted_point> delta_list(2*dimension);
	for (int i = 0; i < dimension; i++)
	{
		int order_tmp = order[i][no];
		if (order_tmp != 0)
		{
			int index_up = index[i][order_tmp-1];
			sorted_point st_up;
			st_up.d = i;
			st_up.up_or_down = -1;
			st_up.order = order_tmp - 1;
			value = -fabs(sample[i][no] - sample[i][index_up]);
			delta_list.come(value, st_up);
		}
		if (order_tmp != sample_size-1)
		{
			int index_down = index[i][order_tmp+1];
			sorted_point st_down;
			st_down.d = i;
			st_down.up_or_down = 1;
			st_down.order = order_tmp + 1;
			value = -fabs(sample[i][no] - sample[i][index_down]);
			delta_list.come(value, st_down);
		}
	}
	
	int* hits = (int*)malloc(sample_size*sizeof(int));
	for (int i = 0; i < sample_size; i++) hits[i] = 0;
	
	sorted_point outcome;
	
	while (counts < k)
	{
		delta_list.leave(&epsilon, &outcome);
		
		int i = outcome.d;
		int index_hits;
		index_hits = index[i][outcome.order];
		
		if (outcome.up_or_down == -1)
		{
			outcome.order--;
			if (outcome.order != -1)
			{
				int index_up = index[i][outcome.order];
				value = -fabs(sample[i][no] - sample[i][index_up]);
				delta_list.come(value, outcome);
			}
		}
		if (outcome.up_or_down == 1)
		{
			outcome.order++;
			if (outcome.order != sample_size)
			{
				int index_down = index[i][outcome.order];
				value = -fabs(sample[i][no] - sample[i][index_down]);
				delta_list.come(value, outcome);
			}
		}
		
		hits[index_hits]++;
		if ((hits[index_hits] == dimension)) counts++;
	}

	free(hits); 
	
	return -2*epsilon;
}

double quick_H(double** sample, int** index, int** order, int dimension, int sample_size, int k)
{
	double H = 0;
	double log_e;
	
	for (int i = 0; i < sample_size; i++)
	{
		double epsilon = get_epsilon(i, sample, index, order, dimension, sample_size, k);
		log_e += log(epsilon);
	}
	
	H = -boost::math::digamma(k) + boost::math::digamma(sample_size) + log_e*dimension/sample_size;

	return H;
}

