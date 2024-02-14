
************************************************************
Title: The new C++ implementation of MOEA/D and MOEA/D-DE
Author: Dr. Hui Li
Institude: Xi'an Jiaotong University
DATE: 2020.2.18
References: 
[1] Qingfu Zhang, Hui Li: MOEA/D: A Multiobjective Evolutionary Algorithm Based on Decomposition. IEEE Trans. Evolutionary Computation 11(6): 712-731 (2007)
[2] Hui Li, Qingfu Zhang: Multiobjective Optimization Problems With Complicated Pareto Sets, MOEA/D and NSGA-II. IEEE Trans. Evolutionary Computation 13(2):284-302  (2009) 
 *******************

List of Folders:
[1] EMO-D/MOEA/D -- The folder including the source files for the MOEA/D implementations
[2] COMMON -- -------The folder including the source files for the test instances
[3] SAVING ------------ The folder including the data files for saving the POF/POS/LOG results
[4] SETTINGS ---------- The folder including the settings of algorithms, instances, and weights

Note:  Before compiling the code, the following three things should be done in advance.
[1] The instances should be specified in 'SETTINGS/instances/instance.txt' . The first two numbers stand for the number of instances under consideration and the number of runs.
For example, '1  1' means that (a) the first instane is 'ZDT1' as listed in 'instance.txt' (b) one run is executed.
[2] The parameters for each instance should be specified in ''SETTINGS/algorithms/MOEAD.txt" or  "SETTINGS/algorithms/MOEAD-DE.txt".
[3] The weight vectors for instances should be specified in "'SETTINGS/weights/".