#!/usr/bin/env ruby

case ARGV[0]
when 'h', 'help', '-h', '--help'
  puts <<-HELP
Try compile your work.

Usage: ./do [<param>]

Parameters:
    h, help         Get this message
  HELP
else
  print `cd ~/shlab-handout && make`
  exit $?.exitstatus
end
