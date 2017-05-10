
#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/runtime.hpp>
#include <hpx/runtime/resource_partitioner.hpp>

#include "system_characteristics.h"

int hpx_main(int argc, char* argv[])
{
    std::cout << "[hpx_main] starting ..." << "\n";

    // get a pointer to the runtime instance
    auto rt_ptr = hpx::get_runtime_ptr();
    if(rt_ptr == nullptr)
        throw std::runtime_error("[hpx main] couldn't get a pointer to the runtime");
    std::cout << "[hpx_main] got a pointer to the runtime" << "\n";

    // get a pointer to the resource_partitioner instance
    hpx::resource::resource_partitioner& rpart = hpx::get_resource_partitioner();

    std::cout << "[hpx_main] got a ref to the resource_partitioner" << "\n";

//    rpart.add_resource(0, "blob"); // throws exception

    // print system characteristics
    //print_system_characteristics();

    // print partition characteristics

    // get executors
/*    auto network_executor = rm.executor_for_pool("network");
    auto f1 = hpx::async(network.executor, some_network_stuff);
    auto even_executor = rm.executor_for_pool("even_pool");
    auto default_executor = rm.executor_for_pool("default_pool");*/

    // use these executors to schedule work

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    std::cout << "[main] " << "starting program... \n";

    auto &rp = hpx::get_resource_partitioner();

    std::cout << "[main] " << "obtained reference to the resource_partitioner\n";

    rp.create_thread_pool("first_pool");
    rp.create_thread_pool("second_pool", hpx::resource::local);
    rp.create_thread_pool("default_pool"); //! different function called create_default_pool !!!!

    std::cout << "[main] " << "thread_pools created \n";

    rp.add_resource(0, "first_pool");
    rp.add_resource(1, "second_pool");
    rp.add_resource(2, "default_pool");
    rp.add_resource(3, "default_pool");

    // throws exception
    // rp.add_resource(2, "blob"); // (bad name)
    // hpx::resource_partitioner rp2; // (cannot instantiate > 1 resource partitioner)

    std::cout << "[main] " << "resources added to thread_pools \n";

    return hpx::init(argc, argv);
}