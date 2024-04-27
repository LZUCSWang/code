#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


#include "../../COMMON/GlobalVariable.h"      
#include "../../COMMON/IndividualBase.h"
#include "../../COMMON/SubProblemBase.h"



class CALG_EMO_MOEAD
{
public:
	CALG_EMO_MOEAD(void);
	~CALG_EMO_MOEAD(void);

	void Execute(int run_id);                  

	void InitializeNeighborhood();
	void InitializePopulation();
	void InitializeParameter();



	void UpdateReference(vector<double> &obj_vect);
    void UpdateProblem(CIndividualBase &child, unsigned sp_id);

	void FindNadirPoint();
	void NormalizeIndividual(CIndividualBase &ind);
	void NormalizeWeight();

    void SelectMatingPool(vector<unsigned> &pool, unsigned sp_id, unsigned selected_size);
	void EvolvePopulation();
	bool IsTerminated();


	void SaveObjSpace(char saveFilename[1024]);
	void SaveVarSpace(char saveFilename[1024]);
	void SavePopulation(int run_id);


public:

    vector <CSubProblemBase> m_PopulationSOP; 
	vector <double>          v_IdealPoint;       
	vector <double>          v_NadirPoint; 

	unsigned int     s_PopulationSize;                
    unsigned int	 s_NeighborhoodSize;              
//	unsigned int     s_ReplacementLimit;            
//	double           s_LocalMatingRatio;         
	int              s_Fevals_Count;

	int              s_PBI_type; 

};

