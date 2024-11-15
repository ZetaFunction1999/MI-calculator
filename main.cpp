#include "data_structure.h"
#include "MIA.h"

/*Main file*/

/*
//===========================================================================================================\\
//===========================================================================================================\\
//                                                                                                           \\
//                                                                                                           \\
//                                                                                                           \\
//                                                                                                           \\
//                                +1s         哲人日已远    典刑在夙昔         +1s                           \\
//                                +1s         风檐展书读    古道照颜色         +1s                           \\
//                                +1s                                          +1s                           \\
//                                +1s           1926.8.17--2022.11.30          +1s                           \\
//                                                                                                           \\
//                                                                                                           \\
//                                                                                                           \\
//                                          ***]/OO@@@@OO]OO]]]]]]]***                                       \\
//                                    *,OOO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O]`****                             \\
//                                *,/O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\]**                           \\
//                            *,oOOO@@@@@@@OOO@@O@@@@O@O@OOOOO@OOOOOOOOOOOOO@O@@@OO]`                        \\
//                          *,OO@@@@@@@@@OOOOOO@OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO@OO@@@@O`                     \\
//                         ,O@@@@@@@@OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO@O\`.                  \\
//                       ,O@@@@@@@@@OOOOOOOOOOOOOOOOOOoOooooOOOoooo`=/oOooOOOOOOOoOOOOOOOOO`.                \\
//                      =@@@@@@@@@@OOOOOOOOOOOOOOOOo//`*`**.,`[****...****^\oOOOOooOOOOOOOOO\.               \\
//                     /@@@@@@@@OOOOOOOOOOOOOOoo/O^*`*........................,*`ooOOOOOOOOOOO\*             \\
//                   .@@@@@@OOOOOOOOOOOOOo[[[****................................**,oooOOOOOO@@O`            \\
//                  .O@@@@@@OOOOOOOOOooo^******......................................=oOOOOoOO@@O.           \\
//                 .@@@@@@@@OOOooooooo^****...........................................,/OOOOOOO@@O.          \\
//                .@@@@@@@@OOOOOo./oooo****.......................         .............=oOOOOOO@@\.         \\
//               .@@@@@@@@@@OOOo`/ooooo/**.................                      .......*=ooOOOO@@@^         \\
//              .O@@@@@@@@@OOOO/ooooOooo***................                        ......,,OOOOO@@@O.        \\
//             .=@@@@@@@@@@@OOOO\]oOOooo^**..................  .                   .......\oOOO@@@@@.        \\
//              /@@@@@@@@@@@OOOO/\OOOOooo`*...................                     .......*,oOO@@@@@.        \\
//             .@@@@@@@@@@@OOOOooOOOOOooo***........................               .......*\OOO@@@@O.        \\
//             .@@@@@@@@@@@OOOOOOOOOOOOo/**............   .   .......             .........\OOO@@@@/.        \\
//              @@@@@@@@@@@@OOOOOOOOOOOoo****.........       .. ......            ........,/\OO@@@@^.        \\
//              @@@@@@@@@@@OOOOOOOOOOOOOOo]]**`*.......    .... .....          .  ........*,OOO@@@@^         \\
//              =@@@@@@@@@@@OOOOOOOOOOOOOOoo/[\o[\/,`*......... ..........................*`=O@@@@@.         \\
//              .=@@@@@@@@@OOOOOOOOO@@@OOOo/`....[[[\OO]].....  ....,]]]]/OOO]]]]]]`......*=oO@@@@/          \\
//               .O@@@@@@@@@@@OOOOO@OOOOoo^]`*......   .,OO^..  ./@O`........   . ..,\O[\.,oOO@@@@.          \\
//               .=O@@@@@@@@@@@OO@@OOOOOOOOOO\`,]]].**....\@O]]O@@o\o]/o*......... ....,@@`O@@@@O^.          \\
//               .=OOOO@@@OOOOOOO@@OOOOOOOOO@@@@@OOOOOO]./O@@@@@@^=OoOOO@@@@@@\`........\@@\OO@O/.           \\
//               .=OOOOOOOOOOOOOO@OOOOOOOOOO/`***...[OOOOOO@@@@@@`.,\oO/[[[[,`.[[\.......@@/\/OO^            \\
//                =OOOOOOOOOOOOOO@oooOoo^**...........oOOO@@`. \@^....**....   ..........@^...,o.            \\
//                ,OOOOOOOOOOOOOO@ooo^*,,****.........,OO@@/..  \@`..****................O^......            \\
//                .OOOOOOOOOOOOOOOOo^*****...........*OO@@O*..  .@O*...****.......... ...@.......            \\
//                 =OOOOOOOOOOOOOO@/o`***............oO@@O^...   .OO.............  ...../`......             \\
//                 .OOOOOOOOOOOOOOOO\`[`*..........,O@@OOO^..    ..\@`.........      ../`......              \\
//                  =OOOOOOOOOOOOOOOOOOOOOOOOOOOOO@@OOoOOO^...    ..[OO]]`......  .]]/`.......               \\
//                  .OOOOOOOOOOOOOOOOo`*........../OOooOOOO^*.......  =OOOOOOOOO[[[.. .......                \\
//                   =OOOOOOOOOOOOOOOo`*........=OOOOO@@@@@OOo`.,@@@\.. ....................                 \\ 
//                   .OOOOOOOOOOOOOOOOOo]**..***\oOOOOOOOOOOOO/.......    .................                  \\
//                    OOOOOOOOOOOOOOOOOOOo/oo./oo/o[[ooooo[[...            ..==`...........                  \\ 
//                      \OOOOOOOOOOOOOOOOOOooooooo^**..........         ......***..........                  \\
//                      .OOOOOOOOOOOOOO/*oOOOOOOoo****.........         ..................                   \\
//                       OOOOOOOOOOOOOo^.,OOOOOOOOo/*****...... ..    ....................                   \\
//                       OOOOOOOOOOOOOo\*.*OOOOOOOOOOOOOOOOOOo\]`***,oo\/^*...............                   \\
//                       =OOOOOOOOOOOOOo`..=OOOOOOOOOOOOOOOO@@@O@OO[[.. .................                    \\
//                        OOOOOOOOOOOOOOo*.*\OOOOooo[[[[[**..... .....     .............                     \\
//                        =OOOOOOOOOOOOOOo***\ooooooo]*............      ..............                      \\
//                         OOOOOOOOOOOOOOOO^*.=Ooo/o`=\`****..........  ..............                       \\
//                       ,@@OOOOOOOOOOOOOOOO^.*ooo^*****.................  ..........                        \\
//                      ,@@@O\OOOOOOOOOOOOOOO^**oo`*...........        .. ..........                         \\
//                     =@@@@@\,OOOOOOOOOOOOOOOo]*oo]*...........    ........**.*...                          \\
//                    @@@@@@@@\.\OOOOOOOOOOOOOOOOoooo]`*..................]/*,/...                           \\
//                  /@@@@@@@@@@@`,OOOOOOOOOOOOOOOOOOOOOo\********......./`**`**..                            \\
//           ,]@@@@@@@@@@@@@@@@@@\..\OOOOOOOOOOOOOOOOOOOOOoooOOOoooooOO`,`****..                             \\
//        /@@@@@@@@@@@@@@@@@@@@@@@@`..,OOOOOOOOOOOOOOOOOOOOOOOOOOOOOoooo*****..,@@\]]`                       \\
//    ,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@\....,\OOOOOOOOOOOOOOOOOOOOOooooooooo][`.. @@@@@@@@@@@\]                 \\
// ,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`......[OOOOOOOOOOOOOOOOooooo`[`**....   O@@@@@@@@@@@@@@@O]`           \\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\.........[OOOOOOOOOOOOoo^*]**.....     O@@@@@@@@@@@@@@@@@@@@O]`      \\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`...........[oooOO/[`.........        @@@@@@@@@@@@@@@@@@@@@@@@@@O]` \\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\.......      ,\\]]]`......         ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O...             .[[\O/.           =@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^.            //,\OOO\/OOO\       =@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\         ,//OOOOO^,/OOO\.O\     =O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O       /@@O@@^/OOOOO\]/O@@\    =O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`   /@OOO@@@@@OO\`]/OO/OOoO    OO@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^ ,OOOO@@OO@@\/OOOOoOO*ooOo   \O@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^  .O^.,O@@@@@@O.]O@  ..[*.. =O@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^  =o*..,OO@O@@OOO^        \`O@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\  [o`...\@@@@OOO\        =*.O@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\ ..O\../O@@@/.=O^       =o`O@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\  =OO/O@O@OOOOOO        OoO@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\  \O@O@@OOOOOO/O       ooO@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O =@@@@O@@O..=OO\`    .ooo@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O/@@O@@@OOOO/,OO\   =ooo@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OO@@@OOOOO\/OO\\ =Ooo`@@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OO@O/`,OO\.=OO/OOo`O@@@@@@@@@@@@@@@@@@@@@@@@@@\\
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OOOOOOOOO/\OOOO^O@@@@@@@@@@@@@@@@@@@@@@@@@@\\
*/

/*Main Function*/
int main(int argc, char* argv[])
{
	/*--------------------*/
	int time_start = 0;
	int time_end   = 0;
	int time_used  = 0;
	int time_total = 0;
	time_start = time(NULL);
	/*--------------------*/
	
	/*parameter list*/
	char* index_file      = NULL;              // -i xxx.pdb
	char* data_directory  = NULL;              // -d .../xxx
	char* output_file     = "MI-analysis.out"; // -o .../xxx.out
	
	char* residue_group_A = NULL;              // -rgA 1,4,7,10-12
	char* residue_group_B = NULL;              // -rgB 2,5,8,13-15
	char* residue_group_C = NULL;              // -rgC 3,6,9,16-18
	char* atom_select     = NULL;              // -as in | -as out
	
	int   begin_frame 	  = 1;                 // -bf 10005
	int   end_frame       = 1;                 // -ef 20000
	int   frame_step      = 1;                 // -fs 5
	
	int   full_mode       = 0;                 // -fm 1
	
	int   kk              = 1;
	
	/*read in parameters*/
	int   opt;
    int   digit_optind = 0;
    int   option_index = 0;
	char* optfmt       = "d:i:o:";
	static struct option long_options[] =
    {  
        {"rgA",required_argument, NULL, 1},
		{"rgB",required_argument, NULL, 2},
        {"rgC",required_argument, NULL, 3},
        {"as", required_argument, NULL, 4},
		{"bf", required_argument, NULL, 5},
		{"ef", required_argument, NULL, 6},
		{"fs", required_argument, NULL, 7},
		{"fm", required_argument, NULL, 8},
        {NULL, 0,                 NULL, 0}
    };
	while((opt = getopt_long_only(argc, argv, optfmt, long_options, &option_index))!= -1)
    {  
        switch (opt)
		{
		case 100:
			data_directory  = optarg;
			break;
		case 105:
			index_file      = optarg;
			break;
		case 111:
			output_file     = optarg;
			break;
			
		case 1:
			residue_group_A = optarg;
			break;
		case 2:
			residue_group_B = optarg;
			break;
		case 3:
			residue_group_C = optarg;
			break;
		case 4:
			atom_select     = optarg;
			break;
		case 5:
			begin_frame     = atoi(optarg);
			break;
		case 6:
			end_frame       = atoi(optarg);
			break;
		case 7:
			frame_step      = atoi(optarg);
			break;
		case 8:
			full_mode       = atoi(optarg);
			break;
		} 
    }
	
	/*Check the input parameters*/
	if (begin_frame >= end_frame)
	{
		printf("Error: -ef should be greater than -bf.\n");
		exit(-1);
	}
	if (data_directory == NULL)
	{
		printf("Error: Please input the directory for data files with option -d.\n");
		exit(-1);
	}
	int TMI_mode = 0;
	if (residue_group_C != NULL) TMI_mode = 1;
	if ((full_mode != 1) && (TMI_mode == 0))
	{
		printf("Ignore option \"fm\" since TMI mode is off.\n");
	}
	
	int      atom_number    = 0;
	int      residue_number = 0;
	atom*    atom_list      = NULL;
	residue* residue_list   = NULL;
	
	/*read information of atoms and residues from index file*/	
	atom*    atom_list_tmp    =    (atom*)malloc(9999*sizeof(atom));
	residue* residue_list_tmp = (residue*)malloc(9999*sizeof(residue));
	read_index(index_file, atom_list_tmp, residue_list_tmp, &atom_number, &residue_number);
	atom_list    =    (atom*)malloc(atom_number*sizeof(atom));
	residue_list = (residue*)malloc(residue_number*sizeof(residue));
	build_list(atom_list, residue_list, atom_list_tmp, residue_list_tmp);
	free(atom_list_tmp);
	free(residue_list_tmp);
	
	/*mark residues and atoms based on their group and index file*/
	int group_number_A = 0;
	int group_number_B = 0;
	int group_number_C = 0;
	mark_residue(residue_list, residue_number, residue_group_A, residue_group_B, residue_group_C);
	mark_atom(atom_list, residue_list, atom_number, residue_number, atom_select);
	build_atom_set(atom_list, residue_list, atom_number, residue_number);
	int* group_A_list   = (int*)malloc(residue_number*sizeof(int));
	int* group_B_list   = (int*)malloc(residue_number*sizeof(int));
	int* group_C_list   = (int*)malloc(residue_number*sizeof(int));
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].residue_group[0] == 'A')
		{
			group_A_list[group_number_A] = i;
			group_number_A++;
		}
		if (residue_list[i].residue_group[1] == 'B')
		{
			group_B_list[group_number_B] = i;
			group_number_B++;
		}
		if (residue_list[i].residue_group[2] == 'C')
		{
			group_C_list[group_number_C] = i;
			group_number_C++;
		}
	}
	
	/*build frame list*/
	int  frame_number  = floor((end_frame-begin_frame)/frame_step)+1;
	int* frame_id_list = (int*)malloc(frame_number*sizeof(int));
	int  frame_id      = begin_frame;
	for (int i = 0; i < frame_number; i++)
	{
		frame_id_list[i] = frame_id;
		frame_id += frame_step;
	}
	for (int i = 0; i < atom_number; i++)
	{
		if (atom_list[i].mark == 0) continue;
		int residue_no = atom_list[i].residue_no;
		if (residue_list[residue_no].mark == 0) continue;
		
		atom_list[i].x = (double*)malloc(frame_number*sizeof(double));
		atom_list[i].y = (double*)malloc(frame_number*sizeof(double));
		atom_list[i].z = (double*)malloc(frame_number*sizeof(double));
	}
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].mark == 0) continue;
		
		residue_list[i].index_x_set = (int**)malloc((residue_list[i].atom_number)*sizeof(int*));
		residue_list[i].index_y_set = (int**)malloc((residue_list[i].atom_number)*sizeof(int*));
		residue_list[i].index_z_set = (int**)malloc((residue_list[i].atom_number)*sizeof(int*));
		residue_list[i].order_x_set = (int**)malloc((residue_list[i].atom_number)*sizeof(int*));
		residue_list[i].order_y_set = (int**)malloc((residue_list[i].atom_number)*sizeof(int*));
		residue_list[i].order_z_set = (int**)malloc((residue_list[i].atom_number)*sizeof(int*));
		
		for (int j = 0; j < residue_list[i].atom_number; j++)
		{
			residue_list[i].index_x_set[j] = (int*)malloc(frame_number*sizeof(int));
		    residue_list[i].index_y_set[j] = (int*)malloc(frame_number*sizeof(int));
		    residue_list[i].index_z_set[j] = (int*)malloc(frame_number*sizeof(int));
		    residue_list[i].order_x_set[j] = (int*)malloc(frame_number*sizeof(int));
		    residue_list[i].order_y_set[j] = (int*)malloc(frame_number*sizeof(int));
		    residue_list[i].order_z_set[j] = (int*)malloc(frame_number*sizeof(int));
		}
	}
	
	/*input frame files*/
	/*--------------------*/
	time_end   = time(NULL);
	time_used  = time_end - time_start;
	time_total+= time_used;
	time_start = time(NULL);
	printf("Reading frames form data files...\n");
	/*--------------------*/
	
	#pragma omp parallel for
	for (int i = 0; i < frame_number; i++)
	{
		char file_name[256] = "";
		strcat(file_name, data_directory);
		if (file_name[strlen(data_directory)-1] != '/') strcat(file_name, "/");
		char frame_no[16];
		sprintf(frame_no, "%d", frame_id_list[i]);
		strcat(file_name, frame_no);
		strcat(file_name, ".pdb");
		input_frame(file_name, i, atom_list, residue_list);
	}
	/*--------------------*/
	time_end   = time(NULL);
	time_used  = time_end - time_start;
	time_total+= time_used;
	time_start = time(NULL);
	printf("Done! Time used: %ds(%.2fmin)\n\n", time_used, double(time_used)/60);
	/*--------------------*/
	
	/*calculate MI*/
	char log_file[256];
	strcat(log_file, output_file);
	strcat(log_file, ".log");
	FILE *point_to_log = fopen("logfile.log", "w");
	fclose(point_to_log);
	
	double** MI_data = (double**)malloc(residue_number*sizeof(double*));
	for (int i = 0; i < residue_number; i++)
	{
		MI_data[i] = (double*)malloc(residue_number*sizeof(double));
		for (int j = 0; j < residue_number; j++)
		{
			MI_data[i][j] = -1;
		}
	}
	/*--------------------*/
	time_end   = time(NULL);
	time_used  = time_end - time_start;
	time_total+= time_used;
	time_start = time(NULL);
	printf("Sorting frames to optimize runing time...\n");
	/*--------------------*/
	exon_sort(atom_list, residue_list, frame_number, residue_number);
	/*--------------------*/
	time_end   = time(NULL);
	time_used  = time_end - time_start;
	time_total+= time_used;
	time_start = time(NULL);
	printf("Done! Time used: %ds(%.2fmin)\n\n", time_used, double(time_used)/60);
	/*--------------------*/
	/*--------------------*/
	time_end   = time(NULL);
	time_used  = time_end - time_start;
	time_total+= time_used;
	time_start = time(NULL);
	printf("Calculating MI(A,B)...\n");
	/*--------------------*/
	MI_A2B(MI_data, atom_list, residue_list, residue_number, frame_number, kk, group_number_B, log_file);
	/*--------------------*/
	time_end   = time(NULL);
	time_used  = time_end - time_start;
	time_total+= time_used;
	time_start = time(NULL);
	printf("Done! Time used: %ds(%.2fmin)\n\n", time_used, double(time_used)/60);
	/*--------------------*/
	
	/*calculate TMI*/
	TMI_data* TMI_list = (TMI_data*)malloc(residue_number*sizeof(TMI_data));
	if (TMI_mode == 1)
	{
		/*--------------------*/
		time_end   = time(NULL);
		time_used  = time_end - time_start;
		time_total+= time_used;
		time_start = time(NULL);
		printf("Calculating MI(A,C)...\n");
		/*--------------------*/
		MI_A2C(MI_data, atom_list, residue_list, residue_number, frame_number, kk, group_number_C, log_file);
		/*--------------------*/
		time_end   = time(NULL);
		time_used  = time_end - time_start;
		time_total+= time_used;
		time_start = time(NULL);
		printf("Done! Time used: %ds(%.2fmin)\n\n", time_used, double(time_used)/60);
		/*--------------------*/
		buil_TMI_list(TMI_list, residue_list, residue_number, full_mode);
		/*--------------------*/
		time_end   = time(NULL);
		time_used  = time_end - time_start;
		time_total+= time_used;
		time_start = time(NULL);
		printf("Calculating MI(A,BC)...\n");
		/*--------------------*/
		MI_A2BC(TMI_list, atom_list, residue_list, residue_number, frame_number, kk, group_number_B, group_number_C, log_file);
		/*--------------------*/
		time_end   = time(NULL);
		time_used  = time_end - time_start;
		time_total+= time_used;
		time_start = time(NULL);
		printf("Done! Time used: %ds(%.2fmin)\n\n", time_used, double(time_used)/60);
		/*--------------------*/
		if (full_mode == 1)
		{
			/*--------------------*/
			time_end   = time(NULL);
			time_used  = time_end - time_start;
			time_total+= time_used;
			time_start = time(NULL);
			printf("Calculating MI(B,C)...\n");
			/*--------------------*/
			MI_BC(MI_data, atom_list, residue_list, residue_number, frame_number, kk, group_number_B, group_number_C, log_file);
			/*--------------------*/
			time_end   = time(NULL);
			time_used  = time_end - time_start;
			time_total+= time_used;
			time_start = time(NULL);
			printf("Done! Time used: %ds(%.2fmin)\n\n", time_used, double(time_used)/60);
			/*--------------------*/
			/*--------------------*/
			time_end   = time(NULL);
			time_used  = time_end - time_start;
			time_total+= time_used;
			time_start = time(NULL);
			printf("Calculating MI(AB,C)...\n");
			/*--------------------*/
			MI_AB2C(TMI_list, atom_list, residue_list, residue_number, frame_number, kk, group_number_B, group_number_C, log_file);
			/*--------------------*/
			time_end   = time(NULL);
			time_used  = time_end - time_start;
			time_total+= time_used;
			time_start = time(NULL);
			printf("Done! Time used: %ds(%.2fmin)\n\n", time_used, double(time_used)/60);
			/*--------------------*/
			/*--------------------*/
			time_end   = time(NULL);
			time_used  = time_end - time_start;
			time_total+= time_used;
			time_start = time(NULL);
			printf("Calculating MI(AC,B)...\n");
			/*--------------------*/
			MI_AC2B(TMI_list, atom_list, residue_list, residue_number, frame_number, kk, group_number_B, group_number_C, log_file);
			/*--------------------*/
			time_end   = time(NULL);
			time_used  = time_end - time_start;
			time_total+= time_used;
			time_start = time(NULL);
			printf("Done! Time used: %ds(%.2fmin)\n\n", time_used, double(time_used)/60);
			/*--------------------*/
		}
		calculate_TMI(TMI_list, MI_data, residue_list, residue_number, full_mode);
	}
	
	/*out put result*/
	FILE *point_to_output = fopen(output_file, "w");
	if (point_to_output == NULL)
	{
		printf("Erro: Cannot open file %s.", output_file);
		exit(1);
	}
	
	if (TMI_mode == 0)
	{
		fputs("resA    resB    ||  I(A,B) \n\n", point_to_output);
	}
	if (TMI_mode == 1)
	{
		if (full_mode == 0)
		{
			fputs("resA    resB    resC    ||   I(A,B) I(A,C) |  A,BC  |  TA,BC \n\n", point_to_output);
		}
		if (full_mode == 1)
		{
			fputs("resA    resB    resC    ||   I(A,B) I(A,C) I(B,C) |  A,BC   AC,B   AB,C  |  TA,BC  TB,AC  TC,AB | CPA  CPB  CPC \n\n", point_to_output);
		}
	}
	
	/*--------------------*/
	time_end   = time(NULL);
	time_used  = time_end - time_start;
	time_total+= time_used;
	time_start = time(NULL);
	printf("Outputing to result file...\n");
	/*--------------------*/
	for (int i = 0; i < residue_number; i++)
	{
		if (residue_list[i].residue_group[0] != 'A') continue;
		
		if (TMI_mode == 0)
		{
			for (int j = 0; j < residue_number; j++)
			{
				if (residue_list[j].residue_group[1] != 'B') continue;
				
				char line[256];
				sprintf(line, "%s%-4d %s%-4d || %6.3f",
				residue_list[i].residue_type, residue_list[i].residue_no,
				residue_list[j].residue_type, residue_list[j].residue_no,
				MI_data[i][j]);
				fputs(line, point_to_output);
				fputs(" \n", point_to_output);
			}
		}
		if (TMI_mode == 1)
		{
			for (int j = 0; j < residue_number; j++)
			{
				if (residue_list[j].residue_group[1] != 'B') continue;
				
				for (int k = 0; k < residue_number; k++)
				{
					if (residue_list[k].residue_group[2] != 'C') continue;
					
					char line[256];
					if (full_mode == 0)
					{
						sprintf(line, "%s%-4d %s%-4d %s%-4d ||   %6.3f %6.3f | %6.3f | %6.3f",
						residue_list[i].residue_type, residue_list[i].residue_no,
						residue_list[j].residue_type, residue_list[j].residue_no,
						residue_list[k].residue_type, residue_list[k].residue_no,
						MI_data[i][j], MI_data[i][k], TMI_list[i].MI_A2BC[j][k], TMI_list[i].TMI_A_BC[j][k]);
					}
					if (full_mode == 1)
					{
						sprintf(line, "%s%-4d %s%-4d %s%-4d ||   %6.3f %6.3f %6.3f | %6.3f %6.3f %6.3f | %6.3f %6.3f %6.3f | %.2f %.2f %.2f",
						residue_list[i].residue_type, residue_list[i].residue_no,
						residue_list[j].residue_type, residue_list[j].residue_no,
						residue_list[k].residue_type, residue_list[k].residue_no,
						MI_data[i][j], MI_data[i][k], MI_data[j][k],
						TMI_list[i].MI_A2BC[j][k],  TMI_list[i].MI_AB2C[j][k],  TMI_list[i].MI_AC2B[j][k], 
						TMI_list[i].TMI_A_BC[j][k], TMI_list[i].TMI_B_AC[j][k], TMI_list[i].TMI_C_AB[j][k],
						TMI_list[i].A4BC[j][k],     TMI_list[i].B4AC[j][k],     TMI_list[i].C4AB[j][k]);
					}
					fputs(line, point_to_output);
					fputs(" \n", point_to_output);
				}
			}
		}
		fputs(" \n", point_to_output);
	}
	fclose(point_to_output);
	/*--------------------*/
	time_end   = time(NULL);
	time_used  = time_end - time_start;
	time_total+= time_used;
	time_start = time(NULL);
	printf("Done! Time used: %ds(%.2fmin)\n\n", time_used, double(time_used)/60);
	/*--------------------*/
	
	printf("Normal terminated! Total time used: %ds(%.2fmin)\n", time_total, double(time_total)/60);
	return 0;
}