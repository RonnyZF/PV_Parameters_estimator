`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 31.03.2019 22:55:55
// Design Name: 
// Module Name: tb_estimador_solo
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


module tb_estimador_solo();

    reg clk;
    wire ap_ctrl_0_done;
    wire ap_ctrl_0_idle;
    wire ap_ctrl_0_ready;
    reg ap_ctrl_0_start;
    wire [31:0] ap_return_0;
    reg rst;
    wire [31:0] interface_param_apprx_1_V_0;
    wire [31:0] interface_param_apprx_2_V_0;
    reg [15:0] seq_in_xadc_0_tdata;
    reg [4:0] seq_in_xadc_0_tid;
    wire seq_in_xadc_0_tready;
    reg seq_in_xadc_0_tvalid;
    
    reg [4:0]ch1;
    reg [4:0]ch2;
    int sel=0;

    design_5_wrapper DUT(
        .ap_clk_0(clk),
        .ap_ctrl_0_done(ap_ctrl_0_done),
        .ap_ctrl_0_idle(ap_ctrl_0_idle),
        .ap_ctrl_0_ready(ap_ctrl_0_ready),
        .ap_ctrl_0_start(ap_ctrl_0_start),
        .ap_return_0(ap_return_0),
        .ap_rst_n_0(rst),
        .interface_param_apprx_1_V_0(interface_param_apprx_1_V_0),
        .interface_param_apprx_2_V_0(interface_param_apprx_2_V_0),
        .seq_in_xadc_0_tdata(seq_in_xadc_0_tdata),
        .seq_in_xadc_0_tid(seq_in_xadc_0_tid),
        .seq_in_xadc_0_tready(seq_in_xadc_0_tready),
        .seq_in_xadc_0_tvalid(seq_in_xadc_0_tvalid)
        );
    
    task reset();
        rst=0;
        repeat(10) @(posedge clk);
        rst=1;
        ap_ctrl_0_start=1;
        seq_in_xadc_0_tdata=16'd0;
        seq_in_xadc_0_tid=5'd0;
        seq_in_xadc_0_tvalid=1'd0;
    endtask    
    
    task send_samples_v(input logic [15:0] data);
        sel=1;
        seq_in_xadc_0_tid=5'h10;
        seq_in_xadc_0_tvalid=1;
        repeat(20) @(posedge clk);
        seq_in_xadc_0_tvalid=0;
    endtask
    
    task send_samples_i(input logic [15:0] data);
        sel=0;
        seq_in_xadc_0_tid=5'h18;
        seq_in_xadc_0_tvalid=1;
        repeat(20) @(posedge clk);
        seq_in_xadc_0_tvalid=0;
    endtask
        
    initial begin
        clk=1;
    end
    
    always #5 clk=~clk;    
    
    initial begin
        reset();
        
        for(int i=0;i<100;i++) begin
            repeat(100) @(posedge clk);
            end
            seq_in_xadc_0_tdata+=1;
            if(sel==0)begin
                send_samples_v(seq_in_xadc_0_tdata);
            end
            else if(sel==1)begin
                send_samples_i(seq_in_xadc_0_tdata);
            end
        end
endmodule
