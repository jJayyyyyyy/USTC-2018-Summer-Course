; 首先输出 [name: ]
; 然后获取用户名, 如 [Alice]
; 最后输出 [hello, Alice]

dataseg segment
	; 相当于定义了3个指针，分别指向3个字符数组
	info db 'n', 'a', 'm', 'e', ':', ' ', '$'
	hello db 'h', 'e', 'l', 'l', 'o', ',', ' ', '$'
	username db 10 DUP('$')
dataseg ends

codeseg segment
	assume cs:codeseg, ds:dataseg
start:
	mov ax, dataseg
	mov ds, ax		; ax 是中转站, dataseg 必须通过 ax 传递给 ds

	lea dx, info		; 效果与 mov dx, offset info 相同
	mov ah, 09h		; 09h的功能是输出字符串
	int 21h			; 结合ah的值进行系统调用


	; bx 是一个指针数组, char * bx[]
	mov bx, offset username

getUsername:
	mov ah, 1		; 输入单个字符, 无缓冲, 输入的字符会放在 al 中
	int 21h
	cmp al, 13		; 判断输入的是否为回车 (ASCII = 13), 判断结果放在 FLAGS 寄存器中
	jz output		; 如果是回车就结束输入，跳到输出函数, jump zero 根据 FLAGS 寄存器的值进行跳转
	mov [bx], al		; 输入的字符会进入 al, char ch = al
				; char * p = bx[i]
				; *p = ch
				; bx 是指针数组的下标, [bx] 是 bx 所指的内容

	inc bx			; bx++, 指针向前移动
	jmp getUsername		; 循环, 重复上述过程

output:
	mov dl, 13		; 等效于 mov dx, 13，13是 ASCII 的回车
	mov ah, 2		; 输出字符，也就是上面的回车
	int 21h

	mov dx, offset hello	; 效果与 lea dx, hello 相同
				; 定位到 hello 字符数组的起点
	mov ah, 09h		; 09h 功能是输出字符串
	int 21h

	mov byte ptr [bx], '$'		; 增加结束符 '$', 相当于C中的 '\0'
					; bx 表示下标, [] 表示内容, byte ptr 是宽度
	mov dx, offset username		; 定位到 username 字符数组的起点
	mov ah, 09h
	int 21h

; 顺序执行，即使没有jmp到这里，也会在ouput结束后执行exit
exit:
	mov ah, 4ch		; 功能相当于 return 0, 结束程序, 返回的值由 al 决定
	int 21h

codeseg ends

end start
