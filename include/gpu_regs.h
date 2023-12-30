#ifndef GUARD_GPU_REGS_H
#define GUARD_GPU_REGS_H

void SetGpuReg(u8 regOffset, u16 value);
void SetGpuRegBits(u8 regOffset, u16 mask);
#endif // GUARD_GPU_REGS_H