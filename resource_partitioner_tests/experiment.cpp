
#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/parallel/executors.hpp>
#include <hpx/include/parallel_algorithm.hpp>
#include <hpx/include/threads.hpp>
#include <hpx/error_code.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <bitset>

#include "resource_manager.h"
#include "system_characteristics.h"

int hpx_main(boost::program_options::variables_map& vm)
{
    bool print_system = vm["print-system"].as<bool>();

    if(print_system)
        print_system_characteristics();

    // -------------------------------------- //
    //      Experiment with RM                //
    // -------------------------------------- //

    resource_manager rm;
    rm.init_pools(2,"even-odd");

    // and then
    // auto e = pool.get_executor();

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    // Get cmd-line options
    boost::program_options::options_description
        desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()
            (
                    "print-system",
                    boost::program_options::value<bool>()->default_value(false),
                    "if set to TRUE, system characteristics are printed out"
            );

    return hpx::init(desc_commandline, argc, argv);
}

