if(EXISTS "/media/yanelox/Новый том/linux_work/ilab_2year/Tree/gtest/build/my_test[1]_tests.cmake")
  include("/media/yanelox/Новый том/linux_work/ilab_2year/Tree/gtest/build/my_test[1]_tests.cmake")
else()
  add_test(my_test_NOT_BUILT my_test_NOT_BUILT)
endif()
