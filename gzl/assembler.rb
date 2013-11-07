#!/usr/bin/ruby

# vars
@width = 32
@inst_map = {
  set:   { bin: '0100', struct: [:reg, :imm] },
  cmp:   { bin: '0110', struct: [:reg, :reg] },
  mov:   { bin: '0111', struct: [:reg, :reg] },
  add:   { bin: '0000', struct: [:reg, :reg, :reg] },
  sub:   { bin: '0001', struct: [:reg, :reg, :reg] },
  mul:   { bin: '0010', struct: [:reg, :reg, :reg] },
  div:   { bin: '0011', struct: [:reg, :reg, :reg] },
  load:  { bin: '1000', struct: [:reg, :addr] },
  store: { bin: '1001', struct: [:addr, :reg] },
  jmp:   { bin: '1100', struct: [:block] },
  jlt:   { bin: '1101', struct: [:block] },
  jgt:   { bin: '1110', struct: [:block] },
}
@jump_map = {}
@regs = {}


# methods
class Integer
  def to_b(len)
    "%0#{ len }d" % self.to_s(2)
  end
end

def fail(msg, line = '?')
  e = SyntaxError.new "#{ARGV[0]}:#{line} #{msg}"
  e.set_backtrace []
  raise e
end

def validate_type(expected, actual)
  case expected
    when :reg
      actual =~ /^\$.*$/
    when :addr
      actual =~ /^\$.*$/
    when :imm
      actual =~ /^\d+$/
    when :block
      actual =~ /^\w+$/
  end
end

def convert_arg(type, arg)
  case type
    when :reg, :addr
      @regs[arg] ||= @regs.length.to_b 3
      if @regs.count > 8
        fail "Using too many registers (max 8)"
      end
      @regs[arg]
    when :imm
      arg.to_i.to_b 25
    when :block
      fail "Unknown block identifier '#{arg}'" unless @jump_map[arg]
      @jump_map[arg]
  end
end


# read program
program = File.readlines(ARGV[0])


# split and clean lines
program = program.inject([]) do |arr, line|
  line = line.chomp.strip.gsub(/(#.*)$/, '')
  unless line.empty?
    arr << line.delete(',').split
  end
  arr
end


# process jumps
program.each_with_index do |line, i|
  inst = line.first
  if /\w+:$/ =~ inst
    fail "Address indentifier taken no arguments", i if line.length > 1
    @jump_map[inst.delete ':'] = (i - @jump_map.length).to_b 28
  end
end
# remove address identifications
program.reject! { |line| @jump_map.has_key? line.first.delete ':' }

# copy to show original in errors
asm = program

# parse program
program.each_with_index do |line, i|
  inst = line.first

  unless @inst_map[inst.to_sym] 
    fail "Unknown instruction '#{inst}'"
  end

  expected_struct = @inst_map[inst.to_sym][:struct]

  unless expected_struct.length == line.length - 1
    fail "Wrong number of arguments in: #{line.to_s}"
  end

  line[0] = @inst_map[inst.to_sym][:bin]

  expected_struct.each_with_index do |type, j|
    unless validate_type expected_struct[j], line[j+1]
      fail "Malformed argument in: '#{asm[i].join ' '}'"
    end

    line[j+1] = convert_arg type, line[j+1]
  end

  # add trailing zeros
  line[-1] += '0' * (@width - line.join.length) 
end


# print program
program.each_with_index do |line, i|
  puts "#{i} #{line.join.to_i(2).to_s(16)}"
end
