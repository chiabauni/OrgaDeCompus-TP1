#include <sys/regdef.h>

#define TAM_SF_EUC 	40
#define OFF_RA_EUC 	36
#define OFF_GP_EUC 	32
#define OFF_FP_EUC 	28
#define OFF_S0_EUC 	24
#define OFF_N 		44
#define OFF_GCD		40
#define OFF_K 		16

#define TAM_SF_EUC_	24
#define OFF_GP_EUC_	20
#define OFF_FP_EUC_	16
#define OFF_B 		28
#define OFF_A 		24
#define OFF_R0 		8
#define OFF_R1		4
#define OFF_R2 		0

	.abicalls
	.text
	.align 2
	.globl euclides
	.ent euclides

euclides:
	.frame	fp, TAM_SF_EUC, ra		# Se crea el Stack Frame
	subu	sp, sp, TAM_SF_EUC

	.cprestore OFF_GP_EUC			# Guarda gp en sp+OFF_GP_EUC
	sw		ra, OFF_RA_EUC(sp)		# Se guardan los registros
	sw		fp, OFF_FP_EUC(sp)		# segun ABI
	sw		s0, OFF_S0_EUC(sp)
	move	fp, sp

	sw		a0, OFF_GCD(fp)			# struct gcd* gcd
	sw		a1, OFF_N(fp)			# size_t n
	sw		zero, OFF_K(fp)			# size_t k = 0

	b		condicion_for

# Obtiene gcd[k].num_a y le aplica ABS
abs_num_a:
	lw		t1, OFF_K(fp)			# t1 = k
	sll		t0, t1, 3				# t0 = t1 << 3 = k * 8
	sll		t1, t1, 2				# t1 = t1 << 2 = k * 4
	addu	t1, t1, t0				# t1 = t1 + t0 = 4*k + 8*k = 12*k

	lw		t0, OFF_GCD(fp)			# t0 = gcd
	addu	s0, t0, t1				# s0 = t0 + t1 = gcd + 12*k = &(gcd[k])

	lw		t0, 0(s0)				# t0 = mem(s0) = *(&gcd[k]) = gcd[k].num_a

	# ABS(gcd[k].num_a)
	bgez	t0, abs_num_b			# if gcd[k].num_a >= 0 GOTO abs_num_b

	subu	t0, zero, t0			# t0 = -t0 = -gcd[k].num_a

# Obtiene gcd[k].num_b y le aplica ABS
abs_num_b:
	move	a0, t0					# Prepara el primer argumento de euclides_

	lw		t0, 4(s0)				# t0 = mem(s0+4) = *(&gcd[k] + 4) = gcd[k].num_b

	# ABS(gcd[k].num_b)
	bgez	t0, llamada_euclides_	# if gcd[k].num_b >= 0 GOTO llamada_euclides_

	subu	t0, zero, t0			# t0 = -t0 = -gcd[k].num_b

llamada_euclides_: # Llamada a euclides_ y ++k
	move	a1, t0					# Prepara el segundo argumento de euclides_

	jal		euclides_

	# Guarda el resultado en memoria
	sw		v0, 8(s0)				# gcd[k].gcd_ab = v0

	# Incrementa k
	lw		t0, OFF_K(fp)			# t0 = k
	addiu	t0, t0, 1				# k++
	sw		t0, OFF_K(fp)			# Guarda k

condicion_for: # (k < n)
	lw		t1, OFF_K(fp)			# t1 = k
	lw		t0, OFF_N(fp)			# t0 = n
	sltu	t0, t1, t0				# t0 = (k < n) ? 1 : 0
	bne		t0, zero, abs_num_a		# if (t0 != 0) GOTO abs_num_a
									# If (k < n) GOTO abs_num_a

	# Termina euclides
	move	sp, fp					# Recupera los registros que se guardaron
	lw		ra, OFF_RA_EUC(sp)
	lw		fp, OFF_FP_EUC(sp)
	lw		s0, OFF_S0_EUC(sp)

	addiu	sp, sp, TAM_SF_EUC
	jr		ra						# Vuelve al caller

	.end euclides


	.align 2
	.ent euclides_
euclides_:
	.frame	fp, TAM_SF_EUC_, ra		# Se crea el Stack Frame
	subu	sp, sp, TAM_SF_EUC_

	.cprestore OFF_GP_EUC_			# Se guardan los registros segun ABI
	sw		fp, OFF_FP_EUC_(sp)
	move	fp, sp


	sw		a0, OFF_A(fp)			# Guarda los parametros (a, b) en memoria
	sw		a1, OFF_B(fp)

	# r2 = MAX(a, b)
	move	t0, a1					# t0 = b
	move	t1, a0					# t1 = a
	slt		t2, t1, t0				# t2 = (t1 < t0) ? 1 : 0
									# t2 = (a < b) ? 1 : 0

	movz	t0, t1, t2				# if (t2 = 0) => t0 = t1
									# If (a >= b) => t0 = a
	sw		t0, OFF_R2(fp)			# mem(fp+OFF_R2) = t0 (Guarda r2)


	# r1 = MIN(a, b)
	move	t0, a1					# t0 = b
	move	t1, a0					# t1 = a
	slt		t2, t0, t1				# t2 = (t0 < t1) ? 1 : 0
									# t2 = (b < a) ? 1 : 0

	movz	t0, t1, t2				# if (t2 = 0) => t0 = t1
									# si b >= a => t0 = a
	sw		t0, OFF_R1(fp)			# mem(fp+OFF_R1) = t0 (Guarda r1)

while:
	lw		t1, OFF_R2(fp)			# t1 = r2
	lw		t0, OFF_R1(fp)			# t0 = r1

	# If ((r0 = r2 % r1) == 0)
	divu	t1, t0					# r2 / r1
	mfhi	t2						# t2 = r0 = r2 % r1
	sw		t2, OFF_R0(fp)			# mem(fp+OFF_R0) = t2 (Guarda r0)
	beq		t2, zero, retorno_euclides_	# if (r0 == 0) GOTO retorno_euclides_ (break)

	sw		t0, OFF_R2(fp)			# r2 = r1
	sw		t2, OFF_R1(fp)			# r1 = r0
	b		while					# while(1)

retorno_euclides_:
	lw		v0, OFF_R1(fp)			# v0 = r1 (return r1)

	move	sp, fp					# Recupera los registros guardados
	lw		fp, OFF_FP_EUC_(sp)
	addiu	sp, sp, TAM_SF_EUC_
	jr		ra

	.end euclides_
