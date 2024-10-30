/**
 @file cdsl_types.h
 @author Greg Lee
 @version 2.0.0
 @brief: "include file for data structure type codes"

 @date: "Tue Sep 24 16:44:11 PDT 2019 @30 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee

 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0):

 1. Permission is hereby granted to use, copy, modify and/or
    distribute this package, provided that:
    #define  copyright notices are retained unchanged,
    #define  any distribution of this package, whether modified or not,
         includes this license text.
 2. Permission is hereby also granted to distribute binary programs
    which depend on this package. If the binary program depends on a
    modified version of this package, you are encouraged to publicly
    release the modified version of this package.

 THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHORS BE LIABLE TO ANY PARTY FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS PACKAGE.

 @section Description

 Defines for basic types.

*/

#ifndef CDSL_TYPES_H
#define CDSL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/**
   C Data Structure Type Codes
*/

// Protocols


#define P_BASIC_TYPE             0x5A000100
#define P_INDEXABLE_TYPE         0x5A000200
#define P_ITERABLE_TYPE          0x5A000300
#define P_ITERABLE_KV_TYPE       0x5A000301
#define P_DITERABLE_TYPE         0x5A000302
#define P_DITERABLE_KV_TYPE      0x5A000303
#define P_SEARCHER_TYPE          0x5A000400
#define P_SORTER_TYPE            0x5A000401
#define P_CLH_COMMAND_TYPE       0x5A010500
#define P_CLH_OPTION_TYPE        0x5A010501

// Lists

#define ALIST_TYPE               0xA5000100
#define SLIST_TYPE               0xA5000101
#define DLIST_TYPE               0xA5000102
   
// Trees

#define BSTREE_TYPE              0xA5000200
#define BSTREE_KV_TYPE           0xA5000201
#define RBTREE_TYPE              0xA5000202
#define RBTREE_KV_TYPE           0xA5000203
#define AVLTREE_TYPE             0xA5000204
#define AVLTREE_KV_TYPE          0xA5000205
#define BTREE_TYPE               0xA5000210
#define TRIE_TYPE                0xA5000220
#define HEAP_TYPE                0xA5000230
#define HEAP_KV_TYPE             0xA5000231
   
// Hash Set, Table

#define HSET_TYPE                0xA5000300
#define HTABLE_TYPE              0xA5000301
   
// Sequence

#define SEQUENCE_TYPE            0xA5000400
#define CIRCULAR_ARRAY_TYPE      0xA5000401
   
// Strings

#define STRING_TYPE              0xA5000500
#define STRING_UTF8_TYPE         0xA5000501
#define CABLE_TYPE               0xA5000510
#define CABLE_UTF8_TYPE          0xA5000511
   
// Graphs

#define DGRAPH_TYPE              0xA5000600
#define DGRAPH_EDGE_TYPE         0xA5000601
#define DGRAPH_VERTEX_TYPE       0xA5000602
#define UGRAPH_TYPE              0xA5000610
#define UGRAPH_EDGE_TYPE         0xA5000611
#define UGRAPH_VERTEX_TYPE       0xA5000612
   
// Miscellaneous

#define CONFIGURATION_TYPE       0xA5000700
#define BINARY_FILE_TYPE         0xA5000701
#define DIRECTORY_TYPE           0xA5000702
#define INPUT_FILE_READER_TYPE   0xA5000703
#define RAW_BUFFER_TYPE          0xA5000704
#define TUPLE_TYPE               0xA5000705
#define AGENT_TYPE               0xA5000704
#define TIMED_AGENT_EXECUTOR_TYPE   0xA5000705
   
// Deques

#define CIRCULAR_BUFFER_TYPE     0xA5000800
#define DEQUE_TYPE               0xA5000801
#define PQUEUE_TYPE              0xA5000802
#define QUEUE_TYPE               0xA5000803
#define STACK_TYPE               0xA5000804
   
// Sorters

#define BSORTER_TYPE             0xA5000900
#define HSORTER_TYPE             0xA5000901
#define ISORTER_TYPE             0xA5000902
#define MSORTER_TYPE             0xA5000903
#define QSORTER_TYPE             0xA5000904
#define SELSORTER_TYPE           0xA5000905
#define SSORTER_TYPE             0xA5000906
   
// Searchers

#define BSEARCHER_TYPE           0xA5000A00
#define LSEARCHER_TYPE           0xA5000A01

// Math
#define MATVEC_TYPE              0xA5000B00
#define QUATERNION_TYPE          0xA5000B01
#define RNG_ISAAC_TYPE           0xA5000B02
#define RNG_ISAAC_GAUSSIAN_TYPE  0xA5000B03
#define FFT_TYPE                 0xA5000B04
#define SVD_TYPE                 0xA5000B05
#define LSQLINE_TYPE             0xA5000B06

// Date
#define DATE_TIME_TYPE           0xA5000C00
#define DATE_TIME_DURATION_TYPE  0xA5000C01
#define DATE_TIME_FORMATTER_PARSER_TYPE   0xA5000C02
#define DATE_TIME_DURATION_FORMATTER_PARSER_TYPE   0xA5000C03
#define TEMPORENC_TYPE           0xA5000C04

// Org_Mode
#define ORG_MODE_ITEM_TYPE       0xA5000D00
#define ORG_MODE_ITEM_FORMATTER_PARSER_TYPE  0xA5000D01
#define ORG_MODE_FILE_READER_TYPE   0xA5000D02

// Query
#define QUERY_TYPE               0xA5000E00

// Command_Line_Handler
#define COMMAND_LINE_HANDLER_TYPE   0xA5000F00

// Fuzzy_Logic
#define FL_VARIABLE_TYPE                  0xA5001000
#define FL_MF_POINT_TYPE                  0xA5001001
#define FL_LTERM_TYPE                     0xA5001002
#define FL_MEMBERSHIP_FUNCTION_TYPE       0xA5001003
#define FL_RULE_TYPE                      0xA5001004
#define FL_RULE_CONDITION_EVALUATOR_TYPE  0xA5001005
#define FL_RULE_BLOCK_TYPE                0xA5001006
#define FL_FUNCTION_BLOCK_TYPE            0xA5001007
#define FCL_PARSER_TYPE                   0xA5001008

// SOA
#define SOA_AGENT_TYPE                    0xA5001101
#define SOA_COMPONENT_TYPE                0xA5001102
#define SOA_COMPONENT_WITH_PRIORITY_TYPE  0xA5001103
#define SOA_COMPONENT_WITH_PRIORITY_CAPABILITY_TYPE   0xA5001104
#define SOA_PATH_TYPE                     0xA5001105
#define SOA_PATH_WITH_AGENTS_TYPE         0xA5001106
#define SOA_PATH_WITH_COMPONENTS_TYPE     0xA5001107
#define SOA_PATH_WITH_COMPONENTS_WITH_PRIORITY_TYPE   0xA5001108
#define SOA_PATHS_WITH_AGENTS_TYPE        0xA5001109
#define SOA_PATHS_WITH_COMPONENTS_TYPE    0xA500110A
#define SOA_PATHS_WITH_COMPONENTS_WITH_PRIORITY_TYPE  0xA500110B
#define SOA_LOCAL_STORE_TYPE              0xA500110C
#define SOA_TIMER_TYPE                    0xA500110D
#define SOA_MESSAGE_CONFABULATOR_TYPE     0xA500110E
#define SOA_NTDV_TYPE                     0xA500110F
#define SOA_NODE_TYPE                     0xA5001110
#define SOA_PDICT_INFO_TYPE               0xA5001111
#define SOA_TIME_TYPE                     0xA5001112
#define SOA_HEARTBEAT_MONITOR_TYPE        0xA5001113
#define SOA_JOB_MONITOR_TYPE              0xA5001114
#define SOA_SERVICE_MONITOR_TYPE          0xA5001115
#define SOA_SNSTP_TYPE                    0xA5001116
#define SOA_COMPONENT_UTILITY_TYPE        0xA5001117
#define SOA_DATA_STORE_TYPE               0xA5001118
#define SOA_NODE_ITERATOR_TYPE            0xA5001119
#define SOA_WORKER_TYPE                   0xA500111A
#define SOA_BASE_TYPE                     0xA500111B

// Trading
#define TICK_FILE_TYPE        0xA5001200
#define BAR_FILE_TYPE         0xA5001201
#define BAR_DATA_TYPE         0xA5001202
#define BARS_DATA_TYPE        0xA5001203
#define BAR_UPDATE_AGENT_TYPE 0xA5001204
#define TICK_ACCESSOR_TYPE    0xA5001205
#define PLOT_TYPE             0xA5001210
#define GGA_TYPE              0xA5001211
#define GGNF_TYPE             0xA5001212
#define EMA_TYPE              0xA5001213
#define EMAEMA_TYPE           0xA5001214
#define APZ_TYPE              0xA5001215
#define MAXIMIN_TYPE          0xA5001220
#define TP3_APZ_TYPE          0xA5001221
#define ALGO_ESF_TYPE         0xA5001230
#define TRADE_TYPE         0xA5001240

#ifdef __cplusplus
}
#endif

#endif /* CDSL_TYPES_H */

/* End of file */
