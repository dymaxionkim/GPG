/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2006. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  HELP_PANEL                      1
#define  HELP_PANEL_HELP_TEXT            2
#define  HELP_PANEL_HELP_OK              3       /* callback function: Callback_Help_Ok */

#define  PANEL                           2
#define  PANEL_N                         2       /* callback function: Callback_N */
#define  PANEL_X                         3       /* callback function: Callback_X */
#define  PANEL_PHI                       4       /* callback function: Callback_Phi */
#define  PANEL_R_C                       5       /* callback function: Callback_R_c */
#define  PANEL_DEDENDUM                  6       /* callback function: Callback_Dedendum */
#define  PANEL_ADDENDUM                  7       /* callback function: Callback_Addendum */
#define  PANEL_M                         8       /* callback function: Callback_M */
#define  PANEL_RESOLUTION_F              9       /* callback function: Callback_Resolution_F */
#define  PANEL_RESOLUTION                10      /* callback function: Callback_Resolution */
#define  PANEL_COMMANDBUTTON_SAVE_I      11      /* callback function: Callback_Save_i */
#define  PANEL_SPLITTER_2                12
#define  PANEL_SPLITTER                  13
#define  PANEL_DECORATION                14
#define  PANEL_COMMANDBUTTON_GEN         15      /* callback function: Callback_Gen */
#define  PANEL_COMMANDBUTTON_SAVE_O      16      /* callback function: Callback_Save_o */
#define  PANEL_COMMANDBUTTON_LOAD_I      17      /* callback function: Callback_Load_i */
#define  PANEL_PICTURE                   18
#define  PANEL_GRAPH                     19
#define  PANEL_COMMANDBUTTON_HELP        20      /* callback function: Callback_Help */
#define  PANEL_COMMANDBUTTON_ABOUT       21      /* callback function: Callback_About */
#define  PANEL_COMMANDBUTTON_QUIT        22      /* callback function: Callback_Quit */
#define  PANEL_INPUT_METHOD              23      /* callback function: Callback_Input_Method */
#define  PANEL_TEXTMSG_2                 24
#define  PANEL_TEXTMSG_3                 25
#define  PANEL_TEXTMSG_4                 26
#define  PANEL_TEXTMSG_5                 27
#define  PANEL_TEXTMSG_6                 28
#define  PANEL_TEXTMSG_7                 29
#define  PANEL_TEXTMSG_8                 30


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK Callback_About(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Addendum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Dedendum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Gen(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Help(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Help_Ok(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Input_Method(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Load_i(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_M(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_N(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Phi(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_R_c(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Resolution(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Resolution_F(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Save_i(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_Save_o(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Callback_X(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
