#include <sys/regdef.h>
	.abicalls
	.text
	.align 2
	.globl euclides
	.ent euclides

euclides:
	# Rutinario
	.frame	fp, 48, ra	# Creando el stack frame
	subu	sp, sp, 48

	sw		ra, 44(sp)	# Guarda los registros para no perderlos
	sw		fp, 40(sp)
	sw		s0, 36(sp)
	move	fp, sp

	.cprestore 16			# Guardas gp en sp+16
	sw		a0, 48(fp)		# struct gcd* gcd
	sw		a1, 52(fp)		# size_t n
	sw		zero, 24(fp)	# size_t k = 0

	b		condicion_for

abs_num_a: # Obtiene gcd[k].num_a y le hace ABS
	lw		t1, 24(fp)		# t1 = k
	sll		t0, t1, 3		# t0 = t1 << 3 = k * 8
	sll		t1, t1, 2		# t1 = t1 << 2 = k * 4
	addu	t1, t1, t0		# t1 = t1 + t0 = 4*k + 8*k = 12*k

	lw		t0, 48(fp)		# t0 = &gcd
	addu	s0, t0, t1		# s0 = t0 + t1 = &gcd + 12*k = &(gcd[k])

	lw		t0, 0(s0)		# t0 = memoria(s0) = *(&gcd + 12*k) = gcd[k].num_a
	
	# ABS(gcd[k].num_a)
	bgez	t0, abs_num_b	# if t0 >= 0 GOTO abs_num_b

	subu	t0, zero, t0	# t0 = -t0

abs_num_b: # Obtiene gcd[k].num_b y hace ABS
	move	a0, t0			# Prepara el primer argumento de euclides_

	lw		t0, 4(s0)		# t0 = mem(t0+4) = *(&gcd + 12*k + 4) = gcd[k].num_b

	# ABS(gcd[k].num_b)
	bgez	t0, llamada_euclides_			# if t0 >= 0 GOTO llamada_euclides_

	subu	t0, zero, t0	# t0 = -t0

llamada_euclides_: # Llamada a euclides_ y ++k
	move	a1, t0			# Prepara el segundo argumento de euclides_

	jal		euclides_

	sw		v0, 8(s0)	# gcd[k].gcd_ab = v0 (Guardo el resultado en memoria)

	# Incrementa k
	lw		t0, 24(fp)	# t0 = k
	addiu	t0, t0, 1	# k++
	sw		t0, 24(fp)	# Guarda k

condicion_for: # (k < n)
	lw		t1, 24(fp)		# t1 = k
	lw		t0, 52(fp)		# t0 = n
	sltu	t0, t1, t0		# t0 = (t1 < t0) ? 1 : 0 (unsigned)
	bne		t0, zero, abs_num_a	# if (t0 != 0) GOTO abs_num_a

	# Termina euclides (Rutinario)
	move	sp, fp
	lw		ra, 44(sp)
	lw		fp, 40(sp)
	lw		s0, 36(sp)

	addiu	sp, sp, 48
	jr		ra

	.end euclides
	
	.align 2
	.ent euclides_
euclides_:
	# Rutinario
	.frame	fp, 32, ra		# Crea stack frame
	subu	sp, sp, 32

	sw		fp, 28(sp)
	move	fp, sp


	sw		a0, 32(fp)		# Guarda a y b en memoria
	sw		a1, 36(fp)
	
	# r2 = MAX(a, b)
	move	t0, a1			# t0 = b
	move	t1, a0			# t1 = a0 = a
	slt		t2, t1, t0		# t2 = (t1 < t0) ? 1 : 0 (signado)
							# t2 = (a < b) ? 1 : 0
							# t2 = 1 si a < b

							# si a >= b => t0 = a
	movz	t0, t1, t2		# if (t2 = 0) => t0 = t1
	sw		t0, 8(fp)		# mem(fp+8) = t0 (r2 = MAX(a, b))


	# r1 = MIN(a, b)
	move	t0, a1			# t0 = b
	move	t1, a0			# t1 = a
	slt		t2, t0, t1		# t2 = (t0 < t1) ? 1 : 0
							# t2 = (b < a) ? 1 : 0
							# t2 = 1 si b < a

							# si b >= a => t0 = a
	movz	t0, t1, t2		# if (t2 = 0) => t0 = t1
	sw		t0, 12(fp)		# mem(fp+12) = t0 (r1 = MIN(a, b))

while:
	lw		t1, 8(fp)		# t1 = r2
	lw		t0, 12(fp)		# t0 = r1

	# If ((r0 = r2 % r1) == 0)
	divu	t1, t0			# t1 / t0 === r2/r1
	mfhi	t2				# t2 = Resto === t2 = r0 = r2 % r1
	sw		t2, 16(fp)		# mem(fp+16) = v0 === r0 = r2 % r1
	beq		t2, zero, retorno_euclides_	# if (t2 == 0) GOTO retorno_euclides_ (break)

	sw		t0, 8(fp)		# r2 = t0 = r1
	sw		t2, 12(fp)		# r1 = t2 = r0
	b		while			# while(1)

retorno_euclides_: # Return de euclides_
	lw		v0, 12(fp)		# v0 = r1
	
	# Rutinario
	move	sp, fp
	lw		fp, 28(sp)
	addiu	sp, sp, 32
	jr		ra

	.end euclides_