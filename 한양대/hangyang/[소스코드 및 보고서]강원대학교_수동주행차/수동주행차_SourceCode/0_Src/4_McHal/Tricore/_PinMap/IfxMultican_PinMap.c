/**
 * \file IfxMultican_PinMap.c
 * \brief MULTICAN I/O map
 * \ingroup IfxLld_Multican
 *
 * \version iLLD_1_0_0_11_0
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#include "IfxMultican_PinMap.h"

IfxMultican_Rxd_In IfxMultican1_RXD0A_P10_5_IN = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P10, 5}, Ifx_RxSel_a};
IfxMultican_Rxd_In IfxMultican1_RXD0B_P13_1_IN = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P13, 1}, Ifx_RxSel_b};
IfxMultican_Rxd_In IfxMultican1_RXD0F_P02_6_IN = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P02, 6}, Ifx_RxSel_f};
IfxMultican_Rxd_In IfxMultican1_RXD0G_P00_5_IN = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P00, 5}, Ifx_RxSel_g};
IfxMultican_Rxd_In IfxMultican1_RXD0H_P33_6_IN = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P33, 6}, Ifx_RxSel_h};
IfxMultican_Rxd_In IfxMultican1_RXD1A_P00_3_IN = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P00, 3}, Ifx_RxSel_a};
IfxMultican_Rxd_In IfxMultican1_RXD1B_P13_3_IN = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P13, 3}, Ifx_RxSel_b};
IfxMultican_Rxd_In IfxMultican1_RXD1C_P20_0_IN = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P20, 0}, Ifx_RxSel_c};
IfxMultican_Rxd_In IfxMultican1_RXD1F_P02_7_IN = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P02, 7}, Ifx_RxSel_f};
IfxMultican_Rxd_In IfxMultican1_RXD1G_P00_6_IN = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P00, 6}, Ifx_RxSel_g};
IfxMultican_Rxd_In IfxMultican1_RXD1H_P20_12_IN = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P20,12}, Ifx_RxSel_h};
IfxMultican_Rxd_In IfxMultican1_RXD2A_P00_3_IN = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P00, 3}, Ifx_RxSel_a};
IfxMultican_Rxd_In IfxMultican1_RXD2C_P20_0_IN = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P20, 0}, Ifx_RxSel_c};
IfxMultican_Rxd_In IfxMultican1_RXD2D_P11_10_IN = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P11,10}, Ifx_RxSel_d};
IfxMultican_Rxd_In IfxMultican1_RXD2E_P20_9_IN = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P20, 9}, Ifx_RxSel_e};
IfxMultican_Rxd_In IfxMultican1_RXD2G_P00_8_IN = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P00, 8}, Ifx_RxSel_g};
IfxMultican_Rxd_In IfxMultican1_RXD2H_P20_13_IN = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P20,13}, Ifx_RxSel_h};
IfxMultican_Rxd_In IfxMultican_RXD0A_P02_1_IN = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P02, 1}, Ifx_RxSel_a};
IfxMultican_Rxd_In IfxMultican_RXD0B_P20_7_IN = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P20, 7}, Ifx_RxSel_b};
IfxMultican_Rxd_In IfxMultican_RXD0D_P02_4_IN = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P02, 4}, Ifx_RxSel_d};
IfxMultican_Rxd_In IfxMultican_RXD0E_P33_7_IN = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P33, 7}, Ifx_RxSel_e};
IfxMultican_Rxd_In IfxMultican_RXD0G_P34_2_IN = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P34, 2}, Ifx_RxSel_g};
IfxMultican_Rxd_In IfxMultican_RXD1A_P15_3_IN = {&MODULE_CAN, IfxMultican_NodeId_1, {&MODULE_P15, 3}, Ifx_RxSel_a};
IfxMultican_Rxd_In IfxMultican_RXD1B_P14_1_IN = {&MODULE_CAN, IfxMultican_NodeId_1, {&MODULE_P14, 1}, Ifx_RxSel_b};
IfxMultican_Rxd_In IfxMultican_RXD1D_P00_1_IN = {&MODULE_CAN, IfxMultican_NodeId_1, {&MODULE_P00, 1}, Ifx_RxSel_d};
IfxMultican_Rxd_In IfxMultican_RXD2A_P15_1_IN = {&MODULE_CAN, IfxMultican_NodeId_2, {&MODULE_P15, 1}, Ifx_RxSel_a};
IfxMultican_Rxd_In IfxMultican_RXD2B_P02_3_IN = {&MODULE_CAN, IfxMultican_NodeId_2, {&MODULE_P02, 3}, Ifx_RxSel_b};
IfxMultican_Rxd_In IfxMultican_RXD2D_P14_8_IN = {&MODULE_CAN, IfxMultican_NodeId_2, {&MODULE_P14, 8}, Ifx_RxSel_d};
IfxMultican_Rxd_In IfxMultican_RXD2E_P10_2_IN = {&MODULE_CAN, IfxMultican_NodeId_2, {&MODULE_P10, 2}, Ifx_RxSel_e};
IfxMultican_Txd_Out IfxMultican1_TXD0_P00_4_OUT = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P00, 4}, IfxPort_OutputIdx_alt3};
IfxMultican_Txd_Out IfxMultican1_TXD0_P02_4_OUT = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P02, 4}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican1_TXD0_P10_6_OUT = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P10, 6}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican1_TXD0_P13_0_OUT = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P13, 0}, IfxPort_OutputIdx_alt7};
IfxMultican_Txd_Out IfxMultican1_TXD0_P33_7_OUT = {&MODULE_CAN1, IfxMultican_NodeId_0, {&MODULE_P33, 7}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican1_TXD1_P00_7_OUT = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P00, 7}, IfxPort_OutputIdx_alt2};
IfxMultican_Txd_Out IfxMultican1_TXD1_P02_5_OUT = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P02, 5}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican1_TXD1_P13_2_OUT = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P13, 2}, IfxPort_OutputIdx_alt2};
IfxMultican_Txd_Out IfxMultican1_TXD1_P20_11_OUT = {&MODULE_CAN1, IfxMultican_NodeId_1, {&MODULE_P20,11}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican1_TXD2_P00_2_OUT = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P00, 2}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican1_TXD2_P00_9_OUT = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P00, 9}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican1_TXD2_P20_10_OUT = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P20,10}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican1_TXD2_P20_14_OUT = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P20,14}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican1_TXD2_P20_3_OUT = {&MODULE_CAN1, IfxMultican_NodeId_2, {&MODULE_P20, 3}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican_TXD0_P02_0_OUT = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P02, 0}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican_TXD0_P02_5_OUT = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P02, 5}, IfxPort_OutputIdx_alt2};
IfxMultican_Txd_Out IfxMultican_TXD0_P20_8_OUT = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P20, 8}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican_TXD0_P33_8_OUT = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P33, 8}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican_TXD0_P34_1_OUT = {&MODULE_CAN, IfxMultican_NodeId_0, {&MODULE_P34, 1}, IfxPort_OutputIdx_alt4};
IfxMultican_Txd_Out IfxMultican_TXD1_P00_0_OUT = {&MODULE_CAN, IfxMultican_NodeId_1, {&MODULE_P00, 0}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican_TXD1_P14_0_OUT = {&MODULE_CAN, IfxMultican_NodeId_1, {&MODULE_P14, 0}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican_TXD1_P15_2_OUT = {&MODULE_CAN, IfxMultican_NodeId_1, {&MODULE_P15, 2}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican_TXD2_P02_2_OUT = {&MODULE_CAN, IfxMultican_NodeId_2, {&MODULE_P02, 2}, IfxPort_OutputIdx_alt5};
IfxMultican_Txd_Out IfxMultican_TXD2_P10_3_OUT = {&MODULE_CAN, IfxMultican_NodeId_2, {&MODULE_P10, 3}, IfxPort_OutputIdx_alt6};
IfxMultican_Txd_Out IfxMultican_TXD2_P15_0_OUT = {&MODULE_CAN, IfxMultican_NodeId_2, {&MODULE_P15, 0}, IfxPort_OutputIdx_alt5};


const IfxMultican_Rxd_In *IfxMultican_Rxd_In_pinTable[IFXMULTICAN_PINMAP_NUM_MODULES][IFXMULTICAN_PINMAP_NUM_NODES][IFXMULTICAN_PINMAP_RXD_IN_NUM_ITEMS] = {
    {
        {
            &IfxMultican_RXD0A_P02_1_IN,
            &IfxMultican_RXD0B_P20_7_IN,
            NULL_PTR,
            &IfxMultican_RXD0D_P02_4_IN,
            &IfxMultican_RXD0E_P33_7_IN,
            NULL_PTR,
            &IfxMultican_RXD0G_P34_2_IN,
            NULL_PTR
        },
        {
            &IfxMultican_RXD1A_P15_3_IN,
            &IfxMultican_RXD1B_P14_1_IN,
            NULL_PTR,
            &IfxMultican_RXD1D_P00_1_IN,
            NULL_PTR,
            NULL_PTR,
            NULL_PTR,
            NULL_PTR
        },
        {
            &IfxMultican_RXD2A_P15_1_IN,
            &IfxMultican_RXD2B_P02_3_IN,
            NULL_PTR,
            &IfxMultican_RXD2D_P14_8_IN,
            &IfxMultican_RXD2E_P10_2_IN,
            NULL_PTR,
            NULL_PTR,
            NULL_PTR
        }
    },
    {
        {
            &IfxMultican1_RXD0A_P10_5_IN,
            &IfxMultican1_RXD0B_P13_1_IN,
            NULL_PTR,
            NULL_PTR,
            NULL_PTR,
            &IfxMultican1_RXD0F_P02_6_IN,
            &IfxMultican1_RXD0G_P00_5_IN,
            &IfxMultican1_RXD0H_P33_6_IN
        },
        {
            &IfxMultican1_RXD1A_P00_3_IN,
            &IfxMultican1_RXD1B_P13_3_IN,
            &IfxMultican1_RXD1C_P20_0_IN,
            NULL_PTR,
            NULL_PTR,
            &IfxMultican1_RXD1F_P02_7_IN,
            &IfxMultican1_RXD1G_P00_6_IN,
            &IfxMultican1_RXD1H_P20_12_IN
        },
        {
            &IfxMultican1_RXD2A_P00_3_IN,
            NULL_PTR,
            &IfxMultican1_RXD2C_P20_0_IN,
            &IfxMultican1_RXD2D_P11_10_IN,
            &IfxMultican1_RXD2E_P20_9_IN,
            NULL_PTR,
            &IfxMultican1_RXD2G_P00_8_IN,
            &IfxMultican1_RXD2H_P20_13_IN
        }
    }
};

const IfxMultican_Txd_Out *IfxMultican_Txd_Out_pinTable[IFXMULTICAN_PINMAP_NUM_MODULES][IFXMULTICAN_PINMAP_NUM_NODES][IFXMULTICAN_PINMAP_TXD_OUT_NUM_ITEMS] = {
    {
        {
            &IfxMultican_TXD0_P02_0_OUT,
            &IfxMultican_TXD0_P02_5_OUT,
            &IfxMultican_TXD0_P34_1_OUT,
            &IfxMultican_TXD0_P33_8_OUT,
            &IfxMultican_TXD0_P20_8_OUT
        },
        {
            &IfxMultican_TXD1_P15_2_OUT,
            &IfxMultican_TXD1_P14_0_OUT,
            &IfxMultican_TXD1_P00_0_OUT,
            NULL_PTR,
            NULL_PTR
        },
        {
            &IfxMultican_TXD2_P15_0_OUT,
            &IfxMultican_TXD2_P10_3_OUT,
            &IfxMultican_TXD2_P02_2_OUT,
            NULL_PTR,
            NULL_PTR
        }
    },
    {
        {
            &IfxMultican1_TXD0_P13_0_OUT,
            &IfxMultican1_TXD0_P10_6_OUT,
            &IfxMultican1_TXD0_P02_4_OUT,
            &IfxMultican1_TXD0_P00_4_OUT,
            &IfxMultican1_TXD0_P33_7_OUT
        },
        {
            &IfxMultican1_TXD1_P13_2_OUT,
            &IfxMultican1_TXD1_P02_5_OUT,
            &IfxMultican1_TXD1_P00_7_OUT,
            &IfxMultican1_TXD1_P20_11_OUT,
            NULL_PTR
        },
        {
            &IfxMultican1_TXD2_P00_2_OUT,
            &IfxMultican1_TXD2_P00_9_OUT,
            &IfxMultican1_TXD2_P20_3_OUT,
            &IfxMultican1_TXD2_P20_10_OUT,
            &IfxMultican1_TXD2_P20_14_OUT
        }
    }
};
