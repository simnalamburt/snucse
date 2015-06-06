#!/usr/bin/env ruby
begin
  case ARGV[0]
  when 'r', 'run'
    `cd ~/proxylab-handout && make`
    system('../proxylab-handout/proxy 10200')
    exit $?.exitstatus
  when 'h', 'help', '-h', '--help'
    puts <<-HELP
Try compile your work.

Usage: ./do [<param>]

Parameters:
    (nothing)       Build the source codes
    run             Run the proxy
    help            Get this message
    HELP
  else
    system('cd ~/proxylab-handout && make')
    exit $?.exitstatus
  end
rescue Interrupt
end
