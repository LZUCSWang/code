`include "defines.v"

module ex(

	input wire										rst,
	
	//送到执行阶段的信息
	input wire[`AluOpBus]         aluop_i,
	input wire[`AluSelBus]        alusel_i,
	input wire[`RegBus]           reg1_i,
	input wire[`RegBus]           reg2_i,
	input wire[`RegAddrBus]       wd_i,
	input wire                    wreg_i,
	input wire[`RegBus]				link_address_i,
	
	input wire[`RegBus]				inst_i,

	//与除法模块相连
	input wire[`DoubleRegBus]     div_result_i, //计算的结果
	input wire                    div_ready_i,  //表示除法的计算状态
	
	//访存阶段写csr相关  控制CSR的写入
	input wire							mem_csr_reg_we, //写入的值来自mem？？
	input wire[11:0]					mem_csr_reg_write_addr,
	input wire[`RegBus]				mem_csr_reg_data,
	
	//回写阶段写csr相关 
	input wire							wb_csr_reg_we,    //写入的值来自alu？？
	input wire[11:0]					wb_csr_reg_write_addr,
	input wire[`RegBus]				wb_csr_reg_data,
	
	//与csr相连
	input wire[`RegBus]				csr_reg_data_i,       //这个是干嘛的
	output reg[11:0]					csr_reg_read_addr_o,
	
	input wire[31:0]					excepttype_i,
	input wire[`RegBus]				current_inst_address_i,
	
	output reg[`RegAddrBus]       wd_o,
	output reg                    wreg_o,
	output reg[`RegBus]				wdata_o,

	output reg[`RegBus]           div_opdata1_o,
	output reg[`RegBus]           div_opdata2_o,
	output reg                    div_start_o,
	output reg                    signed_div_o,//用于标识除法是不是有符号的

	output reg							stallreq,// stallreq = stallreq_for_div;这个暂停请求来自计算除法
	
	output wire[`AluOpBus]			aluop_o,
	output wire[`RegBus]				mem_addr_o,
	output wire[`RegBus]				reg2_o,
	
	output reg							csr_reg_we_o,
	output reg[11:0]					csr_reg_write_addr_o,
	output reg[`RegBus]				csr_reg_data_o,
	
	output wire[31:0]					excepttype_o,
	output wire[`RegBus]				current_inst_address_o
);

	reg[`RegBus] logicout;   //用于记录逻辑计算的结果
	reg[`RegBus] shiftres;   //用于记录移位计算的结果
	reg[`RegBus] arithmeticres;//算数
	reg[`RegBus] moveres;//
	
	wire[`RegBus] reg2_i_mux;
	wire[`RegBus] reg1_i_not;	
	wire[`RegBus] result_sum;
	wire ov_sum;
	wire reg1_eq_reg2;
	wire reg1_lt_reg2;
	wire[`RegBus] opdata1_mult;		//补码：用于减法/有符号运算
	wire[`RegBus] opdata2_mult;		//取反值，
	wire[`DoubleRegBus] hilo_temp;
	reg[`DoubleRegBus] mulres;
	
	reg trapassert;

	reg stallreq_for_div;
	
	assign excepttype_o = {excepttype_i[31:11], trapassert, excepttype_i[9:0]};
	
	assign current_inst_address_o = current_inst_address_i;
	
	assign aluop_o = aluop_i; //传递到访存阶段，用于确定加载、存储类型
	
	
	assign mem_addr_o = (inst_i[6:0] == 7'b0100011) ?
								(reg1_i + {{20{inst_i[31]}},inst_i[31:25],inst_i[11:7]}) :  //S指令的sw等
								(reg1_i + {{20{inst_i[31]}},inst_i[31:20]});  //I指令的lw等
	
	assign reg2_o = reg2_i;

	//这个是干嘛的
	assign reg2_i_mux = ((aluop_i == `EXE_SUB_OP) || (aluop_i == `EXE_SLT_OP)) ? ((~reg2_i)+1) : reg2_i;

	assign result_sum = reg1_i + reg2_i_mux;

    //标志溢出
	assign ov_sum = ((!reg1_i[31] && !reg2_i_mux[31]) && result_sum[31]) || ((reg1_i[31] && reg2_i_mux[31]) && (!result_sum[31]));
	
	//用于比较，比较方式  reg1_lt_reg2等于1表示reg1<reg2   这里为什么不包含`EXE_SLTU_OP，其实在(reg1_i < reg2_i)已经计算出了结果了EXE_SLTU_OP
	assign reg1_lt_reg2 = ((aluop_i == `EXE_SLT_OP)) ?
												 ((reg1_i[31] && !reg2_i[31]) || 
												 (!reg1_i[31] && !reg2_i[31] && result_sum[31])||
			                   (reg1_i[31] && reg2_i[31] && result_sum[31]))
			                   :	(reg1_i < reg2_i);
	
  assign reg1_i_not = ~reg1_i;
  
  //取得乘法操作的操作数，如果是有符号除法且操作数是负数，那么取反加一
	assign opdata1_mult = (((aluop_i == `EXE_MUL_OP) || (aluop_i == `EXE_MULH_OP) || (aluop_i == `EXE_MULHSU_OP))
													&& (reg1_i[31] == 1'b1)) ? (~reg1_i + 1) : reg1_i;
  //EXE_MULHSU_OP表示一个有符号与一个无符号相乘
  assign opdata2_mult = (((aluop_i == `EXE_MUL_OP) || (aluop_i == `EXE_MULH_OP))
													&& (reg2_i[31] == 1'b1)) ? (~reg2_i + 1) : reg2_i;		

  assign hilo_temp = opdata1_mult * opdata2_mult;
  
  always @ (*) begin
		if(rst == `RstEnable) begin
			trapassert = `TrapNotAssert;
		end else begin
		
		end
  end
  
	
	always @ (*) begin
		if(rst == `RstEnable) begin
			logicout = `ZeroWord;
			arithmeticres = `ZeroWord;
		end else begin
			case (aluop_i)
				`EXE_OR_OP:			begin
					logicout = reg1_i | reg2_i;
				end
				`EXE_AND_OP:		begin
					logicout = reg1_i & reg2_i;
				end
				`EXE_XOR_OP:		begin
					logicout = reg1_i ^ reg2_i;
				end
				`EXE_SLT_OP, `EXE_SLTU_OP:		begin
					arithmeticres = reg1_lt_reg2;
				end
				`EXE_ADD_OP, `EXE_ADDI_OP, `EXE_SUB_OP:		begin
					arithmeticres = result_sum;
				end
				default:				begin
					logicout = `ZeroWord;
					arithmeticres = `ZeroWord;
				end
			endcase
		end    //if
	end      //always

	always @ (*) begin
		if(rst == `RstEnable) begin
			shiftres = `ZeroWord;
		end else begin
			case (aluop_i)
				`EXE_SLL_OP:			begin                 //逻辑移位
					shiftres = reg1_i << reg2_i[4:0] ;
				end											 
				`EXE_SRL_OP:		begin
					shiftres = reg1_i >> reg2_i[4:0];
				end												//算术移位
				`EXE_SRA_OP:		begin
					shiftres = ({32{reg1_i[31]}} << (6'd32-{1'b0, reg2_i[4:0]})) | reg1_i >> reg2_i[4:0];
				end
				default:				begin
					shiftres = `ZeroWord;
				end
			endcase
		end    //if
	end      //always

	//用于对乘法结果进行计算
	always @ (*) begin
		if(rst == `RstEnable) begin
			mulres = {`ZeroWord,`ZeroWord};
		end else if ((aluop_i == `EXE_MUL_OP) || (aluop_i == `EXE_MULH_OP) || (aluop_i == `EXE_MULHSU_OP))begin
			if(reg1_i[31] ^ reg2_i[31] == 1'b1) begin
				mulres = ~hilo_temp + 1; 
			end else begin
			  mulres = hilo_temp;
			end
		end else begin
				mulres = hilo_temp;
		end
	end
	
  always @ (*) begin
    stallreq = stallreq_for_div;   //执行阶段发出的请求因为除法
  end

  //DIV、DIVU指令	
	always @ (*) begin
		if(rst == `RstEnable) begin
			stallreq_for_div = `NoStop;
			div_opdata1_o = `ZeroWord;
			div_opdata2_o = `ZeroWord;
			div_start_o = `DivStop;
			signed_div_o = 1'b0;
		end else begin
			stallreq_for_div = `NoStop;
			div_opdata1_o = `ZeroWord;
			div_opdata2_o = `ZeroWord;
			div_start_o = `DivStop;
			signed_div_o = 1'b0;	
			case (aluop_i) 
				`EXE_DIV_OP, `EXE_REM_OP:		begin            //div ,rem 一个除法一个取模
					if(div_ready_i == `DivResultNotReady) begin   //表示除法的结果还未计算出来，这样就要暂停流水线
						div_opdata1_o = reg1_i;
						div_opdata2_o = reg2_i;
						div_start_o = `DivStart;					//div_start_o表示计算除法
						signed_div_o = 1'b1;						//有符号除法
						stallreq_for_div = `Stop;					//
					end else if(div_ready_i == `DivResultReady) begin //结果已经计算出来，就不需要暂停
						div_opdata1_o = reg1_i;
						div_opdata2_o = reg2_i;
						div_start_o = `DivStop;
						signed_div_o = 1'b1;						//有符号除法
						stallreq_for_div = `NoStop;
					end else begin						
						div_opdata1_o = `ZeroWord;
						div_opdata2_o = `ZeroWord;
						div_start_o = `DivStop;
						signed_div_o = 1'b0;						//无符号除法，为什么要在这加这个？这里有什么意义？？？？
						stallreq_for_div = `NoStop;
					end					
				end
				`EXE_DIVU_OP, `EXE_REMU_OP:		begin
					if(div_ready_i == `DivResultNotReady) begin
						div_opdata1_o = reg1_i;
						div_opdata2_o = reg2_i;
						div_start_o = `DivStart;
						signed_div_o = 1'b0;
						stallreq_for_div = `Stop;
					end else if(div_ready_i == `DivResultReady) begin
						div_opdata1_o = reg1_i;
						div_opdata2_o = reg2_i;
						div_start_o = `DivStop;
						signed_div_o = 1'b0;
						stallreq_for_div = `NoStop;
					end else begin						
						div_opdata1_o = `ZeroWord;
						div_opdata2_o = `ZeroWord;
						div_start_o = `DivStop;
						signed_div_o = 1'b0;					//无符号除法，为什么要在这加这个？这里有什么意义？？？？
						stallreq_for_div = `NoStop;
					end					
				end
				default: begin
				end
			endcase
		end
	end
	
//csr模块的  难点！！！
 always @ (*) begin
	if(rst == `RstEnable) begin
		moveres = `ZeroWord;
		csr_reg_write_addr_o = 12'b000000000000;
		csr_reg_we_o = `WriteDisable;
		csr_reg_data_o = `ZeroWord;
	end else begin
		csr_reg_read_addr_o = inst_i[31:20];
		csr_reg_write_addr_o = inst_i[31:20];
		//csr_reg_we_o = `WriteEnable;					//	不能在此处拉高（当aluop还没有确定时），若拉高则会导致逻辑操作的立即数被当作csr写操作的地址
		case(aluop_i)
			`EXE_CSRRC_OP:		begin
				csr_reg_we_o = `WriteEnable;
				//表示在上一阶段的访存阶段写入过csr
				if(mem_csr_reg_we == `WriteEnable &&
					mem_csr_reg_write_addr == inst_i[31:20]) begin
						csr_reg_data_o = reg1_i & mem_csr_reg_data;
						moveres = mem_csr_reg_data;	  //用于记录原数据
				end else if(wb_csr_reg_we == `WriteEnable &&
								wb_csr_reg_write_addr == inst_i[31:20]) begin
						csr_reg_data_o = reg1_i & wb_csr_reg_data;
						moveres = wb_csr_reg_data;	
				end else begin
					csr_reg_data_o = (~reg1_i) & csr_reg_data_i;
					moveres = csr_reg_data_i;	
				end
			end
			`EXE_CSRRS_OP:		begin
				csr_reg_we_o = `WriteEnable;
				if(mem_csr_reg_we == `WriteEnable &&
					mem_csr_reg_write_addr == inst_i[31:20]) begin
						csr_reg_data_o = reg1_i | mem_csr_reg_data;
						moveres = mem_csr_reg_data;
				end else if(wb_csr_reg_we == `WriteEnable &&
								wb_csr_reg_write_addr == inst_i[31:20]) begin
						csr_reg_data_o = reg1_i | wb_csr_reg_data;
						moveres = wb_csr_reg_data;
				end else begin
					csr_reg_data_o = reg1_i | csr_reg_data_i;
					moveres = csr_reg_data_i;
				end
			end
			`EXE_CSRRW_OP:		begin
				csr_reg_we_o = `WriteEnable;
				csr_reg_data_o = reg1_i;
				if(mem_csr_reg_we == `WriteEnable &&
					mem_csr_reg_write_addr == inst_i[31:20]) begin
						moveres = mem_csr_reg_data;
				end else if(wb_csr_reg_we == `WriteEnable &&
								wb_csr_reg_write_addr == inst_i[31:20]) begin
						moveres = wb_csr_reg_data;
				end else begin
					moveres = csr_reg_data_i;
				end
			end
			default:		begin
				csr_reg_we_o = `WriteDisable;
			end
		endcase
	end
 end

 //用于输出结果
 always @ (*) begin
	 wd_o = wd_i;	 	 	
	 wreg_o = wreg_i;
	 case ( alusel_i ) 
	 	`EXE_RES_LOGIC:		begin
			case(aluop_i)
				`EXE_OR_OP, `EXE_AND_OP, `EXE_XOR_OP: begin     //注意这里的语法～！！！
						wdata_o = logicout;
				end
				`EXE_CSRRC_OP, `EXE_CSRRS_OP, `EXE_CSRRW_OP: begin
						wdata_o = moveres;
				end
			endcase
	 	end
	 	`EXE_RES_SHIFT:		begin
	 		wdata_o = shiftres;
	 	end
		`EXE_RES_ARITHMETIC:	begin
			wdata_o = arithmeticres;
		end
		`EXE_RES_MUL:		begin
			case(aluop_i)
				`EXE_MUL_OP:		begin
					wdata_o = mulres[31:0];
				end
				`EXE_MULH_OP, `EXE_MULHU_OP, `EXE_MULHSU_OP:		begin   //保存高位结果
					wdata_o = mulres[63:32];
				end
			endcase
		end
		`EXE_RES_DIV:		begin
			case(aluop_i)
				`EXE_DIV_OP, `EXE_DIVU_OP:		begin
					wdata_o = div_result_i[31:0];
				end
				`EXE_REM_OP, `EXE_REMU_OP:		begin       //因为div模块高位为余数，低位为商
					wdata_o = div_result_i[63:32];
				end
			endcase
		end
		`EXE_RES_JUMP_BRANCH:	begin
			wdata_o = link_address_i;
		end
	 	default:					begin
	 		wdata_o = `ZeroWord;
	 	end
	 endcase
 end	

endmodule
