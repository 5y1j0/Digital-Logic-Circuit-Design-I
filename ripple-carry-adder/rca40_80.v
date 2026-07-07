module rca40_80 (S, A, B, Cout, Cin);
    input  [79:0] A, B; // 80-bit inputs A and B
    input         Cin; // carry in for the first 40-bit block
    output [79:0] S; // 80-bit sum outputs
    output        Cout; // carry out from the most significant 40-bit block

    wire carry; // internal carry wire between the two 40-bit RCA blocks
	 
	 // instantiate first 40-bit RCA block for bits [39:0]
    rca_40b r0 (S[39:0],  A[39:0],  B[39:0],  carry, Cin);
    // instantiate second 40-bit RCA block for bits [79:40]
	 rca_40b r1 (S[79:40], A[79:40], B[79:40], Cout,  carry);
endmodule
