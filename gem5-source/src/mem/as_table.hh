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
    class AddressScalingTable 
    {
        public: 


            struct AddressScalingEntry
            {
                Addr startVirtualAddress;
                Addr endVirtualAddress;
                Addr startScaledVirtualAddress;
                Addr endScaledVirtualAddress;
                
            };
            
            AddressScalingTable(int _scalingFactor);

            // Desctructor
            ~AddressScalingTable();
            
            // Scaling Factor
            int scalingFactor;

            // Vector of Address Scaling Table Entries
            std::vector<AddressScalingEntry> asTable;

            // Function to add an entry to the address scaling table
            void addEntry(Addr startVirtualAddress, Addr endVirtualAddress, int scalingFactor);

            // Function to check if the request falls within the virtual address range of a segment
            bool checkAddress(Addr requestAddress);

            // Function to scale the request address
            Addr scaleAddress(Addr requestAddress);

            // Update the scaled virtual address range of a segment
            void updateAddressScalingEntry(AddressScalingEntry &entry, Addr _startScaledVirtualAddress, Addr _endScaledVirtualAddress);
            

    };
} // namespace gem5

#endif // __MEM_AS_TABLE_HH__
