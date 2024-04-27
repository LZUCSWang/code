// ************************************************************
// Code:   The new C++ implementation of MOEA/D and MOEA/D-DE
// Author: Dr. Hui Li
// Institude: Xi'an Jiaotong University
// DATE: 2020.2.18
// References: 
// [1] Qingfu Zhang, Hui Li: MOEA/D: A Multiobjective Evolutionary Algorithm Based on Decomposition. IEEE Trans. Evolutionary Computation 11(6): 712-731 (2007)
// [2] Hui Li, Qingfu Zhang: Multiobjective Optimization Problems With Complicated Pareto Sets, MOEA/D and NSGA-II. IEEE Trans. Evolutionary Computation 13(2):284-302  (2009) 
// ************************************************************


#include "../../COMMON/GlobalVariable.h"
#include "ALG_EMO_MOEAD.h"
#include "ALG_EMO_MOEAD_DE.h"
#include <time.h>

void ResetRandSeed();

void main()
{


	int total_run, numOfInstance;   
    std::ifstream readf("../../SETTINGS/instances/Instance.txt"); 
	readf>>numOfInstance;                         
	readf>>total_run;    

	char  alg_name[1024];

    sprintf_s(alg_name,"MOEAD");
	//sprintf_s(alg_name,"MOEAD-DE");

	rnd_uni_seed = 123;
	
	for(int inst=1; inst<=numOfInstance; inst++)
	{
		readf>>strTestInstance;     
		readf>>NumberOfVariables;   
		readf>>NumberOfObjectives;  
		readf>>NumberOfFuncEvals;  
		readf>>strCrossOverType;

		printf("\n\n -- Instance: %s, %d Variables %d  Objectives \n\n", strTestInstance, NumberOfVariables, 
						                         NumberOfObjectives);

		clock_t start, temp, finish;
		double  duration, last = 0;
		start = clock();


				
		std::fstream fout;
		char logFilename[1024];
		sprintf_s(logFilename, "../../SAVING/%s/LOG/LOG_%s.dat", alg_name, strTestInstance);
		fout.open(logFilename,std::ios::out);

		for(int run=1; run<=total_run; run++)
		{
			ResetRandSeed();
			
			if(!strcmp(alg_name,"MOEAD"))
			{
			    CALG_EMO_MOEAD MOEAD; 
			    MOEAD.Execute(run); 
			}

            if(!strcmp(alg_name,"MOEAD-DE"))
			{
			    CALG_EMO_MOEAD_DE MOEAD_DE; 
			    MOEAD_DE.Execute(run); 
			}

			
			temp = clock();  
			duration = (double)(temp - start) / CLOCKS_PER_SEC;  
			fout<<duration - last<<" ";
			last = duration;
			if(run%10==0) fout<<"\n";
		}

		fout<<"\n\n";  	finish = clock();  	fout.close();
	}

	return;
}

void ResetRandSeed()
{

	rnd_uni_seed = (rnd_uni_seed + 23)%1377;         
	rnd_uni_init = -(long)rnd_uni_seed;

}
