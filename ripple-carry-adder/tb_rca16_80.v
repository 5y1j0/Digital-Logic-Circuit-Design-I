`timescale 1ns/1ps

module tb_rca_16b;
    // Testbench for the 80-bit RCA built from five 16-bit blocks

	 // Inputs to DUT
    reg  [79:0] A, B; // 80-bit operand A,B
    reg         Cin; // initial carry-in
    // Outputs from DUT
	 wire [79:0] S; // 80-bit sum output
    wire        Cout; // final carry-out

    // Instantiate the Device Under Test (DUT)
    rca16_80 DUT (
        .S   (S), // connect sum
        .A   (A), // connect operand A
        .B   (B), // connect operand B
        .Cout(Cout), // connect carry-out
        .Cin (Cin) // connect carry-in
    );

    initial begin
         // Test vector #1
        A   = 80'b01010101010101010101010101010101010101010101010101010101010101010101010101010101; 
        B   = 80'b10101010101010101010101010101010101010101010101010101010101010101010101010101010;
        Cin = 1'b0; // Cin = 0
        #10; // wait 10 ns
		  // Display the results
        $display("CIN=%b\nA   = %b\nB   = %b\nS   = %b\nCOUT= %b\n", Cin, A, B, S, Cout);

         // Test vector #2
        A   = 80'b00000000000000000000000000000000000000000000000000000000000000000000000000000000;
        B   = 80'b00000000000000000000000000000000000000000000000000000000000000000000000000000000; 
        Cin = 1'b0; // Cin = 0
        #10; // wait another 10 ns
		  // Display the results
        $display("CIN=%b\nA   = %b\nB   = %b\nS   = %b\nCOUT= %b\n", Cin, A, B, S, Cout);

		  // Test vector #3
        A   = 80'b11111111111111111111111111111111111111111111111111111111111111111111111111111111; 
        B   = 80'b11111111111111111111111111111111111111111111111111111111111111111111111111111111; 
        Cin = 1'b0; // Cin = 0
        #10; // wait 10 ns
		  // Display the results
        $display("CIN=%b\nA   = %b\nB   = %b\nS   = %b\nCOUT= %b\n", Cin, A, B, S, Cout);
		  
		  // Test vector #4
        A   = 80'b11111111111111111111111111111111111111111111111111111111111111111111111111111111; 
        B   = 80'b11111111111111111111111111111111111111111111111111111111111111111111111111111111; 
        Cin = 1'b1; // Cin = 0
        #10; // wait 10 ns
		  // Display the results
        $display("CIN=%b\nA   = %b\nB   = %b\nS   = %b\nCOUT= %b\n", Cin, A, B, S, Cout);
		 
		// Test vector #5
        A   = 80'b10000000000000000000000000000000000000000000000000000000000000000000000000000000; 
        B   = 80'b10000000000000000000000000000000000000000000000000000000000000000000000000000000; 
        Cin = 1'b1; // Cin = 0
        #10; // wait 10 ns
		  // Display the results
        $display("CIN=%b\nA   = %b\nB   = %b\nS   = %b\nCOUT= %b\n", Cin, A, B, S, Cout);
		// End simulation
        $finish;
    end
endmodule
