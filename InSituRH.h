/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2005. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  ASYMTIME                        1
#define  ASYMTIME_GRAPH                  2
#define  ASYMTIME_COMMANDBUTTON_4        3       /* callback function: BacktoPreWin */
#define  ASYMTIME_TAATIME                4       /* callback function: DisplayTAACurve */
#define  ASYMTIME_RTIME                  5       /* callback function: DisplayRCurve */
#define  ASYMTIME_COMMANDBUTTON          6       /* callback function: DisplayRHCurve */
#define  ASYMTIME_LEGEND                 7
#define  ASYMTIME_YMAX                   8
#define  ASYMTIME_YMIN                   9
#define  ASYMTIME_ASYMREDRAW             10      /* callback function: ASYMReDraw */
#define  ASYMTIME_TAADIFF                11      /* callback function: DisplayDiffCurve */
#define  ASYMTIME_TEXTMSG                12
#define  ASYMTIME_TEXTMSG_2              13
#define  ASYMTIME_TEXTMSG_3              14
#define  ASYMTIME_TEXTMSG_4              15
#define  ASYMTIME_TEXTMSG_5              16
#define  ASYMTIME_TEXTMSG_6              17
#define  ASYMTIME_TEXTMSG_7              18
#define  ASYMTIME_TEXTMSG_8              19
#define  ASYMTIME_TEXTMSG_9              20
#define  ASYMTIME_TEXTMSG_10             21
#define  ASYMTIME_TEXTMSG_13             22
#define  ASYMTIME_TEXTMSG_14             23
#define  ASYMTIME_TEXTMSG_16             24
#define  ASYMTIME_TEXTMSG_11             25
#define  ASYMTIME_TEXTMSG_12             26
#define  ASYMTIME_TEXTMSG_15             27

#define  DSPTIME                         2
#define  DSPTIME_STRESSRMINS             2
#define  DSPTIME_STRESSRHOURS            3
#define  DSPTIME_STRESSEMINS             4
#define  DSPTIME_STRESSEHOURS            5
#define  DSPTIME_STRESSRDAYS             6
#define  DSPTIME_STRESSEDAYS             7
#define  DSPTIME_TOTALRMINS              8
#define  DSPTIME_TOTALRHOURS             9
#define  DSPTIME_TOTALEMINS              10
#define  DSPTIME_TOTALEHOURS             11
#define  DSPTIME_TOTALRDAYS              12
#define  DSPTIME_TOTALEDAYS              13
#define  DSPTIME_COMMANDBUTTON           14      /* callback function: BacktoPreWin */
#define  DSPTIME_TEXTMSG_7               15
#define  DSPTIME_TEXTMSG_8               16
#define  DSPTIME_TEXTMSG_9               17
#define  DSPTIME_TEXTMSG_10              18

#define  LSETTING                        3
#define  LSETTING_NAME                   2
#define  LSETTING_SELECTED               3       /* callback function: DeleteSelectedMeasurement */
#define  LSETTING_MEASUREMENTLIST        4       /* callback function: SelectTheMeasurement */
#define  LSETTING_COMMANDBUTTON_2        5       /* callback function: BacktoPreWin */
#define  LSETTING_COMMANDBUTTON          6       /* callback function: L_Save */
#define  LSETTING_INFINITE               7       /* callback function: CheckInfinite */
#define  LSETTING_LOOPS                  8

#define  MAINMENU                        4
#define  MAINMENU_NAME                   2
#define  MAINMENU_ROWNAME                3       /* callback function: CheckRowNum */
#define  MAINMENU_STARTDEVICE            4       /* callback function: AssignDeviceName */
#define  MAINMENU_COMMANDBUTTON_7        5       /* callback function: DoTesting */
#define  MAINMENU_CH1                    6
#define  MAINMENU_CH2                    7
#define  MAINMENU_CH3                    8
#define  MAINMENU_CH4                    9
#define  MAINMENU_CH5                    10
#define  MAINMENU_CH6                    11
#define  MAINMENU_CH7                    12
#define  MAINMENU_CH8                    13
#define  MAINMENU_CH9                    14
#define  MAINMENU_CH10                   15
#define  MAINMENU_CH11                   16
#define  MAINMENU_CH12                   17
#define  MAINMENU_CH13                   18
#define  MAINMENU_CH14                   19
#define  MAINMENU_CH15                   20
#define  MAINMENU_CH16                   21
#define  MAINMENU_MEASUREMENTLIST        22      /* callback function: SelectTheMeasurement */
#define  MAINMENU_SELECTED               23      /* callback function: DeleteSelectedMeasurement */
#define  MAINMENU_SETUP                  24      /* callback function: Measurement_Setup */
#define  MAINMENU_COMMANDBUTTON_6        25      /* callback function: ShutDown */
#define  MAINMENU_RTIME                  26      /* callback function: DisplayRCurve */
#define  MAINMENU_TAATIME                27      /* callback function: DisplayTAACurve */
#define  MAINMENU_ASYMTIME               28      /* callback function: DisplayASYMCurve */
#define  MAINMENU_TAADIFF                29      /* callback function: DisplayDiffCurve */
#define  MAINMENU_COMMANDBUTTON_4        30      /* callback function: DisplayRHCurve */
#define  MAINMENU_ASYMFAIL               31
#define  MAINMENU_TAAFAIL                32
#define  MAINMENU_RFAIL                  33
#define  MAINMENU_TOTALMINS              34
#define  MAINMENU_TOTALHOURS             35
#define  MAINMENU_L_LOOPS                36
#define  MAINMENU_TOTALDAYS              37
#define  MAINMENU_COMMANDBUTTON_5        38      /* callback function: DisplayTime */
#define  MAINMENU_L_MEASUREMENTNAME      39
#define  MAINMENU_TAAFAILCHECK           40
#define  MAINMENU_ASYMFAILCHECK          41
#define  MAINMENU_RFAILCHECK             42
#define  MAINMENU_DECORATION             43
#define  MAINMENU_TEXTMSG_2              44
#define  MAINMENU_TEXTMSG_3              45
#define  MAINMENU_TEXTMSG_4              46
#define  MAINMENU_TEXTMSG_5              47
#define  MAINMENU_STRESS_TIMER           48      /* callback function: StressTimeOut */
#define  MAINMENU_DECORATION_2           49
#define  MAINMENU_DECORATION_3           50
#define  MAINMENU_DECORATION_4           51
#define  MAINMENU_FINISHED               52
#define  MAINMENU_TEXTMSG                53

#define  RHCURVE                         5
#define  RHCURVE_GRAPH_CH1               2
#define  RHCURVE_GRAPH_CH2               3
#define  RHCURVE_GRAPH_CH3               4
#define  RHCURVE_GRAPH_CH4               5
#define  RHCURVE_GRAPH_CH5               6
#define  RHCURVE_GRAPH_CH6               7
#define  RHCURVE_GRAPH_CH7               8
#define  RHCURVE_GRAPH_CH8               9
#define  RHCURVE_GRAPH_CH9               10
#define  RHCURVE_GRAPH_CH10              11
#define  RHCURVE_GRAPH_CH11              12
#define  RHCURVE_GRAPH_CH12              13
#define  RHCURVE_GRAPH_CH13              14
#define  RHCURVE_GRAPH_CH14              15
#define  RHCURVE_GRAPH_CH15              16
#define  RHCURVE_GRAPH_CH16              17
#define  RHCURVE_RTIME                   18      /* callback function: DisplayRCurve */
#define  RHCURVE_TAATIME                 19      /* callback function: DisplayTAACurve */
#define  RHCURVE_TAADIFF                 20      /* callback function: DisplayDiffCurve */
#define  RHCURVE_ASYMTIME                21      /* callback function: DisplayASYMCurve */
#define  RHCURVE_COMMANDBUTTON_4         22      /* callback function: BacktoPreWin */

#define  RHSETTING                       6
#define  RHSETTING_NAME                  2
#define  RHSETTING_VOLTAGE               3
#define  RHSETTING_CMPLCURR              4
#define  RHSETTING_RATE                  5
#define  RHSETTING_HFIELD                6
#define  RHSETTING_NUMSTEP               7
#define  RHSETTING_COILGAIN              8
#define  RHSETTING_INITDIR               9
#define  RHSETTING_NUMCYCLE              10
#define  RHSETTING_COMMANDBUTTON_2       11      /* callback function: BacktoPreWin */
#define  RHSETTING_COMMANDBUTTON         12      /* callback function: RH_Save */
#define  RHSETTING_READGAIN              13
#define  RHSETTING_REFI                  14
#define  RHSETTING_TEXTMSG_2             15
#define  RHSETTING_TEXTMSG_3             16
#define  RHSETTING_TEXTMSG               17

#define  RSETTING                        7
#define  RSETTING_NAME                   2
#define  RSETTING_CURRENT                3
#define  RSETTING_TIMES                  4
#define  RSETTING_RATE                   5
#define  RSETTING_COMMANDBUTTON_2        6       /* callback function: BacktoPreWin */
#define  RSETTING_COMMANDBUTTON          7       /* callback function: R_Save */
#define  RSETTING_READGAIN               8
#define  RSETTING_HFIELD                 9
#define  RSETTING_COILGAIN               10
#define  RSETTING_TEXTMSG                11

#define  RTIME                           8
#define  RTIME_GRAPH                     2
#define  RTIME_COMMANDBUTTON_4           3       /* callback function: BacktoPreWin */
#define  RTIME_ASYMTIME                  4       /* callback function: DisplayASYMCurve */
#define  RTIME_TAATIME                   5       /* callback function: DisplayTAACurve */
#define  RTIME_COMMANDBUTTON             6       /* callback function: DisplayRHCurve */
#define  RTIME_LEGEND                    7
#define  RTIME_YMAX                      8
#define  RTIME_YMIN                      9
#define  RTIME_RREDRAW                   10      /* callback function: RReDraw */
#define  RTIME_TAADIFF                   11      /* callback function: DisplayDiffCurve */
#define  RTIME_TEXTMSG                   12
#define  RTIME_TEXTMSG_2                 13
#define  RTIME_TEXTMSG_3                 14
#define  RTIME_TEXTMSG_4                 15
#define  RTIME_TEXTMSG_5                 16
#define  RTIME_TEXTMSG_6                 17
#define  RTIME_TEXTMSG_7                 18
#define  RTIME_TEXTMSG_8                 19
#define  RTIME_TEXTMSG_9                 20
#define  RTIME_TEXTMSG_10                21
#define  RTIME_TEXTMSG_13                22
#define  RTIME_TEXTMSG_14                23
#define  RTIME_TEXTMSG_16                24
#define  RTIME_TEXTMSG_11                25
#define  RTIME_TEXTMSG_12                26
#define  RTIME_TEXTMSG_15                27

#define  SETMENU                         9
#define  SETMENU_TESTTYPE                2
#define  SETMENU_COMMANDBUTTON_3         3       /* callback function: BacktoPreWin */
#define  SETMENU_DELETE                  4       /* callback function: DeleteSetting */
#define  SETMENU_COMMANDBUTTON_2         5       /* callback function: ModifyTheMeasurement */
#define  SETMENU_COMMANDBUTTON           6       /* callback function: SetNewMeasurement */
#define  SETMENU_MEASUREMENTLIST         7
#define  SETMENU_COMMANDBUTTON_4         8       /* callback function: GetColdR */
#define  SETMENU_VTARGET                 9       /* callback function: GetCurrForVTarget */

#define  SSETTING                        10
#define  SSETTING_CV_CH1                 2
#define  SSETTING_CV_CH2                 3
#define  SSETTING_CV_CH3                 4
#define  SSETTING_CV_CH4                 5
#define  SSETTING_CV_CH5                 6
#define  SSETTING_CV_CH6                 7
#define  SSETTING_CV_CH7                 8
#define  SSETTING_CV_CH8                 9
#define  SSETTING_CV_CH9                 10
#define  SSETTING_CV_CH10                11
#define  SSETTING_CV_CH11                12
#define  SSETTING_CV_CH12                13
#define  SSETTING_CV_CH13                14
#define  SSETTING_CV_CH14                15
#define  SSETTING_CV_CH15                16
#define  SSETTING_CV_CH16                17
#define  SSETTING_NAME                   18
#define  SSETTING_CURRENT                19
#define  SSETTING_COMMANDBUTTON_2        20      /* callback function: BacktoPreWin */
#define  SSETTING_COMMANDBUTTON          21      /* callback function: S_Save */
#define  SSETTING_SECS                   22
#define  SSETTING_MINS                   23
#define  SSETTING_HOURS                  24
#define  SSETTING_TEMPERATURE            25
#define  SSETTING_DAYS                   26
#define  SSETTING_VOLTAGE                27
#define  SSETTING_STRESSMODE             28
#define  SSETTING_TDESIRED               29
#define  SSETTING_LEADR                  30
#define  SSETTING_FITB                   31
#define  SSETTING_FITA                   32
#define  SSETTING_GET_VHEAT              33      /* callback function: S_GetVHeat */
#define  SSETTING_VHEAT                  34
#define  SSETTING_TARGETVOLT             35
#define  SSETTING_MINR                   36
#define  SSETTING_MAXR                   37
#define  SSETTING_CURRSTEP               38
#define  SSETTING_STARTCURRENT           39
#define  SSETTING_TEXTMSG                40
#define  SSETTING_DECORATION             41
#define  SSETTING_TEXTMSG_2              42
#define  SSETTING_DECORATION_3           43
#define  SSETTING_TEXTMSG_4              44
#define  SSETTING_DECORATION_2           45
#define  SSETTING_TEXTMSG_3              46

#define  TAADIFF                         11
#define  TAADIFF_GRAPH                   2
#define  TAADIFF_ASYMTIME_5              3       /* callback function: DisplayASYMCurve */
#define  TAADIFF_TAATIME                 4       /* callback function: DisplayTAACurve */
#define  TAADIFF_RTIME_5                 5       /* callback function: DisplayRCurve */
#define  TAADIFF_COMMANDBUTTON_12        6       /* callback function: DisplayRHCurve */
#define  TAADIFF_COMMANDBUTTON_9         7       /* callback function: BacktoPreWin */
#define  TAADIFF_YMAX                    8
#define  TAADIFF_YMIN                    9
#define  TAADIFF_ASYMTIME_4              10      /* callback function: DisplayASYMCurve */
#define  TAADIFF_TAADIFFREDRAW           11      /* callback function: TAADiffReDraw */
#define  TAADIFF_RTIME_4                 12      /* callback function: DisplayRCurve */
#define  TAADIFF_COMMANDBUTTON_10        13      /* callback function: DisplayRHCurve */
#define  TAADIFF_LEGEND_5                14
#define  TAADIFF_COMMANDBUTTON_7         15      /* callback function: BacktoPreWin */
#define  TAADIFF_ASYMTIME_3              16      /* callback function: DisplayASYMCurve */
#define  TAADIFF_RTIME_3                 17      /* callback function: DisplayRCurve */
#define  TAADIFF_COMMANDBUTTON_8         18      /* callback function: DisplayRHCurve */
#define  TAADIFF_LEGEND_4                19
#define  TAADIFF_COMMANDBUTTON_5         20      /* callback function: BacktoPreWin */
#define  TAADIFF_ASYMTIME_2              21      /* callback function: DisplayASYMCurve */
#define  TAADIFF_RTIME_2                 22      /* callback function: DisplayRCurve */
#define  TAADIFF_COMMANDBUTTON_6         23      /* callback function: DisplayRHCurve */
#define  TAADIFF_LEGEND_3                24
#define  TAADIFF_COMMANDBUTTON_4         25      /* callback function: BacktoPreWin */
#define  TAADIFF_ASYMTIME                26      /* callback function: DisplayASYMCurve */
#define  TAADIFF_RTIME                   27      /* callback function: DisplayRCurve */
#define  TAADIFF_COMMANDBUTTON           28      /* callback function: DisplayRHCurve */
#define  TAADIFF_LEGEND                  29
#define  TAADIFF_COMMANDBUTTON_2         30      /* callback function: BacktoPreWin */
#define  TAADIFF_TEXTMSG                 31
#define  TAADIFF_TEXTMSG_2               32
#define  TAADIFF_TEXTMSG_3               33
#define  TAADIFF_TEXTMSG_4               34
#define  TAADIFF_TEXTMSG_5               35
#define  TAADIFF_TEXTMSG_6               36
#define  TAADIFF_TEXTMSG_7               37
#define  TAADIFF_TEXTMSG_8               38
#define  TAADIFF_TEXTMSG_9               39
#define  TAADIFF_TEXTMSG_10              40
#define  TAADIFF_TEXTMSG_13              41
#define  TAADIFF_TEXTMSG_14              42
#define  TAADIFF_TEXTMSG_16              43
#define  TAADIFF_TEXTMSG_11              44
#define  TAADIFF_TEXTMSG_12              45
#define  TAADIFF_TEXTMSG_15              46

#define  TAATIME                         12
#define  TAATIME_GRAPH                   2
#define  TAATIME_COMMANDBUTTON_4         3       /* callback function: BacktoPreWin */
#define  TAATIME_ASYMTIME                4       /* callback function: DisplayASYMCurve */
#define  TAATIME_RTIME                   5       /* callback function: DisplayRCurve */
#define  TAATIME_COMMANDBUTTON           6       /* callback function: DisplayRHCurve */
#define  TAATIME_LEGEND                  7
#define  TAATIME_YMAX                    8
#define  TAATIME_YMIN                    9
#define  TAATIME_TAAREDRAW               10      /* callback function: TAAReDraw */
#define  TAATIME_TAADIFF                 11      /* callback function: DisplayDiffCurve */
#define  TAATIME_TEXTMSG_6               12
#define  TAATIME_TEXTMSG_7               13
#define  TAATIME_TEXTMSG_8               14
#define  TAATIME_TEXTMSG_9               15
#define  TAATIME_TEXTMSG_10              16
#define  TAATIME_TEXTMSG_13              17
#define  TAATIME_TEXTMSG_14              18
#define  TAATIME_TEXTMSG_16              19
#define  TAATIME_TEXTMSG_11              20
#define  TAATIME_TEXTMSG_12              21
#define  TAATIME_TEXTMSG_15              22
#define  TAATIME_TEXTMSG                 23
#define  TAATIME_TEXTMSG_2               24
#define  TAATIME_TEXTMSG_3               25
#define  TAATIME_TEXTMSG_4               26
#define  TAATIME_TEXTMSG_5               27

#define  VIEWCOLDR                       13
#define  VIEWCOLDR_COMMANDBUTTON         2       /* callback function: BacktoPreWin */
#define  VIEWCOLDR_R_16                  3
#define  VIEWCOLDR_R_15                  4
#define  VIEWCOLDR_R_14                  5
#define  VIEWCOLDR_R_13                  6
#define  VIEWCOLDR_R_12                  7
#define  VIEWCOLDR_R_11                  8
#define  VIEWCOLDR_R_10                  9
#define  VIEWCOLDR_R_9                   10
#define  VIEWCOLDR_R_8                   11
#define  VIEWCOLDR_R_7                   12
#define  VIEWCOLDR_R_6                   13
#define  VIEWCOLDR_R_5                   14
#define  VIEWCOLDR_R_4                   15
#define  VIEWCOLDR_R_3                   16
#define  VIEWCOLDR_R_2                   17
#define  VIEWCOLDR_R_1                   18


     /* Menu Bars, Menus, and Menu Items: */

#define  Bar_mnu                         1
#define  Bar_mnu_FILE                    2
#define  Bar_mnu_FILE_SETTING_MNU        3       /* callback function: Setting_Fun */
#define  Bar_mnu_FILE_START_MNU          4       /* callback function: Start_Fun */
#define  Bar_mnu_FILE_END_MNU            5       /* callback function: END_MNU */
#define  Bar_mnu_ABOUT_MNU               6       /* callback function: ABOUT_MNU */

#define  HGA_MNU                         2
#define  HGA_MNU_HGA_FILE                2
#define  HGA_MNU_HGA_FILE_HGA_Setting    3       /* callback function: Setting_Fun */
#define  HGA_MNU_HGA_FILE_HGA_TEST       4       /* callback function: Start_HGA_Fun */
#define  HGA_MNU_HGA_FILE_PULSE          5       /* callback function: PULSE_Fun */
#define  HGA_MNU_HGA_FILE_PRINT          6       /* callback function: HGA_PRINT */
#define  HGA_MNU_HGA_FILE_HGA_END        7       /* callback function: END_MNU */
#define  HGA_MNU_ABOUT                   8       /* callback function: ABOUT_MNU */


     /* Callback Prototypes: */ 

void CVICALLBACK ABOUT_MNU(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK AssignDeviceName(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ASYMReDraw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BacktoPreWin(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckInfinite(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CheckRowNum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DeleteSelectedMeasurement(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DeleteSetting(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayASYMCurve(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayDiffCurve(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayRCurve(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayRHCurve(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayTAACurve(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayTime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DoTesting(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK END_MNU(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK GetColdR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GetCurrForVTarget(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK HGA_PRINT(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK L_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Measurement_Setup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModifyTheMeasurement(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK PULSE_Fun(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK RH_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RReDraw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK R_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SelectTheMeasurement(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetNewMeasurement(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Setting_Fun(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ShutDown(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Start_Fun(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK Start_HGA_Fun(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK StressTimeOut(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK S_GetVHeat(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK S_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TAADiffReDraw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TAAReDraw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
