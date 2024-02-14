`timescale 1ns / 1ps
`define PERIOD 100 
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/05/12 00:19:38
// Design Name: 
// Module Name: tb_div
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_div();
//reg clk;
//reg [31:0]a;
//reg [31:0]b;
//wire [31:0]result;

reg										clk;
reg										rst;
reg                   signed_div_i;
reg[31:0]            opdata1_i;
reg[31:0]		   opdata2_i;
reg                  start_i;
reg                  annul_i;
wire[63:0]             result_o;
wire		          ready_o;

div div0(clk,rst,signed_div_i,opdata1_i,opdata2_i,start_i,annul_i,result_o,ready_o);
initial begin
opdata1_i=0;opdata2_i=0;clk=0;
#10 rst=1;
#100 rst=0;
#100 opdata1_i=25;opdata2_i=5;
   #100 start_i=1;annul_i=0;
#10000 opdata1_i=0;opdata2_i=0;
end
always #(`PERIOD/2) clk=~clk; 

endmodule
