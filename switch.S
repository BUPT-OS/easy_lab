.text
.global thread_switch
.align 8
thread_switch:
    pop     %rax 
    movq    %rax,(%rdi)
    movq    %rsp,0x8(%rdi)   
    movq    %rbp,0x10(%rdi)  
    movq    %rbx,0x18(%rdi)  
    movq    %r12,0x20(%rdi)  
    movq    %r13,0x28(%rdi)  
    movq    %r14,0x30(%rdi)  
    movq    %r15,0x38(%rdi)  
    movq    0x38(%rsi), %r15
    movq    0x30(%rsi), %r14
    movq    0x28(%rsi), %r13
    movq    0x20(%rsi), %r12
    movq    0x18(%rsi), %rbx
    movq    0x10(%rsi), %rbp
    movq    0x8(%rsi), %rsp
    movq    (%rsi),%rax  
    push    %rax
    movq    %rsi,%r10
    movq    0x40(%r10),%rdi
    movq    0x48(%r10),%rsi
    movq    0x50(%r10),%rdx
    ret

