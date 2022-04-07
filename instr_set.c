/*********************************************************
 *                                                       *
 *  CS 21 Midterm Project                                *
 *                                                       *
 *  C simulator for MIPS                                 *
 *                                                       *
 *********************************************************/


#include "mips.h"

/*
 * Notes:
 * EXE_PC = currently executed PC
 * PC = value in the PC register
 * Set `branch = 1` when branching
 * Set `jump = 1` when jumping
 */

/* syscall */
void syscall(); // Implement syscall 1, 5 and 10

/* R-type instructions */
void add(uint32_t inst);
void addu(uint32_t inst);
void sub(uint32_t inst);
void subu(uint32_t inst);
void mult(uint32_t inst);
void div_r(uint32_t inst); // _r because div() is already in the stdlib
void and(uint32_t inst);
void or(uint32_t inst);
void nor(uint32_t inst);
void mfhi(uint32_t inst);
void mflo(uint32_t inst);
void slt(uint32_t inst);
void sltu(uint32_t inst);
void sll(uint32_t inst);
void slr(uint32_t inst); 
void jr(uint32_t inst);

/* I-type instructions */
void addi(uint32_t inst);
void addiu(uint32_t inst);
void ori(uint32_t inst);
void lui(uint32_t inst);
void slti(uint32_t inst);
void sltiu(uint32_t inst);
void beq(uint32_t inst);
void bne(uint32_t inst);
void sw(uint32_t inst);
void lw(uint32_t inst);

/* J-type instructions */
void j(uint32_t inst);
void jal(uint32_t inst);

/* additional functions implemented */


void process(uint32_t inst)
{
  /* insert your code here */
  /* Hint: the helper function INST(x,y) will get bits x:y from inst
   * eg: INST(31:30) to get the last two bits */

  if (inst == 12) { // syscall
    syscall();
    return;
  }

  int opcode = INST(31,26); // get last six bits for the opcode

  if (opcode == 0) {  // opcode = 0, R-type

    // printf("R-TYPE\n");

    int funct = INST(5,0);  // get first six bits for the funct

    // switch case r-type codes (16 types)
    switch (funct) {
      case 32:
        add(inst);
        break;
      case 33:
        addu(inst);
        break;
      case 34:
        sub(inst);
        break;
      case 35:
        subu(inst);
        break;
      case 24:
        mult(inst);
        break;
      case 26:
        div_r(inst);
        break;
      case 36:
        and(inst);
        break;
      case 37:
        or(inst);
        break;
      case 39:
        nor(inst);
        break;
      case 16:
        mfhi(inst);
        break;
      case 18:
        mflo(inst);
        break;
      case 42:
        slt(inst);
        break;
      case 43:
        sltu(inst);
        break;
      case 0:
        sll(inst);
        break;
      case 2:
        slr(inst);
        break;
      case 8:
        jr(inst);
        break;
    }
  }
  else { // I or J - TYPE
    switch (opcode) {
      case 8:
        addi(inst);
        break;

      case 9:
        addiu(inst);
        break;

      case 13:
        ori(inst);
        break;

      case 15:
        lui(inst);
        break;

      case 10:
        slti(inst);
        break;

      case 11:
        sltiu(inst);
        break;

      case 4:
        beq(inst);
        break;

      case 5:
        bne(inst);
        break;

      case 43:
        sw(inst);
        break;

      case 35:
        lw(inst);
        break;

      case 2:
        j(inst);
        break;

      case 3:
        jal(inst);
        break;

    }
  }
  
  
}

/* add additional functions for other instructions */

/* R-TYPE instructions */
void add(uint32_t inst) // R[rd] = R[rs] + R[rt] , placed int
{ // printf("add\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  int temp_rs = R[rs];
  int temp_rt = R[rt];

  // do operation
  R[rd] = R[rs] + R[rt];
  return;
}

void addu(uint32_t inst) // R[rd] = R[rs] + R[rt]
{ // printf("addu\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  // do operation
  R[rd] = R[rs] + R[rt];
}

void sub(uint32_t inst) //  R[rd] = R[rs] - R[rt] , placed int
{ // printf("sub\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  int temp_rs = R[rs];
  int temp_rt = R[rt];

  // do operation
  R[rd] = temp_rs - temp_rt;
}

void subu(uint32_t inst) //  R[rd] = R[rs] - R[rt] 
{ // printf("subu\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  // do operation
  R[rd] = R[rs] - R[rt];
}

void mult(uint32_t inst) // {Hi,Lo} = R[rs] * R[rt]
{ // printf("mult\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);

  // do operation
  HI = (R[rs] * R[rt]) - 4294967295; // keep only the upper 32 bits of the product
  LO = (R[rs] * R[rt]) & 4294967295; // keep only the lower 32 bits of the product
}

void div_r(uint32_t inst) // Lo=R[rs]/R[rt]; Hi=R[rs]%R[rt]
{ // printf("div_r\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);

  // do operation
  
  int temp_rs = R[rs];
  int temp_rt = R[rt];

  LO = temp_rs/temp_rt;
  HI = temp_rs%temp_rt;
}

void and(uint32_t inst)
{ // printf("and\n");
// get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  // do operation
  R[rd] = R[rs] & R[rt];
}

void or(uint32_t inst)
{ // printf("or\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  // do operation
  R[rd] = R[rs] | R[rt];
}

void nor(uint32_t inst)
{ // printf("nor\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  // do operation
  R[rd] = ~(R[rs] | R[rt]);
}

void mfhi(uint32_t inst) // R[rd] = Hi
{ // printf("mfhi\n");
  // get registers
  int rd = INST(15, 11);

  // do operation
  R[rd] = HI;
}

void mflo(uint32_t inst) // R[rd] = Lo
{ // printf("mflo\n");
  // get registers
  int rd = INST(15, 11);

  // do operation
  R[rd] = LO;
}

void slt(uint32_t inst) // R[rd] = (R[rs] < R[rt]) ? 1 : 0
{ // printf("slt\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  int temp_rs = R[rs];
  int temp_rt = R[rt];

  // do operation
  if (temp_rs < temp_rt) {
    R[rd] = 1;
  } else {
    R[rd] = 0;
  }
}

void sltu(uint32_t inst) // R[rd] = (R[rs] < R[rt]) ? 1 : 0
{ // printf("sltu\n");
  // get registers
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  // do operation
  if (R[rs] < R[rt]) {
    R[rd] = 1;
  } else {
    R[rd] = 0;
  }
}

void sll(uint32_t inst) // R[rd] = R[rt] << shamt
{ // printf("sll\n");
  // get registers
  int shamt = INST(10, 6);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  // do operation
  R[rd] = R[rt] << shamt;
}

void slr(uint32_t inst) // R[rd] = R[rt] >> shamt
{ // printf("slr\n");
  // get registers
  int shamt = INST(10, 6);
  int rt = INST(20, 16);
  int rd = INST(15, 11);

  // do operation
  R[rd] = R[rt] >> shamt;
}

void jr(uint32_t inst) // PC=R[rs]
{ // printf("jr\n");
  // get operands
  int rs = INST(25, 21);

  // do jump
  PC = R[rs];
  jump = 1;
}

/* I-TYPE instructions */

void addi(uint32_t inst) // R[rt] = R[rs] + SignExtImm
{ // printf("addi\n");
  // get operands & sign extend imm
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int imm = sign_extend(INST(15, 0), 16);

  // do operation
  R[rt] = R[rs] + imm;
  return;
}

void addiu(uint32_t inst) // R[rt] = R[rs] + SignExtImm
{ // printf("addiu\n"); kahit addiu, di naman talaga unsigned dahil 2s complement
  // get operands & sign extend imm
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int imm = sign_extend(INST(15, 0), 16);

  // do operation
  R[rt] = R[rs] + imm;
  return;
}

void ori(uint32_t inst) // R[rt] = R[rs] | ZeroExtImm
{ // printf("ori\n");
  // get operands & zero extend imm
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int imm = zeroExtend32(INST(15, 0));

  // do operation
  R[rt] = R[rs] | imm;
  return;
}

void lui(uint32_t inst) // R[rt] = {imm, 16’b0} 
{ // printf("lui\n");
  // get destination register & imm
  int rt = INST(20, 16);
  int imm = INST(15, 0);
  // shift imm 16 bits to left
  imm = imm << 16;
  // store in destination register
  R[rt] = imm;
}

void slti(uint32_t inst) // R[rt] = (R[rs] < SignExtImm)? 1 : 0
{ // printf("slti\n");
  // get operands & sign extend imm
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int imm = sign_extend(INST(15, 0), 16);

  // do operation

  // four possible cases
  int x = 0;
  if (INST_(15) == 1){ // imm is negative
    x += 1;
  }
  if (extract32_(R[rs], 31) == 1) { // R[rs] is negative
    x += 2;
  }

  switch (x) {
    case 0: // both positive
      if (R[rs] < imm) {
        R[rt] = 1;
      } else {
        R[rt] = 0;
      }
      break;
    case 1: // negative imm
      R[rt] = 0;
      break;
    case 2: // negative R[rs]
      R[rt] = 1;
      break;
    case 3: // both negative
      if (R[rs] < imm) {
        R[rt] = 1;
      } else {
        R[rt] = 0;
      }
      break;
  }


  /*
  if (R[rs] < imm) {
    R[rt] = 1;
  } else {
    R[rt] = 0;
  }
  */

  // printf("%d < %d = %d", R[rs], imm, R[rt]);

}

void sltiu(uint32_t inst) // R[rt] = (R[rs] < SignExtImm) ? 1 : 0 
{ // printf("sltiu\n");
  // get operands & sign extend imm
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int imm = sign_extend(INST(15, 0), 16);

  // do operation
  if (R[rs] < imm) {
    R[rt] = 1;
  } else {
    R[rt] = 0;
  }
}

void beq(uint32_t inst) // if(R[rs]==R[rt]) PC=PC+4+BranchAddr
{ // printf("beq\n");
  // get operands
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int imm = INST(15, 0);

  // check if need to branch
  if (R[rs] != R[rt]) { // don't branch
    return;
  } else {
    // get branch addr
    
    uint32_t temp = INST(15, 0) << 2;
    uint32_t branch_addr = sign_extend(extract32(temp, 17, 0), 14);

    PC = PC + branch_addr;

    // PC = PC + 4 + (imm * 4);
    branch = 1;
  }
  
}

void bne(uint32_t inst) // if(R[rs]!=R[rt]) PC=PC+4+BranchAddr; 14{immediate[15]}, immediate, 2’b0 
{ // printf("bne\n");
  // get operands
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int imm = INST(15, 0);

  // check if need to branch
  if (R[rs] == R[rt]) { // don't branch
    return;
  } else {
    // get branch addr
    uint32_t temp = INST(15, 0) << 2;
    uint32_t branch_addr = sign_extend(extract32(temp, 17, 0), 14);

    //uint32_t stored_PC = PC;
    
    PC = PC + branch_addr; // not PC + 4 
    branch = 1;
  }
}

void sw(uint32_t inst) //  M[R[rs]+SignExtImm] = R[rt]
{ // printf("sw\n");
  // get operands
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int imm = INST(15, 0);

  // do operation
  uint32_t addr = R[rs]+sign_extend(imm, 16);
  write_word(addr, R[rt]);
  // if ((addr >= 16777216) && (addr <= 71303164)) { // only touch this part of the memory
  //  write_word(addr, R[rt]);
  //}
}

void lw(uint32_t inst) // R[rt] = M[R[rs]+SignExtImm]
{ // printf("lw\n");
// get operands
  int rs = INST(25, 21);
  int rt = INST(20, 16);
  int imm = INST(15, 0);

  // do operation
  R[rt] = read_word(R[rs] + sign_extend(imm, 16));
}

/* J-TYPE instructions*/


void j(uint32_t inst) // PC = JumpAddr
{ // printf("j\n");

  uint32_t temp_PC = PC + 4;
  uint32_t jump_addr = 0;

  jump_addr = temp_PC & 4026531840; // PC+4[31:28]
  jump_addr = jump_addr + (INST(25, 0) << 2); // address and 'b00
  PC = jump_addr;

  jump = 1;
}


void jal(uint32_t inst) // R[31] = PC + 8; PC = JumpAddr
{ // printf("jal\n");
  
  uint32_t temp_PC = PC + 4;
  uint32_t jump_addr = 0;

  // link first before new PC!!! PC + 4 not PC + 8 (EXE_PC?)
  R[31] = PC + 4;

  jump_addr = temp_PC & 4026531840; // PC+4[31:28]
  jump_addr = jump_addr + (INST(25, 0) << 2); // address and 'b00
  PC = jump_addr;
  jump = 1;

  // link
  // R[31] = PC + 8;
}


/* SYSCALL */

// implement syscall 1, 5 and 10

void syscall() // syscall is 12 after checking in MARS
{ int sys_code = R[2];
  switch (sys_code) {
    case 1: // print int
      printf("%d", R[4]);
      break;
    case 5: // read int
      scanf("%d", &R[2]);
      break;
    case 10: // exit
      exit(0);
      break;
  }
}

/* additional functions implemented */

