require 'mkmf'

dir_config("murmur")
have_library("c", "main")

create_makefile("murmur")
