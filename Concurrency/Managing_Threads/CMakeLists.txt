cmake_minimum_required(VERSION  3.20)

project(Managing_Threads)


add_subdirectory(join_thread)
add_subdirectory(detach_thread)

enable_testing()

add_subdirectory(join_thread)
add_subdirectory(detach_thread)
add_subdirectory(wait_thread_finished)
add_subdirectory(detached_daemon_thread)
add_subdirectory(passing_arguments_to_thread_function)
add_subdirectory(transferring_thread_ownership)
add_subdirectory(choose_runtime_threads_count)

