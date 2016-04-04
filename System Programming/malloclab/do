#!/usr/bin/env ruby
require 'diffy'
include Diffy

begin
  case ARGV[0]
  when 't', 'test'
    `cd ~/malloclab-handout && make`
    print `~/malloclab-handout/mdriver -V`
    exit $?.exitstatus
  when 'h', 'help', '-h', '--help'
    puts <<-HELP
Try compile your work.

Usage: ./do [<param>]

Parameters:
    (nothing)       Build the source codes
    test            Run all test suites
    help            Get this message
    HELP
  else
    print `cd ~/malloclab-handout && make`
    exit $?.exitstatus
  end
rescue Interrupt
end
