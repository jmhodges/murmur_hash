# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = %q{murmur_hash}
  s.version = "1.0.0"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Jeff Hodges"]
  s.date = %q{2009-05-03}
  s.description = %q{* A ruby extension for the MurmurHash2 functions. See http://murmurhash.googlepages.com/}
  s.email = ["jeff@somethingsimilar.com"]
  s.extra_rdoc_files = ["History.txt", "Manifest.txt", "README.txt"]
  s.files = ["History.txt", "Manifest.txt", "README.txt", "Rakefile", "lib/murmur_hash.rb", "test/test_murmur_hash.rb", "ext/murmur/extconf.rb", "ext/murmur/murmur_hash.cpp"]
  s.has_rdoc = true
  s.homepage = %q{http://github.com/jmhodges/murmur_hash}
  s.rdoc_options = ["--main", "README.txt"]
  s.require_paths = ["lib", "ext"]
  s.rubyforge_project = %q{murmur_hash}
  s.rubygems_version = %q{1.3.2}
  s.summary = %q{* A ruby extension for the MurmurHash2 functions}
  s.test_files = ["test/test_murmur_hash.rb"]

  if s.respond_to? :specification_version then
    current_version = Gem::Specification::CURRENT_SPECIFICATION_VERSION
    s.specification_version = 3

    if Gem::Version.new(Gem::RubyGemsVersion) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<rake-compiler>, ["~> 0.5"])
      s.add_development_dependency(%q<hoe>, [">= 1.12.2"])
    else
      s.add_dependency(%q<rake-compiler>, ["~> 0.5"])
      s.add_dependency(%q<hoe>, [">= 1.12.2"])
    end
  else
    s.add_dependency(%q<rake-compiler>, ["~> 0.5"])
    s.add_dependency(%q<hoe>, [">= 1.12.2"])
  end
end
