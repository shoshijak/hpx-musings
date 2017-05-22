
#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/runtime.hpp>
#include <hpx/runtime/resource_partitioner.hpp>
#include <hpx/runtime/threads/cpu_mask.hpp>

#include "system_characteristics.h"

int hpx_main(int argc, char* argv[])
{

    hpx::cout << "[hpx_main] starting ..." << "\n";

    // get a pointer to the resource_partitioner instance
    hpx::resource::resource_partitioner& rpart = hpx::get_resource_partitioner();

    // print partition characteristics
    hpx::cout << "\n\n [hpx_main] print resource_partitioner characteristics : " << "\n";
    rpart.print_init_pool_data();

    // print partition characteristics
    hpx::cout << "\n\n [hpx_main] print thread-manager characteristics : " << "\n";
    hpx::threads::get_thread_manager().print_pools();

    // print system characteristics
    //print_system_characteristics();

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    std::cout << "[main] " << "starting program... \n";

    return hpx::init(argc, argv);
}