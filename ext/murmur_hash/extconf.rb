require 'mkmf'

dir_config("murmur_hash")
have_library("c", "main")

create_makefile("murmur_hash")
