/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                         */
/*  \   \        Copyright (c) 2003-2013 Xilinx, Inc.                 */
/*  /   /        All Right Reserved.                                  */
/* /---/   /\                                                         */
/* \   \  /  \                                                        */
/*  \___\/\___\                                                       */
/**********************************************************************/


#include "iki.h"
#include <string.h>
#include <math.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
typedef void (*funcp)(char *, char *);
extern int main(int, char**);
extern void execute_3064(char*, char *);
extern void execute_12073(char*, char *);
extern void execute_12074(char*, char *);
extern void execute_12075(char*, char *);
extern void execute_12076(char*, char *);
extern void execute_12077(char*, char *);
extern void execute_3063(char*, char *);
extern void execute_12069(char*, char *);
extern void execute_12070(char*, char *);
extern void execute_12071(char*, char *);
extern void execute_12072(char*, char *);
extern void vlog_const_rhs_process_execute_0_fast_no_reg_no_agg(char*, char*, char*);
extern void execute_3466(char*, char *);
extern void execute_3467(char*, char *);
extern void execute_3468(char*, char *);
extern void execute_3469(char*, char *);
extern void execute_3254(char*, char *);
extern void execute_3255(char*, char *);
extern void execute_3256(char*, char *);
extern void execute_3257(char*, char *);
extern void execute_3258(char*, char *);
extern void execute_3259(char*, char *);
extern void execute_3260(char*, char *);
extern void execute_3261(char*, char *);
extern void execute_3262(char*, char *);
extern void execute_3263(char*, char *);
extern void execute_3264(char*, char *);
extern void execute_3265(char*, char *);
extern void execute_3266(char*, char *);
extern void execute_3267(char*, char *);
extern void execute_3103(char*, char *);
extern void execute_3104(char*, char *);
extern void execute_3105(char*, char *);
extern void execute_3106(char*, char *);
extern void execute_3107(char*, char *);
extern void execute_3108(char*, char *);
extern void execute_3109(char*, char *);
extern void execute_3110(char*, char *);
extern void execute_3111(char*, char *);
extern void execute_3112(char*, char *);
extern void execute_3113(char*, char *);
extern void execute_3114(char*, char *);
extern void execute_3115(char*, char *);
extern void execute_3070(char*, char *);
extern void execute_3071(char*, char *);
extern void execute_3072(char*, char *);
extern void execute_3073(char*, char *);
extern void execute_3074(char*, char *);
extern void execute_3090(char*, char *);
extern void execute_3091(char*, char *);
extern void execute_3092(char*, char *);
extern void execute_3093(char*, char *);
extern void execute_3094(char*, char *);
extern void execute_3095(char*, char *);
extern void execute_3096(char*, char *);
extern void execute_3097(char*, char *);
extern void execute_3098(char*, char *);
extern void execute_3099(char*, char *);
extern void execute_3100(char*, char *);
extern void execute_3101(char*, char *);
extern void execute_3102(char*, char *);
extern void execute_3470(char*, char *);
extern void execute_3471(char*, char *);
extern void execute_3472(char*, char *);
extern void execute_3473(char*, char *);
extern void execute_3474(char*, char *);
extern void execute_3475(char*, char *);
extern void execute_3476(char*, char *);
extern void execute_3477(char*, char *);
extern void execute_3478(char*, char *);
extern void execute_3479(char*, char *);
extern void execute_3480(char*, char *);
extern void execute_3481(char*, char *);
extern void execute_3482(char*, char *);
extern void execute_3483(char*, char *);
extern void execute_3484(char*, char *);
extern void execute_3485(char*, char *);
extern void execute_3486(char*, char *);
extern void execute_3487(char*, char *);
extern void execute_3488(char*, char *);
extern void execute_3489(char*, char *);
extern void execute_3490(char*, char *);
extern void execute_3491(char*, char *);
extern void execute_3492(char*, char *);
extern void execute_3493(char*, char *);
extern void execute_3494(char*, char *);
extern void execute_3495(char*, char *);
extern void execute_3496(char*, char *);
extern void execute_3497(char*, char *);
extern void execute_3498(char*, char *);
extern void execute_3499(char*, char *);
extern void execute_3500(char*, char *);
extern void execute_3501(char*, char *);
extern void execute_3502(char*, char *);
extern void execute_3503(char*, char *);
extern void execute_3504(char*, char *);
extern void execute_3505(char*, char *);
extern void execute_7470(char*, char *);
extern void execute_7471(char*, char *);
extern void execute_7472(char*, char *);
extern void execute_7473(char*, char *);
extern void execute_7474(char*, char *);
extern void execute_7475(char*, char *);
extern void execute_7476(char*, char *);
extern void execute_7477(char*, char *);
extern void execute_7478(char*, char *);
extern void execute_7479(char*, char *);
extern void execute_7480(char*, char *);
extern void execute_7481(char*, char *);
extern void execute_7482(char*, char *);
extern void execute_7483(char*, char *);
extern void execute_7484(char*, char *);
extern void execute_7485(char*, char *);
extern void execute_7486(char*, char *);
extern void execute_7487(char*, char *);
extern void execute_7488(char*, char *);
extern void execute_7489(char*, char *);
extern void execute_7490(char*, char *);
extern void execute_7491(char*, char *);
extern void execute_7492(char*, char *);
extern void execute_7493(char*, char *);
extern void execute_7494(char*, char *);
extern void execute_7495(char*, char *);
extern void execute_7496(char*, char *);
extern void execute_7497(char*, char *);
extern void execute_7498(char*, char *);
extern void execute_7499(char*, char *);
extern void execute_7500(char*, char *);
extern void execute_7501(char*, char *);
extern void execute_11470(char*, char *);
extern void execute_11471(char*, char *);
extern void execute_11472(char*, char *);
extern void execute_11473(char*, char *);
extern void execute_11474(char*, char *);
extern void execute_11475(char*, char *);
extern void execute_11476(char*, char *);
extern void execute_11477(char*, char *);
extern void execute_11478(char*, char *);
extern void execute_11479(char*, char *);
extern void execute_11480(char*, char *);
extern void execute_11481(char*, char *);
extern void execute_11482(char*, char *);
extern void execute_11483(char*, char *);
extern void execute_11484(char*, char *);
extern void execute_11485(char*, char *);
extern void execute_11486(char*, char *);
extern void execute_11487(char*, char *);
extern void execute_11488(char*, char *);
extern void execute_11489(char*, char *);
extern void execute_11490(char*, char *);
extern void execute_11491(char*, char *);
extern void execute_11492(char*, char *);
extern void execute_11493(char*, char *);
extern void execute_11494(char*, char *);
extern void execute_11495(char*, char *);
extern void execute_11496(char*, char *);
extern void execute_11497(char*, char *);
extern void execute_11498(char*, char *);
extern void execute_11499(char*, char *);
extern void execute_11500(char*, char *);
extern void execute_11501(char*, char *);
extern void execute_11502(char*, char *);
extern void execute_11503(char*, char *);
extern void execute_11504(char*, char *);
extern void execute_11505(char*, char *);
extern void execute_11506(char*, char *);
extern void execute_11507(char*, char *);
extern void execute_11508(char*, char *);
extern void execute_11509(char*, char *);
extern void execute_11510(char*, char *);
extern void execute_11511(char*, char *);
extern void execute_11512(char*, char *);
extern void execute_11513(char*, char *);
extern void execute_11514(char*, char *);
extern void execute_11515(char*, char *);
extern void execute_11516(char*, char *);
extern void execute_11517(char*, char *);
extern void execute_11518(char*, char *);
extern void execute_11519(char*, char *);
extern void execute_11520(char*, char *);
extern void execute_11521(char*, char *);
extern void execute_11522(char*, char *);
extern void execute_11523(char*, char *);
extern void execute_11524(char*, char *);
extern void execute_11525(char*, char *);
extern void execute_11526(char*, char *);
extern void execute_11527(char*, char *);
extern void execute_11528(char*, char *);
extern void execute_11529(char*, char *);
extern void execute_11530(char*, char *);
extern void execute_11531(char*, char *);
extern void execute_11532(char*, char *);
extern void execute_11533(char*, char *);
extern void execute_11534(char*, char *);
extern void execute_11535(char*, char *);
extern void execute_11536(char*, char *);
extern void execute_11537(char*, char *);
extern void execute_11538(char*, char *);
extern void execute_11539(char*, char *);
extern void execute_11540(char*, char *);
extern void execute_11541(char*, char *);
extern void execute_11542(char*, char *);
extern void execute_11543(char*, char *);
extern void execute_11544(char*, char *);
extern void execute_11545(char*, char *);
extern void execute_11546(char*, char *);
extern void execute_11547(char*, char *);
extern void execute_11548(char*, char *);
extern void execute_11549(char*, char *);
extern void execute_11550(char*, char *);
extern void execute_11551(char*, char *);
extern void execute_11552(char*, char *);
extern void execute_11553(char*, char *);
extern void execute_11554(char*, char *);
extern void execute_11555(char*, char *);
extern void execute_11556(char*, char *);
extern void execute_11557(char*, char *);
extern void execute_11558(char*, char *);
extern void execute_11559(char*, char *);
extern void execute_11560(char*, char *);
extern void execute_11561(char*, char *);
extern void execute_11562(char*, char *);
extern void execute_11563(char*, char *);
extern void execute_11564(char*, char *);
extern void execute_11565(char*, char *);
extern void execute_11566(char*, char *);
extern void execute_11567(char*, char *);
extern void execute_11568(char*, char *);
extern void execute_11569(char*, char *);
extern void execute_11570(char*, char *);
extern void execute_11571(char*, char *);
extern void execute_11572(char*, char *);
extern void execute_11573(char*, char *);
extern void execute_11574(char*, char *);
extern void execute_11575(char*, char *);
extern void execute_11576(char*, char *);
extern void execute_11577(char*, char *);
extern void execute_11578(char*, char *);
extern void execute_11579(char*, char *);
extern void execute_11580(char*, char *);
extern void execute_11581(char*, char *);
extern void execute_11582(char*, char *);
extern void execute_11583(char*, char *);
extern void execute_11584(char*, char *);
extern void execute_11585(char*, char *);
extern void execute_11586(char*, char *);
extern void execute_11587(char*, char *);
extern void execute_11588(char*, char *);
extern void execute_11589(char*, char *);
extern void execute_11590(char*, char *);
extern void execute_11591(char*, char *);
extern void execute_11592(char*, char *);
extern void execute_11593(char*, char *);
extern void execute_11594(char*, char *);
extern void execute_11595(char*, char *);
extern void execute_11596(char*, char *);
extern void execute_11597(char*, char *);
extern void execute_11598(char*, char *);
extern void execute_11599(char*, char *);
extern void execute_11600(char*, char *);
extern void execute_11601(char*, char *);
extern void execute_11602(char*, char *);
extern void execute_11603(char*, char *);
extern void execute_11604(char*, char *);
extern void execute_11605(char*, char *);
extern void execute_11606(char*, char *);
extern void execute_11607(char*, char *);
extern void execute_11608(char*, char *);
extern void execute_11609(char*, char *);
extern void execute_11610(char*, char *);
extern void execute_11611(char*, char *);
extern void execute_11612(char*, char *);
extern void execute_11613(char*, char *);
extern void execute_11614(char*, char *);
extern void execute_11615(char*, char *);
extern void execute_11616(char*, char *);
extern void execute_11617(char*, char *);
extern void execute_11618(char*, char *);
extern void execute_11619(char*, char *);
extern void execute_11620(char*, char *);
extern void execute_11621(char*, char *);
extern void execute_11622(char*, char *);
extern void execute_11623(char*, char *);
extern void execute_11624(char*, char *);
extern void execute_11625(char*, char *);
extern void execute_11626(char*, char *);
extern void execute_11627(char*, char *);
extern void execute_11628(char*, char *);
extern void execute_11629(char*, char *);
extern void execute_11630(char*, char *);
extern void execute_11631(char*, char *);
extern void execute_11632(char*, char *);
extern void execute_11633(char*, char *);
extern void execute_11634(char*, char *);
extern void execute_11635(char*, char *);
extern void execute_11636(char*, char *);
extern void execute_11637(char*, char *);
extern void execute_11638(char*, char *);
extern void execute_11639(char*, char *);
extern void execute_11640(char*, char *);
extern void execute_11641(char*, char *);
extern void execute_11642(char*, char *);
extern void execute_11643(char*, char *);
extern void execute_11644(char*, char *);
extern void execute_11645(char*, char *);
extern void execute_11646(char*, char *);
extern void execute_11647(char*, char *);
extern void execute_11648(char*, char *);
extern void execute_11649(char*, char *);
extern void execute_11650(char*, char *);
extern void execute_11651(char*, char *);
extern void execute_11652(char*, char *);
extern void execute_11653(char*, char *);
extern void execute_11654(char*, char *);
extern void execute_11655(char*, char *);
extern void execute_11656(char*, char *);
extern void execute_11657(char*, char *);
extern void execute_11658(char*, char *);
extern void execute_11659(char*, char *);
extern void execute_11660(char*, char *);
extern void execute_11661(char*, char *);
extern void execute_11662(char*, char *);
extern void execute_11663(char*, char *);
extern void execute_11664(char*, char *);
extern void execute_11665(char*, char *);
extern void execute_11666(char*, char *);
extern void execute_11667(char*, char *);
extern void execute_3058(char*, char *);
extern void execute_3060(char*, char *);
extern void execute_3062(char*, char *);
extern void execute_3066(char*, char *);
extern void execute_3067(char*, char *);
extern void execute_3068(char*, char *);
extern void execute_12078(char*, char *);
extern void execute_12079(char*, char *);
extern void execute_12080(char*, char *);
extern void execute_12081(char*, char *);
extern void execute_12082(char*, char *);
extern void vlog_transfunc_eventcallback(char*, char*, unsigned, unsigned, unsigned, char *);
funcp funcTab[339] = {(funcp)execute_3064, (funcp)execute_12073, (funcp)execute_12074, (funcp)execute_12075, (funcp)execute_12076, (funcp)execute_12077, (funcp)execute_3063, (funcp)execute_12069, (funcp)execute_12070, (funcp)execute_12071, (funcp)execute_12072, (funcp)vlog_const_rhs_process_execute_0_fast_no_reg_no_agg, (funcp)execute_3466, (funcp)execute_3467, (funcp)execute_3468, (funcp)execute_3469, (funcp)execute_3254, (funcp)execute_3255, (funcp)execute_3256, (funcp)execute_3257, (funcp)execute_3258, (funcp)execute_3259, (funcp)execute_3260, (funcp)execute_3261, (funcp)execute_3262, (funcp)execute_3263, (funcp)execute_3264, (funcp)execute_3265, (funcp)execute_3266, (funcp)execute_3267, (funcp)execute_3103, (funcp)execute_3104, (funcp)execute_3105, (funcp)execute_3106, (funcp)execute_3107, (funcp)execute_3108, (funcp)execute_3109, (funcp)execute_3110, (funcp)execute_3111, (funcp)execute_3112, (funcp)execute_3113, (funcp)execute_3114, (funcp)execute_3115, (funcp)execute_3070, (funcp)execute_3071, (funcp)execute_3072, (funcp)execute_3073, (funcp)execute_3074, (funcp)execute_3090, (funcp)execute_3091, (funcp)execute_3092, (funcp)execute_3093, (funcp)execute_3094, (funcp)execute_3095, (funcp)execute_3096, (funcp)execute_3097, (funcp)execute_3098, (funcp)execute_3099, (funcp)execute_3100, (funcp)execute_3101, (funcp)execute_3102, (funcp)execute_3470, (funcp)execute_3471, (funcp)execute_3472, (funcp)execute_3473, (funcp)execute_3474, (funcp)execute_3475, (funcp)execute_3476, (funcp)execute_3477, (funcp)execute_3478, (funcp)execute_3479, (funcp)execute_3480, (funcp)execute_3481, (funcp)execute_3482, (funcp)execute_3483, (funcp)execute_3484, (funcp)execute_3485, (funcp)execute_3486, (funcp)execute_3487, (funcp)execute_3488, (funcp)execute_3489, (funcp)execute_3490, (funcp)execute_3491, (funcp)execute_3492, (funcp)execute_3493, (funcp)execute_3494, (funcp)execute_3495, (funcp)execute_3496, (funcp)execute_3497, (funcp)execute_3498, (funcp)execute_3499, (funcp)execute_3500, (funcp)execute_3501, (funcp)execute_3502, (funcp)execute_3503, (funcp)execute_3504, (funcp)execute_3505, (funcp)execute_7470, (funcp)execute_7471, (funcp)execute_7472, (funcp)execute_7473, (funcp)execute_7474, (funcp)execute_7475, (funcp)execute_7476, (funcp)execute_7477, (funcp)execute_7478, (funcp)execute_7479, (funcp)execute_7480, (funcp)execute_7481, (funcp)execute_7482, (funcp)execute_7483, (funcp)execute_7484, (funcp)execute_7485, (funcp)execute_7486, (funcp)execute_7487, (funcp)execute_7488, (funcp)execute_7489, (funcp)execute_7490, (funcp)execute_7491, (funcp)execute_7492, (funcp)execute_7493, (funcp)execute_7494, (funcp)execute_7495, (funcp)execute_7496, (funcp)execute_7497, (funcp)execute_7498, (funcp)execute_7499, (funcp)execute_7500, (funcp)execute_7501, (funcp)execute_11470, (funcp)execute_11471, (funcp)execute_11472, (funcp)execute_11473, (funcp)execute_11474, (funcp)execute_11475, (funcp)execute_11476, (funcp)execute_11477, (funcp)execute_11478, (funcp)execute_11479, (funcp)execute_11480, (funcp)execute_11481, (funcp)execute_11482, (funcp)execute_11483, (funcp)execute_11484, (funcp)execute_11485, (funcp)execute_11486, (funcp)execute_11487, (funcp)execute_11488, (funcp)execute_11489, (funcp)execute_11490, (funcp)execute_11491, (funcp)execute_11492, (funcp)execute_11493, (funcp)execute_11494, (funcp)execute_11495, (funcp)execute_11496, (funcp)execute_11497, (funcp)execute_11498, (funcp)execute_11499, (funcp)execute_11500, (funcp)execute_11501, (funcp)execute_11502, (funcp)execute_11503, (funcp)execute_11504, (funcp)execute_11505, (funcp)execute_11506, (funcp)execute_11507, (funcp)execute_11508, (funcp)execute_11509, (funcp)execute_11510, (funcp)execute_11511, (funcp)execute_11512, (funcp)execute_11513, (funcp)execute_11514, (funcp)execute_11515, (funcp)execute_11516, (funcp)execute_11517, (funcp)execute_11518, (funcp)execute_11519, (funcp)execute_11520, (funcp)execute_11521, (funcp)execute_11522, (funcp)execute_11523, (funcp)execute_11524, (funcp)execute_11525, (funcp)execute_11526, (funcp)execute_11527, (funcp)execute_11528, (funcp)execute_11529, (funcp)execute_11530, (funcp)execute_11531, (funcp)execute_11532, (funcp)execute_11533, (funcp)execute_11534, (funcp)execute_11535, (funcp)execute_11536, (funcp)execute_11537, (funcp)execute_11538, (funcp)execute_11539, (funcp)execute_11540, (funcp)execute_11541, (funcp)execute_11542, (funcp)execute_11543, (funcp)execute_11544, (funcp)execute_11545, (funcp)execute_11546, (funcp)execute_11547, (funcp)execute_11548, (funcp)execute_11549, (funcp)execute_11550, (funcp)execute_11551, (funcp)execute_11552, (funcp)execute_11553, (funcp)execute_11554, (funcp)execute_11555, (funcp)execute_11556, (funcp)execute_11557, (funcp)execute_11558, (funcp)execute_11559, (funcp)execute_11560, (funcp)execute_11561, (funcp)execute_11562, (funcp)execute_11563, (funcp)execute_11564, (funcp)execute_11565, (funcp)execute_11566, (funcp)execute_11567, (funcp)execute_11568, (funcp)execute_11569, (funcp)execute_11570, (funcp)execute_11571, (funcp)execute_11572, (funcp)execute_11573, (funcp)execute_11574, (funcp)execute_11575, (funcp)execute_11576, (funcp)execute_11577, (funcp)execute_11578, (funcp)execute_11579, (funcp)execute_11580, (funcp)execute_11581, (funcp)execute_11582, (funcp)execute_11583, (funcp)execute_11584, (funcp)execute_11585, (funcp)execute_11586, (funcp)execute_11587, (funcp)execute_11588, (funcp)execute_11589, (funcp)execute_11590, (funcp)execute_11591, (funcp)execute_11592, (funcp)execute_11593, (funcp)execute_11594, (funcp)execute_11595, (funcp)execute_11596, (funcp)execute_11597, (funcp)execute_11598, (funcp)execute_11599, (funcp)execute_11600, (funcp)execute_11601, (funcp)execute_11602, (funcp)execute_11603, (funcp)execute_11604, (funcp)execute_11605, (funcp)execute_11606, (funcp)execute_11607, (funcp)execute_11608, (funcp)execute_11609, (funcp)execute_11610, (funcp)execute_11611, (funcp)execute_11612, (funcp)execute_11613, (funcp)execute_11614, (funcp)execute_11615, (funcp)execute_11616, (funcp)execute_11617, (funcp)execute_11618, (funcp)execute_11619, (funcp)execute_11620, (funcp)execute_11621, (funcp)execute_11622, (funcp)execute_11623, (funcp)execute_11624, (funcp)execute_11625, (funcp)execute_11626, (funcp)execute_11627, (funcp)execute_11628, (funcp)execute_11629, (funcp)execute_11630, (funcp)execute_11631, (funcp)execute_11632, (funcp)execute_11633, (funcp)execute_11634, (funcp)execute_11635, (funcp)execute_11636, (funcp)execute_11637, (funcp)execute_11638, (funcp)execute_11639, (funcp)execute_11640, (funcp)execute_11641, (funcp)execute_11642, (funcp)execute_11643, (funcp)execute_11644, (funcp)execute_11645, (funcp)execute_11646, (funcp)execute_11647, (funcp)execute_11648, (funcp)execute_11649, (funcp)execute_11650, (funcp)execute_11651, (funcp)execute_11652, (funcp)execute_11653, (funcp)execute_11654, (funcp)execute_11655, (funcp)execute_11656, (funcp)execute_11657, (funcp)execute_11658, (funcp)execute_11659, (funcp)execute_11660, (funcp)execute_11661, (funcp)execute_11662, (funcp)execute_11663, (funcp)execute_11664, (funcp)execute_11665, (funcp)execute_11666, (funcp)execute_11667, (funcp)execute_3058, (funcp)execute_3060, (funcp)execute_3062, (funcp)execute_3066, (funcp)execute_3067, (funcp)execute_3068, (funcp)execute_12078, (funcp)execute_12079, (funcp)execute_12080, (funcp)execute_12081, (funcp)execute_12082, (funcp)vlog_transfunc_eventcallback};
const int NumRelocateId= 339;

void relocate(char *dp)
{
	iki_relocate(dp, "xsim.dir/tb_alu_behav/xsim.reloc",  (void **)funcTab, 339);

	/*Populate the transaction function pointer field in the whole net structure */
}

void sensitize(char *dp)
{
	iki_sensitize(dp, "xsim.dir/tb_alu_behav/xsim.reloc");
}

	// Initialize Verilog nets in mixed simulation, for the cases when the value at time 0 should be propagated from the mixed language Vhdl net

void wrapper_func_0(char *dp)

{

}

void simulate(char *dp)
{
		iki_schedule_processes_at_time_zero(dp, "xsim.dir/tb_alu_behav/xsim.reloc");
	wrapper_func_0(dp);

	iki_execute_processes();

	// Schedule resolution functions for the multiply driven Verilog nets that have strength
	// Schedule transaction functions for the singly driven Verilog nets that have strength

}
#include "iki_bridge.h"
void relocate(char *);

void sensitize(char *);

void simulate(char *);

extern SYSTEMCLIB_IMP_DLLSPEC void local_register_implicit_channel(int, char*);
extern void implicit_HDL_SCinstatiate();

extern SYSTEMCLIB_IMP_DLLSPEC int xsim_argc_copy ;
extern SYSTEMCLIB_IMP_DLLSPEC char** xsim_argv_copy ;

int main(int argc, char **argv)
{
    iki_heap_initialize("ms", "isimmm", 0, 2147483648) ;
    iki_set_sv_type_file_path_name("xsim.dir/tb_alu_behav/xsim.svtype");
    iki_set_crvs_dump_file_path_name("xsim.dir/tb_alu_behav/xsim.crvsdump");
    void* design_handle = iki_create_design("xsim.dir/tb_alu_behav/xsim.mem", (void *)relocate, (void *)sensitize, (void *)simulate, 0, isimBridge_getWdbWriter(), 0, argc, argv);
     iki_set_rc_trial_count(100);
    (void) design_handle;
    return iki_simulate_design();
}
