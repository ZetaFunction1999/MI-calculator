#ifndef MIA
//####################################################\\
//                                                    \\
//   +--+                _oo0oo_               +--+   \\
//   |编|               o8888888o              |运|   \\
//   |  |               88" . "88              |  |   \\
//   |译|               (| -_- |)              |行|   \\
//   |  |               0\  =  /0              |  |   \\
//   |一|             ___/`---'\___            |不|   \\
//   |  |           .' \\|     |// '.          |  |   \\
//   |次|          / \\|||  :  |||// \         |出|   \\
//   |  |         / _||||| -:- |||||- \        |  |   \\
//   |过|        |   | \\\  -  /// |   |       |错|   \\
//   +--+        | \_|  ''\---/''  |_/ |       +--+   \\
//               \  .-\__  '-'  ___/-. /              \\
//             ___'. .'  /--.--\  `. .'___            \\
//          ."" '<  `.___\_<|>_/___.' >' "".          \\
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |        \\
//         \  \ `_.   \_ __\ /__ _/   .-` /  /        \\
//     =====`-.____`.___ \_____/___.-`___.-'=====     \\
//                       `=---='                      \\
//                                                    \\
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    \\
//                                                    \\
//               佛祖保佑        永无BUG              \\
//####################################################\\

	#define MIA
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	#include<math.h>
	#include<unistd.h>
	#include<getopt.h>
	#include<time.h>
	
	using namespace std;
	
	struct atom
	{
		char    atom_type;
		int     residue_no;
		int     mark;
		
		double* x;
		double* y;
		double* z;
	}; 
	struct residue
	{
		int    residue_no;
		char   residue_type[4];
		char   residue_group[3];
		char   chain;
		
		int    atom_number;
		int*   atom_set;
		int    mark;
		
		int**  index_x_set;
		int**  index_y_set;
		int**  index_z_set;
		int**  order_x_set;
		int**  order_y_set;
		int**  order_z_set;
		
		double x0, x1;
		double y0, y1;
		double z0, z1;
	};
	struct TMI_data
	{
		int      residue_no;

		double** MI_A2BC;
		double** MI_AB2C;
		double** MI_AC2B;
		
		double** TMI_A_BC;
		double** TMI_B_AC;
		double** TMI_C_AB;
		
		double** A4BC;
		double** B4AC;
		double** C4AB;
	};
	
	/*readin.cpp*/
	bool string_compare(char* string_1, char* string_2, int start_1, int start_2, int length);
	void read_index(char* index_file, atom* atom_list, residue* residue_list, int* atom_number, int* residue_number);
	void build_list(atom* atom_list, residue* residue_list, atom* atom_list_tmp, residue* residue_list_tmp);
	void mark_residue(residue* residue_list, int residue_number, char* residue_group_A, char* residue_group_B, char* residue_group_C);
	void mark_atom(atom* atom_list, residue* residue_list, int atom_number, int residue_number, char* atom_select);
	void build_atom_set(atom* atom_list, residue* residue_list, int atom_number, int residue_number);
	void input_frame(char* frame_file, int frame_no, atom* atom_list, residue* residue_list);

	/*calculate.cpp*/
	void buil_TMI_list(TMI_data* TMI_list, residue* residue_list, int residue_number, int full_mode);
	void exon_sort(atom* atom_list, residue* residue_list, int frame_number, int residue_number);
	double MI_X2Y(atom* atom_list, residue* residue_list, int no_X, int no_Y, int frame_number, int kk);
	double MI_X2YZ(atom* atom_list, residue* residue_list, int no_X, int no_Y, int no_Z, int frame_number, int kk);
	void MI_A2B(double** MI_data, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, char* log_file);
	void MI_A2C(double** MI_data, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_C, char* log_file);
	void MI_A2BC(TMI_data* TMI_list, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, int group_number_C, char* log_file);
	void MI_BC(double** MI_data, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, int group_number_C, char* log_file);
	void MI_AB2C(TMI_data* TMI_list, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, int group_number_C, char* log_file);
	void MI_AC2B(TMI_data* TMI_list, atom* atom_list, residue* residue_list, int residue_number, int frame_number, int kk, int group_number_B, int group_number_C, char* log_file);
	void calculate_TMI(TMI_data* TMI_list, double** MI_data, residue* residue_list, int residue_number, int full_mode);
	
	/*mutual_information.cpp*/
	double  mutual_information(double** sample_x,     double** sample_y,     int dimension_x,        int dimension_y,   int sample_size,  int k);
	double            quick_MI(double** sample_x,     int** index_x,         int** order_x,          double** sample_y, int** index_y,    int** order_y, int dimension_x, int dimension_y, int sample_size, int k);
	double           quick_NMI(double** sample_x,     int** index_x,         int** order_x,          double** sample_y, int** index_y,    int** order_y, int dimension_x, int dimension_y, int sample_size, int k);
	double             quick_H(double** sample,       int** index,           int** order,            int dimension,     int sample_size,  int k);

#endif