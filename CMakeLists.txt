cmake_minimum_required(VERSION 3.6)
project(ft_printf)

#set(CCMAKE_C_FLAGS "-std=c99 -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS "-std=c99")

set(SOURCE_FILES
        #test_va.c
        ft_printf.c
        test.c
        write_console.c
        specifier_and_modifier.c
        #libft/libft.a
        libftprintf.h)
        ##libft/libft.h)
add_executable(ft_printf ${SOURCE_FILES})
target_link_libraries(ft_printf ${CMAKE_SOURCE_DIR}/libft/libft.a)