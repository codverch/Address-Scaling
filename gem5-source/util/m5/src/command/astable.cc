/* 
* Sets an entry in the Address-Scaling Table
*/

#include <iostream>
#include <fstream>

// Header file of the Address-Scaling Table
#include "mem/as_table.hh"

namespace gem5
{
   
    void
as_table_set(uint64_t vaddr, uint64_t size)
{
    // Address-Scaling Table Instance
    AddressScalingTable asTable;

    if(asTable.getAddressScalingTable() == NULL)
    {
        // Create the address-scaling table
        asTable = AddressScalingTable(2);
    }
    
    else 
    {
        // Get the address-scaling table
        asTable = asTable.getAddressScalingTable();
    }

    // Add an entry to the address-scaling table
    asTable.addEntry(vaddr, size);
}


}

