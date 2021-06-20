cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-std=c++2a)
add_compile_options(-fmodules-ts)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
string(CONCAT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
  "<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> <SOURCE>"
  " -MT <DYNDEP_FILE> -MD -MF <DEP_FILE>"
  " ${flags_to_scan_deps} -fdep-file=<DYNDEP_FILE> -fdep-output=<OBJECT>")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "gcc")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG
  "${compiler_flags_for_module_map} -fmodule-mapper=<MODULE_MAP_FILE>")
set(PREBUILT_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build")
function(add_module name)
    file(MAKE_DIRECTORY ${PREBUILT_MODULE_PATH})
    add_custom_target(${name}.pcm
            COMMAND
                ${CMAKE_CXX_COMPILER}
                -std=c++2a
                -fmodules-ts
                -c
                ${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}
                -o ${PREBUILT_MODULE_PATH}/${name}.pcm
            )
endfunction()

######################################################
project(test_proj VERSION 1.0)

######## module locations ########
set(test_impl_p test_impl.cc)
set(testmod1_p testmod1.cc)
set(testmodp_p testmodp.cc)
set(filler1_p filler1.cc)
set(filler2_p filler2.cc)

######## module definitions ########
add_module(test_impl ${test_impl_p})
add_module(testmod1 ${testmod1_p})
add_module(filler1 ${filler1_p})
add_module(filler2 ${filler2_p})

add_module(testmodp ${testmodp_p})

######## executable definitions ########
add_executable(test_proj main.cc ${test_impl_p} ${testmod1_p} ${testmodp_p} ${filler1_p} ${filler2_p} )

######## dependency tree ########
add_dependencies(test_proj test_impl.pcm)
add_dependencies(test_impl.pcm testmod1.pcm)
add_dependencies(test_impl.pcm testmodp.pcm)
add_dependencies(test_impl.pcm filler1.pcm)
add_dependencies(test_impl.pcm filler2.pcm)