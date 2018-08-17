dataseg segment
	arr db '7', '3', '2', '8', '9', '1', '4', '5', '6', '0', 13, 10, '$'
dataseg ends

stackseg segment stack			; 要在最后加上 stack, 否则无法建立堆
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

; 通过 getUsername 可以对用户输入的 0~9 进行排序
getUsername:
	mov cx, 10			; 由用户输入10个数字
	mov bx, offset arr		; 此处等效于 mov bx, 0
	L0:
		mov ah, 1			; 带回显的键盘输入
		int 21h				; 系统调用
		mov ds:[bx], al		; 等效于 mov [bx], al
		inc bx
	loop L0

	mov dl, 10				; 先回车换行 '\n'
	mov ah, 2
	int 21h

	;lea dx, arr				; 
	;mov ah, 09h
	;int 21h

bubbleSort:

	mov cx, 9		; 10个数, 9次,
					; i 从0开始, 每次 a[i] vs a[i+1]
	L1:				; 外层循环 cx 次
		push cx
		; sub cx, 1 ; 思考: 如果去掉这行的注释会怎么样，如何证明
		cmp cx, 0
		jz output

		mov bx, offset arr
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
	lea dx, arr
	mov ah, 09h
	int 21h

	mov ah, 4ch
	int 21h
codeseg ends

end start


; 对10个数进行冒泡排序, 修改 L57~L58 可改变排序方式(大->小, 小->大)
;
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


