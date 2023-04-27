// Header file for the address scaling table class.

/*  Whenever CPU sends a request to memory, the request is checked against the address scaling table.
    If the request falls within the virtual address range of a segment, the request is scaled and sent
    to memory. If the request does not fall within the virtual address range of a segment, the request
    is sent to memory without any scaling.
*/


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

            /*
                Address Scaling Table Entry:
                    1. Virtual Address Range: The start and end virtual address range of a segment that needs to be scaled.
                    2. Start Scaled Virtual Address: The base address of the scaled virtual address range of a segment
                    3. Scaling Factor: The scaling factor that needs to be applied to a virtual address     
            */

            // An entry in the address scaling table
            struct AddressScalingEntry
            {
                // Start and end virtual address range of a segment
                Addr startVirtualAddress;
                Addr endVirtualAddress;
                // Start scaled virtual address 
                Addr startScaledVirtualAddress;

                // Not storing the end scaled virtual address as it can be calculated using the scaling factor
            };
            
            // Constructor - Initialize the scaling factor 
            AddressScalingTable(int _scalingFactor);

            // Desctructor
            ~AddressScalingTable();

            // The scaling factor that needs to be applied to a virtual address
            int scalingFactor;

            // Vector of Address Scaling Table Entries
            std::vector<AddressScalingEntry> asTable;

            // Add an entry to the address scaling table
            void addEntry(Addr startVirtualAddress, Addr endVirtualAddress, int scalingFactor);

            // Check if the request falls within the virtual address range of a segment
            bool checkAddress(Addr requestAddress);

            // Scale the requested address
            Addr scaleAddress(Addr requestAddress);

            // Update the scaled virtual address range of a segment in the address scaling table
            void updateAddressScalingEntry(AddressScalingEntry &entry, Addr _startVirtualAddress);
            
    };
} // namespace gem5

#endif // __MEM_AS_TABLE_HH__
