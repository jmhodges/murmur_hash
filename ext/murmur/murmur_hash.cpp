//-----------------------------------------------------------------------------
// MurmurHash2, by Austin Appleby

// Note - This code makes a few assumptions about how your machine behaves -

// 1. We can read a 4-byte value from any address without crashing
// 2. sizeof(int) == 4

// And it has a few limitations -

// 1. It will not work incrementally.
// 2. It will not produce the same results on little-endian and big-endian
//    machines.
#include <stdio.h>
#include <stdint.h>
#include "ruby.h"
#include "limits.h"

unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed )
{
  // 'm' and 'r' are mixing constants generated offline.
  // They're not really 'magic', they just happen to work well.

  const unsigned int m = 0x5bd1e995;
  const int r = 24;

  // Initialize the hash to a 'random' value

  unsigned int h = seed ^ len;

  // Mix 4 bytes at a time into the hash

  const unsigned char * data = (const unsigned char *)key;

  while(len >= 4)
    {
      unsigned int k = *(unsigned int *)data;

      k *= m;
      k ^= k >> r;
      k *= m;

      h *= m;
      h ^= k;

      data += 4;
      len -= 4;
    }

  // Handle the last few bytes of the input array

  switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
      h *= m;
    };

  // Do a few final mixes of the hash to ensure the last few
  // bytes are well-incorporated.

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

//-----------------------------------------------------------------------------
// MurmurHashAligned2, by Austin Appleby

// Same algorithm as MurmurHash2, but only does aligned reads - should be safer
// on certain platforms.

// Performance will be lower than MurmurHash2

#define MURMUR_MIX(h,k,m) { k *= m; k ^= k >> r; k *= m; h *= m; h ^= k; }

unsigned int MurmurHashAligned2 ( const void * key, int len, unsigned int seed )
{
  const unsigned int m = 0x5bd1e995;
  const int r = 24;

  const unsigned char * data = (const unsigned char *)key;

  unsigned int h = seed ^ len;

  int align = (int)data & 3;

  if(align && (len >= 4))
    {
      // Pre-load the temp registers

      unsigned int t = 0, d = 0;

      switch(align)
        {
        case 1: t |= data[2] << 16;
        case 2: t |= data[1] << 8;
        case 3: t |= data[0];
        }

      t <<= (8 * align);

      data += 4-align;
      len -= 4-align;

      int sl = 8 * (4-align);
      int sr = 8 * align;

      // Mix

      while(len >= 4)
        {
          d = *(unsigned int *)data;
          t = (t >> sr) | (d << sl);

          unsigned int k = t;

          MURMUR_MIX(h,k,m);

          t = d;

          data += 4;
          len -= 4;
        }

      // Handle leftover data in temp registers

      d = 0;

      if(len >= align)
        {
          switch(align)
            {
            case 3: d |= data[2] << 16;
            case 2: d |= data[1] << 8;
            case 1: d |= data[0];
            }

          unsigned int k = (t >> sr) | (d << sl);
          MURMUR_MIX(h,k,m);

          data += align;
          len -= align;

          //----------
          // Handle tail bytes

          switch(len)
            {
            case 3: h ^= data[2] << 16;
            case 2: h ^= data[1] << 8;
            case 1: h ^= data[0];
              h *= m;
            };
        }
      else
        {
          switch(len)
            {
            case 3: d |= data[2] << 16;
            case 2: d |= data[1] << 8;
            case 1: d |= data[0];
            case 0: h ^= (t >> sr) | (d << sl);
              h *= m;
            }
        }

      h ^= h >> 13;
      h *= m;
      h ^= h >> 15;

      return h;
    }
  else
    {
      while(len >= 4)
        {
          unsigned int k = *(unsigned int *)data;

          MURMUR_MIX(h,k,m);

          data += 4;
          len -= 4;
        }

      //----------
      // Handle tail bytes

      switch(len)
        {
        case 3: h ^= data[2] << 16;
        case 2: h ^= data[1] << 8;
        case 1: h ^= data[0];
          h *= m;
        };

      h ^= h >> 13;
      h *= m;
      h ^= h >> 15;

      return h;
    }
}

//-----------------------------------------------------------------------------
// MurmurHashNeutral2, by Austin Appleby

// Same as MurmurHash2, but endian- and alignment-neutral.
// Half the speed though, alas.

unsigned int MurmurHashNeutral2 ( const void * key, int len, unsigned int seed )
{
  const unsigned int m = 0x5bd1e995;
  const int r = 24;

  unsigned int h = seed ^ len;

  const unsigned char * data = (const unsigned char *)key;

  while(len >= 4)
    {
      unsigned int k;

      k  = data[0];
      k |= data[1] << 8;
      k |= data[2] << 16;
      k |= data[3] << 24;

      k *= m;
      k ^= k >> r;
      k *= m;

      h *= m;
      h ^= k;

      data += 4;
      len -= 4;
    }

  switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
      h *= m;
    };

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

//-----------------------------------------------------------------------------
// MurmurHash2, 64-bit versions, by Austin Appleby

// The same caveats as 32-bit MurmurHash2 apply here - beware of alignment
// and endian-ness issues if used across multiple platforms.

// 64-bit hash for 64-bit platforms

uint64_t MurmurHash64A ( const void * key, int len, unsigned int seed )
{
	const uint64_t m = 0xc6a4a7935bd1e995LL;
	const int r = 47;

	uint64_t h = seed ^ (len * m);

	const uint64_t * data = (const uint64_t *)key;
	const uint64_t * end = data + (len/8);

	while(data != end)
	{
		uint64_t k = *data++;

		k *= m;
		k ^= k >> r;
		k *= m;

		h ^= k;
		h *= m;
	}

	const unsigned char * data2 = (const unsigned char*)data;

	switch(len & 7)
	{
	case 7: h ^= uint64_t(data2[6]) << 48;
	case 6: h ^= uint64_t(data2[5]) << 40;
	case 5: h ^= uint64_t(data2[4]) << 32;
	case 4: h ^= uint64_t(data2[3]) << 24;
	case 3: h ^= uint64_t(data2[2]) << 16;
	case 2: h ^= uint64_t(data2[1]) << 8;
	case 1: h ^= uint64_t(data2[0]);
	        h *= m;
	};

	h ^= h >> r;
	h *= m;
	h ^= h >> r;

	return h;
}


// 64-bit hash for 32-bit platforms

uint64_t MurmurHash64B ( const void * key, int len, unsigned int seed )
{
	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	unsigned int h1 = seed ^ len;
	unsigned int h2 = 0;

	const unsigned int * data = (const unsigned int *)key;

	while(len >= 8)
	{
		unsigned int k1 = *data++;
		k1 *= m; k1 ^= k1 >> r; k1 *= m;
		h1 *= m; h1 ^= k1;
		len -= 4;

		unsigned int k2 = *data++;
		k2 *= m; k2 ^= k2 >> r; k2 *= m;
		h2 *= m; h2 ^= k2;
		len -= 4;
	}

	if(len >= 4)
	{
		unsigned int k1 = *data++;
		k1 *= m; k1 ^= k1 >> r; k1 *= m;
		h1 *= m; h1 ^= k1;
		len -= 4;
	}

	switch(len)
	{
	case 3: h2 ^= ((unsigned char*)data)[2] << 16;
	case 2: h2 ^= ((unsigned char*)data)[1] << 8;
	case 1: h2 ^= ((unsigned char*)data)[0];
			h2 *= m;
	};

	h1 ^= h2 >> 18; h1 *= m;
	h2 ^= h1 >> 22; h2 *= m;
	h1 ^= h2 >> 17; h1 *= m;
	h2 ^= h1 >> 19; h2 *= m;

	uint64_t h = h1;

	h = (h << 32) | h2;

	return h;
}

VALUE MurmurHashModule = Qnil;

VALUE call_murmur_func
(unsigned int (*func)(const void*, int, unsigned int), VALUE key, VALUE seed) {
  int key_length = RSTRING(key)->len;
  char *key_string = RSTRING(key)->ptr;
  unsigned int seedling = FIX2UINT(seed);

  unsigned int hash_value = func(key_string, key_length, seedling);

  return UINT2NUM(hash_value);
}

VALUE call_murmur64_func
(uint64_t (*func)(const void*, int, unsigned int), VALUE key, VALUE seed) {
  int key_length = RSTRING(key)->len;
  char *key_string = RSTRING(key)->ptr;
  unsigned int seedling = FIX2UINT(seed);

  unsigned int hash_value = func(key_string, key_length, seedling);

  return UINT2NUM(hash_value);
}


VALUE method_murmur_hash(VALUE self, VALUE key, VALUE seed) {
  return call_murmur_func(MurmurHash2, key, seed);
}

VALUE method_aligned_murmur_hash(VALUE self, VALUE key, VALUE seed) {
  return call_murmur_func(MurmurHashAligned2, key, seed);
}

VALUE method_neutral_murmur_hash(VALUE self, VALUE key, VALUE seed) {
  return call_murmur_func(MurmurHashNeutral2, key, seed);
}

VALUE method_murmur_hash64(VALUE self, VALUE key, VALUE seed) {
#ifdef _LP64
  /* we're on a 64-bit machine so act like it, punk */
  return call_murmur64_func(MurmurHash64A, key, seed);
#else
  return call_murmur64_func(MurmurHash64B, key, seed);
#endif
}

extern "C" void Init_murmur() {
  MurmurHashModule = rb_define_module("MurmurHash");

  rb_define_module_function(MurmurHashModule,
                            "murmur_hash",
                            (VALUE(*)(...))&method_murmur_hash,
                            2);

  rb_define_module_function(MurmurHashModule,
                            "aligned_murmur_hash",
                            (VALUE(*)(...))&method_aligned_murmur_hash,
                            2);
  rb_define_module_function(MurmurHashModule,
                            "neutral_murmur_hash",
                            (VALUE(*)(...))&method_neutral_murmur_hash,
                            2);
  rb_define_module_function(MurmurHashModule,
                            "murmur_hash64",
                            (VALUE(*)(...))&method_murmur_hash64,
                            2);
}
