/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This files contains process dump arm reg module. */

#include "dfx_regs.h"

#include <cstdio>
#include <cstdlib>
#include <securec.h>

#include "dfx_define.h"
#include "dfx_log.h"

namespace OHOS {
namespace HiviewDFX {
enum RegisterSeqNum {
    REG_ARM_R0 = 0,
    REG_ARM_R1,
    REG_ARM_R2,
    REG_ARM_R3,
    REG_ARM_R4,
    REG_ARM_R5,
    REG_ARM_R6,
    REG_ARM_R7,
    REG_ARM_R8,
    REG_ARM_R9,
    REG_ARM_R10,
    REG_ARM_R11,
    REG_ARM_R12,
    REG_ARM_R13,
    REG_ARM_R14,
    REG_ARM_R15
};

DfxRegsArm::DfxRegsArm(const ucontext_t& context)
{
    std::vector<uintptr_t> regs {};

    regs.push_back(uintptr_t(context.uc_mcontext.arm_r0));   // 0:r0
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r1));   // 1:r1
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r2));   // 2:r2
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r3));   // 3:r3
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r4));   // 4:r4
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r5));   // 5:r5
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r6));   // 6:r6
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r7));   // 7:r7
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r8));   // 8:r8
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r9));   // 9:r9
    regs.push_back(uintptr_t(context.uc_mcontext.arm_r10)); // 10:r10
    regs.push_back(uintptr_t(context.uc_mcontext.arm_fp));  // 11:fp
    regs.push_back(uintptr_t(context.uc_mcontext.arm_ip));  // 12:ip
    regs.push_back(uintptr_t(context.uc_mcontext.arm_sp));  // 13:sp
    regs.push_back(uintptr_t(context.uc_mcontext.arm_lr));  // 14:lr
    regs.push_back(uintptr_t(context.uc_mcontext.arm_pc));  // 15:pc

    SetRegs(regs);
    DfxLogDebug("fp:%08x ip:%08x sp:%08x lr:%08x pc:%08x \n", regs[REG_ARM_R11], regs[REG_ARM_R12],
        regs[REG_ARM_R13], regs[REG_ARM_R14], regs[REG_ARM_R15]);
}

std::string DfxRegsArm::PrintRegs() const
{
    std::string regString = "";
    char buf[REGS_PRINT_LEN_ARM] = {0};

    regString = regString + "Registers:\n";

    std::vector<uintptr_t> regs = GetRegsData();
    int ret = snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, \
        "r0:%08x r1:%08x r2:%08x r3:%08x\n", \
        regs[REG_ARM_R0], regs[REG_ARM_R1], regs[REG_ARM_R2], regs[REG_ARM_R3]);
    if (ret <= 0) {
        DfxLogError("%s :: snprintf_s failed, line: %d.", __func__, __LINE__);
    }

    ret = snprintf_s(buf + strlen(buf), sizeof(buf) - strlen(buf), sizeof(buf) - strlen(buf) - 1, \
        "r4:%08x r5:%08x r6:%08x r7:%08x\n", \
        regs[REG_ARM_R4], regs[REG_ARM_R5], regs[REG_ARM_R6], regs[REG_ARM_R7]);
    if (ret <= 0) {
        DfxLogError("%s :: snprintf_s failed, line: %d.", __func__, __LINE__);
    }

    ret = snprintf_s(buf + strlen(buf), sizeof(buf) - strlen(buf), sizeof(buf) - strlen(buf) - 1, \
        "r8:%08x r9:%08x r10:%08x\n", \
        regs[REG_ARM_R8], regs[REG_ARM_R9], regs[REG_ARM_R10]);
    if (ret <= 0) {
        DfxLogError("%s :: snprintf_s failed, line: %d.", __func__, __LINE__);
    }

    ret = snprintf_s(buf + strlen(buf), sizeof(buf) - strlen(buf), sizeof(buf) - strlen(buf) - 1, \
        "fp:%08x ip:%08x sp:%08x lr:%08x pc:%08x \n", \
        regs[REG_ARM_R11], regs[REG_ARM_R12], \
        regs[REG_ARM_R13], regs[REG_ARM_R14], regs[REG_ARM_R15]);
    if (ret <= 0) {
        DfxLogError("%s :: snprintf_s failed, line: %d.", __func__, __LINE__);
    }

    regString = regString + std::string(buf);
    return regString;
}
} // namespace HiviewDFX
} // namespace OHOS
