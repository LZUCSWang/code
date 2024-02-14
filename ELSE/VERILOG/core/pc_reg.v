`include "defines.v"

module pc_reg(

	input	wire										clk,
	input wire										rst,
	input wire[5:0]								stall,
	
	input wire										branch_flag_i,
	input wire[`RegBus]							branch_target_address_i,
	
	input wire 										flush,
	input wire[`RegBus]							new_pc,
	
	output reg[`InstAddrBus]					pc,
	output reg                    			ce,
	output wire										branch_flush
	
);

	reg[`RegBus] hold_branch_target_address;
	reg get_branch_target_address;
	reg need_branch;
	
	assign branch_flush = need_branch;

	always @ (*) begin
		if(rst == `RstEnable) begin
			hold_branch_target_address = `ZeroWord;
			need_branch = 1'b0;
		end else if(branch_flag_i == `Branch) begin
			hold_branch_target_address = branch_target_address_i;
			need_branch = 1'b1;
		end
		if(get_branch_target_address == 1'b1) begin
			need_branch = 1'b0;
		end
	end

	always @ (posedge clk) begin
		if (rst == `RstEnable) begin
			get_branch_target_address <= 1'b0;
			pc <= 32'h00000000;
		end else if (ce == `ChipDisable) begin
			pc <= 32'h00000000;					//SDRAM挂载在总线地址0x30000000-0x3fffffff
		end else if(flush == 1'b1) begin
			pc <= new_pc;                      //flush：清空流水线的信号。?
		end else if(stall[0] == `NoStop) begin
			if(need_branch == 1'b1) begin
				pc <= hold_branch_target_address;
				get_branch_target_address <= 1'b1;
			end else if(branch_flag_i != `Branch) begin
				pc <= pc + 4'h4;
				get_branch_target_address <= 1'b0;
		end
	end
end
	
	always @ (posedge clk) begin
		if (rst == `RstEnable) begin
			ce <= `ChipDisable;
		end else begin
			ce <= `ChipEnable;
		end
	end

endmodule
// get_branch_target_address 是在之前通过比较计算得到的一个输出信号，用于表示是否需要获取分支目标地址，其初始值为 0。当执行分支跳转指令时，需要将 get_branch_target_address 的值设为 1，用于获取分支目标地址；而当已经获取了分支目标地址后，就需要将 get_branch_target_address 的值重新设为 0，以便下一次执行跳转指令时可以重新获取目标地址。
// 而 need_branch 表示是否需要进行分支跳转，其初始值也为 0，当执行分支跳转指令时，需要将 need_branch 的值设为 1；当获取了分支目标地址后，就需要将其设回 0，因为此时已经不需要进行分支跳转了，程序将正常顺序执行，不需要清空流水线。
// 代码解析
// need_branch会被设置为1，同时branch_flush也会被设置为1来通知其他模块需要刷新分支预测器，进行分支跳转就需要清空流水线