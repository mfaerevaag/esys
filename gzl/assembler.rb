#!/usr/bin/ruby

imap = {
  dis:   '1111',
  set:   '0100',
  addi:  '0101',
  cmp:   '0110',
  mov:   '0111',
  add:   '0000',
  sub:   '0001',
  mul:   '0010',
  div:   '0011',
  load:  '1000',
  store: '1001',
  jmp:   '1100',
  jlt:   '1101',
  jgt:   '1110',
}

def trail (num, len) 
  " %0#{ len }d" % num.to_i.to_s(2)
end

program = File.read(ARGV[0])

# process immediate values
program = program.gsub(/[^!][\s|,](\-)?\d+/) { |n| trail(n.delete(','), 25) }

# process opcodes
imap.each { |instr, bin| program.gsub! instr.to_s, bin }

# process registers
regs = program.scan(/%\w+/).uniq
fail "Too many registers in use (max 8) #{ regs.join("\n") }" if regs.size > 8

regs.each_with_index { |name, n| program.gsub! name, trail(n, 3) }

# process jumps
ln = 0
jump_map = {}
program.each_line do |line|
  next if line.strip.empty?
  if /\w+:$/ =~ line.strip
    jump_map[line.strip[0..-2]] = trail(ln, 28)
  else
    ln += 1
  end
end

jump_map.each { |jump, addr| program.gsub! jump, addr }

# remove comments
program.gsub!(/#.*$/, '')

# fill in zeroes
ln = 0
program.each_line do |line|
  line.strip!
  if not line.include? ':' and not line.empty?
    size = line.gsub(/,|\s+/, '').size
    n = 32 - size
    instr = line[0..3]
    if [imap[:store], imap[:load], imap[:set]].include? instr then
      line = line[0..6] + ('0' * n) + line[7..-1]
    elsif imap[:dis] == instr then
      line = line[0..3] + ('0' * n) + line[4..-1]
    else
      line = line + ('0' * n)
    end
    puts ln.to_s + ' ' + line.gsub(/,|\s+/, '').to_i(2).to_s(16)
    ln += 1
  end
end
