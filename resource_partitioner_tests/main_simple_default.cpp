
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

    // print system characteristics
    //print_system_characteristics();

    // print partition characteristics

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    std::cout << "[main] " << "starting program... \n";

    return hpx::init(argc, argv);
}