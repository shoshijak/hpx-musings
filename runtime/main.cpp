
#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/runtime.hpp>
#include <hpx/runtime/threads/threadmanager.hpp>
#include <hpx/runtime_impl.hpp>
#include <hpx/parallel/executors.hpp>
#include <hpx/include/parallel_algorithm.hpp>
#include <hpx/include/threads.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <bitset>

// -------------------------------------- //
//      dummy functions used to           //
//      test executors                    //
// -------------------------------------- //

void print_vector(std::vector<double> v){
    std::size_t s = v.size();
    hpx::cout << v[0] ;
    for(size_t i(1); i<s ;i++){
        hpx::cout << ", " << v[i];
    }
    hpx::cout << "\n";
}

double compute(double x, hpx::runtime* rt, hpx::threads::threadmanager_base* thrd_manager){
    hpx::cout << "[compute] on thread_id : " << hpx::this_thread::get_id()  << "\n"
              << "called by thread named : " << rt->get_thread_name() << "\n"
              << "worker thread number   : " << thrd_manager->get_worker_thread_num() << "\n"
              << "computing .............. " << x << "\n\n";
    return x/2;
}

void compute_(hpx::future<double> x/*, hpx::runtime* rt, hpx::threads::threadmanager_base* thrd_manager*/){
    hpx::cout << "[compute] on thread_id : " << hpx::this_thread::get_id()  << "\n";
/*              << "called by thread named : " << rt->get_thread_name() << "\n"
              << "worker thread number   : " << thrd_manager->get_worker_thread_num() << "\n\n"*/
}

void compute_io(double x, hpx::runtime* rt, hpx::threads::threadmanager_base* thrd_manager){
    hpx::cout << "[comp-io] on thread_id : " << hpx::this_thread::get_id()  << "\n"
              << "called by thread named : " << rt->get_thread_name() << "\n"
              << "worker thread number   : " << thrd_manager->get_worker_thread_num() << "\n\n";
}

void qt_main(hpx::runtime* rt, hpx::threads::threadmanager_base* thrd_manager){
    hpx::cout << "[qt_main] on thread_id : " << hpx::this_thread::get_id() << "\n"
              << "called by thread named : " << rt->get_thread_name() << "\n"
              << "worker thread number   : " << thrd_manager->get_worker_thread_num() << "\n\n";
}

int hpx_main(int argc, char* argv[])
{
    hpx::cout << "[hpx-main] System queries: \n\n";

    // -------------------------------------- //
    //      get pointer to instances          //
    //      I can query                       //
    // -------------------------------------- //

    hpx::runtime* rt                                = hpx::get_runtime_ptr();
    hpx::util::runtime_configuration cfg            = rt->get_config();
    const hpx::threads::topology &topo              = rt->get_topology();
    hpx::threads::threadmanager_base &thrd_manager  = rt->get_thread_manager();
    hpx::threads::policies::detail::affinity_data * affdat_ptr = rt->get_affinity_data();  //! only in my local version of HPX

    // -------------------------------------- //
    //      print runtime characteristics     //
    //                                        //
    // -------------------------------------- //

    //! -------------------------------------- runtime
    hpx::cout << "[Runtime], instance number " << rt->get_instance_number() << "\n"
              << "called by thread named     " << rt->get_thread_name() << "\n\n";

    //! -------------------------------------- thread_manager
    hpx::cout << "[Thread manager]\n"
              << "worker thread number  : " << thrd_manager.get_worker_thread_num() << "\n\n";

    //! -------------------------------------- runtime_configuration
    hpx::cout << "[Runtime configuration]\n"
              << "number of localities  : " << cfg.get_num_localities() << "\n"
              << "os thread count       : " << cfg.get_os_thread_count() << "\n"
              << "                        " << hpx::get_os_thread_count() << "\n"
              << "command line          : " << cfg.get_cmd_line() << "\n\n";

    //! -------------------------------------- affinity data
    std::size_t num_of_affinity_masks(affdat_ptr->affinity_masks_.size());
    unsigned long num_of_pu_nums(affdat_ptr->pu_nums_.size());
    hpx::cout << "[Affinity Data]\n"
              << "number of threads     : " << affdat_ptr->num_threads_ << "\n"
              << "affinity domain       : " << affdat_ptr->affinity_domain_ << "\n"
              << "number of pu_nums_    : " << num_of_pu_nums << "\n"
              << "number of aff. masks  : " << num_of_affinity_masks << "\n"
              << "affinity masks        : " << "\n";

    for(std::size_t i(0); i<num_of_affinity_masks; i++){
    hpx::cout << "                        " << std::bitset<8>(affdat_ptr->affinity_masks_[i]) << "\n";
    }

    hpx::cout << "pu_nums               : " << "\n";
    for(unsigned long i(0); i<num_of_pu_nums; i++){
    hpx::cout << "                        " << std::bitset<8>(affdat_ptr->pu_nums_[i]) << ",  " << affdat_ptr->pu_nums_[i] << "\n";
    }

    //! -------------------------------------- topology
    hpx::cout << "[Topology]\n"
              << "number of sockets     : " << topo.get_number_of_sockets() << "\n"
              << "number of numa nodes  : " << topo.get_number_of_numa_nodes() << "\n"
              << "number of cores       : " << topo.get_number_of_cores() << "\n"
              << "number of PUs         : " << topo.get_number_of_pus() << "\n"
              << "hardware concurrency  : " << hpx::threads::hardware_concurrency() << "\n\n";


    // -------------------------------------- //
    //      play around with executors        //
    //                                        //
    // -------------------------------------- // (ignoring throttle-queue executor)

    //! -------------------------------------- FOR ALGORITHMS (have to do with executor_traits)
    //! -------------------------------------- Questions: find default executor of all parallel policies?
    //! -------------------------------------- hpx::parallel::distribution_policy_executor
    //! -------------------------------------- hpx::parallel::parallel_executor (in execution policy hpx::parallel::execution::parallel_policy/par)
    //! -------------------------------------- hpx::parallel::sequential_executor (in execution policy hpx::parallel::execution::sequenced_policy/seq)
    std::vector<double> d(40);
    print_vector(d);
    auto my_policy = hpx::parallel::execution::par; hpx::parallel::parallel_executor my_exec; //! ok
//    auto my_policy = hpx::parallel::execution::par; hpx::parallel::sequential_executor my_exec; //! ok
//    auto my_policy = hpx::parallel::execution::par; hpx::parallel::distribution_policy_executor<hpx::components::default_distribution_policy> my_exec; //! compiler error
//    auto my_policy = hpx::parallel::execution::seq; hpx::parallel::sequential_executor my_exec; //! ok
//    auto my_policy = hpx::parallel::execution::seq; hpx::parallel::parallel_executor my_exec; //! compiler error
//    auto my_policy = hpx::parallel::execution::seq; hpx::parallel::parallel_executor my_exec; //! compiler error
//    auto my_policy = hpx::parallel::execution::seq; hpx::parallel::main_pool_executor my_exec; //! compiler error
//    auto my_policy = hpx::parallel::execution::seq; hpx::parallel::default_executor my_exec(0); //! compiler error
//    auto my_policy = hpx::parallel::execution::seq; hpx::parallel::local_queue_executor my_exec; //! compiler error
//    auto my_policy = hpx::parallel::execution::seq; hpx::parallel::this_thread_static_queue_executor my_exec; //! compiler error
    my_policy = my_policy.on(my_exec);
    hpx::parallel::fill(my_policy, begin(d), end(d), 2);
    print_vector(d);

    //! -------------------------------------- hpx::compute::cuda::concurrent_executor
    //! -------------------------------------- hpx::compute::cuda::default_executor
    //! -------------------------------------- hpx::compute::host::block_executor
    //! -------------------------------------- hpx::compute::host::default_executor

    //! -------------------------------------- hpx::parallel::this_thread_static_queue_executor
    //! -------------------------------------- hpx::parallel::this_thread_static_priority_queue_executor

    //! -------------------------------------- hpx::parallel::local_queue_executor
    //! -------------------------------------- hpx::parallel::static_queue_executor
    //! -------------------------------------- hpx::parallel::local_priority_queue_executor
    //! -------------------------------------- hpx::parallel::static_priority_queue_executor
    {
        hpx::parallel::local_queue_executor my_loc_exec; //! this example is pretty useless
        hpx::future<double> my_future   = hpx::async(compute, 42, rt, &thrd_manager);
        hpx::future<void> my_future_2 = my_future.then(
                my_loc_exec,
                [&](hpx::future<void>){
                    compute(3.14, rt, &thrd_manager);
                });
        my_future_2.get();
    } // the executor's destructor will wait for all spawned tasks to finish executing

    // can be used as template parameter for hpx::components::executor_components (cf component_with_executor.cpp)

    //! -------------------------------------- hpx::parallel::local_queue_os_executor
    //! -------------------------------------- hpx::parallel::static_queue_os_executor
    //! -------------------------------------- hpx::parallel::local_priority_queue_os_executor
    //! -------------------------------------- hpx::parallel::static_priority_queue_os_executor

    //! -------------------------------------- hpx::parallel::local_queue_attached_executor
    //! -------------------------------------- hpx::parallel::static_queue_attached_executor
    //! -------------------------------------- hpx::parallel::local_priority_queue_attached_executor
    //! -------------------------------------- hpx::parallel::static_priority_queue_attached_executor

    //! -------------------------------------- SERVICE EXECUTORS
    //!                                        These are OS-threads, not HPX-threads!
    //! -------------------------------------- Quirks: runtime error if instantiated at global scope
    //!                                                runtime error is used as argument of async, and the callable of the async does some async work or some parallel sync work (but hpx::parallel::execution::seq = okay)
    //! -------------------------------------- hpx::parallel::timer_pool_executor
    //! -------------------------------------- hpx::parallel::main_pool_executor
    {   // Controlling where threads execute
        hpx::parallel::main_pool_executor my_main_exec;
        my_main_exec.add(hpx::util::bind(compute, 100, rt, &thrd_manager));
    }
    {   // Allow Qt or OpenGL stuff to execute on a single OS-thread
        hpx::parallel::main_pool_executor my_main_exec;
        hpx::future<void> qt_app = hpx::async(my_main_exec, qt_main, rt, &thrd_manager);
        // do something while Qt is executing ...
        qt_app.wait();
    }
    //! -------------------------------------- hpx::parallel::parcel_pool_executor
    // no examples
    //! -------------------------------------- hpx::parallel::io_pool_executor
    {   // launch work on the thread dedicated to I/O
        hpx::parallel::io_pool_executor my_io_exec;
        my_io_exec.add(hpx::util::bind(compute_io, 33, rt, &thrd_manager));
    }
    //! -------------------------------------- hpx::parallel::default_executor (run with --hpx:queuing=static to disable stealing and get wanted results)
    {   // run a thread on a large stack (constructor argument is of type thread_stacksize)
        hpx::threads::executors::default_executor large_stack_executor(
                hpx::threads::thread_stacksize_large);
        hpx::future<void> f =
                hpx::async(large_stack_executor, compute, 44, rt, &thrd_manager);
        f.wait();
    }
    {   // run a thread with high priority (constructor argument is of type thread_priority)
        hpx::threads::executors::default_executor high_priority_executor(
                hpx::threads::thread_priority_critical);
        hpx::future<void> f =
                hpx::async(high_priority_executor, compute, 33, rt, &thrd_manager);
        f.wait();
    }
    {   // run a thread with high priority AND on a large stack
        hpx::threads::executors::default_executor fancy_executor(
                hpx::threads::thread_priority_critical,
                hpx::threads::thread_stacksize_large);
        hpx::future<void> f =
                hpx::async(fancy_executor, compute, 22, rt, &thrd_manager);
        f.wait();
    }
    {
        hpx::parallel::default_executor my_executor_worker_0(0);    //! this binds to worker-threads, not cores!
        hpx::future<void> f0a =
                hpx::async(my_executor_worker_0, compute, 0.1, rt, &thrd_manager);
        f0a.wait();
        hpx::future<void> f0b =
                hpx::async(my_executor_worker_0, compute, 0.2, rt, &thrd_manager);
        f0b.wait();
    }
    {
        hpx::parallel::default_executor my_executor_worker_1(1);
        hpx::future<void> f1 =
                hpx::async(my_executor_worker_1, compute, 1, rt, &thrd_manager);
        f1.wait();
    }
    {
        hpx::parallel::default_executor my_executor_worker_0(0);
        my_executor_worker_0.add(hpx::util::bind(compute, 0, rt, &thrd_manager));
    }
    //! -------------------------------------- hpx::threads::executors::current_executor (hpx::parallel::current_executor)

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    // ...
    return hpx::init(argc, argv);
}

