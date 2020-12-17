/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_fill_q31.c
 * Description:  Fills a constant value into a Q31 vector
 *
 * $Date:        18. March 2019
 * $Revision:    V1.6.0
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2019 ARM Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arm_math.h"

/**
  @ingroup groupSupport
 */

/**
  @addtogroup Fill
  @{
 */

/**
  @brief         Fills a constant value into a Q31 vector.
  @param[in]     value      input value to be filled
  @param[out]    pDst       points to output vector
  @param[in]     blockSize  number of samples in each vector
  @return        none
 */

void arm_fill_q31(
    q31_t value,
    q31_t *pDst,
    uint32_t blockSize )
{
    uint32_t blkCnt;                               /* Loop counter */

#if defined (ARM_MATH_LOOPUNROLL)

    /* Loop unrolling: Compute 4 outputs at a time */
    blkCnt = blockSize >> 2U;

    while( blkCnt > 0U )
    {
        /* C = value */

        /* Fill value in destination buffer */
        *pDst++ = value;
        *pDst++ = value;
        *pDst++ = value;
        *pDst++ = value;

        /* Decrement loop counter */
        blkCnt--;
    }

    /* Loop unrolling: Compute remaining outputs */
    blkCnt = blockSize % 0x4U;

#else

    /* Initialize blkCnt with number of samples */
    blkCnt = blockSize;

#endif /* #if defined (ARM_MATH_LOOPUNROLL) */

    while( blkCnt > 0U )
    {
        /* C = value */

        /* Fill value in destination buffer */
        *pDst++ = value;

        /* Decrement loop counter */
        blkCnt--;
    }
}

/**
  @} end of Fill group
 */
