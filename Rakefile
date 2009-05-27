# -*- ruby -*-
require 'rubygems'
require 'rake'

def define_rake_stuff
  require 'hoe'
  begin
    require './lib/murmur_hash.rb'

  rescue LoadError => e
    murmur_bundle = File.expand_path(File.dirname(__FILE__) + '/lib/murmur')
    if (e.message =~ /#{murmur_bundle}(\.bundle)?$/)
      STDERR.puts "Looks like you have not run a successful `rake compile`, yet. Do that next!"
    else
      raise e
    end
  end
  Rake::ExtensionTask.new('murmur')
  define_hoe_tasks
end

def define_hoe_tasks
  # We don't want to fail completely if the library couldn't be
  # required in due to gem problems or similar. So, we have a default
  # version that will satisfy Hoe until those issues are (probably)
  # resolved later in this Rakefile.
  version = '0'
  if defined?(MurmurHash)
    version = MurmurHash::VERSION
  end

  h = Hoe.new('murmur_hash', version) do |p|
    # p.rubyforge_name = 'murmur_hash' # if different than lowercase project name
    p.developer('Jeff Hodges', 'jeff@somethingsimilar.com')
    p.extra_deps << ['rake-compiler', '~>0.5']
    p.blog_categories = ['murmur_hash', 'ruby']
    p.spec_extras = { :extensions => ["ext/murmur/extconf.rb"] }
  end
  
  Rake::Task[:test].prerequisites << :compile
  h
end

begin
  require 'rake/extensiontask'
  define_rake_stuff
rescue LoadError => e
  STDERR.puts(
              "Be sure to run 'sudo rake setup' because you don't have all the gems installed"
              )
end


def conditionally_install_gem(name, version_requirements, all_gems)
  di = Gem::DependencyInstaller.new
  new_dep = Gem::Dependency.new(name, version_requirements)
  if all_gems.search(new_dep).empty?
    di.install new_dep
  end
end

task :default => :compile

desc "If you're building from source, run this task first to setup the necessary dependencies."
task :setup do
  require 'rubygems'
  require 'rubygems/dependency_installer'
  require 'rubygems/requirement'

  all_gems = Gem::SourceIndex.from_installed_gems
  puts "Checking for gems that need to be installed."
  conditionally_install_gem('hoe', '~>1.12', all_gems)

  require 'hoe'
  h = define_hoe_tasks

  # Runtime dependencies from the Gem's spec
  dependencies = h.spec.dependencies

  # Refresh to catch what is needed by this library but was installed
  # along with hoe, so we don't repeat the (long) install process.
  all_gems = Gem::SourceIndex.from_installed_gems

  dependencies.each do |dep|
    conditionally_install_gem(dep.name, dep.version_requirements, all_gems)
  end

  puts "\nAnd done."
end

# vim: syntax=Ruby
