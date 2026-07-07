module rca_16b (S, A, B, Cout, Cin);
 input [15:0] A, B; // 16-bit inputs A and B
 input Cin; // carry in for the first adder
 output [15:0] S;  // 16-bit sum outputs
 output Cout; // carry out from the most significant bit

 wire [15:0] carry; // internal carry wires between adders
 
 genvar i; // loop variable for generate

 generate
 for (i=0; i<16; i=i+1) begin : fa_gen
 if (i==0)
 // first full adder uses Cin as its carry input
 full_adder FA0 (A[i], B[i], Cin, S[i], carry[i]);
 else
 // subsequent full adders use previous carry
 full_adder FA1 (A[i], B[i], carry[i-1], S[i], 
 carry[i]);
 end
 endgenerate
 
 // final carry out is the carry from the MSB adder
 assign Cout = carry[15];
 endmodule
 