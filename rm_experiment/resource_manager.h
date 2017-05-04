//
// Created by shoshijak on 04/05/17.
//

#ifndef RM_EXPERIMENT_RESOURCE_MANAGER_H
#define RM_EXPERIMENT_RESOURCE_MANAGER_H

#include <string>
#include <vector>

#include <hpx/include/runtime.hpp>
#include <hpx/runtime_impl.hpp>


class resource_manager {

public:

    resource_manager()
            :topology_(hpx::get_runtime_ptr()->get_topology())
    {};

    void init_pools(std::size_t num_pools, std::string description) {

        // resize vector of pools
        pu_pools_ = std::vector<pu_pool>(num_pools, std::vector<bool>(topology_.get_number_of_pus(), false));

        if(description == "even-odd") {
            even_odd_pool();
        } else if(description=="other_kinds_of_pools") {
            /* other kinds of pools ... (to be implemented) */
        } else {
            /* throw an exception if the argument has not been recognised */
        }
        //! TODO this should be a switch on an enum, not an if on a string...
    }

private:

    // Functions that create masks corresponding to pools
    void even_odd_pool() {
        size_t half_num_pus = topology_.get_number_of_pus()/2;
        for(size_t i(0); i<half_num_pus; i+=2){
            pu_pools_[0][i]   = 1; // "even" pool
            pu_pools_[1][i+1] = 1; // "odd" pool
        }

        if (topology_.get_number_of_pus() % 2) { // if the total number of PUs is odd
            pu_pools_[0].back() = 1;
        }

        //! TODO there are probably much faster and smarter ways of doing this with bitmasks ...
    }

    // own a reference to the topology
    hpx::threads::topology const& topology_;

    // a PU pool is a vector of booleans the length of number_of_PUs
    // the elements with value "true" are part of the pool
    // the reason for representing PU pools like this is it harmonizes well with the data members of hwloc_topology_info:
    //
    //          std::vector<std::size_t> socket_numbers_
    //                  is a vector of size num_of_pus, giving the socket number each PU is on
    //          std::vector<std::size_t> numa_node_numbers_
    //                  is a vector of size num_of_pus, giving the numa-node number each PU is on
    //          std::vector<std::size_t> core_numbers_
    //                  is a vector of size num_of_pus, giving the core number each PU is on
    //
    //! TODO or re-write this more elegantly with a bitmask instead? (like affinity_mask in the HPX source code)
    typedef std::vector<bool> pu_pool;

    // the resource manager holds a vector of such pu_pool s
    //! TODO pu_pools_ should probably also carry a name (eg "network-pool") to be more user friendly
    //! make a simple struct for pu_pools_
    std::vector<pu_pool> pu_pools_;

};


#endif //RM_EXPERIMENT_RESOURCE_MANAGER_H
