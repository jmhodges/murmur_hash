require "test/unit"
require File.expand_path(File.dirname(__FILE__) + "/../lib/murmur_hash")


# I'm sure there's a simpler way to do this, but I can't remember it
# sooo. From:
# http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-talk/256730
# Also posted at: http://gist.github.com/55220
module Endian
  def self.big?
    endianness == :big
  end

  def self.little?
    endianness == :little
  end

  def self.endianness
    x = 0xdeadbeef

    endian_type = {
      Array(x).pack("V*") => :little,
      Array(x).pack("N*") => :big
    }

    endian_type[Array(x).pack("L*")]
  end
end

class TestMurmurHash < Test::Unit::TestCase
  def test_neutral_does_the_right_thing
    assert_equal(3435905073, MurmurHash.neutral_murmur_hash("string", 23),
                 "neutral_murmur_hash returns the same on boxes of both endianesses"
                 )
  end

  def test_normal_does_the_right_thing
    answer = Endian.little? ? 3435905073 : "FIXME find a big-endian box"
    assert_equal(answer, MurmurHash.murmur_hash("string", 23),
                 "murmur_hash returns #{answer} on a #{Endian.endianness}-endian box, which this box is"
                 )
  end

  def test_aligned_does_the_right_thing
    answer = Endian.little? ? 3435905073 : "FIXME find a big-endian box"
    assert_equal(answer, MurmurHash.aligned_murmur_hash("string", 23),
                 "aligned_murmur_hash returns #{answer} on a #{Endian.endianness}-endian box, which this box is"
                 )
  end

  def test_64bit_does_the_right_thing
    answer = Endian.little? ? 12403831550545192078 : "FIXME find a big-endian box"
    assert_equal(answer, MurmurHash.murmur_hash64("string", 23),
                 "64-bit murmur_hash returns #{answer} on a #{Endian.endianness}-endian box, which this box is"
                 )
  end

  def test_seeds_can_be_as_big_as_unsigned_32bit_ints_but_no_bigger
    assert_equal 713507990, MurmurHash.murmur_hash('a', 4294967295), "bumping the seed up to the edge of 2**32 - 1 in 32-bit hashing"
    assert_raises(RangeError){ MurmurHash.murmur_hash('a', 4294967296) }
    assert_equal 5672511219810442881, MurmurHash.murmur_hash64('a', 4294967295), "bumping the seed up to the edge of  2**32 - 1 in 64-bit hashing"
    assert_raises(RangeError){ MurmurHash.murmur_hash64('a', 4294967296) }
  end
  
  def test_all_hash_methods_raise_error_if_key_is_not_a_string
    assert_raises(TypeError) { MurmurHash.murmur_hash([], 23) }
    assert_raises(TypeError) { MurmurHash.neutral_murmur_hash([], 23) }
    assert_raises(TypeError) { MurmurHash.aligned_murmur_hash([], 23) }
    assert_raises(TypeError) { MurmurHash.murmur_hash64([], 23) }
  end

  def test_all_hash_methods_raise_error_if_seed_is_not_a_fixnum
    assert_raises(TypeError) { MurmurHash.murmur_hash("fa", []) }
    assert_raises(TypeError) { MurmurHash.neutral_murmur_hash("fa", "fff") }
    assert_raises(TypeError) { MurmurHash.aligned_murmur_hash("fa", 23.0) }
    assert_raises(TypeError) { MurmurHash.murmur_hash64("fa", "faf") }
  end
end
