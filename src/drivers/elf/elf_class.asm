; elf_class.asm
; 32-bit x86 NASM assembly - ELFReader class for C usage

section .bss
; Nothing hardcoded here. Buffer will be provided by object.

section .text
global ELFReader_init
global ELFReader_read_header
global ELFReader_print_header

; --------------------------
; ELFReader struct layout
; size: 12 bytes
; offset 0: path pointer (char*)
; offset 4: buffer pointer (uint8_t* for header)
; offset 8: file descriptor (int)
; --------------------------

; --------------------------
; void ELFReader_init(ELFReader* self, const char* path, uint8_t* buffer)
; edi = pointer to ELFReader object
; esi = path pointer
; edx = buffer pointer
; --------------------------
ELFReader_init:
    mov [edi + 0], esi        ; path
    mov [edi + 4], edx        ; buffer
    mov dword [edi + 8], -1   ; fd = -1
    ret

; --------------------------
; void ELFReader_read_header(ELFReader* self)
; edi = pointer to ELFReader object
; --------------------------
ELFReader_read_header:
    ; open file
    mov eax, 5                  ; sys_open
    mov ebx, [edi + 0]          ; path
    mov ecx, 0                  ; O_RDONLY
    int 0x80
    mov [edi + 8], eax           ; save fd

    ; read 52 bytes into buffer
    mov eax, 3                  ; sys_read
    mov ebx, [edi + 8]          ; fd
    mov ecx, [edi + 4]          ; buffer pointer
    mov edx, 52                 ; bytes to read
    int 0x80

    ; close file
    mov eax, 6                  ; sys_close
    mov ebx, [edi + 8]
    int 0x80
    ret

; --------------------------
; void ELFReader_print_header(ELFReader* self)
; edi = pointer to ELFReader object
; --------------------------
ELFReader_print_header:
    ; just print first 16 bytes (magic) for demonstration
    mov eax, 4          ; sys_write
    mov ebx, 1          ; stdout
    mov ecx, [edi + 4]  ; buffer pointer
    mov edx, 16         ; length
    int 0x80
    ret
