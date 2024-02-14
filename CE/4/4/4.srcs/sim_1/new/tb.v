`timescale 1ns / 1ps

module alu_tb;
    reg [11:0] alu_control;
    reg [31:0] alu_src1;
    reg [31:0] alu_src2;
    wire [31:0] alu_result;

    alu alu_inst (
        .alu_control(alu_control),
        .alu_src1(alu_src1),
        .alu_src2(alu_src2),
        .alu_result(alu_result)
    );

    initial begin
        // Test ALU operations here
        // ALU_ADD
        alu_control = 12'b100000000000;
        alu_src1 = 32'h00000001;
        alu_src2 = 32'h00000002;
        #10 $display("ALU_ADD: alu_result = %h", alu_result);

        // ALU_SUB
        alu_control = 12'b010000000000;
        alu_src1 = 32'h00000003;
        alu_src2 = 32'h00000001;
        #10 $display("ALU_SUB: alu_result = %h", alu_result);

        // ALU_SLT
        alu_control = 12'b001000000000;
        alu_src1 = 32'hFFFFFFFE;
        alu_src2 = 32'h00000001;
        #10 $display("ALU_SLT: alu_result = %h", alu_result);

        // ALU_SLTU
        alu_control = 12'b000100000000;
        alu_src1 = 32'h00000001;
        alu_src2 = 32'hFFFFFFFE;
        #10 $display("ALU_SLTU: alu_result = %h", alu_result);

        // ALU_AND
        alu_control = 12'b000010000000;
        alu_src1 = 32'hAAAAAAAA;
        alu_src2 = 32'h55555555;
        #10 $display("ALU_AND: alu_result = %h", alu_result);

        // ALU_NOR
        alu_control = 12'b000001000000;
        alu_src1 = 32'hA5A5A5A5;
        alu_src2 = 32'h5A5A5A5A;
        #10 $display("ALU_NOR: alu_result = %h", alu_result);

        // ALU_OR
        alu_control = 12'b000000100000;
        alu_src1 = 32'hF0F0F0F0;
        alu_src2 = 32'h0F0F0F0F;
        #10 $display("ALU_OR: alu_result = %h", alu_result);

        // ALU_XOR
        alu_control = 12'b000000010000;
        alu_src1 = 32'h12345678;
        alu_src2 = 32'h87654321;
        #10 $display("ALU_XOR: alu_result = %h", alu_result);

        // ALU_SLL
        alu_control = 12'b000000001000;
        alu_src1 = 32'h00000001;
        alu_src2 = 5'b00100;
        #10 $display("ALU_SLL: alu_result = %h", alu_result);

        // ALU_SRL
        alu_control = 12'b000000000100;
        alu_src1 = 32'h00000004;
        alu_src2 = 32'hF0000000;
        #10 $display("ALU_SRL: alu_result = %h", alu_result);

        // ALU_SRA
        alu_control = 12'b000000000010;
        alu_src1 = 32'h00000004;
        alu_src2 = 32'hF0000000;
        #10 $display("ALU_SRA: alu_result = %h", alu_result);

        // ALU_LUI
        alu_control = 12'b000000000001;
        alu_src1 = 32'h00000001;
        alu_src2 = 32'h00001234;
        #10 $display("ALU_LUI: alu_result = %h", alu_result);

        $finish;
    end
endmodule
