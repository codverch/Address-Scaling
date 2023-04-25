/* Address Scaling Table stores the following information:
   1. Virtual Address Range: The start and end virtual address range of a segment 
                             that needs to be scaled.
   2. Physical Address Range: The start and end physical address range of a segment 
                                that needs to be scaled.
   3. Scaling Factor: The scaling factor that needs to be applied 
*/

#include "mem/as_table.hh"
#include "base/types.hh"


namespace gem5
{

    /* Constructor */
    AddressScalingTable::AddressScalingTable( int _scalingFactor)
    {

        // Set the scaling factor
        scalingFactor = _scalingFactor;

    }

    /* Add an entry to the Address Scaling Table */
    void 
    AddressScalingTable::addEntry(Addr _startVirtualAddress, Addr _endVirtualAddress,  int _scalingFactor)
    {

        // Check that the end virtual address is greater than or equal to the start virtual address
        if (_endVirtualAddress < _startVirtualAddress) 
        {
            std::cout << "End virtual address must be greater than or equal to start virtual address" << std::endl;
        }
        
        // Create a new entry
        AddressScalingEntry newEntry;
        newEntry.startVirtualAddress = _startVirtualAddress;
        newEntry.endVirtualAddress = _endVirtualAddress;
        // Set the start and end scaled virtual address to 0, they will be set later
        newEntry.startScaledVirtualAddress = 0;
        newEntry.endScaledVirtualAddress = 0;

        // Add the new entry to the address scaling table
        asTable.push_back(newEntry);
    }

    /* Check if the requested address falls within the virtual address range of any segment */
    bool
    AddressScalingTable::checkAddress(Addr requestAddress)
    {
        // Iterate through the address scaling table
        for (int i = 0; i < asTable.size(); i++)
        {
            // Check if the request address falls within the virtual address range of the segment
            if (requestAddress >= asTable[i].startVirtualAddress && requestAddress <= asTable[i].endVirtualAddress)
            {
                return true;
            }
        }

        // If the request address does not fall within the virtual address range of any segment, return false
        return false;
    }

   
    /* Scale the request address */
    
    Addr
    AddressScalingTable::scaleAddress(Addr requestAddress)
    {
    // Check if the requested address falls within the virtual address range of any segment
    if (checkAddress(requestAddress))
    {
        // Find the segment that contains the request address
        AddressScalingEntry segment;
        for (auto& entry : asTable)
        {
            if (requestAddress >= entry.startVirtualAddress && requestAddress <= entry.endVirtualAddress)
            {
                segment = entry;
                break;
            }
        }

        // Calculate the scaled address with the offset
        Addr offset = requestAddress - segment.startVirtualAddress;
        Addr scaledAddress = (offset * scalingFactor) + segment.startScaledVirtualAddress;

        // Update the scaled virtual address range of the segment
        updateAddressScalingEntry(segment, segment.startVirtualAddress, segment.endVirtualAddress);

        return scaledAddress;
    }

    // If the request address does not fall within the virtual address range of any segment, do not scale the address
    return requestAddress;
   
    }


    /* Update an Address Scaling Entry */
    void 
    AddressScalingTable::updateAddressScalingEntry(AddressScalingEntry &entry, Addr _startVirtualAddress, Addr _endVirtualAddress)
    {
        // Calculate the scaled virtual address range
        entry.startScaledVirtualAddress = entry.startVirtualAddress;
        entry.endScaledVirtualAddress = entry.endVirtualAddress;
    }
    
        
   
}