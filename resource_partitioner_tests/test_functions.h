//
// Created by shoshijak on 04/05/17.
//

#ifndef RM_EXPERIMENT_TEST_FUNCTIONS_H
#define RM_EXPERIMENT_TEST_FUNCTIONS_H

// -------------------------------------- //
//      dummy functions used to           //
//      test stuff                        //
// -------------------------------------- //

void print_vector(std::vector<double> const& v){
    std::size_t s = v.size();
    if(s==0) {
        hpx::cout << "(empty)\n";
        return;
    }
    hpx::cout << v[0] ;
    for(size_t i(1); i<s ;i++){
        hpx::cout << ", " << v[i];
    }
    hpx::cout << "\n";
}

void print_vector(std::vector<long unsigned int> const& v){
    std::size_t s = v.size();
    if(s==0) {
        hpx::cout << "(empty)\n";
        return;
    }
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

#endif //RM_EXPERIMENT_TEST_FUNCTIONS_H
