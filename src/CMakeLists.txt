cmake_minimum_required ( VERSION 3.16 )
project ( library_app )

include_directories ( include )

add_executable ( kivi
				 main.c
				 include/db_utils.h
)
