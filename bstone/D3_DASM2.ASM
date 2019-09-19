.386C
IDEAL
MODEL	MEDIUM,C

; *** BLAKE STONE: ALIENS OF GOLD RESTORATION ***
INCLUDE 'GAMEVER.EQU'

;============================================================================

DATASEG

EXTRN	mr_rowofs:WORD
EXTRN	mr_count:WORD
EXTRN	mr_xstep:WORD
EXTRN	mr_ystep:WORD
EXTRN	mr_xfrac:WORD
EXTRN	mr_yfrac:WORD
EXTRN	mr_dest:WORD
EXTRN jimflags:WORD
; *** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***
IFNDEF GAMEVER_RESTORATION_AOG_100
EXTRN shadingtable:DWORD
ENDIF


FARDATA

planepics		db	8192 dup(?)	;	// 4k of ceiling, 4k of floor


PUBLIC	planepics

;============================================================================

CODESEG

; *** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***
IFNDEF GAMEVER_RESTORATION_AOG_100
;============================
;
; MapLSRow
;
;============================

PROC	MapLSRow
PUBLIC	MapLSRow
	push	esi
	push	edi
	push	ebp
	push 	ds

	mov      ax,[WORD shadingtable + 2]
	mov      fs,ax
	mov      bp,[mr_rowofs]
	mov		cx,[mr_count]
	mov		dx,[mr_ystep]
	shl		edx,16
	mov		dx,[mr_xstep]
	mov		si,[mr_yfrac]
	shl		esi,16
	mov		si,[mr_xfrac]
	mov		di,[mr_dest]
	mov		ax,SEG planepics
	mov		ds,ax
	mov		ax,0a000h
	mov		es,ax

; eax		and mask
; ebx		scratch offset and pixel values
; ecx   	loop counter
; edx		packed x / y step values
; esi		packed x / y fractional values
; edi		write pointer
; ebp		toprow to bottomrow delta
; es:		screenseg
; ds:		pictures


@@pixelloop:
	shld	ebx,esi,22				; shift y units in
	shld	ebx,esi,7				; shift x units in and one extra bit
	and	bx,1111111111110b		; mask off extra top bits and 0 low bit
	add	esi,edx					; position += step
	mov   ax,[bx]  				; get two source pixel
	mov	bx,ss:[WORD shadingtable]
	mov   bl,al						; map ceiling pixel
	mov   al,[fs:bx]           ; map ceiling pixel
	mov   [es:di],al     		; write ceiling pixel
	mov   bl,ah						; map floor pixel
	mov   ah,[fs:bx]           ; map floor pixel
	mov   [es:di+bp],ah     	; write floor pixel

	inc	di
	loop	@@pixelloop

	pop	ds
	pop	ebp
	pop	edi
	pop	esi

	retf

ENDP



;============================
;
; F_MapLSRow
;
;============================

PROC	F_MapLSRow
PUBLIC	F_MapLSRow
	push	esi
	push	edi
	push	ebp
	push 	ds

	mov      ax,[WORD shadingtable + 2]
	mov      fs,ax
	mov     bp,[mr_rowofs]
	mov		cx,[mr_count]
	mov		dx,[mr_ystep]
	shl		edx,16
	mov		dx,[mr_xstep]
	mov		si,[mr_yfrac]
	shl		esi,16
	mov		si,[mr_xfrac]
	mov		di,[mr_dest]
	mov		ax,SEG planepics
	mov		ds,ax
	mov		ax,0a000h
	mov		es,ax

; eax		and mask
; ebx		scratch offset and pixel values
; ecx   	loop counter
; edx		packed x / y step values
; esi		packed x / y fractional values
; edi		write pointer
; ebp		toprow to bottomrow delta
; es:		screenseg
; ds:		pictures


@@pixelloop:
	shld	ebx,esi,22				; shift y units in
	shld	ebx,esi,7				; shift x units in and one extra bit
	and	bx,1111111111110b		; mask off extra top bits and 0 low bit
	add	esi,edx					; position += step
	mov   ax,[bx]  				; get two source pixel
	mov	bx,ss:[WORD shadingtable]
	mov   bl,ah						; map floor pixel
	mov   ah,[fs:bx]           ; map floor pixel
	mov   [es:di+bp],ah     	; write floor pixel

	inc	di
	loop	@@pixelloop

	pop	ds
	pop	ebp
	pop	edi
	pop	esi

	retf

ENDP





;============================
;
; C_MapLSRow
;
;============================

PROC	C_MapLSRow
PUBLIC	C_MapLSRow
	push	esi
	push	edi
	push	ebp
	push 	ds

	mov      ax,[WORD shadingtable + 2]
	mov      fs,ax
	mov     bp,[mr_rowofs]
	mov		cx,[mr_count]
	mov		dx,[mr_ystep]
	shl		edx,16
	mov		dx,[mr_xstep]
	mov		si,[mr_yfrac]
	shl		esi,16
	mov		si,[mr_xfrac]
	mov		di,[mr_dest]
	mov		ax,SEG planepics
	mov		ds,ax
	mov		ax,0a000h
	mov		es,ax

; eax		and mask
; ebx		scratch offset and pixel values
; ecx   	loop counter
; edx		packed x / y step values
; esi		packed x / y fractional values
; edi		write pointer
; ebp		toprow to bottomrow delta
; es:		screenseg
; ds:		pictures


@@pixelloop:
	shld	ebx,esi,22				; shift y units in
	shld	ebx,esi,7				; shift x units in and one extra bit
	and	bx,1111111111110b		; mask off extra top bits and 0 low bit
	add	esi,edx					; position += step
	mov   ax,[bx]  				; get two source pixel
	mov	bx,ss:[WORD shadingtable]
	mov   bl,al						; map ceiling pixel
	mov   al,[fs:bx]           ; map ceiling pixel
	mov   [es:di],al     		; write ceiling pixel

	inc	di
	loop	@@pixelloop

	pop	ds
	pop	ebp
	pop	edi
	pop	esi

	retf

ENDP

ENDIF ;RESTORATION

;============================
;
; MapRow
;
;============================

PROC	MapRow
PUBLIC	MapRow
	push	esi
	push	edi
	push	ebp
	push 	ds

	mov      bp,[mr_rowofs]
	mov		cx,[mr_count]
	mov		dx,[mr_ystep]
	shl		edx,16
	mov		dx,[mr_xstep]
	mov		si,[mr_yfrac]
	shl		esi,16
	mov		si,[mr_xfrac]
	mov		di,[mr_dest]
	mov		ax,SEG planepics
	mov		ds,ax
	mov		ax,0a000h
	mov		es,ax

; eax		and mask
; ebx		scratch offset and pixel values
; ecx   	loop counter
; edx		packed x / y step values
; esi		packed x / y fractional values
; edi		write pointer
; ebp		toprow to bottomrow delta
; es:		screenseg
; ds:		pictures

	; *** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***
IFDEF GAMEVER_RESTORATION_AOG_100
	mov	ax,1111111111110b
ENDIF

@@pixelloop:
	shld	ebx,esi,22				; shift y units in
	shld	ebx,esi,7				; shift x units in and one extra bit
	; *** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***
IFDEF GAMEVER_RESTORATION_AOG_100
	and	bx,ax		; mask off extra top bits and 0 low bit
	add	esi,edx					; position += step
	mov   bx,[bx]  				; get two source pixel
	mov   [es:di],bl     		; write ceiling pixel
	mov   [es:di+bp],bh     	; write floor pixel
ELSE
	and	bx,1111111111110b		; mask off extra top bits and 0 low bit
	add	esi,edx					; position += step
	mov   ax,[bx]  				; get two source pixel
	mov   [es:di],al     		; write ceiling pixel
	mov   [es:di+bp],ah     	; write floor pixel
ENDIF
	inc	di
	loop	@@pixelloop

	pop	ds
	pop	ebp
	pop	edi
	pop	esi

	retf

ENDP



;============================
;
; F_MapRow
;
;============================

PROC	F_MapRow
PUBLIC	F_MapRow
	push	esi
	push	edi
	push	ebp
	push 	ds

	mov      bp,[mr_rowofs]
	mov		cx,[mr_count]
	mov		dx,[mr_ystep]
	shl		edx,16
	mov		dx,[mr_xstep]
	mov		si,[mr_yfrac]
	shl		esi,16
	mov		si,[mr_xfrac]
	mov		di,[mr_dest]
	mov		ax,SEG planepics
	mov		ds,ax
	mov		ax,0a000h
	mov		es,ax

; eax		and mask
; ebx		scratch offset and pixel values
; ecx   	loop counter
; edx		packed x / y step values
; esi		packed x / y fractional values
; edi		write pointer
; ebp		toprow to bottomrow delta
; es:		screenseg
; ds:		pictures

	; *** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***
IFDEF GAMEVER_RESTORATION_AOG_100
	mov	ax,1111111111110b
ENDIF

@@pixelloop:
	shld	ebx,esi,22				; shift y units in
	shld	ebx,esi,7				; shift x units in and one extra bit
	; *** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***
IFDEF GAMEVER_RESTORATION_AOG_100
	and	bx,ax		; mask off extra top bits and 0 low bit
	add	esi,edx					; position += step
	mov   bx,[bx]  				; get two source pixel
	mov   [es:di+bp],bh     	; write floor pixel
ELSE
	and	bx,1111111111110b		; mask off extra top bits and 0 low bit
	add	esi,edx					; position += step
	mov   ax,[bx]  				; get two source pixel
	mov   [es:di+bp],ah     	; write floor pixel
ENDIF

	inc	di
	loop	@@pixelloop

	pop	ds
	pop	ebp
	pop	edi
	pop	esi

	retf

ENDP





;============================
;
; C_MapRow
;
;============================

PROC	C_MapRow
PUBLIC	C_MapRow
	push	esi
	push	edi
	push	ebp
	push 	ds

	mov     bp,[mr_rowofs]
	mov		cx,[mr_count]
	mov		dx,[mr_ystep]
	shl		edx,16
	mov		dx,[mr_xstep]
	mov		si,[mr_yfrac]
	shl		esi,16
	mov		si,[mr_xfrac]
	mov		di,[mr_dest]
	mov		ax,SEG planepics
	mov		ds,ax
	mov		ax,0a000h
	mov		es,ax

; eax		and mask
; ebx		scratch offset and pixel values
; ecx   	loop counter
; edx		packed x / y step values
; esi		packed x / y fractional values
; edi		write pointer
; ebp		toprow to bottomrow delta
; es:		screenseg
; ds:		pictures

	; *** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***
IFDEF GAMEVER_RESTORATION_AOG_100
	mov	ax,1111111111110b
ENDIF

@@pixelloop:
	shld	ebx,esi,22				; shift y units in
	shld	ebx,esi,7				; shift x units in and one extra bit
	; *** BLAKE STONE: ALIENS OF GOLD V1.0 RESTORATION ***
IFDEF GAMEVER_RESTORATION_AOG_100
	and	bx,ax		; mask off extra top bits and 0 low bit
	add	esi,edx					; position += step
	mov   bx,[bx]  				; get two source pixel
	mov   [es:di],bl     		; write ceiling pixel
ELSE
	and	bx,1111111111110b		; mask off extra top bits and 0 low bit
	add	esi,edx					; position += step
	mov   ax,[bx]  				; get two source pixel
	mov   [es:di],al     		; write ceiling pixel
ENDIF

	inc	di
	loop	@@pixelloop

	pop	ds
	pop	ebp
	pop	edi
	pop	esi

	retf

ENDP


END

