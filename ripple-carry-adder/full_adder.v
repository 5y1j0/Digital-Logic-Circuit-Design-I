module full_adder (
input a, // input bit A
input b, // input bit B
input cin, // carry in from previous stage
output sum, // sum output
output cout // carry out
);

// sum = a XOR b XOR cin
assign sum = a ^ b ^ cin;

// cout = (a AND b) OR (b AND cin) OR (a AND cin)
assign cout = (a & b) | ( b & cin) | (a & cin);

endmodule
