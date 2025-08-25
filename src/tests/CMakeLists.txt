add_executable(s21_containers_tests
    s21_test_list.cpp
    s21_test_multiset.cpp
    s21_test_queue.cpp
    s21_test_set.cpp
    s21_test_stack.cpp
)

target_include_directories(s21_containers_tests PRIVATE 
    ../container/Container_Adaptor/queue/s21_queue.h
    ../Container_Adaptor/stack/s21_stack.h
    ../Sequence_Containers/list/s21_list.h
    ../Sequence_Containers/vector/s21_vector.h
    ../Sorted_Container/map/s21_map.h
    ../Sorted_Container/Set_Conteiner/s21_multiset.h
    ../Sorted_Container/Set_Conteiner/s21_set.h)

target_link_libraries(s21_containers_tests PRIVATE GTest::GTest GTest::GMock)

enable_testing()
add_test(NAME s21_containers_tests COMMAND s21_containers_tests)