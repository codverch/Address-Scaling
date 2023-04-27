/* 
    Address Scaling Table stores the following information:

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

    /* 
    * Constructor: Takes the scaling factor as an argument and sets it.
    */
    AddressScalingTable::AddressScalingTable(int _scalingFactor)
    {
        // Set the scaling factor
        scalingFactor = _scalingFactor;
    }

    /*
    * Add an entry to the Address Scaling Table : Sets the start and end virtual address range of a segment
    * that needs to be scaled. Any address that falls within this range will be scaled whenever it is accessed.
    */
    void 
    AddressScalingTable::addEntry(Addr _startVirtualAddress, Addr _endVirtualAddress,  int _scalingFactor)
    {

        // Check that the end virtual address is greater than or equal to the start virtual address
        if (_endVirtualAddress < _startVirtualAddress) 
        {
            throw "End virtual address must be greater than or equal to start virtual address";
        }
        
        // Create a new entry in the address scaling table
        AddressScalingEntry newEntry;
        // Set the start and end virtual address range of the address scaling entry
        newEntry.startVirtualAddress = _startVirtualAddress;
        newEntry.endVirtualAddress = _endVirtualAddress;
        // Set the start scaled virtual address to 0 initially
        newEntry.startScaledVirtualAddress = 0;
        
        // Add the new entry to the address scaling table
        asTable.push_back(newEntry);

    }

    /* 
    * Check if the requested address falls within the virtual address range of any segment
    * that needs to be scaled. Returns true if the address falls within the virtual address range
    * of any segment, false otherwise.s 
    */
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

   
    /* Scale the request address if it falls within the virtual address range of any segment by 
    *  calling tge checkAddress() function. Scaling is done by multiplying the offset of the request address
    *  from the start virtual address of the segment with the scaling factor and adding it to the start scaled
    *  virtual address of the segment (which is the same as the start virtual address initially). 
    *  Returns the scaled address.
    */
    Addr
    AddressScalingTable::scaleAddress(Addr requestAddress)
    {
        // Check if the requested address falls within the virtual address range of any segment
        if (checkAddress(requestAddress))
        {
            // Find the segment that contains the request address
            AddressScalingEntry segment;
            // Iterate through the address scaling table
            for (auto& entry : asTable)
            {
                // If the requested address matches any segment in the address scaling table, set the segment to that entry
                if (requestAddress >= entry.startVirtualAddress && requestAddress <= entry.endVirtualAddress)
                {
                    segment = entry;
                    // Break out of the loop
                    break;
                }
            }

            // Calculate the scaled address with the offset
            Addr offset = requestAddress - segment.startVirtualAddress;
            Addr scaledAddress = (offset * scalingFactor) + segment.startScaledVirtualAddress;

            // Update the scaled virtual address range of the segment
            updateAddressScalingEntry(segment, segment.startVirtualAddress);

            // Return the scaled address
            return scaledAddress;
    }

            // If the request address does not fall within the virtual address range of any segment, do not scale the address
            // and return the requested address as it is
            return requestAddress;
    }

    /* Update an Address Scaling Entry
    *  Initialize the start scaled virtual address of the segment to the start virtual address of the segment.
    */
    
    void 
    AddressScalingTable::updateAddressScalingEntry(AddressScalingEntry &entry, Addr _startVirtualAddress)
    {
        // Set the start scaled virtual address
        entry.startScaledVirtualAddress = _startVirtualAddress;
    }
        
}