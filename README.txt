= murmur_hash

* http://github.com/jmhodges/murmur_hash

== DESCRIPTION:

* A ruby extension for the MurmurHash2 functions. See http://murmurhash.googlepages.com/

== FEATURES/PROBLEMS:

* Provides all 3 versions of the 32-bit MurmurHash functions which
  are:
  
  * `MurmurHash.murmur_hash`, the simplest and fastest version of
    MurmurHash2. Note: output depends on the endianness of the machine
    it is run on.
  * `MurmurHash.neutral_murmur_hash`, a version of the
    straight-forward MurmurHash2 function that does not depend on the
    endianness of the machine it is run on. Slightly slower.
  * `MurmurHash.aligned_murmur_hash`, a version of the MurmurHash2
    function that does only byte-aligned reads. It is slightly safer
    on some uncommon platforms.

== SYNOPSIS:
  # 23 can be any unsigned 32-bit integer (i.e. from 0 to 2**32 - 1)
  hash_number = MurmurHash.murmur_hash("somestring", 23) 

== REQUIREMENTS:

* rake-compiler for compilation

== INSTALL:

* sudo gem install murmur_hash

== LICENSE:

(The MIT License)

Copyright (c) 2009 Jeff Hodges

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
