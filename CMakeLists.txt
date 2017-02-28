cmake_minimum_required(VERSION 3.6)
project(ft_printf)

set(CCMAKE_C_FLAGS "-std=c99 -Wall -Wextra -Werror")
#set(CMAKE_C_FLAGS "-std=c99")

set(SOURCE_FILES
        test.cc
        ft_printf.c
        init_struct.c
        parser.c
        convert_to_data.c
        itoa_base.c
        write_specifier_cs.c
        write_specifier_ox.c
        write_specifier_pidu.c
        count_letters.c
        convert_to_char.c
        fix_center_flag.c
        check_flag_zero.c
        init_memory.c
        ft_printf.h)
add_executable(ft_printf ${SOURCE_FILES})
target_link_libraries(ft_printf ${CMAKE_SOURCE_DIR}/libft/libft.a)