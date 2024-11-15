#include "MIA.h"

bool string_compare(char* string_1, char* string_2, int start_1, int start_2, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (string_1[start_1+i] != string_2[start_2+i]) return 0;
	}
	return 1;
}
double string_to_double(char* string, int start, int end)
{
	double result = 0;
	char number[16];
	for (int i = start; i <= end; i++) number[i-start] = string[i];
	number[end-start+1] = '\0';
	result = atof(number);
	return result;
}
void read_index(char* index_file, atom* atom_list_tmp, residue* residue_list_tmp, int* atom_number, int* residue_number)
{
	int a_n = 0;
	int r_n = 0;
	
	for (int i = 0; i < 9999; i++)
	{
		atom_list_tmp[i].mark = 9999;
		residue_list_tmp[i].atom_number = 0;
	}
	
	FILE *point_to_index = fopen(index_file, "r");
	if (point_to_index == NULL)
	{
		printf("Erro: Cannot open index file %s.", index_file);
		exit(1);
	}
	
	char line[128];
	int residue_no_tmp = 0;
	for (int i = 0; i < 128; i++) line[i] = ' ';
	char atom_residue_no[5];
	while (feof(point_to_index) == 0)
	{
		fgets(line, 128, point_to_index);
		if (!string_compare(line, "ATOM", 0, 0, 4)) continue;
		
		atom_residue_no[0] = line[22];
		atom_residue_no[1] = line[23];
		atom_residue_no[2] = line[24];
		atom_residue_no[3] = line[25];
		atom_residue_no[4] = '\0';
		residue_no_tmp = atoi(atom_residue_no);
		
		atom_list_tmp[a_n].atom_type = line[80];
		atom_list_tmp[a_n].residue_no = residue_no_tmp;
		atom_list_tmp[a_n].mark = 0;
		residue_list_tmp[residue_no_tmp].residue_no = residue_no_tmp;
		residue_list_tmp[residue_no_tmp].residue_type[0] = line[17];
		residue_list_tmp[residue_no_tmp].residue_type[1] = line[18];
		residue_list_tmp[residue_no_tmp].residue_type[2] = line[19];
		residue_list_tmp[residue_no_tmp].residue_type[3] = '\0';
		residue_list_tmp[residue_no_tmp].chain = line[21];
		if (residue_list_tmp[residue_no_tmp].atom_number == 0) r_n++;
		(residue_list_tmp[residue_no_tmp].atom_number)++;
		
		a_n++;
	}
	
	*atom_number = a_n;
	*residue_number = r_n;
	
	fclose(point_to_index);
	
	return;
}
void build_list(atom* atom_list, residue* residue_list, atom* atom_list_tmp, residue* residue_list_tmp)
{
	int a_n = 0;
	int r_n = 0;
	
	for (int i = 0; i < 9999; i++)
	{
		if (residue_list_tmp[i].atom_number == 0) continue;
		
		residue_list[r_n].residue_no = i;
		residue_list[r_n].residue_type[0]=residue_list_tmp[i].residue_type[0];
		residue_list[r_n].residue_type[1]=residue_list_tmp[i].residue_type[1];
		residue_list[r_n].residue_type[2]=residue_list_tmp[i].residue_type[2];
		residue_list[r_n].residue_type[3]=residue_list_tmp[i].residue_type[3];
		residue_list[r_n].chain = residue_list_tmp[i].chain;
		residue_list[r_n].atom_number = 0;
		residue_list[r_n].mark = 0;
		residue_list_tmp[i].mark = r_n;
		
		r_n++;
	}
	for (int i = 0; i < 9999; i++)
	{
		if (atom_list_tmp[i].mark == 9999) continue;
		
		atom_list[a_n].atom_type = atom_list_tmp[i].atom_type;
		int residue_no_tmp = residue_list_tmp[atom_list_tmp[i].residue_no].mark;
		atom_list[a_n].residue_no = residue_no_tmp;
		atom_list[a_n].mark = 0;
		(residue_list[residue_no_tmp].atom_number)++;
		
		a_n++;
	}
	
	return;
}
void mark_residue(residue* residue_list, int residue_number, char* residue_group_A, char* residue_group_B, char* residue_group_C)
{
	int number_A = 2;
	int number_B = 2;
	int number_C = 2;
	char default_A[] = "?";
	char default_B[] = "?";
	char default_C[] = "?";
	if (residue_group_A == NULL) residue_group_A = default_A;
	if (residue_group_B == NULL) residue_group_B = default_B;
	if (residue_group_C == NULL) residue_group_C = default_C;
	for (int i = 0; i < strlen(residue_group_A); i++)
	{
		if (residue_group_A[i] == ',') number_A++;
	}
	for (int i = 0; i < strlen(residue_group_B); i++)
	{
		if (residue_group_B[i] == ',') number_B++;
	}
	for (int i = 0; i < strlen(residue_group_C); i++)
	{
		if (residue_group_C[i] == ',') number_C++;
	}
	char** residue_set_A = (char**)malloc(number_A*sizeof(char*));
	char** residue_set_B = (char**)malloc(number_B*sizeof(char*));
	char** residue_set_C = (char**)malloc(number_C*sizeof(char*));
	char* ptrA = NULL;
	char* ptrB = NULL;
	char* ptrC = NULL;
	number_A = 0;
	number_B = 0;
	number_C = 0;
	while ((residue_set_A[number_A] = strtok_r(residue_group_A, ",", &ptrA)) != NULL)
	{
		number_A++;
		residue_group_A = NULL;
	}
	while ((residue_set_B[number_B] = strtok_r(residue_group_B, ",", &ptrB)) != NULL)
	{
		number_B++;
		residue_group_B = NULL;
	}
	while ((residue_set_C[number_C] = strtok_r(residue_group_C, ",", &ptrC)) != NULL)
	{
		number_C++;
		residue_group_C = NULL;
	}
	for (int i = 0; i < residue_number; i++)
	{
		residue_list[i].mark = 0;
		residue_list[i].residue_group[0] = ' ';
		residue_list[i].residue_group[1] = ' ';
		residue_list[i].residue_group[2] = ' ';
		
		for (int j = 0; j < number_A; j++)
		{
			if (residue_set_A[j][0] == '?')
			{
				residue_list[i].mark++;
				residue_list[i].residue_group[0] = 'A';
				break;
			}
			if (residue_set_A[j][0] == '%')
			{
				if (strlen(residue_set_A[j]) == 1)
				{
					printf("Erro: Incorrect input of -rgA.\n");
					exit(1);
				}
				if (residue_set_A[j][1] == residue_list[i].chain)
				{
					residue_list[i].mark++;
					residue_list[i].residue_group[0] = 'A';
					break;
				}
			}
			if (residue_list[i].residue_no == atoi(residue_set_A[j]))
			{
				residue_list[i].mark++;
				residue_list[i].residue_group[0] = 'A';
				break;
			}
		}
		for (int j = 0; j < number_B; j++)
		{
			if (residue_set_B[j][0] == '?')
			{
				residue_list[i].mark++;
				residue_list[i].residue_group[1] = 'B';
				break;
			}
			if (residue_set_B[j][0] == '%')
			{
				if (strlen(residue_set_B[j]) == 1)
				{
					printf("Erro: Incorrect input of -rgB.\n");
					exit(1);
				}
				if (residue_set_B[j][1] == residue_list[i].chain)
				{
					residue_list[i].mark++;
					residue_list[i].residue_group[1] = 'B';
					break;
				}
			}
			if (residue_list[i].residue_no == atoi(residue_set_B[j]))
			{
				residue_list[i].mark++;
				residue_list[i].residue_group[1] = 'B';
				break;
			}
		}
		for (int j = 0; j < number_C; j++)
		{
			if (residue_set_C[j][0] == '%')
			{
				if (strlen(residue_set_C[j]) == 1)
				{
					printf("Erro: Incorrect input of -rgC.\n");
					exit(1);
				}
				if (residue_set_C[j][1] == residue_list[i].chain)
				{
					residue_list[i].mark++;
					residue_list[i].residue_group[2] = 'C';
					break;
				}
			}
			if (residue_list[i].residue_no == atoi(residue_set_C[j]))
			{
				residue_list[i].mark++;
				residue_list[i].residue_group[2] = 'C';
				break;
			}
		}
	}
	
	return;
}
void mark_atom(atom* atom_list, residue* residue_list, int atom_number, int residue_number, char* atom_select)
{
	if (atom_select == NULL) goto atom_select_default;
	if (strstr(atom_select, "in") != NULL)
	{
		for (int i = 0; i < atom_number; i++)
		{
			int residue_no = atom_list[i].residue_no;
			if (atom_list[i].atom_type == '&')
			{
				atom_list[i].mark = 1;
			}
			else
			{
				residue_list[residue_no].atom_number--;
				atom_list[i].mark = 0;
			}
		}
		
		return;
	}
	if (strstr(atom_select, "out") != NULL)
	{
		for (int i = 0; i < atom_number; i++)
		{
			int residue_no = atom_list[i].residue_no;
			if (atom_list[i].atom_type == '!')
			{
				residue_list[residue_no].atom_number--;
				atom_list[i].mark = 0;
			}
			else
			{
				atom_list[i].mark = 1;
			}
		}
		
		return;
	}
atom_select_default:	
	for (int i = 0; i < atom_number; i++) atom_list[i].mark = 1;
	return;
}
void build_atom_set(atom* atom_list, residue* residue_list, int atom_number, int residue_number)
{
	int* tmp = (int*)malloc(residue_number*sizeof(int));
	for (int i = 0; i < residue_number; i++)
	{
		tmp[i] = 0;
		residue_list[i].atom_set = (int*)malloc(residue_list[i].atom_number*sizeof(int));
	}
	
	for (int i = 0; i < atom_number; i++)
	{
		int residue_no = atom_list[i].residue_no;
		if (atom_list[i].mark != 0)
		{
			residue_list[residue_no].atom_set[tmp[residue_no]] = i;
			tmp[residue_no]++;
		}
	}
	
	free(tmp);
}
void input_frame(char* frame_file, int frame_no, atom* atom_list, residue* residue_list)
{
	int a_n = 0;
	FILE *point_to_frame = fopen(frame_file, "r");
	if (point_to_frame == NULL)
	{
		printf("Erro: Cannot open frame file %s.\n", frame_file);
		exit(1);
	}
	
	char line[128];
	while (feof(point_to_frame) == 0)
	{
		fgets(line, 128, point_to_frame);
		if (!string_compare(line, "ATOM", 0, 0, 4)) continue;
		a_n++;
		if (atom_list[a_n-1].mark == 0) continue;
		int residue_no = atom_list[a_n-1].residue_no;
		if (residue_list[residue_no].mark == 0) continue;
		atom_list[a_n-1].x[frame_no] = string_to_double(line, 31, 37);
		atom_list[a_n-1].y[frame_no] = string_to_double(line, 39, 45);
		atom_list[a_n-1].z[frame_no] = string_to_double(line, 47, 53);
	}
	
	fclose(point_to_frame);
	return;
}
