`timescale 1ns / 1ps


`define STARTADDR 32'd0  // 程序起始地址


module single_cycle_cpu(
    input clk,    // 时钟
    input resetn,  // 复位信号，低电平有效

    //display data
    input  [ 4:0] rf_addr,
    input  [31:0] mem_addr,
    output [31:0] rf_data,
    output [31:0] mem_data,
    output [31:0] cpu_pc,
    output [31:0] cpu_inst
    );

//取指
    reg  [31:0] pc;
    wire [31:0] next_pc;
    reg [1:0] pc_src;
    reg [31:0] bq;
    reg [31:0] jar;


    assign next_pc = pc + 4;
    always @ (posedge clk)
    begin
        if (!resetn) 
        begin
            pc <= `STARTADDR;
        end
        else 
        begin
            case(pc_src)
                2'b00:pc <= next_pc;
                2'b01:pc <= bq;
                2'b10:pc <= jar;
                default:pc <= 0;
            endcase
        end
    end

    wire [31:0] inst_addr;
    wire [31:0] inst;
    assign inst_addr = pc;
    inst_rom my_inst_rom(
        .addr      (inst_addr[6:2]),
        .inst      (inst          )
    );
    assign cpu_pc = pc;
    assign cpu_inst = inst;
//

//译码
    wire [5:0] op;       
    wire [4:0] rs;       
    wire [4:0] rt;       
    wire [4:0] rd;       
    wire [4:0] sa;      
    wire [5:0] funct;    
    wire [15:0] imm;     
    wire [15:0] offset;  
    wire [25:0] target;  

    assign op     = inst[31:26];
    assign rs     = inst[25:21];
    assign rt     = inst[20:16];
    assign rd     = inst[15:11];
    assign sa     = inst[10:6];
    assign funct  = inst[5:0];
    assign imm    = inst[15:0];
    assign offset = inst[15:0];
    assign target = inst[25:0];
    
    
    wire inst_ADDU, inst_SLL, inst_SRL, inst_SUBU, inst_NOR, inst_OR, inst_XOR, inst_SLT, inst_AND;//R型
    wire inst_ADDIU, inst_SW，inst_BEQ, inst_LW, inst_BNE, inst_LUI;//I型
    wire inst_J;//J型

    assign inst_ADDU  = (op == 6'b000000) & (sa == 5'b00000) & (funct == 6'b100001);
    assign inst_SLL   = (op == 6'b000000) & (rs==5'd0) & (funct == 6'b000000);
    assign inst_SRL   = (op == 6'b000000) & (rs==5'd0) & (funct == 6'b000010);
    assign inst_SUBU  = (op == 6'b000000) & (sa == 5'b00000) & (funct == 6'b100011);
    assign inst_NOR   = (op == 6'b000000) & (sa == 5'b00000) & (funct == 6'b100111);
    assign inst_OR    = (op == 6'b000000) & (sa == 5'b00000) & (funct == 6'b100101);
    assign inst_XOR   = (op == 6'b000000) & (sa == 5'b00000) & (funct == 6'b100110);
    assign inst_SLT   = (op == 6'b000000) & (sa == 5'b00000) & (funct == 6'b101010);
    assign inst_AND   = (op == 6'b000000) & (sa == 5'b00000) & (funct == 6'b100100);
    
    assign inst_ADDIU = (op == 6'b001001);
    assign inst_SW    = (op == 6'b101011);
    assign inst_BEQ   = (op == 6'b000100);
    assign inst_LW    = (op == 6'b100011);
    assign inst_BNE   = (op == 6'b000101);
    assign inst_LUI   = (op == 6'b001111);
    
    assign inst_J     = (op == 6'b000010);

    //无条件跳转
    pc_src = inst_J ? 2'b00 : 2'b10;  
    jar = {pc[31:28], target, 2'b00};

    //分支跳转
    pc_src = ((inst_BEQ)&(rs_value == rt_value) | (inst_BNE)&(rs_value != rt_value)) ? 2'b00 : 2'b01; 
    bq[31:2] = pc[31:2] + {{14{offset[15]}}, offset};
    bq[1:0]  = pc[1:0];

    wire rf_wen;
    wire [4:0] rf_waddr;
    wire [31:0] rf_wdata;
    wire [31:0] rs_value, rt_value;

    regfile my_regfile(
        .clk    (clk      ),
        .wen    (rf_wen   ),
        .raddr1 (rs       ),
        .raddr2 (rt       ),
        .waddr  (rf_waddr ),
        .wdata  (rf_wdata ),
        .rdata1 (rs_value ),
        .rdata2 (rt_value ),
        .test_addr(rf_addr),
        .test_data(rf_data)
    );
    
    wire inst_add, inst_sll, inst_srl, inst_sub, inst_nor, inst_or, inst_xor, inst_slt, inst_and, inst_lui;

    assign inst_add = inst_ADDU | inst_ADDIU | inst_LW | inst_SW;
    assign inst_sll = inst_SLL;
    assign inst_srl = inst_SRL;
    assign inst_sub = inst_SUBU;
    assign inst_nor = inst_NOR;
    assign inst_or  = inst_OR;
    assign inst_xor = inst_XOR;
    assign inst_slt = inst_SLT;
    assign inst_and = inst_AND;
    
    assign inst_lui = inst_LUI;


    wire [31:0] ext_imm;
    wire   inst_shf_sa;
    wire   inst_imm_sign;
    assign ext_imm = {{16{imm[15]}}, imm};
    assign inst_shf_sa = inst_SLL | inst_SRL;
    assign inst_imm_sign = inst_ADDIU | inst_LUI | inst_LW | inst_SW;
    
    wire [31:0] alu_operand1;
    wire [31:0] alu_operand2;
    wire [11:0] alu_control;
    assign alu_operand1 = inst_shf_sa ? {27'd0,sa} : rs_value;
    assign alu_operand2 = inst_imm_sign ? ext_imm : rt_value;

    assign alu_control = {inst_add,
                          inst_sub,
                          inst_slt,
                          inst_sltu,
                          inst_and,
                          inst_nor,
                          inst_or, 
                          inst_xor,
                          inst_sll,
                          inst_srl,
                          inst_sra,
                          inst_lui};
//

//执行
    wire [31:0] alu_result;

    alu my_alu(
        .alu_control  (alu_control ),  // I, 12, ALU控制信号
        .alu_src1     (alu_operand1),  // I, 32, ALU操作数1
        .alu_src2     (alu_operand2),  // I, 32, ALU操作数2
        .alu_result   (alu_result  )   // O, 32, ALU结果
    );
//
    
//访存
    wire [3 :0] dm_wen;
    wire [31:0] dm_addr;
    wire [31:0] dm_wdata;
    wire [31:0] dm_rdata;
    assign dm_wen  = {4{inst_SW & resetn}};
    assign dm_addr = alu_result;
    assign dm_wdata = rt_value;
    data_ram data_ram_module(
        .clk   (clk         ),
        .wen   (dm_wen      ),
        .addr  (dm_addr[6:2]),
        .wdata (dm_wdata    ),
        .rdata (dm_rdata    ),
        .test_addr(mem_addr[6:2]),
        .test_data(mem_data     )
    );
//

//写回
    wire inst_wdest_rt;
    wire inst_wdest_rd;
    assign inst_wdest_rt = inst_ADDIU | inst_LW | inst_LUI;
    assign inst_wdest_rd = inst_ADDU | inst_SUBU | inst_SLT | inst_AND | inst_NOR
                          | inst_OR   | inst_XOR  | inst_SLL | inst_SRL;                   

    assign rf_wen   = (inst_wdest_rt | inst_wdest_rd) & resetn;
    assign rf_waddr = inst_wdest_rd ? rd : rt;
    assign rf_wdata = inst_LW ? dm_rdata : alu_result;
//
endmodule