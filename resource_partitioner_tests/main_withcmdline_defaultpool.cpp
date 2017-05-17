
#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/runtime.hpp>
#include <hpx/runtime/resource_partitioner.hpp>
#include <boost/format.hpp>

#include "system_characteristics.h"

int hpx_main(boost::program_options::variables_map& vm)
{
    std::cout << "[hpx_main] starting ..." << "\n";

    std::uint64_t myblob = vm["blob"].as<std::uint64_t>();

    std::cout << "[hpx_main] extracted cmd line option : " << myblob << ".\n";

    // get a pointer to the runtime instance
    auto rt_ptr = hpx::get_runtime_ptr();
    if(rt_ptr == nullptr)
        throw std::runtime_error("[hpx main] couldn't get a pointer to the runtime");
    std::cout << "[hpx_main] got a pointer to the runtime" << "\n";

    // get a pointer to the resource_partitioner instance
    hpx::resource::resource_partitioner& rpart = hpx::get_resource_partitioner();

    std::cout << "[hpx_main] got a reference to the resource_partitioner" << "\n";

    // print partition characteristics
    std::cout << "[hpx_main] print resource_partitioner characteristics : " << "\n";
    rpart.print_me();
    //print_system_characteristics();

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    std::cout << "[main] " << "starting program... \n";

    boost::program_options::options_description
            desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options() //! how to use: --blob 44
            ("blob",
             boost::program_options::value<std::uint64_t>()->default_value(43),
             "my cute little blob");

    return hpx::init(desc_commandline, argc, argv);
}