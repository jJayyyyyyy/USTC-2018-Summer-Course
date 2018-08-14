dataseg segment
	str db '9', '8', '7', '3', '2', '1', '4', '5', '6', '0', 13, 10, '$'
dataseg ends

; 要在最后加上 stack, 否则无法建立堆
stackseg segment stack
	s dw 1 dup(0)
stackseg ends

codeseg segment
	assume cs:codeseg, ds:dataseg, ss:stackseg
start:
	mov ax, dataseg
	mov ds, ax

	mov ax, stackseg
	mov ss, ax
	mov sp, 10h			; 栈顶指针, 栈向上生长(高地址->低地址)

	lea dx, str
	mov ah, 09h
	int 21h

	mov cx, 10			; 10个数

	L1:					; 外层循环 cx 次
		push cx
		sub cx, 1
		cmp cx, 0
		jz output

		mov bx, offset str
		mov ax, 0

		L2:				; 外层循环 cx - 1 次
			mov al, [bx]
			mov ah, [bx+1]
			cmp al, ah
			jbe next			; continue, 从小到大
			;jae next			; contunue, 从大到小

			;mov dl, al
			;mov al, ah
			;mov ah, dl
			xchg al, ah
			
			mov [bx], al
			mov [bx+1], ah

			next:
				nop

			add bx, 1;

		loop L2

		pop cx
	loop L1			; 做完一次循环，cx--, 若cx==0则退出, 参考<汇编语言> P100

output:
	lea dx, str
	mov ah, 09h
	int 21h

	mov ah, 4ch
	int 21h
codeseg ends
	end start


; 对10个数进行冒泡排序, 修改 L39~L40 可改变排序方式(大->小, 小->大)
; C语言表达
; for( int i = 0; i < n; i++ ){
; 	for( int j = 0; j < n-i; j++ ){
; 		if( a[j] > a[j+1] ){
; 			swap(...);
; 		}
; 	}
; }

; TODO:
; 由用户输入 n, 并输入 n 个待排序数字
; string -> int, 如用户输入"12", 则要将其转化为 dw/dd 12
; 设置 stack 大小


