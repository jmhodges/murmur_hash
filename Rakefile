require 'rake'
require 'fileutils'
include FileUtils

LIB_ENDING = Config::CONFIG['DLEXT']
ARCHLIB = "lib/#{::Config::CONFIG['arch']}"

ext = "ext/murmur_hash"
ext_so = "#{ext}/murmur_hash.#{LIB_ENDING}"
ext_files = FileList[
                     "#{ext}/extconf.rb",
                     "#{ext}/Makefile",
                     "lib"
                    ]
task :murmur_hash =>
  ["#{ext}/Makefile", ext_so]

file "#{ext}/Makefile" => ["#{ext}/extconf.rb"] do
  Dir.chdir(ext) { ruby "extconf.rb" }
end

file ext_so => ext_files do
  Dir.chdir(ext) do
    sh(RUBY_PLATFORM =~ /win32/ ? 'nmake' : 'make')
  end
  mkdir_p ARCHLIB
  cp ext_so, ARCHLIB
end

task "lib" do
  directory "lib"
end

desc "Compiles the Ruby extension for murmur_hash"
task :compile => :murmur_hash do
  if Dir.glob(File.join(ARCHLIB,"murmur_hash.*")).length == 0
    STDERR.puts "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
    STDERR.puts "Gem actually failed to build.  Your system is"
    STDERR.puts "NOT configured properly to build hpricot."
    STDERR.puts "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
    exit(1)
  end
end

task :package do
  sh 'gem build murmur_hash.gemspec'
end

task :repackage do
  sh 'rm murmur_hash*.gem'
  sh 'gem build murmur_hash.gemspec'
end
