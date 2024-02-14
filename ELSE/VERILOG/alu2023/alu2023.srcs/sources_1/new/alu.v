`timescale 1ps/1ps
/***********************************alu design ******************************/
// The functions implemented are 1. 32-bit overrun adder (subtractor) 2. 32-bit unsigned number left shift 3. 32-bit unsigned number logical right shift 4. 32-bit unsigned number truncated from right 5. 32-bit unsigned number truncated from left 6. 32-bit number logical sum, 7. 32-bit number logical or, 8. 32-bit number logical series non, 9. 32-bit number logical iso-or
// 10. Arithmetic right shift of 32-bit signed numbers 11. 32-bit logical non 12.signed comparator 13.unsigned comparator
//alu basic implementation using gate level
/***********************************alu_op******************************/
/* operation operation
		8'b00100000 ADD
		8'b00100010 SUB
	
		8'b00100100 AND
		8'b00100101 OR
		8'b00100110 XOR
		8'b01111100 SLL(Logical Left Shift)
		8'b00000010 SRL(Logical Right Shift)
		8'b00011111 no
		8'b00000011 SRA(arithmetic right shift)

		8'b00000111 32-bit unsigned number truncated from the right
		8'b00001111 32-bit unsigned truncation from left

		8'b00111111 32-bit signed comparator
		8'b01111111 32-bit unsigned comparator

*/
/*********************************** input, output port description ******************************/
/*
   input x -------------------- input operand 1, for the monomial operator, the default is the first operand
   input y -------------------- input operand 2
   input z -------------------- input operand 3, used to indicate the number of bits for shift and truncation operations
   output d -------------------- output port selection, 1 - result is output from f2, 0 - result is output from f
   output f[31:0] ------------------- output result
   output isoverflowed -------------- whether there is an overflow
*/
/*********************************** expand ******************************/
/*
This design also separately designs a 32-bit divider (supporting signed and unsigned) without restoring remainder method, and a 32-bit boost multiplier.
*/
module alu(f,x,y,z,operation,isoverflowed);
input [31:0]x;//x means the operation ? ?1
input [31:0]y;//y means the operation ? ?2
input [4:0]z; // indicates shift number or truncation number
input [7:0]operation; //Indicates function selection
output reg[31:0] f;
output wire isoverflowed;
//wire overflow;
wire [31:0]f1;
wire [31:0]f2;
wire [31:0]f3;
wire [31:0]f4;
wire [31:0]f5;
wire [31:0]f6;
wire [31:0]f7;
wire [31:0]f8;
wire [31:0]f9;
wire [31:0]f10;
wire [31:0]f11;
wire [31:0]f12;
wire [31:0]f13;
adder32 addresult(x,y,f1,isoverflowed);
shiftbitleft leftshiftresult(f2,x,z);
shiftbitright rightshiftresult(f3,x,z);
right_truncation right_truncationresult(f4,x,z);
left_truncation left_truncationresult(f5,x,z);
bitwiseand andresult(x,y,f6);
bitwiseor orresult(x,y,f7);
no noresult(f8,x);
xor32 xoresult(f9,x,y);
adder32 subresult(x,~y+1,f10,isoverflowed);
right_shift_arithmetic sraresult(x,z,f11);
comparator32 slt(x,y,f12);
comparator32_unsigned sltu(x,y,f13);
always @(*) begin
case (operation)
8'b00100000:  f<=f1;
8'b00100010:  f<=f10;
8'b00100100:  f<=f6;
8'b00100101:  f<=f7;		 
8'b00100110:  f<=f9;
8'b01111100:  f<=f2;
8'b00000010:  f<=f3;
8'b00011111:  f<=f8;
8'b00000011:  f<=f11;
8'b00000111:  f<=f4;
8'b00001111:  f<=f5;
8'b00111111: f<=f12;
8'b01111111: f<=f13;
	default: f<=0;
endcase;
end
endmodule
module mux8to1(d0, d1, d2, d3, d4, d5, d6, d7, s0, s1, s2, f);
	input d0, d1, d2, d3, d4, d5, d6, d7, s0, s1, s2;
	output f;
	wire w1,w2;
	mux4to1 mux0 (d0, d1, d2, d3, s0, s1, w1);
	mux4to1 mux1 (d4, d5, d6, d7, s0, s1, w2);
	mux2to1 mux2 (w1, w2, s2, f);
endmodule
module mux4to1(d0, d1, d2, d3, s0, s1, f);
	input d0, d1, d2, d3, s0, s1;
	output f;
	wire w1,w2;
	mux2to1 mux0 (d0, d1, s0, w1);
	mux2to1 mux1 (d2, d3, s0, w2);
	mux2to1 mux2 (w1, w2, s1, f);
endmodule
module mux2to1(d0, d1, s0, f);
	input d0, d1, s0;
	output f;
	
	and(w17, d1, s0);
	not(w15, s0);
	and(w18, w15, d0);
	or(f, w17, w18);
endmodule
module adder32(A,
               B,
               S,
               C32);
    input [31:0] A;
    input [31:0] B;
    output [31:0] S;
    output C32;
    
    wire px1,gx1,px2,gx2;
    wire c16;
    wire zero;
    assign zero=1'b0;
    
    CLA_16 CLA1(
    .A(A[15:0]),
    .B(B[15:0]),
    .c0(zero),
    .S(S[15:0]),
    .px(px1),
    .gx(gx1)
    );
    
    CLA_16 CLA2(
    .A(A[31:16]),
    .B(B[31:16]),
    .c0(c16),
    .S(S[31:16]),
    .px(px2),
    .gx(gx2)
    );
    xor (c16,gx1,0);
    wire px2c16;
    and (px2c16,px2,c16);
    xor (C32,gx2,px2c16);
    
    
endmodule
module adder(X,
	Y,
	Cin,
	F,
	Cout);
	
	input X,Y,Cin;
	output F,Cout;
	xor (F,X,Y,Cin);
	wire XxorY,XxorYandCin,XY;
	xor (XxorY,X,Y);
	and (XxorYandCin,XxorY,Cin);
	and (XY,X,Y);
	or (Cout,XxorYandCin,XY);
	
endmodule
module CLA(c0,c1,c2,c3,c4,p1,p2,p3,p4,g1,g2,g3,g4);
	
	input c0,g1,g2,g3,g4,p1,p2,p3,p4;
	output c1,c2,c3,c4;
	wire p1c0,p2g1,p2p1c0,p3g2,p3p2g1,p3p2p1c0,p4g3,p4p3g2,p4p3p2g1,p4p3p2p1c0;
	and(p1c0,p1,c0),
	(p2g1,p2,g1),
	(p2p1c0,p2,p1c0),
	(p3g2,p3,g2),
	(p3p2g1,p3,p2g1),
	(p3p2p1c0,p3,p2p1c0),
	(p4g3,p4,g3),
	(p4p3g2,p4,p3g2),
	(p4p3p2g1,p4,p3p2g1);
	xor (c1,g1,p1c0),
	(c2,g2,p2g1,p2p1c0),
	(c3,g3,p3g2,p3p2g1,p3p2p1c0),
	(c4,g4,p4g3,p4p3g2,p4p3p2g1);
	
endmodule
module adder_4(x,y,c0,c4,F,Gm,Pm);
	input [3:0] x;
	input [3:0] y;
	input c0;
	output c4,Gm,Pm;
	output [3:0] F;
	
	wire p1,p2,p3,p4,g1,g2,g3,g4;
	wire c1,c2,c3;
	adder adder1(
	.X(x[0]),
	.Y(y[0]),
	.Cin(c0),
	.F(F[0]),
	.Cout()
	);
	
	adder adder2(
	.X(x[1]),
	.Y(y[1]),
	.Cin(c1),
	.F(F[1]),
	.Cout()
	);
	
	adder adder3(
	.X(x[2]),
	.Y(y[2]),
	.Cin(c2),
	.F(F[2]),
	.Cout()
	);
	
	adder adder4(
	.X(x[3]),
	.Y(y[3]),
	.Cin(c3),
	.F(F[3]),
	.Cout()
	);
	
	CLA CLA(
	.c0(c0),
	.c1(c1),
	.c2(c2),
	.c3(c3),
	.c4(c4),
	.p1(p1),
	.p2(p2),
	.p3(p3),
	.p4(p4),
	.g1(g1),
	.g2(g2),
	.g3(g3),
	.g4(g4)
	);
	
	xor (p1,x[0],y[0]),
	(p2,x[1],y[1]),
	(p3,x[2],y[2]),
	(p4,x[3],y[3]);
	
	and (g1,x[0],y[0]),
	(g2,x[1],y[1]),
	(g3,x[2],y[2]),
	(g4,x[3],y[3]);
	
	wire p4g3,p4p3g2,p4p3p2g1;
	and(Pm,p1,p2,p3,p4),
	(p4g3,p4,g3),
	(p4p3g2,p4,p3,g2),
	(p4p3p2g1,p4,p3,p2,g1);
	xor (Gm,g4,p4g3,p4p3g2,p4p3p2g1);
	
	
endmodule
module CLA_16(A,B,c0,S,px,gx);
	input [15:0] A;
	input [15:0] B;
	input c0;
	output gx,px;
	output [15:0] S;
	
	wire c4,c8,c12;
	wire Pm1,Gm1,Pm2,Gm2,Pm3,Gm3,Pm4,Gm4;
	
	adder_4 adder1(
	.x(A[3:0]),
	.y(B[3:0]),
	.c0(c0),
	.c4(),
	.F(S[3:0]),
	.Gm(Gm1),
	.Pm(Pm1)
	);
	
	adder_4 adder2(
	.x(A[7:4]),
	.y(B[7:4]),
	.c0(c4),
	.c4(),
	.F(S[7:4]),
	.Gm(Gm2),
	.Pm(Pm2)
	);
	
	adder_4 adder3(
	.x(A[11:8]),
	.y(B[11:8]),
	.c0(c8),
	.c4(),
	.F(S[11:8]),
	.Gm(Gm3),
	.Pm(Pm3)
	);
	
	adder_4 adder4(
	.x(A[15:12]),
	.y(B[15:12]),
	.c0(c12),
	.c4(),
	.F(S[15:12]),
	.Gm(Gm4),
	.Pm(Pm4)
	);
	wire Pm1c0,Pm2Gm1,Pm2Pm1c0,Pm3Gm2,Pm3Pm2Gm1,Pm3Pm2Pm1c0;
	and (Pm1c0,Pm1,c0),
	(Pm2Gm1,Pm2,Gm1),
	(Pm2Pm1c0,Pm2,Pm1,c0),
	(Pm3Gm2,Pm3,Gm2),
	(Pm3Pm2Gm1,Pm3,Pm2,Gm1),
	(Pm3Pm2Pm1c0,Pm3,Pm2,Pm1,c0);
	xor (c4,Gm1,Pm1c0),
	(c8,Gm2,Pm2Gm1,Pm2Pm1c0),
	(c12,Gm3,Pm3Gm2,Pm3Pm2Gm1,Pm3Pm2Pm1c0);
	
	wire Pm4Gm3,Pm4Pm3Gm2,Pm4Pm3Pm2Gm1;
	and (px,Pm1,Pm2,Pm3,Pm4),
	(Pm4Gm3,Pm4,Gm3),
	(Pm4Pm3Gm2,Pm4,Pm3,Gm2),
	(Pm4Pm3Pm2Gm1,Pm4,Pm3,Pm2,Gm1);
	xor (gx,Gm4,Pm4Gm3,Pm4Pm3Gm2,Pm4Pm3Pm2Gm1);
	
endmodule
module shiftbitleft(c,a,b);
output [31:0]c;
input [31:0]a;
input [4:0]b;// indicates the shifted bit??
wire [31:0]d,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16,d17,d18
,d19,d20,d21,d22,d23,d24,d25,d26,d27,d28,d29,d30,d31;
assign d={31'd0,a[0]};
assign d1={30'd0,a[0],a[1]};
assign d2={29'd0,a[0],a[1],a[2]};
assign d3={28'd0,a[0],a[1],a[2],a[3]};
assign d4={27'd0,a[0],a[1],a[2],a[3],a[4]};
assign d5={26'd0,a[0],a[1],a[2],a[3],a[4],a[5]};
assign d6={25'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6]};
assign d7={24'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7]};
assign d8={23'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8]};
assign d9={22'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9]};
assign d10={21'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10]};
assign d11={20'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11]};
assign d12={19'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12]};
assign d13={18'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13]};
assign d14={17'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14]};
assign d15={16'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15]};
assign d16={15'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16]};
assign d17={14'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17]};
assign d18={13'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18]};
assign d19={12'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19]};
assign d20={11'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20]};
assign d21={10'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21]};
assign d22={9'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22]};
assign d23={8'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23]};
assign d24={7'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23],a[24]};
assign d25={6'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23],a[24],a[25]};
assign d26={5'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23],a[24],a[25],a[26]};
assign d27={4'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23],a[24],a[25],a[26],a[27]};
assign d28={3'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23],a[24],a[25],a[26],a[27],a[28]};
assign d29={2'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23],a[24],a[25],a[26],a[27],a[28],a[29]};
assign d30={1'd0,a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23],a[24],a[25],a[26],a[27],a[28],a[29],a[30]};
assign d31={a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16],a[17],a[18],a[19],a[20],a[21],a[22],a[23],a[24],a[25],a[26],a[27],a[28],a[29],a[30],a[31]};
mux32 m1(d,b,c[0]);
mux32 m2(d1,b,c[1]);
mux32 m3(d2,b,c[2]);
mux32 m4(d3,b,c[3]);
mux32 m5(d4,b,c[4]);
mux32 m6(d5,b,c[5]);
mux32 m7(d6,b,c[6]);
mux32 m8(d7,b,c[7]);
mux32 m9(d8,b,c[8]);
mux32 m10(d9,b,c[9]);
mux32 m11(d10,b,c[10]);
mux32 m12(d11,b,c[11]);
mux32 m13(d12,b,c[12]);
mux32 m14(d13,b,c[13]);
mux32 m15(d14,b,c[14]);
mux32 m16(d15,b,c[15]);
mux32 m17(d16,b,c[16]);
mux32 m18(d17,b,c[17]);
mux32 m19(d18,b,c[18]);
mux32 m20(d19,b,c[19]);
mux32 m21(d20,b,c[20]);
mux32 m22(d21,b,c[21]);
mux32 m23(d22,b,c[22]);
mux32 m24(d23,b,c[23]);
mux32 m25(d24,b,c[24]);
mux32 m26(d25,b,c[25]);
mux32 m27(d26,b,c[26]);
mux32 m28(d27,b,c[27]);
mux32 m29(d28,b,c[28]);
mux32 m30(d29,b,c[29]);
mux32 m31(d30,b,c[30]);
mux32 m32(d31,b,c[31]);
endmodule
module shiftbitright(c,a,b);
input [31:0]a;

input [4:0]b;
output [31:0]c;
wire [31:0]d0,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15,d16,d17,d18
,d19,d20,d21,d22,d23,d24,d25,d26,d27,d28,d29,d30,d31;
assign d0={31'd0,a[31]};
assign d1={30'd0,a[31],a[30]};
assign d2={29'd0,a[31],a[30],a[29]};
assign d3={28'd0,a[31],a[30],a[29],a[28]};
assign d4={27'd0,a[31],a[30],a[29],a[28],a[27]};
assign d5={26'd0,a[31],a[30],a[29],a[28],a[27],a[26]};
assign d6={25'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25]};
assign d7={24'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24]};
assign d8={23'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23]};
assign d9={22'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22]};
assign d10={21'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21]};
assign d11={20'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20]};
assign d12={19'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19]};
assign d13={18'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18]};
assign d14={17'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17]};
assign d15={16'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16]};
assign d16={15'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15]};
assign d17={14'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14]};
assign d18={13'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13]};
assign d19={12'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12]};
assign d20={11'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11]};
assign d21={10'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10]};
assign d22={9'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9]};
assign d23={8'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9],a[8]};
assign d24={7'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9],a[8],a[7]};
assign d25={6'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9],a[8],a[7],a[6]};
assign d26={5'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9],a[8],a[7],a[6],a[5]};
assign d27={4'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9],a[8],a[7],a[6],a[5],a[4]};
assign d28={3'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9],a[8],a[7],a[6],a[5],a[4],a[3]};
assign d29={2'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9],a[8],a[7],a[6],a[5],a[4],a[3],a[2]};
assign d30={1'd0,a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9],a[8],a[7],a[6],a[5],a[4],a[3],a[2],a[1]};
assign d31={a[31],a[30],a[29],a[28],a[27],a[26],a[25],a[24],a[23],a[22],a[21],a[20],a[19],a[18],a[17],a[16],a[15],a[14],a[13],a[12],a[11],a[10],a[9],a[8],a[7],a[6],a[5],a[4],a[3],a[2],a[1],a[0]};
mux32 m1(d31,b,c[0]);
mux32 m2(d30,b,c[1]);
mux32 m3(d29,b,c[2]);
mux32 m4(d28,b,c[3]);
mux32 m5(d27,b,c[4]);
mux32 m6(d26,b,c[5]);
mux32 m7(d25,b,c[6]);
mux32 m8(d24,b,c[7]);
mux32 m9(d23,b,c[8]);
mux32 m10(d22,b,c[9]);
mux32 m11(d21,b,c[10]);
mux32 m12(d20,b,c[11]);
mux32 m13(d19,b,c[12]);
mux32 m14(d18,b,c[13]);
mux32 m15(d17,b,c[14]);
mux32 m16(d16,b,c[15]);
mux32 m17(d15,b,c[16]);
mux32 m18(d14,b,c[17]);
mux32 m19(d13,b,c[18]);
mux32 m20(d12,b,c[19]);
mux32 m21(d11,b,c[20]);
mux32 m22(d10,b,c[21]);
mux32 m23(d9,b,c[22]);
mux32 m24(d8,b,c[23]);
mux32 m25(d7,b,c[24]);
mux32 m26(d6,b,c[25]);
mux32 m27(d5,b,c[26]);
mux32 m28(d4,b,c[27]);
mux32 m29(d3,b,c[28]);
mux32 m30(d2,b,c[29]);
mux32 m31(d1,b,c[30]);
mux32 m32(d0,b,c[31]);
endmodule
module mux32(x,y,f);
input [31:0]x;
input [4:0]y;
output f;
mux16to1 mux1(x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],x[8],x[9],x[10],x[11],x[12],x[13],x[14],x[15],y[0],y[1],y[2],y[3],w1);
mux16to1 mux2(x[16],x[17],x[18],x[19],x[20],x[21],x[22],x[23],x[24],x[25],x[26],x[27],x[28],x[29],x[30],x[31],y[0],y[1],y[2],y[3],w2);
mux2to1 mux3(w1,w2,y[4],f);


endmodule
module mux16to1(d0, d1, d2, d3, d4, d5, d6, d7,d8,d9,d10,d11,d12,d13,d14,d15, s0, s1, s2, s3,f);
input d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14,d15;
input s0, s1, s2, s3;
output f;
mux8to1 mux0(d0,d1,d2,d3,d4,d5,d6,d7,s0,s1,s2,w1);
mux8to1 mux1(d8,d9,d10,d11,d12,d13,d14,d15,s0,s1,s2,w2);
mux2to1 mux3(w1,w2,s3,f);
endmodule
module right_truncation(f,x,y);//Cut from low?
input  [31:0] x;
input  [4:0]y;
output [31:0]f;
wire [31:0]temp;
assign temp=1<<(y-1);
wire temp2;
assign temp2=0;
or or1(w1,temp[31],temp2);and and1(f[31],x[0],w1);
or or2(w2,temp[30],w1);and and2(f[30],x[1],w2);
or or3(w3,temp[29],w2);and and3(f[29],x[2],w3);
or or4(w4,temp[28],w3);and and4(f[28],x[3],w4);
or or5(w5,temp[27],w4);and and5(f[27],x[4],w5);
or or6(w6,temp[26],w5);and and6(f[26],x[5],w6);
or or7(w7,temp[25],w6);and and7(f[25],x[6],w7);
or or8(w8,temp[24],w7);and and8(f[24],x[7],w8);
or or9(w9,temp[23],w8);and and9(f[23],x[8],w9);
or or10(w10,temp[22],w9);and and10(f[22],x[9],w10);
or or11(w11,temp[21],w10);and and11(f[21],x[10],w11);
or or12(w12,temp[20],w11);and and12(f[20],x[11],w12);
or or13(w13,temp[19],w12);and and13(f[19],x[12],w13);
or or14(w14,temp[18],w13);and and14(f[18],x[13],w14);
or or15(w15,temp[17],w14);and and15(f[17],x[14],w15);
or or16(w16,temp[16],w15);and and16(f[16],x[15],w16);
or or17(w17,temp[15],w16);and and17(f[15],x[16],w17);
or or18(w18,temp[14],w17);and and18(f[14],x[17],w18);
or or19(w19,temp[13],w18);and and19(f[13],x[18],w19);
or or20(w20,temp[12],w19);and and20(f[12],x[19],w20);
or or21(w21,temp[11],w20);and and21(f[11],x[20],w21);
or or22(w22,temp[10],w21);and and22(f[10],x[21],w22);
or or23(w23,temp[9],w22);and and23(f[9],x[22],w23);
or or24(w24,temp[8],w23);and and24(f[8],x[23],w24);
or or25(w25,temp[7],w24);and and25(f[7],x[24],w25);
or or26(w26,temp[6],w25);and and26(f[6],x[25],w26);
or or27(w27,temp[5],w26);and and27(f[5],x[26],w27);
or or28(w28,temp[4],w27);and and28(f[4],x[27],w28);
or or29(w29,temp[3],w28);and and29(f[3],x[28],w29);
or or30(w30,temp[2],w29);and and30(f[2],x[29],w30);
or or31(w31,temp[1],w30);and and31(f[1],x[30],w31);
or or32(w32,temp[0],w31);and and32(f[0],x[31],w32);
endmodule
//Cut off from high level??
module left_truncation(f,x,y);
input [31:0]x;
input [4:0]y;
output [31:0]f;
wire [31:0]temp;
assign temp=1<<(y-1);

wire temp2;
assign temp2=0;
or or1(w1,temp[31],temp2);and and1(f[0],x[0],w1);
or or2(w2,temp[30],w1);and and2(f[1],x[1],w2);
or or3(w3,temp[29],w2);and and3(f[2],x[2],w3);
or or4(w4,temp[28],w3);and and4(f[3],x[3],w4);
or or5(w5,temp[27],w4);and and5(f[4],x[4],w5);
or or6(w6,temp[26],w5);and and6(f[5],x[5],w6);
or or7(w7,temp[25],w6);and and7(f[6],x[6],w7);
or or8(w8,temp[24],w7);and and8(f[7],x[7],w8);
or or9(w9,temp[23],w8);and and9(f[8],x[8],w9);
or or10(w10,temp[22],w9);and and10(f[9],x[9],w10);
or or11(w11,temp[21],w10);and and11(f[10],x[10],w11);
or or12(w12,temp[20],w11);and and12(f[11],x[11],w12);
or or13(w13,temp[19],w12);and and13(f[12],x[12],w13);
or or14(w14,temp[18],w13);and and14(f[13],x[13],w14);
or or15(w15,temp[17],w14);and and15(f[14],x[14],w15);
or or16(w16,temp[16],w15);and and16(f[15],x[15],w16);
or or17(w17,temp[15],w16);and and17(f[16],x[16],w17);
or or18(w18,temp[14],w17);and and18(f[17],x[17],w18);
or or19(w19,temp[13],w18);and and19(f[18],x[18],w19);
or or20(w20,temp[12],w19);and and20(f[19],x[19],w20);
or or21(w21,temp[11],w20);and and21(f[20],x[20],w21);
or or22(w22,temp[10],w21);and and22(f[21],x[21],w22);
or or23(w23,temp[9],w22);and and23(f[22],x[22],w23);
or or24(w24,temp[8],w23);and and24(f[23],x[23],w24);
or or25(w25,temp[7],w24);and and25(f[24],x[24],w25);
or or26(w26,temp[6],w25);and and26(f[25],x[25],w26);
or or27(w27,temp[5],w26);and and27(f[26],x[26],w27);
or or28(w28,temp[4],w27);and and28(f[27],x[27],w28);
or or29(w29,temp[3],w28);and and29(f[28],x[28],w29);
or or30(w30,temp[2],w29);and and30(f[29],x[29],w30);
or or31(w31,temp[1],w30);and and31(f[30],x[30],w31);
or or32(w32,temp[0],w31);and and32(f[31],x[31],w32);

endmodule
//32-bit with operations
module bitwiseand(x,y,f);
	input [31:0] x, y;
	output [31:0] f;
	
	and and1[31:0](f,x,y);
endmodule
module bitwiseor(x,y,f);
	input [31:0] x, y;
	output [31:0] f;
	
	or(f[0],x[0],y[0]);
	or(f[1],x[1],y[1]);
	or(f[2],x[2],y[2]);
	or(f[3],x[3],y[3]);
	or(f[4],x[4],y[4]);
	or(f[5],x[5],y[5]);
	or(f[6],x[6],y[6]);
	or(f[7],x[7],y[7]);
	or(f[8],x[8],y[8]);
	or(f[9],x[9],y[9]);
	or(f[10],x[10],y[10]);
	or(f[11],x[11],y[11]);
	or(f[12],x[12],y[12]);
	or(f[13],x[13],y[13]);
	or(f[14],x[14],y[14]);
	or(f[15],x[15],y[15]);
	or(f[16],x[16],y[16]);
	or(f[17],x[17],y[17]);
	or(f[18],x[18],y[18]);
	or(f[19],x[19],y[19]);
	or(f[20],x[20],y[20]);
	or(f[21],x[21],y[21]);
	or(f[22],x[22],y[22]);
	or(f[23],x[23],y[23]);
	or(f[24],x[24],y[24]);
	or(f[25],x[25],y[25]);
	or(f[26],x[26],y[26]);
	or(f[27],x[27],y[27]);
	or(f[28],x[28],y[28]);
	or(f[29],x[29],y[29]);
	or(f[30],x[30],y[30]);
	or(f[31],x[31],y[31]);
endmodule
module no(out,x);
output [31:0] out;
input [31:0] x;
not not1[31:0](out,x);
endmodule
module xor32 (out,x,y);
input [31:0]x;
input [31:0]y;
output [31:0]out;
xor(out[0],x[0],y[0]);
xor(out[1],x[1],y[1]);
xor(out[2],x[2],y[2]);
xor(out[3],x[3],y[3]);
xor(out[4],x[4],y[4]);
xor(out[5],x[5],y[5]);
xor(out[6],x[6],y[6]);
xor(out[7],x[7],y[7]);
xor(out[8],x[8],y[8]);
xor(out[9],x[9],y[9]);
xor(out[10],x[10],y[10]);
xor(out[11],x[11],y[11]);
xor(out[12],x[12],y[12]);
xor(out[13],x[13],y[13]);
xor(out[14],x[14],y[14]);
xor(out[15],x[15],y[15]);
xor(out[16],x[16],y[16]);
xor(out[17],x[17],y[17]);
xor(out[18],x[18],y[18]);
xor(out[19],x[19],y[19]);
xor(out[20],x[20],y[20]);
xor(out[21],x[21],y[21]);
xor(out[22],x[22],y[22]);
xor(out[23],x[23],y[23]);
xor(out[24],x[24],y[24]);
xor(out[25],x[25],y[25]);
xor(out[26],x[26],y[26]);
xor(out[27],x[27],y[27]);
xor(out[28],x[28],y[28]);
xor(out[29],x[29],y[29]);
xor(out[30],x[30],y[30]);
xor(out[31],x[31],y[31]);
endmodule
// 32bit right_shift_arithmetic
module right_shift_arithmetic (
   input signed [31:0] data_in, 
   input [4:0] shift_amount,   
   output reg[31:0] data_out 
);
always @(*) begin
	data_out<=({32{data_in[31]}} << (6'd32-{1'b0, shift_amount[4:0]})) |data_in >> shift_amount[4:0];
end
endmodule
//slt
module comparator32(
    input signed [31:0] A,
    input signed [31:0] B,
    output reg[31:0] result
   
);

  reg signed [31:0] A_comp;
  reg signed [31:0] B_comp;
  always @(*) begin
    if (A[31] == 1'b0 && B[31] == 1'b1) begin // A is positive, B is negative
      result=0;
    end
    else if (A[31] == 1'b1 && B[31] == 1'b0) begin // A is negative, B is positive
      result=1;
    end
    else begin // both are positive or negative
      result=A<B;
    end
  end

endmodule
//sltu
module comparator32_unsigned(
    input  [31:0] A,
    input  [31:0] B,
    output reg[31:0] result
   
);
  always @(*) begin
    result=A<B;
  end
endmodule

