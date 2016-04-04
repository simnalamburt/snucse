#!/usr/bin/env ruby
require 'parallel'
require 'diffy'
include Diffy

begin
  case ARGV[0]
  when 't', 'test'
    def test(n)
      if (11..13) === n
        puts "#{n}: \e[33mUnknown\e[0m"
        return
      end

      n = n.to_s.rjust(2, '0')
      actual = `cd ~/shlab-handout && ./sdriver.pl -t trace#{n}.txt -s ./tsh    -a "-p"`.gsub!(/[0-9]/, '#')
      expected = `cd ~/shlab-handout && ./sdriver.pl -t trace#{n}.txt -s ./tshref -a "-p"`.gsub!(/[0-9]/, '#')

      diff = Diff.new(expected, actual)
      unless diff.any?
        puts "#{n}: \e[32mPassed\e[0m"
      else
        puts "#{n}: \e[31mFailed\e[0m", '', diff.to_s(:color), ''
      end
    end

    n = ARGV[1]
    if n.nil?
      Parallel.map(1..16, in_processes: 10, &method(:test))
    else
      test(n)
    end
  when 'h', 'help', '-h', '--help'
    puts <<-HELP
Try compile your work.

Usage: ./do [<param>]

Parameters:
    (nothing)       Build the source codes
    test            Run all test suites
    test <n>        Run n-th test suite
    help            Get this message
    HELP
  else
    print `cd ~/shlab-handout && make`
    exit $?.exitstatus
  end
rescue Interrupt
end
