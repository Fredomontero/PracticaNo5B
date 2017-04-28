dosseg
.model tiny

.code
public  _outportB
public  _inportB
public  _putchar
public  _delay

;**********************************************
;Procedimiento que escribe el dato almacenado *
;en AL en el puerto direccionado por DX       *
;**********************************************
_outportB proc
  push bp
  mov bp,sp
  push dx
  push ax
  mov ax,0

  mov word ptr dx,[bp+4]
  mov byte ptr al,[bp+6]
  out dx,al

  pop ax
  pop dx
  pop bp

  ret
_outportB endp

;****************************************************
;Procedimiento que imprime en pantalla el caracter  *
;almacenado en DL me diante el servicio 2 de la int *
;21h                                                *
;****************************************************
_putchar proc
  push bp
  mov bp,sp
  push dx
  push ax

  mov byte ptr dl,[bp+4]
  mov ah,2
  int 21h

  pop ax
  pop dx
  pop bp
  ret
_putchar endp

;**********************************************
;Procedimiento que obtiene un dato del puerto *
;especificado en DX                           *
;**********************************************
_inportB proc
  push bp
  mov bp,sp
  push dx
  mov ax,0

  mov word ptr dx,[bp+4]
  in al,dx

  pop dx
  pop bp
  ret
_inportB endp

;**************************************************
;Procedimiento que genera una pausa en el sistema *
;                                                 *
;**************************************************
_delay proc
  push bp
  mov bp,sp
  push cx

  mov word ptr cx,[bp+4]
inicio:
  nop
  loop inicio

  pop cx
  pop bp
  ret
_delay endp

end
