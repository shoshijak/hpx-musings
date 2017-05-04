// Shoshana Jakobovits
// April 2017

/*
    try with promise, with packaged-task and with new HPX version
*/

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/lcos.hpp>
#include <cmath>

void show_turtle();

hpx::future<void> babybaby_task(double a){
    hpx::cout << "******   Baby- Baby-task: execution starting...\n\n";
    hpx::this_thread::sleep_for(std::chrono::seconds(1));
    show_turtle();
    return hpx::make_ready_future();
}

hpx::future<void> baby_task(){
  hpx::cout << "Baby-task: Execution starting...\n";
  hpx::this_thread::sleep_for(std::chrono::seconds(1));
  hpx::future<void> babybaby_task_future(hpx::async(
      babybaby_task,42
    ));
  hpx::cout << "Baby-task: Baby-Baby-task launched.\n";
  return babybaby_task_future;
}

hpx::future<void> mama_task(){
  hpx::cout << "Mama-task: Execution starting...\n";
  hpx::this_thread::sleep_for(std::chrono::seconds(1));
  hpx::future<void> baby_task_future(hpx::async(
      baby_task
    ));
  hpx::cout << "Mama-task: Baby-task launched.\n";
  return baby_task_future;
}

hpx::future<void> grandma_task(){
  hpx::cout << "Grandma-task: Execution starting...\n";
  hpx::this_thread::sleep_for(std::chrono::seconds(1));
  hpx::future<void> mama_task_future(hpx::async(
      mama_task
    ));
  hpx::cout << "Grandma-task: Mama-task launched.\n";
  return mama_task_future;
}

void setup_step(){
  hpx::cout << "Setup-step: Launching Grandma-task...\n";
  hpx::future<void> grandma_task_future = grandma_task();
  hpx::cout << "Setup-step: Grandma-task returned. Waiting for future of Grandma-task to be ready...\n";
  grandma_task_future.wait();
  hpx::cout << "\n******   Grandma-task is ready!\n\n";
}

int hpx_main(int argc, char* argv[])
{
  hpx::cout << "\n-- Main: Launching Setup-step...\n"
            << "-- which calls Grandma-task, which launches Mama-task, which launches Baby-task\n";
  setup_step();
  hpx::cout << "-- Main: Setup-step completed, we can move on to whatever the next step is now\n\n";
  return hpx::finalize();
}

int main(int argc, char* argv[])
{
  return hpx::init(argc, argv);
}

void show_turtle(){
  hpx::cout
<<"******         ___\n"
<<"******    ,,  // \\\\ \n"
<<"******   (_,\\/ \\_/ \\ \n"
<<"******     \\ \\_/_\\_/>\n"
<<"******     /_/  /_/\n\n"
<<"******   Hello world, I'm not the turtle all the way down!\n\n";
}
