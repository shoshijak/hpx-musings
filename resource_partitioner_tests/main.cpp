
#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/runtime.hpp>
#include <hpx/runtime/resource_partitioner.hpp>
#include <hpx/runtime/threads/executors/customized_pool_executors.hpp>

#include "system_characteristics.h"

int hpx_main(int argc, char* argv[])
{
    hpx::cout << "[hpx_main] starting ..." << "\n";
    std::cout << "[hpx_main] starting STD ..." << "\n";

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

    // get executors
    hpx::threads::executors::customized_pool_executor my_exec("first_pool");
    hpx::cout << "\n\n [hpx_main] got customized executor " << "\n";

    // use these executors to schedule work


    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    std::cout << "[main] " << "starting program... \n";

    auto &rp = hpx::get_resource_partitioner();

    rp.create_thread_pool("first_pool", hpx::resource::abp_priority);
    rp.create_thread_pool("second_pool", hpx::resource::local_priority_lifo);

    std::cout << "[main] " << "thread_pools created \n";

    rp.add_resource(1, "first_pool");
    rp.add_resource(0, "second_pool");
    rp.add_resource(2, "second_pool");
//    rp.add_resource_to_default(2);

    std::cout << "[main] " << "resources added to thread_pools \n";

    return hpx::init(argc, argv);
}