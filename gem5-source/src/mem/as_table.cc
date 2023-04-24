/* Address Scaling Table stores the following information:
   1. Virtual Address Range: The start and end virtual address range of a segment 
                             that needs to be scaled.
   2. Physical Address Range: The start and end physical address range of a segment 
                                that needs to be scaled.
   3. Scaling Factor: The scaling factor that needs to be applied 
*/

#include "mem/as_table.hh"


namespace gem5
{

    /* Constructor */
    AdressScalingTable::AdressScalingTable()
    {
        // Initialize the address scaling table
        asTable = std::vector<AddressScalingEntry>();
    }

    /* Add an entry to the Address Scaling Table */
    void 
    AdressScalingTable::addEntry(Addr _startVirtualAddress, Addr _endVirtualAddress,  Addr _scalingFactor)
    {
        // Create a new entry
        AddressScalingEntry newEntry;
        newEntry.startVirtualAddress = _startVirtualAddress;
        newEntry.endVirtualAddress = _endVirtualAddress;
        newEntry.scalingFactor = _scalingFactor;
        // Set the start and end scaled virtual address to 0, they will be set later
        newEntry.startScaledVirtualAddress = 0;
        newEntry.endScaledVirtualAddress = 0;

        // Add the new entry to the address scaling table
        asTable.push_back(newEntry);
    }

    /* Check if the requested address falls within the virtual address range of any segment */
    bool
    AddressScalingEntry::checkAddress(Addr requestAddress)
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

    /* Update an Address Scaling Table Entry */
    void
    AddressScalingEntry::updateEntry(Addr _startVirtualAddress, Addr _startScaledVirtualAddress, Addr _endScaledVirtualAddress)
    {
        // Iterate through the address scaling table
        for (int i = 0; i < asTable.size(); i++)
        {
            // Check if the start virtual address of the entry matches the start virtual address of the segment
            if (asTable[i].startVirtualAddress == _startVirtualAddress)
            {
                // Update the scaled virtual address range of the segment
                asTable[i].startScaledVirtualAddress = _startScaledVirtualAddress;
                asTable[i].endScaledVirtualAddress = _endScaledVirtualAddress;
            }
        }
    }
    
    /* Scale the request address */
   
}