require 'rake'

Gem::Specification.new do |s|
  s.name = "murmur_hash"
  s.version = "0.9.8"

  if s.respond_to? :required_rubygems_version=
      s.required_rubygems_version = Gem::Requirement.new(">= 1.2")
  end
  s.authors = ['Jeff Hodges', 'Austin Appleby']

  s.date = "2008-01-30"
  s.summary = "A ruby extension of the MurmurHash2 functions"
  s.description = s.summary.dup
  s.email = "jeff@somethingsimilar.com"
  s.files = FileList['README.rdoc', 'ext/**/extconf.rb', 'ext/**/*.cpp'].to_a
  s.has_rdoc = true
  s.homepage = "http://github.com/jashkenas/ruby-processing/wikis"
  s.rdoc_options = ["--line-numbers", "--inline-source", "--title", "MurmurHash", "--main", "README.rdoc"]
  s.require_paths = ["lib"]
  s.rubyforge_project = "murmur_hash"
  s.extensions = FileList['ext/**/extconf.rb']
end
