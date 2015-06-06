#!/usr/bin/env ruby
begin
  case ARGV[0]
  when 'h', 'help', '-h', '--help'
    puts <<-HELP
Try compile your work.

Usage: ./do [<param>]

Parameters:
    (nothing)       Build the source codes
    help            Get this message
    HELP
  else
    print `cd ~/proxylab-handout && make`
    exit $?.exitstatus
  end
rescue Interrupt
end
