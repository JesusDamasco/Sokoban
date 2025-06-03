section .text
    global mover_jugador

mover_jugador:
    push rbp
    mov rbp, rsp
    push rbx
    push rsi
    push rdi
    push r12
    push r13
    push r14

    ; rcx -> puntero a struct Mapa
    ; edx -> dx
    ; r8d -> dy

    ; nuevo X = jugadorX + dx
    mov eax, [rcx + 16]
    add eax, edx
    mov r12d, eax    ; r12d = nuevo X

    ; nuevo Y = jugadorY + dy
    mov eax, [rcx + 20]
    add eax, r8d
    mov r13d, eax    ; r13d = nuevo Y

    ; validar límites
    cmp r12d, 0
    jl salir
    cmp r13d, 0
    jl salir

    mov eax, [rcx + 4] ; columnas
    cmp r12d, eax
    jge salir
    mov eax, [rcx + 0] ; filas
    cmp r13d, eax
    jge salir

    ; rbx = mapa->tablero[r13d]
    mov rax, [rcx]
    mov r14, r13
    shl r14, 3
    add rax, r14
    mov rbx, [rax]

    ; celda destino = tablero[r13][r12]
    movzx edi, byte [rbx + r12]
    cmp dil, '#'
    je salir

    ; si es caja
    cmp dil, 'C'
    jne mover_jugador_normal

    ; calcular posición nueva de caja
    mov eax, r12d
    add eax, edx
    mov r14d, eax

    mov eax, r13d
    add eax, r8d
    mov r15d, eax

    ; validar nueva posición de caja
    cmp r14d, 0
    jl salir
    cmp r15d, 0
    jl salir

    mov eax, [rcx + 4]
    cmp r14d, eax
    jge salir
    mov eax, [rcx + 0]
    cmp r15d, eax
    jge salir

    ; obtener celda nueva caja
    mov rax, [rcx]
    mov rsi, r15
    shl rsi, 3
    add rax, rsi
    mov rdi, [rax]
    movzx eax, byte [rdi + r14]
    cmp al, ' '
    je mover_caja
    cmp al, 'X'
    je mover_caja
    jmp salir

mover_caja:
    ; eliminar caja vieja
    mov rax, [rcx]
    mov rsi, r13
    shl rsi, 3
    add rax, rsi
    mov rdi, [rax]
    mov byte [rdi + r12], ' '

    ; obtener puntero a nueva posición de caja
    mov rsi, r15
    shl rsi, 3
    mov rax, [rcx]
    add rsi, rax
    mov rdi, [rsi]

    ; verificar si había una X
    movzx eax, byte [rdi + r14]
    cmp al, 'X'
    jne no_objetivo

    ; era un objetivo: restar contador y no poner caja
    sub dword [rcx + 24], 1
    jmp fin_caja

no_objetivo:
    ; mover caja a nueva posición
    mov byte [rdi + r14], 'C'

fin_caja:


mover_jugador_normal:
    ; borrar jugador viejo
    mov rax, [rcx]
    mov esi, [rcx + 20]
    shl rsi, 3
    add rax, rsi
    mov rbx, [rax]
    mov edi, [rcx + 16]
    mov byte [rbx + rdi], ' '

    ; colocar jugador nuevo
    mov rax, [rcx]
    mov rsi, r13
    shl rsi, 3
    add rax, rsi
    mov rbx, [rax]
    mov byte [rbx + r12], 'P'

    ; actualizar coordenadas
    mov [rcx + 16], r12d
    mov [rcx + 20], r13d

salir:
    pop r14
    pop r13
    pop r12
    pop rdi
    pop rsi
    pop rbx
    pop rbp
    ret