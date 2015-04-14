#!/usr/bin/env ruby

case ARGV[0]
when 'test'
  print `cd ~/cachelab-handout && make`
  exit $?.exitstatus
when 'score'
  print `cd ~/cachelab-handout && make && ./test-csim`
  exit $?.exitstatus
else
  puts <<-HELP
Usage: ./do <command>

Commands:
    test        Test if everything's fine
    score       Get score of it
  HELP
end
