/*
    Address Scaling Table stores the following information:
    1. Virtual Address Range: The start and end virtual address range of a segment 
                              that needs to be scaled.
    2. Physical Address Range: The start and end physical address range of a segment 
                                 that needs to be scaled.
    3. Scaling Factor: The scaling factor that needs to be applied

*/  

// Whenever CPU sends a request to memory, the request is checked against the
// address scaling table. If the request falls within the virtual address range
// of a segment, the request is scaled and sent to memory. If the request does
// not fall within the virtual address range of a segment, the request is sent
// to memory without any scaling.


#ifndef __MEM_AS_TABLE_HH__
#define __MEM_AS_TABLE_HH__


#include <iostream>
#include <vector>
#include <string>
#include "base/types.hh"


namespace gem5
{
    class AdressScalingTable 
    {
        public: 


            struct AddressScalingEntry
            {
                Addr startVirtualAddress;
                Addr endVirtualAddress;
                Addr startScaledVirtualAddress;
                Addr endScaledVirtualAddress;
                Addr scalingFactor;
            };
            
            AdressScalingTable();

            // Vector of Address Scaling Table Entries
            std::vector<AdressScalingTable> asTable;

            // Function to add an entry to the address scaling table
            void addEntry(Addr startVirtualAddress, Addr endVirtualAddress, Addr scalingFactor);

            // Function to check if the request falls within the virtual address range of a segment
            bool checkAddress(Addr requestAddress);

            // Function to scale the request address
            Addr scaleAddress(Addr requestAddress);

            // Update an Address Scaling Table Entry
            void updateEntry(Addr startVirtualAddress, Addr _startScaledVirtualAddress, Addr _endScaledVirtualAddress);

            

    };
} // namespace gem5
