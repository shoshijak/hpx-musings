//
// Created by shoshijak on 04/05/17.
//

my_custom_thread_pool pool;
for(auto s : resource_manager.get_sockets()) {
    for(auto c : s.cores()) {
        for (auto pu : c.pus()) {
            if (pu.index %2) {
                pool.add_pu()
            }
        }
    }
}

my_other_custom_pool pool2;
pool2.add(resource_manager.get_free_pus());

and then
auto e = pool.get_executor();

///////////////////////////////////////////////////

my_custom_pu_pool pool;
for(auto s : resource_manager.get_sockets()) {
    for(auto c : s.cores()) {
        for (auto pu : c.pus()) {
            if (pu.index %2) {
                pool.add_pu()
            }
        }
    }
}

my_other_custom_pool pool2;
pool2.add(resource_manager.get_free_pus());

and then
auto e = pool.get_executor();