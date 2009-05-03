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
  version = '0'
  if defined?(MurmurHash)
    version = MurmurHash::VERSION
  end

  h = Hoe.new('murmur_hash', version) do |p|
    # p.rubyforge_name = 'murmur_hash' # if different than lowercase project name
    p.developer('Jeff Hodges', 'jeff@somethingsimilar.com')
    p.extra_deps << ['rake-compiler', '~>0.5']
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

# Putting this out here cuts off a great deal of time.
@gems = Gem::SourceIndex.from_installed_gems

def conditionally_install_gem(name, version_requirements)

  di = Gem::DependencyInstaller.new
  hoe_dep = Gem::Dependency.new('hoe', "~> 1.12")
  if @gems.search(hoe_dep).empty?
    di.install hoe_dep
  end
end

task :default => :compile

# Taken liberally from http://blog.labnotes.org/2008/02/28/svn-checkout-rake-setup/
desc "If you're building from source, run this task first to setup the necessary dependencies."
task :setup do
  require 'rubygems'
  require 'rubygems/dependency_installer'
  require 'rubygems/requirement'

  puts "Checking for gems that need to be installed."
  conditionally_install_gem('hoe', '~>1.12')

  require 'hoe'
  h = define_hoe_tasks

  # Runtime dependencies from the Gem's spec
  dependencies = h.spec.dependencies

  dependencies.each do |dep|
    conditionally_install_gem(dep.name, dep.version_requirements)
  end

  puts "\nAnd done."
end

# vim: syntax=Ruby
