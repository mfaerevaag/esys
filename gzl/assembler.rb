instr_map = {
  :dis     => '1111',
  :set     => '0100',
  :addi    => '0101',
  :cmp     => '0110',
  :mov     => '0111',

  :add     => '0000',
  :sub     => '0001',
  :mul     => '0010',
  :div     => '0011',

  :load    => '1000',
  :store   => '1001',

  :jmp     => '1100',
  :jlt     => '1101',
  :jgt     => '1110',
}

def trail(num, len)
  "%0#{ len }d" % num.to_i.to_s(2)
end

program = File.read(ARGV[0])

# process immediate values
imms = program.scan(/[\s|,]\d+/).uniq
imms.each do |imm|
  program = program.gsub(imm, trail(imm, 25))
end

# process opcodes
instr_map.each do |instr, bin|
  program = program.gsub instr.to_s, bin
end

# process registers
regs = program.scan(/%\w+/).uniq
fail 'Too many registers in use (max 8)' if regs.size > 8

regs.each_with_index do |name, n|
  program = program.gsub name, trail(n, 2)
end

# process jumps
ln = 0
jump_map = {}
program.each_line do |line| 
  next if line.strip.empty?
  if /\w+:$/ =~ line.strip
    jump_map[line.strip[0..-2]] = ln.to_s(2)
  else
    ln += 1
  end
end

jump_map.each do |jump, addr|
  program = program.gsub jump, addr
end

# remove comments
program = program.gsub(/#.*$/, '')

program.each_line do |line|
  if not line.include? ':' and not line.strip.empty?
    puts line.strip.gsub(/,|\s+/, '')
  end
end
