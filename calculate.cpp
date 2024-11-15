#include "data_structure.h"
#include "MIA.h"

void buil_TMI_list(TMI_data* TMI_list, residue* residue_list, int residue_number, int full_mode)
{
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].mark == 0) continue;
		
		TMI_list[i].MI_A2BC = (double**)malloc(residue_number*sizeof(double*));
		for (int j = 0; j < residue_number; j++)
		{
			if (residue_list[j].residue_group[1] != 'B') continue;
			
			TMI_list[i].MI_A2BC[j] = (double*)malloc(residue_number*sizeof(double));
			for (int m = 0; m < residue_number; m++)
			{
				TMI_list[i].MI_A2BC[j][m] = -1;
			}
		}
		
		if (full_mode == 1)
		{
			TMI_list[i].MI_AB2C = (double**)malloc(residue_number*sizeof(double*));
			TMI_list[i].MI_AC2B = (double**)malloc(residue_number*sizeof(double*));
			for (int j = 0; j < residue_number; j++)
			{
				if (residue_list[j].residue_group[1] != 'B') continue;
				
				TMI_list[i].MI_AB2C[j] = (double*)malloc(residue_number*sizeof(double));
				TMI_list[i].MI_AC2B[j] = (double*)malloc(residue_number*sizeof(double));
				for (int m = 0; m < residue_number; m++)
				{
					TMI_list[i].MI_AB2C[j][m] = -1;
					TMI_list[i].MI_AC2B[j][m] = -1;
				}
			}
		}
	}
	
	return;
}
void exon_sort(atom* atom_list, residue* residue_list, int frame_number, int residue_number)
{
	double* copy   = (double*)malloc(frame_number*sizeof(double));
	double* sorted = (double*)malloc(frame_number*sizeof(double));
	int*    index  =    (int*)malloc(frame_number*sizeof(int));

	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].mark == 0) continue;
		
		for (int k = 0; k < residue_list[i].atom_number; k++)
		{	
			for (int j = 0; j < frame_number; j++)
			{
				copy[j]  = atom_list[residue_list[i].atom_set[k]].x[j];
				index[j] = j;
			}
			sort_merge<double>(copy, 0, frame_number-1, sorted, index, residue_list[i].index_x_set[k]);
			for (int j = 0; j < frame_number; j++)
			{
				int no                             = residue_list[i].index_x_set[k][j];
				residue_list[i].order_x_set[k][no] = j;
			}
			
			for (int j = 0; j < frame_number; j++)
			{
				copy[j]  = atom_list[residue_list[i].atom_set[k]].y[j];
				index[j] = j;
			}
			sort_merge<double>(copy, 0, frame_number-1, sorted, index, residue_list[i].index_y_set[k]);
			for (int j = 0; j < frame_number; j++)
			{
				int no                             = residue_list[i].index_y_set[k][j];
				residue_list[i].order_y_set[k][no] = j;
			}
			
			for (int j = 0; j < frame_number; j++)
			{
				copy[j]  = atom_list[residue_list[i].atom_set[k]].z[j];
				index[j] = j;
			}
			sort_merge<double>(copy, 0, frame_number-1, sorted, index, residue_list[i].index_z_set[k]);
			for (int j = 0; j < frame_number; j++)
			{
				int no                             = residue_list[i].index_z_set[k][j];
				residue_list[i].order_z_set[k][no] = j;
			}
		}
	}
	
	free(index);
	free(sorted);
	free(copy);
}
double MI_X2Y(atom* atom_list, residue* residue_list, int no_X, int no_Y, int frame_number, int kk)
{
	double MI;
	
	int     atom_number_X = residue_list[no_X].atom_number;
	double**     sample_X = (double**)malloc(3*atom_number_X*sizeof(double*));
	int**         index_X =    (int**)malloc(3*atom_number_X*sizeof(int*));
	int**         order_X =    (int**)malloc(3*atom_number_X*sizeof(int*));
	
	int     atom_number_Y = residue_list[no_Y].atom_number;
	double**     sample_Y = (double**)malloc(3*atom_number_Y*sizeof(double*));
	int**         index_Y =    (int**)malloc(3*atom_number_Y*sizeof(int*));
	int**         order_Y =    (int**)malloc(3*atom_number_Y*sizeof(int*));
	
	for (int k = 0; k < atom_number_X; k++)
	{
		int mm          = residue_list[no_X].atom_set[k];
		sample_X[3*k+0] = atom_list[mm].x;
		sample_X[3*k+1] = atom_list[mm].y;
		sample_X[3*k+2] = atom_list[mm].z;
		index_X[3*k+0]  = residue_list[no_X].index_x_set[k];
		index_X[3*k+1]  = residue_list[no_X].index_y_set[k];
		index_X[3*k+2]  = residue_list[no_X].index_z_set[k];
		order_X[3*k+0]  = residue_list[no_X].order_x_set[k];
		order_X[3*k+1]  = residue_list[no_X].order_y_set[k];
		order_X[3*k+2]  = residue_list[no_X].order_z_set[k];
	}
	for (int k = 0; k < atom_number_Y; k++)
	{
		int mm          = residue_list[no_Y].atom_set[k];
		sample_Y[3*k+0] = atom_list[mm].x;
		sample_Y[3*k+1] = atom_list[mm].y;
		sample_Y[3*k+2] = atom_list[mm].z;
		index_Y[3*k+0]  = residue_list[no_Y].index_x_set[k];
		index_Y[3*k+1]  = residue_list[no_Y].index_y_set[k];
		index_Y[3*k+2]  = residue_list[no_Y].index_z_set[k];
		order_Y[3*k+0]  = residue_list[no_Y].order_x_set[k];
		order_Y[3*k+1]  = residue_list[no_Y].order_y_set[k];
		order_Y[3*k+2]  = residue_list[no_Y].order_z_set[k];
	}
	MI = quick_MI(sample_X, index_X, order_X, sample_Y, index_Y, order_Y, 3*atom_number_X, 3*atom_number_Y, frame_number, kk);
	
	free(sample_X);
	free(index_X);
	free(order_X);
	free(sample_Y);
	free(index_Y);
	free(order_Y);

	return MI;
}
double MI_X2YZ(atom* atom_list, residue* residue_list, int no_X, int no_Y, int no_Z, int frame_number, int kk)
{
	double MI;
	
	int     atom_number_X = residue_list[no_X].atom_number;
	int     atom_number_Y = residue_list[no_Y].atom_number;
	double**     sample_X = (double**)malloc(3*atom_number_X *sizeof(double*));
	int**         index_X =    (int**)malloc(3*atom_number_X *sizeof(int*));
	int**         order_X =    (int**)malloc(3*atom_number_X *sizeof(int*));
	
	int     atom_number_YZ= residue_list[no_Y].atom_number + residue_list[no_Z].atom_number;
	double**     sample_YZ= (double**)malloc(3*atom_number_YZ*sizeof(double*));
	int**         index_YZ=    (int**)malloc(3*atom_number_YZ*sizeof(int*));
	int**         order_YZ=    (int**)malloc(3*atom_number_YZ*sizeof(int*));
	
	for (int k = 0; k < atom_number_X; k++)
	{
		int mm          = residue_list[no_X].atom_set[k];
		sample_X[3*k+0] = atom_list[mm].x;
		sample_X[3*k+1] = atom_list[mm].y;
		sample_X[3*k+2] = atom_list[mm].z;
		index_X[3*k+0]  = residue_list[no_X].index_x_set[k];
		index_X[3*k+1]  = residue_list[no_X].index_y_set[k];
		index_X[3*k+2]  = residue_list[no_X].index_z_set[k];
		order_X[3*k+0]  = residue_list[no_X].order_x_set[k];
		order_X[3*k+1]  = residue_list[no_X].order_y_set[k];
		order_X[3*k+2]  = residue_list[no_X].order_z_set[k];
	}
	for (int k = 0; k < atom_number_Y; k++)
	{
		int mm           = residue_list[no_Y].atom_set[k];
		sample_YZ[3*k+0] = atom_list[mm].x;
		sample_YZ[3*k+1] = atom_list[mm].y;
		sample_YZ[3*k+2] = atom_list[mm].z;
		index_YZ[3*k+0]  = residue_list[no_Y].index_x_set[k];
		index_YZ[3*k+1]  = residue_list[no_Y].index_y_set[k];
		index_YZ[3*k+2]  = residue_list[no_Y].index_z_set[k];
		order_YZ[3*k+0]  = residue_list[no_Y].order_x_set[k];
		order_YZ[3*k+1]  = residue_list[no_Y].order_y_set[k];
		order_YZ[3*k+2]  = residue_list[no_Y].order_z_set[k];
	}
	for (int k = atom_number_Y; k < atom_number_YZ; k++)
	{
		int mm           = residue_list[no_Z].atom_set[k-atom_number_Y];
		sample_YZ[3*k+0] = atom_list[mm].x;
		sample_YZ[3*k+1] = atom_list[mm].y;
		sample_YZ[3*k+2] = atom_list[mm].z;
		index_YZ[3*k+0]  = residue_list[no_Z].index_x_set[k-atom_number_Y];
		index_YZ[3*k+1]  = residue_list[no_Z].index_y_set[k-atom_number_Y];
		index_YZ[3*k+2]  = residue_list[no_Z].index_z_set[k-atom_number_Y];
		order_YZ[3*k+0]  = residue_list[no_Z].order_x_set[k-atom_number_Y];
		order_YZ[3*k+1]  = residue_list[no_Z].order_y_set[k-atom_number_Y];
		order_YZ[3*k+2]  = residue_list[no_Z].order_z_set[k-atom_number_Y];
	}
	MI = quick_MI(sample_X, index_X, order_X, sample_YZ, index_YZ, order_YZ, 3*atom_number_X, 3*atom_number_YZ, frame_number, kk);
	
	free(sample_X);
	free(index_X);
	free(order_X);
	free(sample_YZ);
	free(index_YZ);
	free(order_YZ);

	return MI;
}
void MI_A2B(double** MI_data, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, char* log_file)
{
	FILE *point_to_log = fopen("logfile.log", "a");
	
	int group_number_A = 0;
	int count_A = 0;
	
	for (int i = 0; i < residue_number; i++) if (residue_list[i].residue_group[0] == 'A') group_number_A++;
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].residue_group[0] != 'A') continue;
		count_A++;
		int count_B = 0;
		for (int j = 0; j < residue_number; j++)
		{
			if (residue_list[j].residue_group[1] != 'B') continue;
			count_B++;
			
			double MI;
			
			char log_line[256];
			sprintf(log_line, "MI[A:%s%-4d(%4d/%4d) | B:%s%-4d(%4d/%4d)]\n",
			residue_list[i].residue_type, residue_list[i].residue_no,
			count_A, group_number_A,
			residue_list[j].residue_type, residue_list[j].residue_no,
			count_B, group_number_B);
			fputs(log_line, point_to_log);
			
			if (MI_data[i][j] != -1) continue;
			if (MI_data[j][i] != -1)
			{
				MI_data[i][j] = MI_data[j][i];
				continue;
			}
			
			MI = MI_X2Y(atom_list, residue_list, i, j, frame_number, kk);
			
			if (MI<0) MI = 0;
			MI_data[i][j] = MI;
		}
	}
	
	fclose(point_to_log);
	return;
}
void MI_A2C(double** MI_data, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_C, char* log_file)
{
	FILE *point_to_log = fopen("logfile.log", "a");
	
	int group_number_A = 0;
	int count_A = 0;
	
	for (int i = 0; i < residue_number; i++) if (residue_list[i].residue_group[0] == 'A') group_number_A++;
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].residue_group[0] != 'A') continue;
		count_A++;
		int count_C = 0;
		for (int j = 0; j < residue_number; j++)
		{
			if (residue_list[j].residue_group[2] != 'C') continue;
			count_C++;
			
			double MI;
			
			char log_line[256];
			sprintf(log_line, "MI[A:%s%-4d(%4d/%4d) | C:%s%-4d(%4d/%4d)]\n",
			residue_list[i].residue_type, residue_list[i].residue_no,
			count_A, group_number_A,
			residue_list[j].residue_type, residue_list[j].residue_no,
			count_C, group_number_C);
			fputs(log_line, point_to_log);
			
			if (MI_data[i][j] != -1) continue;
			if (MI_data[j][i] != -1)
			{
				MI_data[i][j] = MI_data[j][i];
				continue;
			}
			
			MI = MI_X2Y(atom_list, residue_list, i, j, frame_number, kk);
			
			if (MI<0) MI = 0;
			MI_data[i][j] = MI;
		}
	}
	
	fclose(point_to_log);
	return;
}
void MI_A2BC(TMI_data* TMI_list, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, int group_number_C, char* log_file)
{
	FILE *point_to_log = fopen("logfile.log", "a");
	
	int group_number_A = 0;
	int count_A = 0;
	
	for (int i = 0; i < residue_number; i++) if (residue_list[i].residue_group[0] == 'A') group_number_A++;
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].residue_group[0] != 'A') continue;
		count_A++;
		int count_B = 0;
		for (int j = 0; j < residue_number; j++)
		{
			if (residue_list[j].residue_group[1] != 'B') continue;
			count_B++;
			int count_C = 0;
			for (int k = 0; k < residue_number; k++)
			{
				if (residue_list[k].residue_group[2] != 'C') continue;
				count_C++;
				double MI;
				
				char log_line[256];
				sprintf(log_line, "MI[A:%s%-4d(%4d/%4d) | B:%s%-4d(%4d/%4d) C:%s%-4d(%4d/%4d)]\n",
				residue_list[i].residue_type, residue_list[i].residue_no,
				count_A, group_number_A,
				residue_list[j].residue_type, residue_list[j].residue_no,
				count_B, group_number_B,
				residue_list[k].residue_type, residue_list[k].residue_no,
				count_C, group_number_C);
				fputs(log_line, point_to_log);
				
				if (residue_list[k].residue_group[1] == 'B')
				{
					if (TMI_list[i].MI_A2BC[k][j] != -1)
					{
						TMI_list[i].MI_A2BC[j][k] = TMI_list[i].MI_A2BC[k][j];
						continue;
					}
				}
				
				MI = MI_X2YZ(atom_list, residue_list, i, j, k, frame_number, kk);
				
				if (MI<0) MI = 0;
				TMI_list[i].MI_A2BC[j][k] = MI;
			}
		}
	}
	
	fclose(point_to_log);
	return;
}
void MI_BC(double** MI_data, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, int group_number_C, char* log_file)
{
	FILE *point_to_log = fopen("logfile.log", "a");
	
	int group_number_A = 0;
	int count_A = 0;
	
	for (int i = 0; i < residue_number; i++) if (residue_list[i].residue_group[0] == 'A') group_number_A++;
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].residue_group[0] != 'A') continue;
		count_A++;
		int count_B = 0;
		for (int j = 0; j < residue_number; j++)
		{
			if (residue_list[j].residue_group[1] != 'B') continue;
			count_B++;
			int count_C = 0;
			for (int k = 0; k < residue_number; k++)
			{
				if (residue_list[k].residue_group[2] != 'C') continue;
				count_C++;
				
				double MI;
				
				char log_line[256];
				sprintf(log_line, "A:%s%-4d(%4d/%4d) : MI[B:%s%-4d(%4d/%4d) | C:%s%-4d(%4d/%4d)]\n",
				residue_list[i].residue_type, residue_list[i].residue_no,
				count_A, group_number_A,
				residue_list[j].residue_type, residue_list[j].residue_no,
				count_B, group_number_B,
				residue_list[k].residue_type, residue_list[k].residue_no,
				count_C, group_number_C);
				fputs(log_line, point_to_log);
				
				if (MI_data[j][k] != -1) continue;
				if (MI_data[k][j] != -1)
				{
					MI_data[j][k] = MI_data[k][j];
					continue;
				}
				
				MI = MI_X2Y(atom_list, residue_list, j, k, frame_number, kk);
				
				if (MI<0) MI = 0;
				MI_data[j][k] = MI;
			}
		}
	}
	
	fclose(point_to_log);
	return;
}
void MI_AB2C(TMI_data* TMI_list, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, int group_number_C, char* log_file)
{
	FILE *point_to_log = fopen("logfile.log", "a");
	
	int group_number_A = 0;
	int count_A = 0;
	
	for (int i = 0; i < residue_number; i++) if (residue_list[i].residue_group[0] == 'A') group_number_A++;
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].residue_group[0] != 'A') continue;
		count_A++;
		int count_B = 0;
		for (int j = 0; j < residue_number; j++)
		{
			if (residue_list[j].residue_group[1] != 'B') continue;
			count_B++;
			int count_C = 0;
			for (int k = 0; k < residue_number; k++)
			{
				if (residue_list[k].residue_group[2] != 'C') continue;
				count_C++;
				
				double MI;
				
				char log_line[256];
				sprintf(log_line, "MI[A:%s%-4d(%4d/%4d) B:%s%-4d(%4d/%4d) | C:%s%-4d(%4d/%4d)]\n",
				residue_list[i].residue_type, residue_list[i].residue_no,
				count_A, group_number_A,
				residue_list[j].residue_type, residue_list[j].residue_no,
				count_B, group_number_B,
				residue_list[k].residue_type, residue_list[k].residue_no,
				count_C, group_number_C);
				fputs(log_line, point_to_log);
				
				if (residue_list[k].residue_group[1] == 'B')
				{
					if (TMI_list[i].MI_AB2C[k][j] != -1)
					{
						TMI_list[i].MI_AB2C[j][k] = TMI_list[i].MI_AB2C[k][j];
						continue;
					}
				}
				
				MI = MI_X2YZ(atom_list, residue_list, k, i, j, frame_number, kk);
				
				if (MI<0) MI = 0;
				TMI_list[i].MI_AB2C[j][k] = MI;
			}
		}
	}
	
	fclose(point_to_log);
	return;
}
void MI_AC2B(TMI_data* TMI_list, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, int group_number_C, char* log_file)
{
	FILE *point_to_log = fopen("logfile.log", "a");
	
	int group_number_A = 0;
	int count_A = 0;
	
	for (int i = 0; i < residue_number; i++) if (residue_list[i].residue_group[0] == 'A') group_number_A++;
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].residue_group[0] != 'A') continue;
		count_A++;
		int count_B = 0;
		for (int j = 0; j < residue_number; j++)
		{
			if (residue_list[j].residue_group[1] != 'B') continue;
			count_B++;
			int count_C = 0;
			for (int k = 0; k < residue_number; k++)
			{
				if (residue_list[k].residue_group[2] != 'C') continue;
				count_C++;
				
				double MI;
				
				char log_line[256];
				sprintf(log_line, "MI[A:%s%-4d(%4d/%4d) C:%s%-4d(%4d/%4d) | B:%s%-4d(%4d/%4d)]\n",
				residue_list[i].residue_type, residue_list[i].residue_no,
				count_A, group_number_A,
				residue_list[k].residue_type, residue_list[k].residue_no,
				count_C, group_number_C,
				residue_list[j].residue_type, residue_list[j].residue_no,
				count_B, group_number_B);
				fputs(log_line, point_to_log);
				
				if (residue_list[k].residue_group[1] == 'B')
				{
					if (TMI_list[i].MI_AC2B[k][j] != -1)
					{
						TMI_list[i].MI_AC2B[j][k] = TMI_list[i].MI_AC2B[k][j];
						continue;
					}
				}
				
				MI = MI_X2YZ(atom_list, residue_list, j, i, k, frame_number, kk);
				
				if (MI<0) MI = 0;
				TMI_list[i].MI_AC2B[j][k] = MI;
			}
		}
	}
	
	fclose(point_to_log);
	return;
}
void calculate_TMI(TMI_data* TMI_list, double** MI_data, residue* residue_list, int residue_number, int full_mode)
{
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].residue_group[0] != 'A') continue;

		TMI_list[i].TMI_A_BC = (double**)malloc(residue_number*sizeof(double*));
		for (int j = 0; j < residue_number; j++)
		{
			if (residue_list[j].residue_group[1] != 'B') continue;
			
			TMI_list[i].TMI_A_BC[j] = (double*)malloc(residue_number*sizeof(double));
			for (int k = 0; k < residue_number; k++)
			{
				if (residue_list[k].residue_group[2] != 'C') continue;
				
				TMI_list[i].TMI_A_BC[j][k] = MI_data[i][j] + MI_data[i][k] - TMI_list[i].MI_A2BC[j][k];
			}
		}
		
		if (full_mode == 1)
		{
			TMI_list[i].TMI_B_AC = (double**)malloc(residue_number*sizeof(double*));
			TMI_list[i].TMI_C_AB = (double**)malloc(residue_number*sizeof(double*));
			TMI_list[i].A4BC     = (double**)malloc(residue_number*sizeof(double*));
			TMI_list[i].B4AC     = (double**)malloc(residue_number*sizeof(double*));
			TMI_list[i].C4AB     = (double**)malloc(residue_number*sizeof(double*));
			for (int j = 0; j < residue_number; j++)
			{
				if (residue_list[j].residue_group[1] != 'B') continue;
				
				TMI_list[i].TMI_B_AC[j] = (double*)malloc(residue_number*sizeof(double));
				TMI_list[i].TMI_C_AB[j] = (double*)malloc(residue_number*sizeof(double));
				TMI_list[i].A4BC[j]     = (double*)malloc(residue_number*sizeof(double));
				TMI_list[i].B4AC[j]     = (double*)malloc(residue_number*sizeof(double));
				TMI_list[i].C4AB[j]     = (double*)malloc(residue_number*sizeof(double));
				for (int k = 0; k < residue_number; k++)
				{
					if (residue_list[k].residue_group[2] != 'C') continue;
					
					TMI_list[i].TMI_B_AC[j][k] = MI_data[i][j] + MI_data[j][k] - TMI_list[i].MI_AC2B[j][k];
					TMI_list[i].TMI_C_AB[j][k] = MI_data[i][k] + MI_data[j][k] - TMI_list[i].MI_AB2C[j][k];
					TMI_list[i].A4BC[j][k] = 0;
					TMI_list[i].B4AC[j][k] = 0;
					TMI_list[i].C4AB[j][k] = 0;
					if (MI_data[j][k] != 0) TMI_list[i].A4BC[j][k] = TMI_list[i].TMI_A_BC[j][k] / MI_data[j][k];
					if (MI_data[i][k] != 0) TMI_list[i].B4AC[j][k] = TMI_list[i].TMI_B_AC[j][k] / MI_data[i][k];
					if (MI_data[i][j] != 0) TMI_list[i].C4AB[j][k] = TMI_list[i].TMI_C_AB[j][k] / MI_data[i][j];
				}
			}
		}
	}
}