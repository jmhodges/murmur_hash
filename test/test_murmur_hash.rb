require "test/unit"
require "murmur_hash"


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
end
