#include <sys/regdef.h>
	.abicalls
	.text
	.align 2
	.globl euclides
	.ent euclides

euclides:
	.frame	fp, 36, ra		# Se crea el Stack Frame
	subu	sp, sp, 36

	.cprestore 28			# Guarda gp en sp+28
	sw		ra, 32(sp)		# Se guardan los registros
	sw		fp, 24(sp)		# segun ABI
	sw		s0, 20(sp)
	move	fp, sp

	sw		a0, 36(fp)		# struct gcd* gcd
	sw		a1, 40(fp)		# size_t n
	sw		zero, 16(fp)	# size_t k = 0

	b		condicion_for

# Obtiene gcd[k].num_a y le aplica ABS
abs_num_a:
	lw		t1, 16(fp)		# t1 = k
	sll		t0, t1, 3		# t0 = t1 << 3 = k * 8
	sll		t1, t1, 2		# t1 = t1 << 2 = k * 4
	addu	t1, t1, t0		# t1 = t1 + t0 = 4*k + 8*k = 12*k

	lw		t0, 36(fp)		# t0 = gcd
	addu	s0, t0, t1		# s0 = t0 + t1 = gcd + 12*k = &(gcd[k])

	lw		t0, 0(s0)		# t0 = mem(s0) = *(&gcd[k]) = gcd[k].num_a
	
	# ABS(gcd[k].num_a)
	bgez	t0, abs_num_b	# if gcd[k].num_a >= 0 GOTO abs_num_b

	subu	t0, zero, t0	# t0 = -t0 = -gcd[k].num_a

# Obtiene gcd[k].num_b y le aplica ABS
abs_num_b:
	move	a0, t0			# Prepara el primer argumento de euclides_

	lw		t0, 4(s0)		# t0 = mem(s0+4) = *(&gcd[k] + 4) = gcd[k].num_b

	# ABS(gcd[k].num_b)
	bgez	t0, llamada_euclides_	# if gcd[k].num_b >= 0 GOTO llamada_euclides_

	subu	t0, zero, t0	# t0 = -t0 = -gcd[k].num_b

llamada_euclides_: # Llamada a euclides_ y ++k
	move	a1, t0			# Prepara el segundo argumento de euclides_

	jal		euclides_

	# Guarda el resultado en memoria
	sw		v0, 8(s0)		# gcd[k].gcd_ab = v0 

	# Incrementa k
	lw		t0, 16(fp)		# t0 = k
	addiu	t0, t0, 1		# k++
	sw		t0, 16(fp)		# Guarda k

condicion_for: # (k < n)
	lw		t1, 16(fp)		# t1 = k
	lw		t0, 40(fp)		# t0 = n
	sltu	t0, t1, t0		# t0 = (k < n) ? 1 : 0
	bne		t0, zero, abs_num_a	# if (t0 != 0) GOTO abs_num_a
								# if (k < n) GOTO abs_num_a

	# Termina euclides
	move	sp, fp			# Recupera los registros que se guardaron
	lw		ra, 32(sp)
	lw		fp, 24(sp)
	lw		s0, 20(sp)

	addiu	sp, sp, 36
	jr		ra				# Vuelve al caller

	.end euclides
	

	.align 2
	.ent euclides_
euclides_:
	.frame	fp, 20, ra		# Se crea el Stack Frame
	subu	sp, sp, 20

	.cprestore 16			# Se guardan los registros segun ABI
	sw		fp, 12(sp)		
	move	fp, sp


	sw		a0, 20(fp)		# Guarda los parametros (a, b) en memoria
	sw		a1, 24(fp)
	
	# r2 = MAX(a, b)
	move	t0, a1			# t0 = b
	move	t1, a0			# t1 = a
	slt		t2, t1, t0		# t2 = (t1 < t0) ? 1 : 0
							# t2 = (a < b) ? 1 : 0

	movz	t0, t1, t2		# if (t2 = 0) => t0 = t1
							# if (a >= b) => t0 = a
	sw		t0, 0(fp)		# mem(fp+0) = t0 (Guarda r2)


	# r1 = MIN(a, b)
	move	t0, a1			# t0 = b
	move	t1, a0			# t1 = a
	slt		t2, t0, t1		# t2 = (t0 < t1) ? 1 : 0
							# t2 = (b < a) ? 1 : 0

	movz	t0, t1, t2		# if (t2 = 0) => t0 = t1
							# si b >= a => t0 = a
	sw		t0, 4(fp)		# mem(fp+4) = t0 (Guarda r1)

while:
	lw		t1, 0(fp)		# t1 = r2
	lw		t0, 4(fp)		# t0 = r1

	# If ((r0 = r2 % r1) == 0)
	divu	t1, t0			# r2 / r1
	mfhi	t2				# t2 = r0 = r2 % r1
	sw		t2, 8(fp)		# mem(fp+8) = t2 (Guarda r0)
	beq		t2, zero, retorno_euclides_	# if (r0 == 0) GOTO retorno_euclides_ (break)

	sw		t0, 0(fp)		# r2 = r1
	sw		t2, 4(fp)		# r1 = r0
	b		while			# while(1)

retorno_euclides_:
	lw		v0, 4(fp)		# v0 = r1 (return r1)
	
	move	sp, fp			# Recupera los registros guardados
	lw		fp, 12(sp)
	addiu	sp, sp, 20
	jr		ra

	.end euclides_