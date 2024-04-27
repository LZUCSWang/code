`timescale 1ns / 1ps

module single_cycle_cpu_tb;

reg clk;
reg resetn;
reg [4:0] rf_addr;
reg [31:0] mem_addr;
wire [31:0] rf_data;
wire [31:0] mem_data;
wire [31:0] cpu_pc;
wire [31:0] cpu_inst;

single_cycle_cpu uut(
    .clk(clk),
    .resetn(resetn),
    .rf_addr(rf_addr),
    .mem_addr(mem_addr),
    .rf_data(rf_data),
    .mem_data(mem_data),
    .cpu_pc(cpu_pc),
    .cpu_inst(cpu_inst)
);

initial begin
    // Initialize inputs
    clk = 0;
    resetn = 0;
    rf_addr = 0;
    mem_addr = 0;

    // Apply reset
    #10 resetn = 1;

    // Test case 1
    #10 mem_addr = 0;
    #10 rf_addr = 1;
    #10 clk = 1;
    #10 clk = 0;

    // Add more test cases as needed

    #10 $finish;
end

// Add clock generation if necessary
always #5 clk = ~clk;

endmodule
