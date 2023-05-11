/* 
 * scaled_address.v
 * Aim: Given a virtual address, compute the scaled address in a single cycle.
 * */

 `timescale 1ps/1ps

 module scaled_address(
                        input                     clk,                     // clock
                        input       [63:0]        baseAddrSeg,             // base address of the segment
                        input       [5:0]         cacheLineSize,           // size of the cache line
                        input       [5:0]         subCacheLineSize,        // size of the sub-cache line
                        input       [63:0]        virtualAddress,          // virtual address
                        input       [5:0]         offsetInCacheLine,       // offset in the cache line
                        output reg  [63:0]        scaledAddress            // scaled address
                    );

reg [63:0] temp;
reg [63:0] i;

always @(posedge clk) 
    begin
    temp <= virtualAddress - baseAddrSeg;
    
    case(subCacheLineSize)
        56: i = (temp * 146) >> 10;     // Division by 7
        48: i = (temp * 205) >> 10;     // Division by 5
        40: i = (temp * 341) >> 10;     // Division by 3 
    endcase

    offsetInCacheLine = temp % subCacheLineSize;
    scaledAddress = offsetInCacheLine + baseAddrSeg + (i * cacheLineSize);
    end

endmodule

