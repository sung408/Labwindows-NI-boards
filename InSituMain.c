#include <cvirte.h>		/* Needed if linking in external compiler; harmless otherwise */
// 9/16/04    const. V QST. 
// 02/17/04 +V & -V Stress
// 09/17/03   Individual Voltage/Current Stress -Sung
//Ver2 Sung : Const Current Stress Mode,
//Version 1.1.5 
//07/22/03
//Sung added const Current Density Stress Mode
//Version 1.1.4
//Sung modified to change the legend of TAADIFF panel (Adding 'SetLegend_B' function)
//08/05/02
//Version 1.1.3
//Sung modified to add a new panel for displaying TAA_diff vs time
//05/06/02
//Version 1.1.2
//Sung modified to calculate assymetry values with different initial values 
//of H field. Modified "calpara(...)" and "RH_Testing(...)"
//05/03/2002
//Version 1.1.1
//Sung Modified to enable to scale the graphs
//05/02/2002

//Version 1.1
//Sung Modified for adding constant H_Field for R test
//05/02/2002


#include "cvi_db.h"

/**************************************************************************************/

#include <userint.h>
#include <ansi_c.h>
#include <formatio.h>		  
#include <ansi_c.h>
#include <analysis.h>
#include <stdlib.h>	   //1.1.3 Sung
#include <stdio.h>	

#include <dataacq.h>
#include <utility.h>
#include <math.h>
#include <InSituMain.h>
#include <InSituRH.h>


static int mainmenu;


/****************************************************************/
/*		description:	Main program of the Magtest				*/
/*						initial the Ni-daq board				*/
/*						initial the analog and digit port 		*/
/*						load the user interface 				*/
/****************************************************************/

int R_Time=1;

int stop_flag;
int CtrlCurr=15;

void Setup_Current (int mycurr,int channel)
{
	short a,b,c;
	int Code;
	double temp;
	
	/*DIG_Prt_Config(1, 0, 0, 1);
	DIG_Prt_Config(1, 1, 0, 1); 
	DIG_Prt_Config(1, 2, 0, 1);*/
	
	//GetCtrlVal (H_TestP, Test_Curr, &mycurr);
	a = channel*16 + 1;  //  1: board 1
	b = 12;			
	temp=(mycurr)/20.0*2048.0 + 2048.0;
	c=temp;
	c=c & 255; 
	c=255-c;
	Code = DIG_Out_Port(1, 2, c);
	Delay(0.01);
	Code = DIG_Out_Port(1, 0, a);
	Delay(0.01);
	Code = DIG_Out_Port(1, 1, b); 
	Delay(0.01);
			
	b=14;			
	Code = DIG_Out_Port(1, 1, b); 
	Delay(0.01);
			
	c=temp;
	c=c & 3840;
	c=c/256;
	c=255-c;
			
	b=13;
	Code = DIG_Out_Port(1, 2, c);
	Delay(0.01);
	Code = DIG_Out_Port(1, 1, b);
	Delay(0.01);
	b=15;			
	Code = DIG_Out_Port(1, 1, b); 
	Delay(0.01);
			
	b=10;
	Code = DIG_Out_Port(1, 1, b);
	Delay(0.01);
	b=15;
	Code = DIG_Out_Port(1, 1, b);
	Delay(0.01);
}




void GetAllMeasurementName(int panel,int ctrl){
	char temp[10];
	char SQLSTR[100];
	int hstmt;
	int NameInd,NameIndMax;
	int sta,rescode,NewNameFlag;
	char TableName[4][15];
	int i,j;
	char MeasurementName[20];
	
	strcpy(TableName[0],"RSetting");
	strcpy(TableName[1],"RHSetting");	
	strcpy(TableName[2],"SSetting");	
	strcpy(TableName[3],"LSetting");	
	j=0;
	DeleteListItem (panel, ctrl, 0, -1);		
	for(i=0;i<4;i++){
		strcpy(SQLSTR,	"select Name from "); 					   
		strcat(SQLSTR,TableName[i]);
		hstmt = DBActivateSQL(hdbc,SQLSTR);
		DBBindColChar (hstmt, 1, 20, MeasurementName, &sta, "");
		
		while((rescode = DBFetchNext(hstmt))==DB_SUCCESS){
			InsertListItem (panel, ctrl, j, MeasurementName, j);
			j=j+1;
		}
		DBDeactivateSQL(hstmt);  
	}
}

void SetLegend(int panel,int ctrl){
	PlotPoint(panel,ctrl,10,17,VAL_SOLID_CIRCLE,VAL_DK_RED);
	PlotPoint(panel,ctrl,10,16,VAL_SOLID_CIRCLE,VAL_DK_BLUE);
	PlotPoint(panel,ctrl,10,15,VAL_SOLID_CIRCLE,VAL_DK_GREEN);
	PlotPoint(panel,ctrl,10,14,VAL_SOLID_CIRCLE,VAL_DK_CYAN);
	PlotPoint(panel,ctrl,10,13,VAL_SOLID_CIRCLE,VAL_DK_MAGENTA);
	PlotPoint(panel,ctrl,10,12,VAL_SOLID_CIRCLE,VAL_DK_YELLOW);
	PlotPoint(panel,ctrl,10,11,VAL_ASTERISK,VAL_DK_RED);
	PlotPoint(panel,ctrl,10,10,VAL_ASTERISK,VAL_DK_BLUE);
	PlotPoint(panel,ctrl,10,9,VAL_ASTERISK,VAL_DK_GREEN);
	PlotPoint(panel,ctrl,10,8,VAL_ASTERISK,VAL_DK_CYAN);
	PlotPoint(panel,ctrl,10,7,VAL_ASTERISK,VAL_DK_MAGENTA);
	PlotPoint(panel,ctrl,10,6,VAL_ASTERISK,VAL_DK_YELLOW);
	PlotPoint(panel,ctrl,10,5,VAL_SOLID_DIAMOND,VAL_DK_RED);
	PlotPoint(panel,ctrl,10,4,VAL_SOLID_DIAMOND,VAL_DK_BLUE);
	PlotPoint(panel,ctrl,10,3,VAL_SOLID_DIAMOND,VAL_DK_GREEN);
	PlotPoint(panel,ctrl,10,2,VAL_SOLID_DIAMOND,VAL_DK_CYAN);
}

//Sung Added : Ver. 1.1.4
void SetLegend_B(int panel,int ctrl){
 
	int H1,H2,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,H14,H15,H16;  //Plot Handler
	
	H1=PlotPoint(panel,ctrl,10,17,VAL_SOLID_CIRCLE,VAL_DK_RED);
	H2=PlotPoint(panel,ctrl,10,16,VAL_SOLID_CIRCLE,VAL_DK_BLUE);
	H3=PlotPoint(panel,ctrl,10,15,VAL_SOLID_CIRCLE,VAL_DK_GREEN);
	H4=PlotPoint(panel,ctrl,10,14,VAL_SOLID_CIRCLE,VAL_DK_CYAN);
	H5=PlotPoint(panel,ctrl,10,13,VAL_SOLID_CIRCLE,VAL_DK_MAGENTA);
	H6=PlotPoint(panel,ctrl,10,12,VAL_SOLID_CIRCLE,VAL_DK_YELLOW);
	H7=PlotPoint(panel,ctrl,10,11,VAL_ASTERISK,VAL_DK_RED);
	H8=PlotPoint(panel,ctrl,10,10,VAL_ASTERISK,VAL_DK_BLUE);
	H9=PlotPoint(panel,ctrl,10,9,VAL_ASTERISK,VAL_DK_GREEN);
	H10=PlotPoint(panel,ctrl,10,8,VAL_ASTERISK,VAL_DK_CYAN);
	H11=PlotPoint(panel,ctrl,10,7,VAL_ASTERISK,VAL_DK_MAGENTA);
	H12=PlotPoint(panel,ctrl,10,6,VAL_ASTERISK,VAL_DK_YELLOW);
	H13=PlotPoint(panel,ctrl,10,5,VAL_SOLID_DIAMOND,VAL_DK_RED);
	H14=PlotPoint(panel,ctrl,10,4,VAL_SOLID_DIAMOND,VAL_DK_BLUE);
	H15=PlotPoint(panel,ctrl,10,3,VAL_SOLID_DIAMOND,VAL_DK_GREEN);
	H16=PlotPoint(panel,ctrl,10,2,VAL_SOLID_DIAMOND,VAL_DK_CYAN);

    SetPlotAttribute (panel, ctrl, H1, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H2, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H3, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H4, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H5, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H6, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H7, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H8, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H9, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H10, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H11, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H12, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H13, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H14, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H15, ATTR_PLOT_STYLE, VAL_SCATTER);
    SetPlotAttribute (panel, ctrl, H16, ATTR_PLOT_STYLE, VAL_SCATTER);
  
}
main()
{
	int error;
  	short Board;
	int i;
	
	Acc_STime=0;
	SSetting.Temperature = 0;
	stop_flag = 0;
	AI_Clear(1);
	AI_Clear(2);
	AI_Clear(3);  
	//AI_Setup (1, 2, 1);
	
  	Init_DA_Brds (1,&Board);
  	Init_DA_Brds(2,&Board);
  	Init_DA_Brds (3,&Board); 
  	Init_DA_Brds (4,&Board);
  	
	AI_Configure (2, -1, 0, 10, 0, 0);
	MIO_Config (2, 1, 0);
	AO_Configure (2, 0, 0, 1, 1, 0);
	AO_Configure (2, 1, 1, 0, 10.0, 0);
	AO_VWrite(2,1,1);  ///???????

  	Delay (0.01);
	
	Delay (0.01); 
  	OddRow=-1;
  	TotalTimes.Days=0;
  	TotalTimes.Hours=0;
  	TotalTimes.Mins=0;
  	
  	
  	H_MainWin	=  LoadPanel(0, "InSituRH.uir", MAINMENU);
  	H_SetMenu	=  LoadPanel(0, "InSituRH.uir", SETMENU);
  	H_RSetting	=  LoadPanel(0, "InSituRH.uir", RSETTING);
  	H_SSetting	=  LoadPanel(0, "InSituRH.uir", SSETTING);
  	H_RHSetting	=  LoadPanel(0, "InSituRH.uir", RHSETTING);
  	H_LSetting	=  LoadPanel(0, "InSituRH.uir", LSETTING);
  	H_RHCurve	=  LoadPanel(0, "InSituRH.uir", RHCURVE);
  	H_TaaCurve	=  LoadPanel(0, "InSituRH.uir", TAATIME);
  	H_RCurve	=  LoadPanel(0, "InSituRH.uir", RTIME);
  	H_AsymCurve	=  LoadPanel(0, "InSituRH.uir", ASYMTIME);
  	H_DspTime	=  LoadPanel(0, "InSituRH.uir", DSPTIME);
	H_TAADiff	=  LoadPanel(0, "InSituRH.uir", TAADIFF);
	H_ViewColdR	=  LoadPanel(0, "InSituRH.uir", VIEWCOLDR); 
	
     hdbc = DBConnect ("DSN=MRAM;DLG=2");
  	DisplayPanel(H_MainWin); 
	GetAllMeasurementName(H_MainWin,MAINMENU_MEASUREMENTLIST); 
	SetLegend(H_RCurve,RTIME_LEGEND);
	SetLegend(H_AsymCurve,ASYMTIME_LEGEND);
	SetLegend(H_TaaCurve,TAATIME_LEGEND);
	SetLegend_B(H_TAADiff,TAADIFF_LEGEND); 
	
	
  	RunUserInterface(); 
  
}


/****************************************************************/
/*		description:	Exit from the program					*/
/*						it is the call back function from thr 	*/
/*						user interface					 		*/
/****************************************************************/

int  ShutDown(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	char temp[10];
	int response;
	int i;
	char File_Path[100];
	char Wafer[20];
	char Row[10];
	FILE *fp;
	char CurrDateTime[30];
  	if (event == EVENT_COMMIT)
  	{   
  		response = ConfirmPopup ("Stop", "Do you want tp stop the measurement?");
  		if(response){
  			stop_flag=1000;
  			
  			// Turn off bias current
  			
  			for(i=0;i<32;i++)
  				AO_VWrite(1,16+i,0);
  			
  			for(i=0;i<16;i++)
  				AO_VWrite(3,16+i,0);
  				
  				
  			for(i=0;i<16;i++)
  				AO_VWrite(4,16+i,0);
  				
  			strcpy(File_Path, "c:\\testdata\\log_file\\");
			strcat(File_Path,"stoplog.txt");
			GetCtrlVal(H_MainWin,MAINMENU_NAME,Wafer);
			GetCtrlVal(H_MainWin,MAINMENU_ROWNAME,Row);
			if(strlen(Wafer)!=0 && strlen(Row)!=0){
				if((fp=fopen(File_Path,"r"))==NULL){
					fp = fopen(File_Path,"w+");
					fprintf(fp,"Wafer,Row,DateTime,StressedTime\n");
				}else{
					fclose(fp);
					fp = fopen(File_Path,"a+");
				}
				strcpy(CurrDateTime,DateStr());
				strcat(CurrDateTime," ");
				strcat(CurrDateTime,TimeStr());
				fprintf(fp,"%s,%s,%s,%.3f\n",Wafer,Row,CurrDateTime,Acc_STime);
				fclose(fp);
    			
    		}
    		QuitUserInterface(0);
    	}
  	}
  	else if (event == EVENT_RIGHT_CLICK){
    	MessagePopup("Quit Button Help","This button causes the program to quit");
    }   
  return(0);
}	 

int CVICALLBACK Measurement_Setup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DisplayPanel(H_SetMenu); 
			GetAllMeasurementName(H_SetMenu,SETMENU_MEASUREMENTLIST); 
			break;
		}
	return 0;
}

void GetNewMeasurementName(char *TableName, char *NewName){
	char temp[10],temp1[10];
	char SQLSTR[100];
	int hstmt;
	int NameInd,NameIndMax;
	int sta,rescode,NewNameFlag;
	
	NameIndMax=0;
	strcpy(SQLSTR,	"select Name from "); 					   
	strcat(SQLSTR,TableName);
	
	hstmt = DBActivateSQL(hdbc,SQLSTR);
	
	DBBindColChar (hstmt, 1, 20, NewName, &sta, "");
	
	strncpy(temp,TableName,2);
	temp[2]='\0';
	NewNameFlag=0;
	while((rescode = DBFetchNext(hstmt))==DB_SUCCESS){
		NewNameFlag=1;
		if(strcmp(temp,"RH")!=0)
			strcpy(temp1,&NewName[1]);
		else
			strcpy(temp1,&NewName[2]);	
		NameInd = atof(temp1);
		
		if(NameInd>NameIndMax)
			NameIndMax = NameInd;
	}
	
	if(NewNameFlag==1){
		sprintf(temp1,"%d",NameIndMax+1);
		if(strcmp(temp,"RH")!=0)
			strcpy(&NewName[1],temp1);
		else
			strcpy(&NewName[2],temp1);
	}else{
		if(strcmp(temp,"RS")==0)
			strcpy(NewName,"R1");
		else if(strcmp(temp,"RH")==0)
			strcpy(NewName,"RH1");			
		else if(strcmp(temp,"SS")==0)
			strcpy(NewName,"S1");			
		else if(strcmp(temp,"LS")==0)
			strcpy(NewName,"L1");
	}
	DBDeactivateSQL(hstmt);  
}  



int CVICALLBACK SetNewMeasurement (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int index;
	char NewName[20];
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(H_SetMenu,SETMENU_TESTTYPE,&index);
			HidePanel(panel);
			switch (index){
				case 1:
					DisplayPanel(H_RSetting);
					GetNewMeasurementName("RSETTING",NewName);
					ResetTextBox(H_RSetting,RSETTING_NAME,NewName);
					break;
				case 2:
					DisplayPanel(H_RHSetting);
					GetNewMeasurementName("RHSETTING",NewName);
					ResetTextBox(H_RHSetting,RHSETTING_NAME,NewName);
					break;
				case 3:
					DisplayPanel(H_SSetting);
					GetNewMeasurementName("SSETTING",NewName);
					ResetTextBox(H_SSetting,SSETTING_NAME,NewName);
					break;
				case 4:
					DisplayPanel(H_LSetting);					
					GetNewMeasurementName("LSETTING",NewName);
					GetAllMeasurementName(H_LSetting,LSETTING_MEASUREMENTLIST);
					ResetTextBox(H_LSetting,LSETTING_NAME,NewName);
		//			DeleteListItem (H_LSetting, LSETTING_SELECTED, 0, -1);  
					break;
			}	

			break;
		}
	return 0;
}

int CVICALLBACK BacktoPreWin (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetAllMeasurementName(H_SetMenu,SETMENU_MEASUREMENTLIST); 			
			if(panel==H_SetMenu)			
				GetAllMeasurementName(H_MainWin,MAINMENU_MEASUREMENTLIST) ;
			
			if(panel==H_SetMenu || panel==H_DspTime || panel ==H_RCurve || panel==H_RHCurve|| panel==H_TaaCurve|| panel==H_AsymCurve || panel==H_TAADiff || panel==H_ViewColdR) //Ver. 1.1.3 added new panel
				DisplayPanel(H_MainWin);
			else
				DisplayPanel(H_SetMenu);
			HidePanel(panel);		
			break;
		}
	return 0;
}

int CVICALLBACK R_Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int hstmt;
	char temp[20];
	char SQLSTR[500];
	int Add_Flag=0;
	int ReadGain;
	short Read_Gain_Val[8];
	int Gain_Index;
	
	Read_Gain_Val[0]=-1;
	Read_Gain_Val[1]=1;
	Read_Gain_Val[2]=2;
	Read_Gain_Val[3]=5;
	Read_Gain_Val[4]=10;
	Read_Gain_Val[5]=20;
	Read_Gain_Val[6]=50;
	Read_Gain_Val[7]=100;
	
	
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(H_RSetting,RSETTING_NAME,RSetting.Name);
			GetCtrlVal(H_RSetting,RSETTING_CURRENT,&RSetting.Current);
			GetCtrlVal(H_RSetting,RSETTING_RATE,&RSetting.Rate);
			GetCtrlVal(H_RSetting,RSETTING_TIMES,&RSetting.Times);
			GetCtrlVal(H_RSetting,RSETTING_READGAIN,&Gain_Index);
			GetCtrlVal(H_RSetting,RSETTING_HFIELD,&RSetting.H_Field);    //Sung modified 05/02/02
			GetCtrlVal(H_RSetting,RSETTING_COILGAIN,&RSetting.CoilGain); //Sung modified 05/02/02    
			RSetting.ReadGain = Read_Gain_Val[Gain_Index];
				
			if(Add_Flag==0) {
				strcpy(SQLSTR, "delete from RSETTING where Name = '");
				strcat (SQLSTR,RSetting.Name);
				strcat(SQLSTR,"'" );
				hstmt = DBActivateSQL(hdbc,SQLSTR);
			}
			strcpy(SQLSTR,"insert into RSETTING values('");
			strcat(SQLSTR,RSetting.Name);
			strcat(SQLSTR,"'," );
			sprintf(temp,"%.2f,",RSetting.Current);
			strcat(SQLSTR,temp);
			sprintf(temp,"%.2f,",RSetting.Rate);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d,",RSetting.Times);
			strcat(SQLSTR,temp);			
			sprintf(temp,"%d,",RSetting.ReadGain);     //Sung modified 05/02/02
			strcat(SQLSTR,temp);
			sprintf(temp,"%.2f,",RSetting.H_Field);	   //Sung modified 05/02/02
			strcat(SQLSTR,temp);
			sprintf(temp,"%.2f)",RSetting.CoilGain);   //Sung modified 05/02/02
			strcat(SQLSTR,temp);
			
			if ((hstmt = DBActivateSQL(hdbc,SQLSTR))==0){
				MessagePopup("In Situ RH Testing","Can not insert the record, please check the Product name");
			}
			
			DBDeactivateSQL(hstmt);			
			
			break;
		}
	return 0;
}

int CVICALLBACK S_Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int hstmt;
	char temp[20];
	char SQLSTR[300];
	int Add_Flag=0;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(H_SSetting,SSETTING_NAME,SSetting.Name);
			GetCtrlVal(H_SSetting,SSETTING_CURRENT,&SSetting.Current);
			GetCtrlVal(H_SSetting,SSETTING_DAYS,&SSetting.Days);
			GetCtrlVal(H_SSetting,SSETTING_HOURS,&SSetting.Hours);
			GetCtrlVal(H_SSetting,SSETTING_MINS,&SSetting.Mins);
			GetCtrlVal(H_SSetting,SSETTING_SECS,&SSetting.Secs); 
			GetCtrlVal(H_SSetting,SSETTING_TEMPERATURE,&SSetting.Temperature);
			GetCtrlVal(H_SSetting,SSETTING_VOLTAGE,&SSetting.Voltage);
			GetCtrlVal(H_SSetting,SSETTING_STRESSMODE,&SSetting.Stressmode);
			
			if(Add_Flag==0) {
				strcpy(SQLSTR, "delete from SSETTING where Name = '");
				strcat (SQLSTR,SSetting.Name);
				strcat(SQLSTR,"'" );
				hstmt = DBActivateSQL(hdbc,SQLSTR);
			}
			strcpy(SQLSTR,"insert into SSETTING values('");
			strcat(SQLSTR,SSetting.Name);
			strcat(SQLSTR,"'," );
			sprintf(temp,"%.2f,",SSetting.Current);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d,",SSetting.Days);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d,",SSetting.Hours);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d,",SSetting.Mins);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d,",SSetting.Secs);
			strcat(SQLSTR,temp);
			sprintf(temp,"%.2f,",SSetting.Temperature);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d,",SSetting.Stressmode);
			strcat(SQLSTR,temp);
			sprintf(temp,"%.2f)",SSetting.Voltage);
			strcat(SQLSTR,temp);

			
			
			if ((hstmt = DBActivateSQL(hdbc,SQLSTR))==0){
				MessagePopup("In Situ RH Testing","Can not insert the record, please check the Product name");
			}
			
			DBDeactivateSQL(hstmt);		
			break;
		}
	return 0;
}

int CVICALLBACK RH_Save (int panel, int control, int event,	 
		void *callbackData, int eventData1, int eventData2)
{
	int hstmt;
	char temp[20];
	char SQLSTR[300];
	int Add_Flag=0;
	int Read_Gain_Val[80];
	int Gain_Index;
	Read_Gain_Val[0]=-1;
	Read_Gain_Val[1]=1;
	Read_Gain_Val[2]=2;
	Read_Gain_Val[3]=5;
	Read_Gain_Val[4]=10;
	Read_Gain_Val[5]=20;
	Read_Gain_Val[6]=50;
	Read_Gain_Val[7]=100;
	
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(H_RHSetting,RHSETTING_NAME,RHSetting.Name);
			GetCtrlVal(H_RHSetting,RHSETTING_VOLTAGE,&RHSetting.Voltage);
			GetCtrlVal(H_RHSetting,RHSETTING_CMPLCURR,&RHSetting.CmplCurr);
			GetCtrlVal(H_RHSetting,RHSETTING_HFIELD,&RHSetting.H_Field);
			GetCtrlVal(H_RHSetting,RHSETTING_NUMSTEP,&RHSetting.StepNum);
			GetCtrlVal(H_RHSetting,RHSETTING_COILGAIN,&RHSetting.CoilGain);
			GetCtrlVal(H_RHSetting,RHSETTING_RATE,&RHSetting.Rate);
			GetCtrlVal(H_RHSetting,RHSETTING_NUMCYCLE,&RHSetting.CycleNum);
			GetCtrlVal(H_RHSetting,RHSETTING_INITDIR,&RHSetting.InitDir);
			GetCtrlVal(H_RHSetting,RHSETTING_READGAIN,&Gain_Index);
			RHSetting.ReadGain = Read_Gain_Val[Gain_Index];
			
			if(Add_Flag==0) {
				strcpy(SQLSTR, "delete from RHSETTING where Name = '");
				strcat (SQLSTR,RHSetting.Name);
				strcat(SQLSTR,"'" );
				hstmt = DBActivateSQL(hdbc,SQLSTR);
			}
			strcpy(SQLSTR,"insert into RHSETTING values('");
			strcat(SQLSTR,RHSetting.Name);
			strcat(SQLSTR,"'," );
			sprintf(temp,"%.2f,",RHSetting.Voltage);
			strcat(SQLSTR,temp);
			sprintf(temp,"%.2f,",RHSetting.CmplCurr);
			strcat(SQLSTR,temp);
			sprintf(temp,"%.2f,",RHSetting.H_Field);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d,",RHSetting.StepNum);
			strcat(SQLSTR,temp);			
			sprintf(temp,"%.2f,",RHSetting.CoilGain);
			strcat(SQLSTR,temp);
			sprintf(temp,"%.2f,",RHSetting.Rate);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d,",RHSetting.CycleNum);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d,",RHSetting.InitDir);
			strcat(SQLSTR,temp);
			sprintf(temp,"%d)",RHSetting.ReadGain);
			strcat(SQLSTR,temp);
			
			if ((hstmt = DBActivateSQL(hdbc,SQLSTR))==0){
				MessagePopup("In Situ RH Testing","Can not insert the record, please check the Product name");
			}
			
			DBDeactivateSQL(hstmt);		
			break;
		}
	return 0;
}
void PutIttotheMeasurementList(int panel,int settinglist, int measurementlist,char * SelectedName){

	int MeasurementVal;
	int MeasurementIndex;
	char MeasurementName[20];
	int Num_Selected;
	
  	GetCtrlVal(panel,settinglist,&MeasurementVal);
  	GetIndexFromValue(panel,settinglist,&MeasurementIndex,MeasurementVal);
  	GetLabelFromIndex(panel,settinglist,MeasurementIndex,MeasurementName);
  	GetNumListItems (panel,measurementlist , &Num_Selected);
  	InsertListItem (panel, measurementlist,Num_Selected, MeasurementName,Num_Selected);
  	strcpy(SelectedName,MeasurementName);
}
void GetMeasurementTime(char *SelectedName,int *days,int *hours,int *mins,int *loops){
	char TableName[20];
	char SQLSTR[200];
	int hstmt,sta;
	if(SelectedName[0]=='L'){
		strcpy(SQLSTR,	"select Cycle_Num,Duration_Day,Duration_Hour,Duration_Min from "); 					   		
		strcpy(TableName,"LSetting");
	}
	else if (SelectedName[0]=='S'){
		strcpy(SQLSTR,	"select Duration_Day,Duration_Hour,Duration_Min from "); 					   
		strcpy(TableName,"SSetting");
	}
	else if (SelectedName[1]=='H'){
		*days=0;
		*hours=0;
		*mins=5;
		return;
	}
	else{
		*days=0;
		*hours=0;
		*mins=1;
		return;
	}
	
	
	strcat(SQLSTR,TableName);
	strcat(SQLSTR, " where Name = '");
	strcat(SQLSTR,SelectedName);
	strcat(SQLSTR,"'");
	
	hstmt = DBActivateSQL(hdbc,SQLSTR); 
	if(SelectedName[0]!='L'){   			
		DBBindColInt (hstmt,1,days, &sta);
		DBBindColInt (hstmt,2,hours, &sta);
		DBBindColInt (hstmt,3,mins, &sta);
	}else{
		DBBindColInt (hstmt,1,loops, &sta);
		DBBindColInt (hstmt,2,days, &sta);
		DBBindColInt (hstmt,3,hours, &sta);
		DBBindColInt (hstmt,4,mins, &sta);
	}
	DBFetchNext(hstmt);
	
}

void CalculateTotalTime(struct TotalTimes *TotalTimes, int days,int hours,int mins,int flag){
	if(flag==1){
		TotalTimes->Mins+=mins;				
		if(TotalTimes->Mins>=60){
			TotalTimes->Mins-=60;
			TotalTimes->Hours++;	
			if(TotalTimes->Hours>=24){
				TotalTimes->Mins-=24;						
				TotalTimes->Days++;
			}	 
		}
		TotalTimes->Hours+=hours;	
		if(TotalTimes->Hours>=24){
			TotalTimes->Hours-=24;						
			TotalTimes->Days++;
		}
		TotalTimes->Days+=days;
	}else{
		TotalTimes->Days-=days;		
		if(TotalTimes->Hours<hours){			
			TotalTimes->Days--;					
			TotalTimes->Hours+=24;
		}
		TotalTimes->Hours-=hours;
		if(TotalTimes->Mins<mins){ 
			if(TotalTimes->Hours==0){
				TotalTimes->Days--;					
				TotalTimes->Hours+=24;	
			}
			TotalTimes->Hours--;	
			TotalTimes->Mins+=60;	
		}
		TotalTimes->Mins-=mins;		
	}
}

int CVICALLBACK SelectTheMeasurement (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{	  
	int days,hours,mins,loops;
	char SelectedName[20];
	int i;
	switch (event)
		{
		case EVENT_LEFT_DOUBLE_CLICK:
			if (panel==H_MainWin){
				PutIttotheMeasurementList( panel,control,MAINMENU_SELECTED,SelectedName);
				GetMeasurementTime(SelectedName,&days,&hours,&mins,&loops);				
				if(SelectedName[0]=='L' && loops>1){
					for (i=0;i<loops;i++){													
						CalculateTotalTime(&TotalTimes,days,hours,mins,1);
					}
				}else{
					CalculateTotalTime(&TotalTimes,days,hours,mins,1);
				}
				SetCtrlVal(panel,MAINMENU_TOTALDAYS,TotalTimes.Days);
				SetCtrlVal(panel,MAINMENU_TOTALHOURS,TotalTimes.Hours);
				SetCtrlVal(panel,MAINMENU_TOTALMINS,TotalTimes.Mins);
				if(SelectedName[0]=='L' && days==0 && hours==0 && mins==0){  
					SetCtrlAttribute(panel,MAINMENU_TOTALDAYS,ATTR_DIMMED,1);
					SetCtrlAttribute(panel,MAINMENU_TOTALHOURS,ATTR_DIMMED,1);
					SetCtrlAttribute(panel,MAINMENU_TOTALMINS,ATTR_DIMMED,1);					
				}
			}
			else{
				PutIttotheMeasurementList( panel,control,LSETTING_SELECTED,SelectedName);			
			}
			break;
		}
	return 0;
}

int CVICALLBACK DeleteSelectedMeasurement (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int SelectedVal;
	int SelectedIndex;
	char SelectedName[20];
	int days,hours,mins,loops;
	int i;
	int response;
	switch (event)
		{
		case EVENT_COMMIT:
			//response = ConfirmPopup ("Stop", "Do you want tp stop the measurement?");  ctlin
  			//if(response){																 ctlin
				GetCtrlVal(panel,control,&SelectedVal);
  				GetIndexFromValue(panel,control,&SelectedIndex,SelectedVal);
  				GetLabelFromIndex(panel,control,SelectedIndex,SelectedName);
  				DeleteListItem (panel, control, SelectedIndex, 1);
  				if(panel==H_MainWin){
  					GetMeasurementTime(SelectedName,&days,&hours,&mins,&loops);					
  					if(SelectedName[0]=='L' && days==0 && hours==0 && mins==0){  
						SetCtrlAttribute(panel,MAINMENU_TOTALDAYS,ATTR_DIMMED,0);
						SetCtrlAttribute(panel,MAINMENU_TOTALHOURS,ATTR_DIMMED,0);
						SetCtrlAttribute(panel,MAINMENU_TOTALMINS,ATTR_DIMMED,0);					
					}
					if( SelectedName[0]=='L' && loops>1){
						for(i=0;i<loops;i++){
  							CalculateTotalTime(&TotalTimes,days,hours,mins,-1);
  						}
  					}
  					else{
						CalculateTotalTime(&TotalTimes,days,hours,mins,-1);
					}
					SetCtrlVal(panel,MAINMENU_TOTALDAYS,TotalTimes.Days);
					SetCtrlVal(panel,MAINMENU_TOTALHOURS,TotalTimes.Hours);
					SetCtrlVal(panel,MAINMENU_TOTALMINS,TotalTimes.Mins);
				}
			//}																			ctlin
			break;
		}
	return 0;
}

int CVICALLBACK L_Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int hstmt;
	char temp[20];
	char SQLSTR[300];
	int Add_Flag=0;
	int Num_Selected; 
	int i,j;
	char TotalMeasurement[300];
	int CheckedInf;
	int days,hours,mins,loops;
	switch (event)
		{
		case EVENT_COMMIT:
			LSetting.L_Times.Days=0;
  			LSetting.L_Times.Hours=0;
  			LSetting.L_Times.Mins=0;
		    GetCtrlVal(H_LSetting,LSETTING_NAME,LSetting.Name);
			GetCtrlVal(H_LSetting,LSETTING_LOOPS,&LSetting.Loops);
			
			GetNumListItems (panel,LSETTING_SELECTED , &Num_Selected);
			for (i=0;i<Num_Selected;i++){
				GetLabelFromIndex(panel,LSETTING_SELECTED,i,LSetting.MeasurementName);
				GetMeasurementTime(LSetting.MeasurementName,&days,&hours,&mins,&loops);				
				if(loops>1){
					for (j=0;j<loops;j++){
						CalculateTotalTime(&LSetting.L_Times,days,hours,mins,1);
					}
				}else{
					CalculateTotalTime(&LSetting.L_Times,days,hours,mins,1);
				}
				if(i==0){
					strcpy(TotalMeasurement,LSetting.MeasurementName);	
				}
				else{
					strcat(TotalMeasurement,",");
					strcat(TotalMeasurement,LSetting.MeasurementName);	
				}
			}
			GetCtrlVal(H_LSetting,LSETTING_INFINITE,&CheckedInf);
			if(CheckedInf==1){
				LSetting.Loops = 0;
				LSetting.L_Times.Days=0;
				LSetting.L_Times.Hours=0;
				LSetting.L_Times.Mins=0;
			}
			if(i!=0){
				if(Add_Flag==0) {
					strcpy(SQLSTR, "delete from LSETTING where Name = '");
					strcat (SQLSTR,LSetting.Name);
					strcat(SQLSTR,"'" );
					hstmt = DBActivateSQL(hdbc,SQLSTR);
				}
				strcpy(SQLSTR,"insert into LSETTING values('");
				strcat(SQLSTR,LSetting.Name);
				strcat(SQLSTR,"'," );
				sprintf(temp,"%d,'",LSetting.Loops);
				strcat(SQLSTR,temp);
				strcat(SQLSTR,TotalMeasurement);
				strcat(SQLSTR,"',");
				sprintf(temp,"%d,",LSetting.L_Times.Days);
				strcat(SQLSTR,temp);
				sprintf(temp,"%d,",LSetting.L_Times.Hours);
				strcat(SQLSTR,temp);
				sprintf(temp,"%d)",LSetting.L_Times.Mins);
				strcat(SQLSTR,temp);
				if ((hstmt = DBActivateSQL(hdbc,SQLSTR))==0){
					MessagePopup("In Situ RH Testing","Can not insert the record, please check the Product name");
				}
				DBDeactivateSQL(hstmt);		
			}else{
				MessagePopup("In Situ RH Testing","Please select measurement from the measurement list");
			}
			break;
		}
	return 0;
}

int CVICALLBACK CheckInfinite (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int CheckedVal;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(panel,control,&CheckedVal);
			if(CheckedVal==1)
				SetCtrlAttribute (panel,LSETTING_LOOPS , ATTR_DIMMED,1 );
			else
				SetCtrlAttribute (panel,LSETTING_LOOPS , ATTR_DIMMED,0 );
			break;
		}
	return 0;
}

int CVICALLBACK CheckRowNum (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char RowName[20];
	int LastDigit;
	switch (event)
		{
		case EVENT_LOST_FOCUS:
			GetCtrlVal(panel,control,RowName);
			if( strlen(RowName)>0){
				LastDigit=atof(&RowName[strlen(RowName)-1]);
				if(LastDigit%2==0)
					OddRow=0;
				else
					OddRow=1;
			}
			break;
		}
	return 0;
}

int CVICALLBACK AssignDeviceName (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char DeviceName[20];
	char SQLSTR[200];
	int hstmt;
	char temp[10];
	int i,j,Index,sta,rescode;
	switch (event)
		{
		case EVENT_LOST_FOCUS: 		 //"Event Lost Focus!!! Sung
			if(OddRow==-1){
				MessagePopup("In Situ RH Testing","Please Enter Wafer & Row Name");
				break;
			}
			else{
		   		GetCtrlVal(panel,control,DeviceName);
		   		StringUpperCase (DeviceName);
				if( strlen(DeviceName)>0){
					strcpy(SQLSTR,"select index from DeviceName where devicename='"); 					   
					strcat(SQLSTR,DeviceName);
					if(OddRow==1)
						strcat(SQLSTR,"' and IsOddRow=1");
					else
						strcat(SQLSTR,"' and IsOddRow=0");					
				
					hstmt = DBActivateSQL(hdbc,SQLSTR);
					DBBindColInt (hstmt, 1, &Index, &sta);	
					
					if((rescode = DBFetchNext(hstmt))!=DB_SUCCESS){
						MessagePopup("In Situ RH Testing","The Device Name is incorrect, please try again");	
						break;
					}
					DBDeactivateSQL(hstmt);		
					for(j=0;j<16;j++){
						SetCtrlVal(panel,MAINMENU_CH1+j,0);
					}
					strcpy(SQLSTR,"select devicename from DeviceName where index>="); 					   
					sprintf(temp,"%d and ",Index);
					strcat(SQLSTR,temp);
					if(OddRow==1)       
						strcat(SQLSTR,"IsOddRow=1 ");	
					else
						strcat(SQLSTR,"IsOddRow=0 ");							
					
					strcat(SQLSTR, "order by index");
					hstmt = DBActivateSQL(hdbc,SQLSTR);
					DBBindColChar (hstmt, 1, 20,DeviceName, &sta,""); 
					i=0;
					
				
					while((rescode = DBFetchNext(hstmt))==DB_SUCCESS){
						SetCtrlAttribute (panel,MAINMENU_CH1+i, ATTR_LABEL_TEXT, DeviceName);
						strcpy(Devices.Name[i],DeviceName);
						i=i+1;
						if(i==16)
							break;
					}
					DBDeactivateSQL(hstmt);  
					for(j=i;j<16;j++){
						SetCtrlAttribute (panel,MAINMENU_CH1+j , ATTR_LABEL_TEXT, "");
						SetCtrlVal(panel,MAINMENU_CH1+j,1);
						strcpy(Devices.Name[i],"");
					}
				}
			}
			break;
		}
	return 0;
}
void L_Setting(char *MeasurementName,int flag){
	int hstmt;
	char temp[20];
	char SQLSTR[300];
	int rescode;
	char Name[20];
	int Loops;
	char *tempStr;
	char MeasurementInLoop[500];
	char NameInLoop[20];
	int j,sta;
	int Location;
	
	strcpy(SQLSTR,	"select * from LSetting where Name = '"); 					   
	strcat(SQLSTR,MeasurementName);
	strcat(SQLSTR,"'");	
	hstmt = DBActivateSQL(hdbc,SQLSTR);
	
	DBBindColChar (hstmt, 1, 20, Name, &sta, "");
	DBBindColInt (hstmt, 2, &Loops, &sta);
	DBBindColChar (hstmt, 3, 500, MeasurementInLoop, &sta, "");
	if((rescode = DBFetchNext(hstmt))==DB_SUCCESS){
		if(flag==1){	
	 		ResetTextBox(H_LSetting,LSETTING_NAME,Name);
			SetCtrlVal(H_LSetting,LSETTING_LOOPS,Loops);
			if(Loops==0){
				SetCtrlVal(H_LSetting,LSETTING_INFINITE,1);
				SetCtrlAttribute (H_LSetting,LSETTING_LOOPS , ATTR_DIMMED,1 );
				SetCtrlVal(H_LSetting,LSETTING_LOOPS,1);      
			}
			else
				SetCtrlVal(H_LSetting,LSETTING_INFINITE,0);			
			
			GetAllMeasurementName(H_LSetting,LSETTING_MEASUREMENTLIST); 
			j=0;
			DeleteListItem(H_LSetting, LSETTING_SELECTED, 0, -1);   		
			while ((tempStr=strstr(MeasurementInLoop,","))!=NULL){
				Location = strlen(MeasurementInLoop)-strlen(tempStr)+1;
				strncpy(NameInLoop,MeasurementInLoop,Location-1);
				NameInLoop[Location-1]='\0';
				strcpy(MeasurementInLoop,&MeasurementInLoop[Location]);
				InsertListItem (H_LSetting, LSETTING_SELECTED, j, NameInLoop,j);   
				j=j+1;
			}
			InsertListItem (H_LSetting, LSETTING_SELECTED, j, MeasurementInLoop,j);   
			DisplayPanel(H_LSetting);
			HidePanel(H_SetMenu);
		}
		else{
			 strcpy(LSetting.Name,Name);
 			 LSetting.Loops = Loops;
 		   	 strcpy(LSetting.MeasurementName,MeasurementInLoop);
		}
	} 
	DBDeactivateSQL(hstmt);  
}

void S_Setting(char *MeasurementName,int flag){
	int hstmt;
	char SQLSTR[500];
	int rescode, Stressmode;
	char Name[20];
	double Current,Temperature,Voltage;
	int Days,Hours,Mins,Secs;
	int sta;
	
	
	strcpy(SQLSTR,	"select * from SSetting where Name = '"); 					   
	strcat(SQLSTR,MeasurementName);
	strcat(SQLSTR,"'");	
	hstmt = DBActivateSQL(hdbc,SQLSTR);
	
	DBBindColChar (hstmt, 1, 20, Name, &sta, "");
	DBBindColDouble (hstmt, 2, &Current, &sta);
	DBBindColInt (hstmt, 3, &Days, &sta);
	DBBindColInt (hstmt, 4, &Hours, &sta);
	DBBindColInt (hstmt, 5, &Mins, &sta);
	DBBindColInt (hstmt, 6, &Secs, &sta); 
	DBBindColDouble (hstmt, 7, &Temperature, &sta);
	DBBindColInt (hstmt, 8, &Stressmode, &sta);
	DBBindColDouble (hstmt, 9, &Voltage, &sta);
	
	if((rescode = DBFetchNext(hstmt))==DB_SUCCESS){
		if(flag==1){
	 		ResetTextBox(H_SSetting,SSETTING_NAME,Name);
			SetCtrlVal(H_SSetting,SSETTING_CURRENT,Current);
			SetCtrlVal(H_SSetting,SSETTING_DAYS,Days);
			SetCtrlVal(H_SSetting,SSETTING_HOURS,Hours);
			SetCtrlVal(H_SSetting,SSETTING_MINS,Mins);
			SetCtrlVal(H_SSetting,SSETTING_SECS,Secs);    
			SetCtrlVal(H_SSetting,SSETTING_TEMPERATURE,Temperature);
			SetCtrlVal(H_SSetting,SSETTING_STRESSMODE,Stressmode);
			SetCtrlVal(H_SSetting,SSETTING_VOLTAGE,Voltage);
			DisplayPanel(H_SSetting);
			HidePanel(H_SetMenu);
		}else{
			strcpy(SSetting.Name,Name);
 			SSetting.Current=Current;
 			SSetting.Days=Days;
 			SSetting.Hours=Hours;
 			SSetting.Mins=Mins;
 			SSetting.Secs=Secs;    
 			SSetting.Temperature=Temperature;
 			SSetting.Voltage=Voltage;
 			SSetting.Stressmode=Stressmode;
 		}
	}
	DBDeactivateSQL(hstmt);  
	
}

void R_Setting(char *MeasurementName,int flag){
	int hstmt;
	char SQLSTR[500];
	int rescode;
	char Name[20];
	double Current,Rate;
	int Times;
	int sta,i;
	short Read_Gain_Val[8];
	int ReadGain;
	double H_Field;          //Sung modified 05/02/02  
	double CoilGain;	     //Sung modified 05/02/02 
	
	Read_Gain_Val[0]=-1;
	Read_Gain_Val[1]=1;
	Read_Gain_Val[2]=2;
	Read_Gain_Val[3]=5;
	Read_Gain_Val[4]=10;
	Read_Gain_Val[5]=20;
	Read_Gain_Val[6]=50;
	Read_Gain_Val[7]=100;
	
	strcpy(SQLSTR,	"select * from RSetting where Name = '"); 					   
	strcat(SQLSTR,MeasurementName);
	strcat(SQLSTR,"'");	
	hstmt = DBActivateSQL(hdbc,SQLSTR);
	
	DBBindColChar (hstmt, 1, 20, Name, &sta, "");
	DBBindColDouble (hstmt, 2, &Current, &sta);
	DBBindColDouble (hstmt, 3, &Rate, &sta);
	DBBindColInt (hstmt, 4, &Times, &sta);
	DBBindColInt (hstmt, 5, &ReadGain, &sta);
	DBBindColDouble (hstmt, 6, &H_Field, &sta);    //Sung modified 05/02/02
	DBBindColDouble (hstmt, 7, &CoilGain, &sta);   //Sung modified 05/02/02   
	
	
	
	for (i=0;i<8;i++){
		if(Read_Gain_Val[i]==ReadGain){
			break;
		}
	}
	if((rescode = DBFetchNext(hstmt))==DB_SUCCESS){
		if(flag==1){
	 		ResetTextBox(H_RSetting,RSETTING_NAME,Name);
			SetCtrlVal(H_RSetting,RSETTING_CURRENT,Current);
			SetCtrlVal(H_RSetting,RSETTING_RATE,Rate);
			SetCtrlVal(H_RSetting,RSETTING_TIMES,Times);
			SetCtrlVal(H_RSetting,RSETTING_READGAIN,i);
			SetCtrlVal(H_RSetting,RSETTING_HFIELD,H_Field);      //Sung modified 05/02/02 
			SetCtrlVal(H_RSetting,RSETTING_COILGAIN,CoilGain);	 //Sung modified 05/02/02 
			DisplayPanel(H_RSetting);
			HidePanel(H_SetMenu);
		}else{
			strcpy(RSetting.Name,Name);
			RSetting.Current=Current;
			
			RSetting.Rate=Rate;
			RSetting.Times=Times;
			RSetting.ReadGain=ReadGain;
			RSetting.H_Field=H_Field;	      //Sung modified 05/02/02
			RSetting.CoilGain=CoilGain;       //Sung modified 05/02/02
		}
	}
	DBDeactivateSQL(hstmt);  
	
}

void RH_Setting(char *MeasurementName,int flag){
	int hstmt;
	char SQLSTR[500];
	int rescode;
	char Name[20];
	double Voltage,Rate,CmplCurr,H_Field,Coil_Gain, RefCurr;
	int Step_Num,Cycle_Num,Init_Dir;
	int sta,i;
	short Read_Gain_Val[8];
	int ReadGain;
	
	Read_Gain_Val[0]=-1;
	Read_Gain_Val[1]=1;
	Read_Gain_Val[2]=2;
	Read_Gain_Val[3]=5;
	Read_Gain_Val[4]=10;
	Read_Gain_Val[5]=20;
	Read_Gain_Val[6]=50;
	Read_Gain_Val[7]=100;
	
	strcpy(SQLSTR,	"select * from RHSetting where Name = '"); 					   
	strcat(SQLSTR,MeasurementName);
	strcat(SQLSTR,"'");	
	hstmt = DBActivateSQL(hdbc,SQLSTR);
	
	DBBindColChar (hstmt, 1, 20, Name, &sta, "");
	DBBindColDouble (hstmt, 2, &Voltage, &sta);
	DBBindColDouble (hstmt, 3, &CmplCurr, &sta);
	DBBindColDouble (hstmt, 4, &H_Field, &sta);
	DBBindColInt (hstmt, 5, &Step_Num, &sta);
	DBBindColDouble (hstmt, 6, &Coil_Gain, &sta);
	DBBindColDouble (hstmt, 7, &Rate, &sta);
	DBBindColInt (hstmt, 8, &Cycle_Num, &sta);
	DBBindColInt (hstmt, 9, &Init_Dir, &sta);
	DBBindColInt (hstmt, 10, &ReadGain, &sta);
	DBBindColDouble (hstmt, 11, &RefCurr, &sta);      
	
	if((rescode = DBFetchNext(hstmt))==DB_SUCCESS){
		if(flag==1){
	 		ResetTextBox(H_RHSetting,RHSETTING_NAME,Name);
			SetCtrlVal(H_RHSetting,RHSETTING_VOLTAGE,Voltage);
			SetCtrlVal(H_RHSetting,RHSETTING_CMPLCURR,CmplCurr);
			SetCtrlVal(H_RHSetting,RHSETTING_HFIELD,H_Field); 
			SetCtrlVal(H_RHSetting,RHSETTING_NUMSTEP,Step_Num);
			SetCtrlVal(H_RHSetting,RHSETTING_COILGAIN,Coil_Gain);
			SetCtrlVal(H_RHSetting,RHSETTING_RATE,Rate);	   
			SetCtrlVal(H_RHSetting,RHSETTING_NUMCYCLE,Cycle_Num);
			SetCtrlVal(H_RHSetting,RHSETTING_INITDIR,Init_Dir);
			SetCtrlVal(H_RHSetting,RHSETTING_REFI,RefCurr);     
			
			
			for(i=0;i<8;i++){
				if(ReadGain==Read_Gain_Val[i]){
					break;
				}
			}
			SetCtrlVal(H_RHSetting,RHSETTING_READGAIN,i);
			DisplayPanel(H_RHSetting);
			HidePanel(H_SetMenu);
		}else{
			strcpy(RHSetting.Name,Name);
			RHSetting.Voltage=Voltage;
 			RHSetting.CmplCurr=CmplCurr;
 			RHSetting.H_Field=H_Field;
 			RHSetting.StepNum=Step_Num;
 			RHSetting.CoilGain=Coil_Gain;
 			RHSetting.Rate=Rate;
 			RHSetting.CycleNum=Cycle_Num;
 			RHSetting.InitDir=Init_Dir;
 			RHSetting.ReadGain=ReadGain;
 			RHSetting.RefCurr=RefCurr;    
 		}
	}
	DBDeactivateSQL(hstmt);  
}
	
int CVICALLBACK ModifyTheMeasurement (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int MeasurementVal;
	int MeasurementIndex;
	char MeasurementName[20];
	
	switch (event)
		{
		case EVENT_LEFT_DOUBLE_CLICK:
		case EVENT_COMMIT:
			GetCtrlVal(panel,SETMENU_MEASUREMENTLIST,&MeasurementVal);
  			GetIndexFromValue(panel,SETMENU_MEASUREMENTLIST,&MeasurementIndex,MeasurementVal);
  			GetLabelFromIndex(panel,SETMENU_MEASUREMENTLIST,MeasurementIndex,MeasurementName);
  			if(MeasurementName[0]=='L')
  				L_Setting(MeasurementName,1);
  			else if(MeasurementName[0]=='S')
  				S_Setting(MeasurementName,1);
  			else if(MeasurementName[1]=='H' && MeasurementName[0]=='R')
  				RH_Setting(MeasurementName,1);
  			else
  				R_Setting(MeasurementName,1);
			break;
		}
		
	return 0;
}




void Save_R(double CurrentR[],double DiffR[],int index,char *Wafer,char *Row){
int i;
char File_Path[100];
FILE* fp;
char CurrDateTime[30];

	strcpy(File_Path, "c:\\testdata\\r_data\\");
	strcat(File_Path,Wafer);
	strcat(File_Path,".res");
	if((fp=fopen(File_Path,"r"))==NULL){
		fp = fopen(File_Path,"w+");
		//Sung modified 05/02/02 (Added "HField")
		fprintf(fp,"Wafer,Row,DateTime,HField, Current,StressedTime,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R,Dev,R\n");
	}else{
		fclose(fp);
		fp = fopen(File_Path,"a+");
	}
	strcpy(CurrDateTime,DateStr());
	strcat(CurrDateTime," ");
	strcat(CurrDateTime,TimeStr());
	//Sung modified 05/02/02 (Added "%.2f" and "RSetting.H_Field")  
	fprintf(fp,"%s,%s,%s,%.2f,%.3f,%.3f",Wafer,Row,CurrDateTime,RSetting.H_Field,RSetting.Current,Acc_STime);
	for(i=0;i<16;i++){
		fprintf(fp,",%s,%.3f",Devices.Name[i],CurrentR[i]);
	}
	fprintf(fp,"\n");
	fclose(fp);
}

void Save_RH_Sum(double TAA[],double ASYM[],double T_Diff[],double A_Diff[],char *Wafer,
				char *Row, char *MeasurementName)
{
	int i;
	char File_Path[100];
	FILE* fp;
	char CurrDateTime[30];
	char temp[1000];

	strcpy(File_Path, "c:\\testdata\\rh_data\\");
	strcat(File_Path,Wafer);
	strcat(File_Path,"-");
	strcat(File_Path,MeasurementName);
	strcat(File_Path,".sum");
	if((fp=fopen(File_Path,"r"))==NULL){
		fp = fopen(File_Path,"w+");
		strcpy(temp,"Wafer,Row,DateTime,StressedTime,Temperature,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff");
		strcat(temp,",Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff");
		strcat(temp,",Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff,Dev,TAA,TAA_Diff,ASYM,ASYM_Diff");
		
		fprintf(fp,"%s\n",temp);
		//fprintf(fp,"Wafer,Row,DateTime,DeviceName,StressedTime,TAA,TAA_Diff,ASYM,ASYM_Diff\n");
	}else{
		fclose(fp);
		fp = fopen(File_Path,"a+");
	}
	strcpy(CurrDateTime,DateStr());
	strcat(CurrDateTime," ");
	strcat(CurrDateTime,TimeStr());
	fprintf(fp,"%s,%s,%s,%.3f,%.3f",Wafer,Row,CurrDateTime,Acc_STime,SSetting.Temperature);
	for(i=0;i<16;i++){
		fprintf(fp,",%s,%.3f,%.3f,%.3f,%.3f",Devices.Name[i],TAA[i],T_Diff[i],ASYM[i],A_Diff[i]);
	}						
	fprintf(fp,"\n");
	fclose(fp);
}

void DisplayR_TAA_ASYM(int index,double *Previous,double *Current,int flag){
static double RX_Val;
static double TAAX_Val;
static double ASYMX_Val;
static double TAADIFFX_Val;
double Previous_X;
double X_Val;
int style[16];
int color[16];
int i;
time_t Curr_Time;
double Elp_Seconds;
int panel,ctrl;

	style[0]= VAL_SOLID_CIRCLE;
	style[1]= VAL_SOLID_CIRCLE;
	style[2]= VAL_SOLID_CIRCLE;
	style[3]= VAL_SOLID_CIRCLE;
	style[4]= VAL_SOLID_CIRCLE;
	style[5]= VAL_SOLID_CIRCLE;
	style[6]= VAL_ASTERISK;
	style[7]= VAL_ASTERISK;
	style[8]= VAL_ASTERISK;
	style[9]= VAL_ASTERISK;
	style[10]= VAL_ASTERISK;
	style[11]= VAL_ASTERISK;
	style[12]= VAL_SOLID_DIAMOND;
	style[13]= VAL_SOLID_DIAMOND;
	style[14]= VAL_SOLID_DIAMOND;
	style[15]= VAL_SOLID_DIAMOND;
	
	color[0]= VAL_DK_RED;
	color[1]= VAL_DK_BLUE;
	color[2]= VAL_DK_GREEN;
	color[3]= VAL_DK_CYAN;
	color[4]= VAL_DK_MAGENTA;
	color[5]= VAL_DK_YELLOW;
	color[6]= VAL_DK_RED;
	color[7]= VAL_DK_BLUE;
	color[8]= VAL_DK_GREEN;
	color[9]= VAL_DK_CYAN;
	color[10]= VAL_DK_MAGENTA;
	color[11]= VAL_DK_YELLOW;
	color[12]= VAL_DK_RED;
	color[13]= VAL_DK_BLUE;
	color[14]= VAL_DK_GREEN;
	color[15]= VAL_DK_CYAN;
	time(&Curr_Time);  
	Elp_Seconds = difftime(Curr_Time,Start_Time);      
	if(flag==1){	
		panel=H_RCurve;
		ctrl = RTIME_GRAPH;
		Previous_X = RX_Val;
		if(index!=0)
			RX_Val=Elp_Seconds/60;
	}else if(flag==2){
		panel=H_TaaCurve;
		ctrl = TAATIME_GRAPH;
		Previous_X = TAAX_Val;
		if(index!=0)
			TAAX_Val=Elp_Seconds/60;
	}else if (flag==3){
		panel=H_AsymCurve;
		ctrl = ASYMTIME_GRAPH;
		Previous_X = ASYMX_Val;
		if(index!=0)
			ASYMX_Val=Elp_Seconds/60;
	}else {
		panel=H_TAADiff;
		ctrl = TAADIFF_GRAPH;
		Previous_X = TAADIFFX_Val;
		if(index!=0)
			TAADIFFX_Val=Elp_Seconds/60;
	}
	if(index==0){
		for(i=0;i<16;i++){
			if(Devices.IsBlocked[i]!=1)
				PlotPoint(panel,ctrl,0,Current[i],style[i],color[i]);
		}
	}
	else{
		//X_Val=log(Elp_Seconds/60);
		X_Val=Elp_Seconds/60;		
		for(i=0;i<16;i++){
			if(Devices.IsBlocked[i]!=1){
				PlotPoint(panel,ctrl,X_Val,Current[i],style[i],color[i]);
				PlotLine (panel, ctrl, Previous_X, Previous[i], X_Val,Current[i], color[i]);		
			}
		}		
	}
}
void Display_RH(double *Read_V[],double Read_F[]){
 int i,j;
	for (i=0;i<16;i++){
		for (j=0;j<RHSetting.StepNum;j++){
			DeleteGraphPlot(H_RHCurve, RHCURVE_GRAPH_CH1+i, -1, 1);       
			PlotXY (H_RHCurve, RHCURVE_GRAPH_CH1+i, Read_F, Read_V[i],
		        RHSetting.StepNum, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE,
        		VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
        }
    }
}


void R_Testing(int index,char * Wafer, char *Row){
	short Board;
	static double R0[20];
	int i;
	static double CurrentR[20];
	double PreviousR[20];
	double RFail;
	int RFailCheck;
	double DiffR[20];
	short ReadBuf[2000];
	double VReadBuf[2000];
	int ret;
	double V_KEPCO;	                                  //Sung modified 05/02/02
	
	
	for (i=0;i<16;i++){     
					AO_VWrite(3,16+i,0);  
					Delay(0.01);
					}

	for (i=0;i<16;i++){     
					AO_VWrite(4,16+i,0);  
					Delay(0.01);
					}
	
	
	for (i=0;i<16;i++){     
					AO_VWrite(1,i,0);  
					Delay(0.01);
					}
					


	
	//Modification for applying Const H_Field for R Test
	V_KEPCO=RSetting.H_Field/RSetting.CoilGain;	         //Sung modified 05/02/02
	AO_VWrite(2,0,V_KEPCO);
	Delay (0.1);									     //Sung modified 05/02/02
													     //Sung modified 05/02/02
	
	for(i=0;i<16;i++){									 //Sung 9-18-03
				GetCtrlVal(H_MainWin,MAINMENU_CH1+i,&Devices.IsBlocked[i]);
		}
	
	
	for (i=0;i<16;i++){
		PreviousR[i] = CurrentR[i];		
		if(Devices.IsBlocked[i]!=1){
			AO_VWrite(1,16+i,RSetting.Current);
			Delay(0.1);			//ctlin 6-19-00					
			if(i<=7){
				//AI_VRead(2,i,RSetting.ReadGain,&CurrentR[i]);
				ret = DAQ_Start (2, i, RSetting.ReadGain, ReadBuf, 2000, 1, 10);
				
				Delay(0.025);
				ret = DAQ_VScale (2, i, RSetting.ReadGain, 1.0, 0.0, 2000, ReadBuf, VReadBuf);
			}
			else{
				//AI_VRead(2,8+i,RSetting.ReadGain,&CurrentR[i]);				
				DAQ_Start (2, 8+i, RSetting.ReadGain, ReadBuf, 2000, 1, 10);
				
				Delay(0.025);
				DAQ_VScale (2, 8+i, RSetting.ReadGain, 1.0, 0.0, 2000, ReadBuf, VReadBuf);
			}
			
			Mean (VReadBuf, 2000,&CurrentR[i]);
			DAQ_Clear(2);
			CurrentR[i] = 1000*CurrentR[i]/RSetting.Current;	
//			AO_VWrite(1,16+i,0);					sung Aug 03
			
			if (CurrentR[i]<1 || CurrentR[i]>50000)
			   			{Devices.IsBlocked[i]=1; 
						 SetCtrlVal(H_MainWin,MAINMENU_CH1+i,1);
						 AO_VWrite(1,16+i,0); 		  // if blocked set current zero	  9/18/03 sung  
			 			 Delay(0.1);
			 			}
			 			
			
			if(index>0){
				GetCtrlVal(H_MainWin,MAINMENU_RFAIL, &RFail);

				GetCtrlVal(H_MainWin,MAINMENU_RFAILCHECK, &RFailCheck);
				if(RFailCheck==1 && (DiffR[i]=fabs(CurrentR[i]-R0[i])/R0[i])>(0.01*RFail)){ //ctlin 6-27-00
					Devices.IsBlocked[i]=1;
					SetCtrlVal(H_MainWin,MAINMENU_CH1+i,1);
				}
			}else{								   //if First R measurement
				DiffR[i]=0;
				R0[i]=CurrentR[i];
			}
			AO_VWrite(1,16+i,0);		//reseting
		}
		else{
			CurrentR[i]=-9999;			  // if device is blocked   
			DiffR[i]=0;
			AO_VWrite(1,16+i,0); 		  // if blocked set current zero	  9/18/03 sung   
			Delay(0.1);
		}
	}
	Save_R(CurrentR,DiffR,index,Wafer,Row);
	DisplayR_TAA_ASYM(index,PreviousR,CurrentR,1);
    AO_VWrite(2,0,0);		                            //Sung modified 05/02/02
    Delay(0.1);											//Sung modified 05/02/02  off Kepco
}

double Cal_Voltage_Field(int F_Volt, int fieldDirection)
{
	//F_Volt is i pass in as step, field_Gain is magnetic field gain
	
	int qurt;
	double v_field, field, step,v;
	
	
	v = RHSetting.H_Field/ RHSetting.CoilGain;
		
	switch (fieldDirection)
	{
		case 0:
			v_field = v * (sin((F_Volt) * 6.283185307/(RHSetting.StepNum)+1.5708));   
			break;
		case 1:
			v_field = v * (cos((F_Volt) * 6.283185307/(RHSetting.StepNum)+1.5708)); 
			break;
		case 2:
			v_field = v * ((-1)*sin((F_Volt) * 6.283185307/(RHSetting.StepNum)+1.5708)); 
			break;
		case 3:
			v_field = v * ((-1)*cos((F_Volt) * 6.283185307/(RHSetting.StepNum)+1.5708)); 
			break;
	    default :
	    	v_field = v * (sin((F_Volt) * 6.283185307/(RHSetting.StepNum)+1.5708));  
	    	break;
	}	
	return v_field;
	
}	

void Save_RH(double *Read_V[],double Read_F[],char *Wafer,char *Row,
			char *MeasurementName)
{    
  	int i;
	char File_Path[100];
	FILE* fp;
	char CurrDateTime[30];
	int j;
	
	//TAA = (max(read_V)-min(Read_V))/RHSetting.Current;
	
	strcpy(File_Path, "c:\\testdata\\rh_data\\");
	strcat(File_Path,Wafer);
	strcat(File_Path,"-");
	
	strcat(File_Path,MeasurementName);
	strcat(File_Path,".dat");
	if((fp=fopen(File_Path,"r"))==NULL){
		fp = fopen(File_Path,"w+");
		fprintf(fp,"Wafer,Row,DateTime,Voltage,Field,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val,Dev,Val\n");
	}else{
		fclose(fp);
		fp = fopen(File_Path,"a+");
	}
	strcpy(CurrDateTime,DateStr());
	strcat(CurrDateTime," ");
	strcat(CurrDateTime,TimeStr());
	
	for(j=0;j<RHSetting.StepNum;j++){
		fprintf(fp,"%s,%s,%s,%.3f,%.3f",Wafer,Row,CurrDateTime,RHSetting.Voltage,Read_F[j]);
		for(i=0;i<16;i++){
			fprintf(fp,",%s,%f",Devices.Name[i],Read_V[i][j]);		
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

//Sung added parameter H_dir for CapPara function and modified the 
//formula for getting Asymmetry values
//05/03/02     Version 1.1.2
void CalPara(double V[],double *TAA_Val,double *ASYM_Val,int H_dir){	
	double V_zeroF;                //voltage(resistance) at 0 H_Field
	double max,min;
	int max_ind,min_ind;
	
	MaxMin1D (V, RHSetting.StepNum, &max, &max_ind, &min, &min_ind);
	
	// TAA equals peak to peak voltage
	*TAA_Val = (max-min);
	
	switch (H_dir)
	{
		case 0: case 2:
		    V_zeroF= (V[RHSetting.StepNum/4] + V[RHSetting.StepNum*3/4])/2;    
		case 1: case 3:
			V_zeroF= (V[0]+V[RHSetting.StepNum/2] + V[RHSetting.StepNum-1])/3; 
		default:
			V_zeroF= (V[RHSetting.StepNum/4] + V[RHSetting.StepNum*3/4])/2; 
	}
           
	*ASYM_Val =100 *(((max-V_zeroF)-(V_zeroF-min))/(max-min));
		
}


void RH_Testing(int index,char * Wafer, char *Row){
	static double TAA[20];
	static double ASYM[20];
	int i,sign;
	static double CurrentTAA[20];
	static double CurrentASYM[20];
	static double CurrentT_Diff[20];     //Ver. 1.1.3
	double PreviousTAA[20];
	double PreviousASYM[20];
	double PreviousT_Diff[20];           //Ver. 1.1.3
	double TAAFail;
	double ASYMFail;
	int TAAFailCheck;
	int ASYMFailCheck;
	double T_Diff[20];
	double A_Diff[20];
	double *Read_V[16];
	double *Read_F;
	short Temp_V[2000];
	double VReadBuf[2000];
	double Temp_M;
	int j,k,l;
	double v_h;
	double TAA_Val[20];
	double ASYM_Val[20];
	double RHCurrent[20];	 //ver2.2
	FILE *fp;

	
   //This is to measure R values for calculating "Pseudo Const. V"
	 
	short Board;
	static double R0[20];
	//int i;
	static double CurrentR[20];
	//double PreviousR[20];
	double RFail;
	int RFailCheck;
	double DiffR[20];
	short ReadBuf[2000];
	//double VReadBuf[2000];
	int ret;
	//double V_KEPCO;	                                  //Sung modified 05/02/02
	
	//Modification for applying Const H_Field for R Test
	//V_KEPCO=RSetting.H_Field/RSetting.CoilGain;	         //Sung modified 05/02/02
	//AO_VWrite(2,0,V_KEPCO);
	//Delay (0.1);									     //Sung modified 05/02/02
													     //Sung modified 05/02/02
	
	for(i=0;i<16;i++){									 //Sung 9-18-03
				GetCtrlVal(H_MainWin,MAINMENU_CH1+i,&Devices.IsBlocked[i]);
		}
	
	
	for (i=0;i<16;i++){
		//PreviousR[i] = CurrentR[i];		
		if(Devices.IsBlocked[i]!=1){
			AO_VWrite(1,16+i,RHSetting.RefCurr);
			Delay(0.1);			//ctlin 6-19-00					
			if(i<=7){
				//AI_VRead(2,i,RSetting.ReadGain,&CurrentR[i]);
				ret = DAQ_Start (2, i, RSetting.ReadGain, ReadBuf, 2000, 1, 10);
				
				Delay(0.025);
				ret = DAQ_VScale (2, i, RSetting.ReadGain, 1.0, 0.0, 2000, ReadBuf, VReadBuf);
			}
			else{
				//AI_VRead(2,8+i,RSetting.ReadGain,&CurrentR[i]);				
				DAQ_Start (2, 8+i, RSetting.ReadGain, ReadBuf, 2000, 1, 10);
				
				Delay(0.025);
				DAQ_VScale (2, 8+i, RSetting.ReadGain, 1.0, 0.0, 2000, ReadBuf, VReadBuf);
			}
			
			Mean (VReadBuf, 2000,&CurrentR[i]);
			DAQ_Clear(2);
			CurrentR[i] = 1000*CurrentR[i]/RHSetting.RefCurr;	
//			AO_VWrite(1,16+i,0);					sung Aug 03
			
			if (CurrentR[i]>999 || CurrentR[i]<1)
			   			{Devices.IsBlocked[i]=1; 
						 SetCtrlVal(H_MainWin,MAINMENU_CH1+i,1);
						 AO_VWrite(1,16+i,0); 		  // if blocked set current zero	  9/18/03 sung  
			 			 Delay(0.1);
			 			}
			 			
			
		
			//AO_VWrite(1,16+i,0);		//reseting
		}
		else{
			CurrentR[i]=-9999;			  // if device is blocked   
		//	DiffR[i]=0;
			AO_VWrite(1,16+i,0); 		  // if blocked set current zero	  9/18/03 sung   
			Delay(0.1);
		}
	}
	//Save_R(CurrentR,DiffR,index,Wafer,Row);
	//DisplayR_TAA_ASYM(index,PreviousR,CurrentR,1);
    //AO_VWrite(2,0,0);		                            //Sung modified 05/02/02
    Delay(0.1);											//Sung modified 05/02/02  off Kepco


	// Print the current time to a file
	// fp = fopen("c:\\testdata\\temptime.txt","a");
	// fprintf(fp,"%s,",TimeStr());			   
	
	//Turn on the bias current	
	for (i=0;i<16;i++){
		if(Devices.IsBlocked[i]!=1){  
		    RHCurrent[i]=RHSetting.Voltage/CurrentR[i]/1000;
			AO_VWrite(1,16+i,RHCurrent[i]);
			Delay(0.01);
		}
		Read_V[i] = (double *)calloc((RHSetting.StepNum+1), sizeof(double ));
	}
	Read_F = (double *)calloc((RHSetting.StepNum+1), sizeof(double ));
	
	Delay(1.0);				//ctlin 6-19-00 Soaking
	
	// Decide field sweep direction
	
	if(OddRow==1)
		sign=1;
	else
		sign=-1;
		
	//loop cycle and field steps
	for (j=0;j<RHSetting.CycleNum;j++){
		for(k=0;k<RHSetting.StepNum;k++){
			v_h = Cal_Voltage_Field(k, RHSetting.InitDir) ;
			Read_F[k] = v_h * RHSetting.CoilGain;
			AO_VWrite(2,0,sign * v_h);
			Delay(0.1);		//ctlin 6-19-00
			
			//Measure 16 channels
			for (i=0;i<16;i++){
				if(Devices.IsBlocked[i]!=1){
					if(i<=7){
						DAQ_Start (2, i, RHSetting.ReadGain, Temp_V, 2000, 1, 10);
						Delay(0.025);
						DAQ_VScale (2, i, RHSetting.ReadGain, 1.0, 0.0, 2000, Temp_V, VReadBuf);	
					}
					else{
						DAQ_Start (2, 8+i, RHSetting.ReadGain, Temp_V, 2000, 1, 10);
						Delay(0.025);
						DAQ_VScale (2, 8+i, RHSetting.ReadGain, 1.0, 0.0, 2000, Temp_V, VReadBuf);	
					}
					Mean(VReadBuf,2000,&Temp_M);
					DAQ_Clear(2);
					Temp_M *= 1000;
					Read_V[i][k]+=Temp_M;
				}
				else{
					Read_V[i][k]=-9999;
				}
			}
		}
	}
	
	// Turn off field voltage
	AO_VWrite(2,0,0);
	Delay(0.01);
	
	// Turn off bias current
	
	//for (i=0;i<16;i++){
	//	if(Devices.IsBlocked[i]!=1){
	//		AO_VWrite(1,16+i,0);
	//		Delay(0.01);
	//	}
	//}
	
	// Print the end time of the above process
	
	// fprintf(fp,"%s\n",TimeStr());
	// fclose(fp);
	
	// Average over cycled times
	
	for(k=0;k<RHSetting.StepNum;k++){
		for (i=0;i<16;i++){
			Read_V[i][k] /=RHSetting.CycleNum;
		}
	}					
	
	// Calculate TAA ASYM and their variations
	for(i=0;i<16;i++){
		PreviousTAA[i] = CurrentTAA[i];
		PreviousASYM[i] = CurrentASYM[i];
		PreviousT_Diff[i]=CurrentT_Diff[i];            //Ver 1.1.3
		
		if(Devices.IsBlocked[i]!=1){    		
			CalPara(Read_V[i],&TAA_Val[i],&ASYM_Val[i],RHSetting.InitDir);  //Sung added the last argument(.InitDir)
			CurrentTAA[i] = TAA_Val[i];										//InitDir 05/03/02 ver1.1.2
			CurrentASYM[i] = ASYM_Val[i];
			if(index>0){												    //if index>0
				GetCtrlVal(H_MainWin,MAINMENU_TAAFAIL, &TAAFail);
				GetCtrlVal(H_MainWin,MAINMENU_TAAFAILCHECK, &TAAFailCheck);
				T_Diff[i]=(TAA_Val[i]-TAA[i])/TAA[i];						//Definition of T_Diff 
				CurrentT_Diff[i]=T_Diff[i];
				if(TAAFailCheck==1 && fabs(T_Diff[i])>(0.01*TAAFail)){ //ctlin 6-27-00
					Devices.IsBlocked[i]=1;
					SetCtrlVal(H_MainWin,MAINMENU_CH1+i,1);
				}
				GetCtrlVal(H_MainWin,MAINMENU_ASYMFAIL, &ASYMFail);
				GetCtrlVal(H_MainWin,MAINMENU_ASYMFAILCHECK, &ASYMFailCheck);
				A_Diff[i]=(ASYM_Val[i]-ASYM[i])/ASYM[i];
				if(ASYMFailCheck ==1 && fabs(A_Diff[i])>(0.01*ASYMFail)){ //ctlin 6-27-00
					Devices.IsBlocked[i]=1;
					SetCtrlVal(H_MainWin,MAINMENU_CH1+i,1);
				}   
			}else{
				TAA[i]=TAA_Val[i];                                             //index=0
				ASYM[i]=ASYM_Val[i];
				T_Diff[i]=0;
				A_Diff[i]=0;
				CurrentT_Diff[i]=0;                                             //*****Inserted later 2003
			}
		}else{
			TAA_Val[i]=-9999;
			ASYM_Val[i]=-9999;
			T_Diff[i]=0;
			A_Diff[i]=0;														   
			
		}
	}
	Save_RH(Read_V,Read_F,Wafer,Row,RHSetting.Name);
	Save_RH_Sum(TAA_Val,ASYM_Val,T_Diff,A_Diff,Wafer,Row,RHSetting.Name);
	
	Display_RH(Read_V,Read_F);
	DisplayR_TAA_ASYM(index,PreviousTAA,CurrentTAA,2);
	DisplayR_TAA_ASYM(index,PreviousASYM,CurrentASYM,3);
    DisplayR_TAA_ASYM(index,PreviousT_Diff,CurrentT_Diff,4);
	
	for (i=0;i<16;i++){
		free(Read_V[i]);
	}					
	free(Read_F);
}																						  



int CVICALLBACK GetColdR (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	short Board;

	int i;
	double CurrentRs[20];
	short ReadBuf[2000];
	double VReadBuf[2000];
	int ret;
	double R_measure_current = 0.1;
	const int Gain=10;   //Gain value for DAQ_XXX function
	
	int k;
	char WaferName[20];
	char Row[20];
	char File_Path[100];
	FILE* fp;
	char CurrDateTime[30];
	
	switch (event)
		{
		case EVENT_COMMIT:
		
	GetCtrlVal(H_MainWin,MAINMENU_NAME,WaferName);
   	GetCtrlVal(H_MainWin,MAINMENU_ROWNAME,Row);
   			
	for(i=0;i<16;i++){
				GetCtrlVal(H_MainWin,MAINMENU_CH1+i,&Devices.IsBlocked[i]);
	}
			
	
	if(strlen(WaferName)==0 || strlen(Row)==0){
				MessagePopup("In Situ RH Testing","Please complete the input");
				break;
			}
	
		
			 //Get Cold Resistance values for const. J   // RSetting.ReadGain=10 for DAQ_Stare, DAQ_...funtins Sung 07/23/03           
	for (i=0;i<16;i++)
			{
			if(Devices.IsBlocked[i]!=1)
				{
				AO_VWrite(1,16+i,R_measure_current);
				Delay(0.1);			//ctlin 6-19-00					
				if(i<=7)
				  
					{
					ret = DAQ_Start (2, i, Gain, ReadBuf, 2000, 1, 10);	   //For open error Sung
					
					Delay(0.025);
					ret = DAQ_VScale (2, i, Gain, 1.0, 0.0, 2000, ReadBuf, VReadBuf);
					}
				else
					{
					DAQ_Start (2, 8+i, Gain, ReadBuf, 2000, 1, 10);
					
		
							  
					Delay(0.025);
					DAQ_VScale (2, 8+i, Gain, 1.0, 0.0, 2000, ReadBuf, VReadBuf);
					}
			   
			
				Mean (VReadBuf, 2000,&CurrentRs[i]);
				DAQ_Clear(2);
				ColdR[i] = 1000*CurrentRs[i]/R_measure_current;	
				AO_VWrite(1,16+i,0);                               //Set Out=0A   sung Aug 03
			
				if (ColdR[i]<1)					//Block the Resistace <1ohm
			   			{Devices.IsBlocked[i]=1; 
						 SetCtrlVal(H_MainWin,MAINMENU_CH1+i,1);
			 			}
				}
				
			else
			    {
				ColdR[i] = -9999;
				AO_VWrite(1,16+i,0); 		  // if blocked set current zero	  9/18/03 sung 
			    Delay(0.1);
			    }
				   
		SetCtrlVal(H_ViewColdR,VIEWCOLDR_R_1-i,ColdR[i]);  //VIEWCOLDR_R_1-i : As R_1 has larger controlID integer value
														   //                 than R_2, and so on  (Defined in header file)
	
			 }																	  

	strcpy(File_Path, "c:\\testdata\\r_data\\");
	strcat(File_Path,WaferName);
	strcat(File_Path,"_");
	strcat(File_Path,Row);  							
	strcat(File_Path,"_Cold");   
	strcat(File_Path,".res");
	
	if((fp=fopen(File_Path,"r"))==NULL){
		fp = fopen(File_Path,"w+");
	}else{
		fclose(fp);
		fp = fopen(File_Path,"a+");
	}
	strcpy(CurrDateTime,DateStr());
	strcat(CurrDateTime," ");
	strcat(CurrDateTime,TimeStr());
	
		
	strcpy(CurrDateTime,DateStr());
	strcat(CurrDateTime," ");
	strcat(CurrDateTime,TimeStr());
	
	fprintf(fp,"%s",CurrDateTime);
	
	
	
	//Save Cold Resistance
	for(k=0;k<16;k++){
		fprintf(fp,",%s,%.3f",Devices.Name[k],ColdR[k]);
	}
	fprintf(fp,"\n");
	
	fclose(fp);
	
	DisplayPanel(H_ViewColdR);

			break;
		}
	return 0;
}


// To get Vheat value for const current density stress test 7/22/03
// To get the value of current density 
int CVICALLBACK S_GetVHeat (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{	

	int i,k;
	char WaferName[20];
	char Row[20];
	char File_Path[100];
	FILE* fp;
	char CurrDateTime[30];
	
	switch (event)
		{
		case EVENT_COMMIT:

	GetCtrlVal(H_SSetting,SSETTING_LEADR,&LeadR);
	GetCtrlVal(H_SSetting,SSETTING_TDESIRED,&T);
	GetCtrlVal(H_SSetting,SSETTING_FITA,&A);
	GetCtrlVal(H_SSetting,SSETTING_FITB,&B);
	
	Vheat=(-B+sqrt(B*B+4*A*T))/(2*A);
	
	SetCtrlVal(H_SSetting,SSETTING_VHEAT,Vheat);
	
	
	
	 //Set CurrentForConstJ values   // RSetting.ReadGain=10 for DAQ_Stare, DAQ_...funtins Sung 07/23/03           
	for (i=0;i<16;i++)
			{
				VDevice[i]=Vheat/(ColdR[i]-LeadR)*ColdR[i];      //Define VDevice[]
				CurrentForConstJ[i]=VDevice[i]/ColdR[i];				 //Define CurrentForConstJ[]
														  
			}


    //Save The const courret density parameters	
	
    GetCtrlVal(H_MainWin,MAINMENU_NAME,WaferName);
	GetCtrlVal(H_MainWin,MAINMENU_ROWNAME,Row);
	
	if(strlen(WaferName)==0 || strlen(Row)==0){
				MessagePopup("In Situ RH Testing","Please complete the input");
				break;
			}
	
	strcpy(File_Path, "c:\\testdata\\r_data\\");
	strcat(File_Path,WaferName);
	strcat(File_Path,"_");
	strcat(File_Path,Row);  
	strcat(File_Path,".ccd");
	
	if((fp=fopen(File_Path,"r"))==NULL){
		fp = fopen(File_Path,"w+");
	}else{
		fclose(fp);
		fp = fopen(File_Path,"a+");
	}
	strcpy(CurrDateTime,DateStr());
	strcat(CurrDateTime," ");
	strcat(CurrDateTime,TimeStr());
	
	fprintf(fp,"%s,%s,%s,%s,%.2f,%s,%.4f,%s,%.4f,%s,%.2f,%s,%d",WaferName,Row,CurrDateTime,"LeadR",LeadR,"A",A,"B",B,"Vheat",Vheat,"T",T);
	fprintf(fp,"\n");
	//Save Resistance
	for(k=0;k<16;k++){
		fprintf(fp,",%s,%.3f",Devices.Name[k],ColdR[k]);
	}
	fprintf(fp,"\n");
	
	//Save VDevice[]
	for(k=0;k<16;k++){
		fprintf(fp,",%s,%.3f",Devices.Name[k],VDevice[k]);
	}
	fprintf(fp,"\n");
	
	//Save CurrentForConstJ[]
	for(k=0;k<16;k++){
		fprintf(fp,",%s,%.3f",Devices.Name[k],CurrentForConstJ[k]);
	}
	fprintf(fp,"\n");
	
	fclose(fp);
	
			break;
		}
	return 0;
}

int CVICALLBACK GetCurrForVTarget (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	double R0[20];
	int i;
	int j,k;
	static double CurrentR[20];
	static double CurrentV[20];
	short ReadBuf[2000];
	double VReadBuf[2000];
	int Gain;
	int ret;
	double MinR,MaxR,TargetV,CurrStep,StartCurrent;
	static double AppliedCurrent[20];

	char WaferName[20];
	char Row[20];
	char File_Path[100];
	FILE* fp;
	char CurrDateTime[30];

	Gain=5;

	switch (event)
		{
		case EVENT_COMMIT:
	
	
													     
	
	GetCtrlVal(H_SSetting,SSETTING_MINR,&MinR);
	GetCtrlVal(H_SSetting,SSETTING_MAXR,&MaxR);
	GetCtrlVal(H_SSetting,SSETTING_TARGETVOLT,&TargetV); 
	GetCtrlVal(H_SSetting,SSETTING_CURRSTEP,&CurrStep);   
	GetCtrlVal(H_SSetting,SSETTING_STARTCURRENT,&StartCurrent);  
	
	
    
	for(i=0;i<16;i++){									 //Sung 9-18-03
				GetCtrlVal(H_MainWin,MAINMENU_CH1+i,&Devices.IsBlocked[i]);
		}
	
	 j=0;                                  //Initialize j
	 
	for (i=0;i<16;i++){
			
		if(Devices.IsBlocked[i]!=1){
			
	      do {			//UNIT   ;;  TargetV:mV    CurrentV:V		START OF while loop
			
			
			AppliedCurrent[i]=StartCurrent+j*CurrStep;
			
			AO_VWrite(1,16+i,AppliedCurrent[i]);
			Delay(0.1);			//ctlin 6-19-00					
			if(i<=7){
				//AI_VRead(2,i,RSetting.ReadGain,&CurrentR[i]);
				ret = DAQ_Start (2, i, Gain, ReadBuf, 2000, 1, 10);
				
				Delay(0.025);
				ret = DAQ_VScale (2, i, Gain, 1.0, 0.0, 2000, ReadBuf, VReadBuf);
			}
			else{
				//AI_VRead(2,8+i,RSetting.ReadGain,&CurrentR[i]);				
				DAQ_Start (2, 8+i, Gain, ReadBuf, 2000, 1, 10);
				
				Delay(0.025);
				DAQ_VScale (2, 8+i, Gain, 1.0, 0.0, 2000, ReadBuf, VReadBuf);
			}
			
			Mean (VReadBuf, 2000,&CurrentV[i]);
			DAQ_Clear(2);
			CurrentR[i] = 1000*CurrentV[i]/AppliedCurrent[i];	
//			AO_VWrite(1,16+i,0);					sung Aug 03
			j=j+1; 
			
			if (CurrentR[i]<MinR || CurrentR[i]>MaxR  )
			   			{Devices.IsBlocked[i]=1; 
						 SetCtrlVal(H_MainWin,MAINMENU_CH1+i,1);
						 AO_VWrite(1,16+i,0); 		  // if blocked set current zero	  9/18/03 sung  
			 			 Delay(0.1);
			 			 break;
			 			}
			 	}		 while ((CurrentV[i]<(TargetV/1000)) && j<5000);   //End of do-while
		  
		  AO_VWrite(1,16+i,0);    //Set output 0mA after while loop 
		  SetCtrlVal(H_ViewColdR,VIEWCOLDR_R_1-i,CurrentR[i]);
		}
		
		else{							  // if device is blocked      
			CurrentR[i]=-9999;			  
			AO_VWrite(1,16+i,0); 		  // if blocked set current zero	  9/18/03 sung   
			Delay(0.1);
		}
	}
	
	
	
	for(i=0;i<16;i++){									 
				CurrentForConstJ[i]=AppliedCurrent[i];
	}
	
	DisplayPanel(H_ViewColdR);     

    //Saving Stress Current
    GetCtrlVal(H_MainWin,MAINMENU_NAME,WaferName);
	GetCtrlVal(H_MainWin,MAINMENU_ROWNAME,Row);
	
	if(strlen(WaferName)==0 || strlen(Row)==0){
				MessagePopup("In Situ RH Testing","Please complete the input");
				break;
			}
	
	strcpy(File_Path, "c:\\testdata\\r_data\\");
	strcat(File_Path,WaferName);
	strcat(File_Path,"_");
	strcat(File_Path,Row);  
	strcat(File_Path,".tgt");
	
	if((fp=fopen(File_Path,"r"))==NULL){
		fp = fopen(File_Path,"w+");
	}else{
		fclose(fp);
		fp = fopen(File_Path,"a+");
	}
	strcpy(CurrDateTime,DateStr());
	strcat(CurrDateTime," ");
	strcat(CurrDateTime,TimeStr());
	
	fprintf(fp,"%s,%s,%s",WaferName,Row,CurrDateTime);
	fprintf(fp,"\n");
	fprintf(fp,"%s,%.2f,%s,%.2f,%s,%.2f,%s,%.6f,%s,%6f","Target V",TargetV,"MinR",MinR,"MaxR",MaxR,"StepI",CurrStep,"StartI",StartCurrent);
	fprintf(fp,"\n");
	//Save Resistance
	for(k=0;k<16;k++){
		fprintf(fp,",%s,%.3f",Devices.Name[k],CurrentR[k]);
	}
	fprintf(fp,"\n");
	
	//Save VDevice[]
	for(k=0;k<16;k++){
		fprintf(fp,",%s,%.3f",Devices.Name[k],CurrentV[k]);
	}
	fprintf(fp,"\n");
	
	//Save CurrentForConstJ[]
	for(k=0;k<16;k++){
		fprintf(fp,",%s,%.6f",Devices.Name[k],CurrentForConstJ[k]);
	}
	fprintf(fp,"\n");
	
	fclose(fp);
			   


			break;
		}
	return 0;
}



void S_Testing()
{	
	int i;
	double CurrentRs[20];
	double Stresscurrent[20];
	short ReadBuf[2000];
	double VReadBuf[2000];
	int ret;
	double R_measure_current = 0.1;					      
	const int Gain=10;						                         //Gain value for DAQ_XXX funtions for Const V stress & Const Current Density Stress 
	
	   
	   	
	   	if(SSetting.Stressmode==5)                                     //Target VoltageMode for MRAM
	    {	
		 for (i=0;i<16;i++)
			{
			if(Devices.IsBlocked[i]!=1)
				{
			//	Stresscurrent[i]=CurrentForConstJ[i];
				AO_VWrite(1,16+i,CurrentForConstJ[i]);
				}					 
			}
		 time(&Stress_Time);	
	    }
	   	
	   	
	   	else if(SSetting.Stressmode==4)			                         //Individual Current Stress Mode  09-17-03
		{
		for (i=0;i<16;i++)
			{
			if(Devices.IsBlocked[i]!=1)
				{			
				AO_VWrite(1,16+i,IndVoltCurr[i]/3);
			 	AO_VWrite(3,16+i,IndVoltCurr[i]/3);  
				AO_VWrite(4,16+i,IndVoltCurr[i]/3);  
				
				}
			}   
     	time(&Stress_Time);	
     	}
	
	
		else if(SSetting.Stressmode==3)			                       //Individual Const Volt. Stress Mode  09-17-03
		{
		
		for (i=0;i<16;i++)
			{
		      AO_VWrite(3,16+i,CtrlCurr);
			  Delay(0.01);
			}
			
		Delay(0.1);
		
		for (i=0;i<16;i++)
			{
			if(Devices.IsBlocked[i]!=1)
				{
				AO_VWrite(1,16+i,IndVoltCurr[i]);
				}					 
			}
		time(&Stress_Time);	
		}
	
	
	
	
	else if(SSetting.Stressmode==2)                                     //const Current Density  Stress Mode
	{	
		for (i=0;i<16;i++)
			{
			if(Devices.IsBlocked[i]!=1)
				{
			//	Stresscurrent[i]=CurrentForConstJ[i];
				AO_VWrite(1,16+i,CurrentForConstJ[i]);
				}					 
			}
		time(&Stress_Time);	
	}
	
	else if(SSetting.Stressmode==1)			                       //Const Volt. Stress Mode
		{
		time(&Stress_Time);			
		
		for (i=0;i<16;i++)
			{
		      AO_VWrite(3,16+i,CtrlCurr);
			  Delay(0.01);
			}
			
		Delay(0.1);
		
		for (i=0;i<16;i++)
			{
			if(Devices.IsBlocked[i]!=1)
				{			
				AO_VWrite(1,i,SSetting.Voltage);
				}
			}   
		
		}
	else										                       //Const Current Stress Mode 
		{
		time(&Stress_Time);			
		for (i=0;i<16;i++)
			{
			if(Devices.IsBlocked[i]!=1)
				{			
				AO_VWrite(1,16+i,SSetting.Current/3);
				AO_VWrite(3,16+i,SSetting.Current/3); 
				AO_VWrite(4,16+i,SSetting.Current/3); 
				
				
				
				
				}
			}   
		}
	 }
	 

//void S_Testing(){
//	int i;
//	time(&Stress_Time);			
//	for (i=0;i<16;i++){
//		if(Devices.IsBlocked[i]!=1){			
//			AO_VWrite(1,16+i,SSetting.Current);
//		}
//	}   
//	
//}
void DisplayCurrentLoop(int i){
	SetCtrlVal(H_MainWin, MAINMENU_L_LOOPS,i+1);
}
void DisplayCurrentMeasurement(char *Name){
	SetCtrlVal(H_MainWin, MAINMENU_L_MEASUREMENTNAME, Name);
}
void L_Testing(int R_Index,int RH_Index,char * Wafer, char *Row){
 	int i,j;
	char *tempStr;
	int Location;
	char NameInLoop[20];
	char MeasurementInLoop[200];
	double Total_Stress;
	int Active_P;
	
 	SetCtrlAttribute (H_MainWin, MAINMENU_L_LOOPS, ATTR_DIMMED, 0);
	
	for (i=0;i<LSetting.Loops;i++){
		strcpy(MeasurementInLoop,LSetting.MeasurementName);		
		DisplayCurrentLoop(i);
		while ((tempStr=strstr(MeasurementInLoop,","))!=NULL || strlen(MeasurementInLoop)>0){
			if(tempStr!=NULL){
				Location = strlen(MeasurementInLoop)-strlen(tempStr)+1;
				strncpy(NameInLoop,MeasurementInLoop,Location-1);
				NameInLoop[Location-1]='\0';
				strcpy(MeasurementInLoop,&MeasurementInLoop[Location]);
			}
			else{
				strcpy(NameInLoop,MeasurementInLoop);
				MeasurementInLoop[0]='\0';
			}
			
			DisplayCurrentMeasurement(NameInLoop);
			
			if(NameInLoop[0]=='R' && NameInLoop[1]!='H'){
				R_Setting(NameInLoop,2);
				R_Testing(R_Index,Wafer,Row);
				R_Index++;
			}else if(NameInLoop[1]=='H'){
				RH_Setting(NameInLoop,2);
				RH_Testing(RH_Index,Wafer,Row);
				RH_Index++;
			}else if(NameInLoop[0]=='S'){
				s_test=1;
				
				S_Setting(NameInLoop,2);
				S_Testing();
 				Total_Stress = SSetting.Days *24*60*60 + SSetting.Hours * 60*60 + SSetting.Mins*60+SSetting.Secs;
 				Acc_STime += SSetting.Days *24*60 + SSetting.Hours + SSetting.Mins/60.00;
 				
 				// Enable and start timer
 				SetCtrlAttribute (H_MainWin, MAINMENU_STRESS_TIMER, ATTR_ENABLED, 1);
				SetCtrlAttribute (H_MainWin, MAINMENU_STRESS_TIMER, ATTR_INTERVAL, Total_Stress);			 					
				
				while(s_test==1){
					Active_P = GetActivePanel ();
					DisplayPanel(Active_P);
					ProcessSystemEvents ();
					if(stop_flag==1000)
						return;
				}
				
			}else{
				L_Setting(NameInLoop,2);
				L_Testing(R_Index,RH_Index,Wafer,Row);
			}
		}	
	}
	SetCtrlVal (H_MainWin, MAINMENU_L_LOOPS, 0);
	
	//SetCtrlAttribute (H_MainWin, MAINMENU_L_LOOPS, ATTR_DIMMED, 1);
}
void DisplayCurrentIndex(int i){
	CheckListItem(H_MainWin, MAINMENU_SELECTED, i,1);
	SetCtrlIndex(H_MainWin, MAINMENU_SELECTED, i);
}
void RefreshIndicator(int Num_Selected){
	int i;
	for (i=0;i<Num_Selected;i++)    
		CheckListItem(H_MainWin, MAINMENU_SELECTED, i,0);
}

	
	
void SaveIndValue(char WaferName[],char Row[]){			//Save Individual volt/curr values
	char File_Path[100];
	FILE* fp;
	char CurrDateTime[30];
	int k;

	strcpy(File_Path, "c:\\testdata\\r_data\\");
	strcat(File_Path,WaferName);
	strcat(File_Path,"_");
	strcat(File_Path,Row);  
	strcat(File_Path,".ind");
	
	if((fp=fopen(File_Path,"r"))==NULL){
		fp = fopen(File_Path,"w+");
	}else{
		fclose(fp);
		fp = fopen(File_Path,"a+");
	}
	strcpy(CurrDateTime,DateStr());
	strcat(CurrDateTime," ");
	strcat(CurrDateTime,TimeStr());
	
	fprintf(fp,"%s,%s,%s",WaferName,Row,CurrDateTime);
	
	for(k=0;k<16;k++){
		fprintf(fp,",%s,%.3f",Devices.Name[k],IndVoltCurr[k]);
	}
	fprintf(fp,"\n");
	
	fclose(fp);


}



int CVICALLBACK DoTesting (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int Num_Selected,i;
	char MeasurementName[20];
	char WaferName[20];
	char Row[20];
	char DeviceName[20];
	double Total_Stress;
	int j;
	int Active_P;
	
	switch (event)
		{
		case EVENT_COMMIT:
			SetCtrlVal(panel,MAINMENU_FINISHED,"  It's Running !!!               ");
			GetCtrlVal(panel,MAINMENU_NAME,WaferName);
			GetCtrlVal(panel,MAINMENU_ROWNAME,Row);
			GetCtrlVal(panel,MAINMENU_STARTDEVICE,DeviceName);
			time(&Start_Time);			
			if(strlen(WaferName)==0 || strlen(Row)==0 ||strlen(DeviceName)==0){
				MessagePopup("In Situ RH Testing","Please complete the input");
				break;
			}
				
			for(i=0;i<16;i++){
				GetCtrlVal(panel,MAINMENU_CH1+i,&Devices.IsBlocked[i]);
			}
			
			
				for(i=0;i<16;i++){												//Get Individual volt/curr Stress values  09/17/03
				GetCtrlVal(H_SSetting,SSETTING_CV_CH1+i,&IndVoltCurr[i]);       
			}
			
				for(i=0;i<16;i++){
					if (IndVoltCurr[i]!=0){         //if individual stress test, save values  09/17/03
						SaveIndValue(WaferName,Row);
						break;
					 }
			}
			
			
			
			
			
			
			
			GetNumListItems (panel,MAINMENU_SELECTED , &Num_Selected);
			RefreshIndicator(Num_Selected);
			R_Index=0;
			RH_Index=0;
			for (i=0;i<Num_Selected;i++){
				GetLabelFromIndex(panel,MAINMENU_SELECTED,i,MeasurementName);
				DisplayCurrentIndex(i);
				DisplayCurrentMeasurement(MeasurementName);
				if(MeasurementName[0]=='R' && MeasurementName[1]!='H' ){
					R_Setting(MeasurementName,2);
					R_Testing(R_Index,WaferName,Row);
					R_Index++;
				}else if(MeasurementName[1]=='H'){
					RH_Setting(MeasurementName,2);
					RH_Testing(RH_Index,WaferName,Row);
					RH_Index++;
				}else if(MeasurementName[0]=='S'){
					S_Setting(MeasurementName,2);
					S_Testing();
 					Total_Stress = SSetting.Days *24*60*60 + SSetting.Hours * 60*60 + SSetting.Mins*60+ SSetting.Secs;
 					Acc_STime += SSetting.Days *24*60 + SSetting.Hours + SSetting.Mins/60.00+SSetting.Secs/(60*60);
					
					// Enable and start timer
					SetCtrlAttribute (panel, MAINMENU_STRESS_TIMER, ATTR_ENABLED, 1);
					SetCtrlAttribute (panel, MAINMENU_STRESS_TIMER, ATTR_INTERVAL, Total_Stress);			 					
					
					s_test=1;
					while(s_test==1){			
						Active_P = GetActivePanel ();
						DisplayPanel(Active_P);
						ProcessSystemEvents ();
						if(stop_flag==1000)
							return 0;
					}
					//for(j=0;j<Total_Stress;j++){
					//	Delay(60);
					//	ProcessSystemEvents ();
					//}
					
					// Turn off bias current
					
					//for (j=0;j<16;j++){
					//	if(Devices.IsBlocked[j]!=1){			
					//		AO_VWrite(1,16+j,0);
					//	}
					//}
					
					//SetCtrlAttribute (panel, MAINMENU_STRESS_TIMER, ATTR_ENABLED, 0);			
				}else{
					L_Setting(MeasurementName,2);
					L_Testing(R_Index,RH_Index,WaferName,Row);
				}
			}
			
			// Turn off bias current ctlin 2/1/200
  			
  			for(i=0;i<16;i++)
  				AO_VWrite(1,16+i,0);
  				
  			for (i=0;i<8;i++){     
					AO_VWrite(3,16+i,0);  
					Delay(0.01);
					}	
  				
  				
			SetCtrlVal(panel,MAINMENU_FINISHED,"Measurement Finished!");
			break;
		}
		
	return 0;
}

int CVICALLBACK StressTimeOut (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	switch (event)
		{
		case EVENT_TIMER_TICK:
			
			// Turn off bias current
			
			// for (i=0;i<16;i++){
			//	if(Devices.IsBlocked[i]!=1){			
			//		AO_VWrite(1,16+i,0);
			//	}
			// }
			
			SetCtrlAttribute (panel, MAINMENU_STRESS_TIMER, ATTR_ENABLED, 0);			
			s_test=0;			
			break;
		}
	return 0;
}

int CVICALLBACK DisplayTime (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	time_t Curr_Time;
	struct TotalTimes Elp_Time;
	double Elp_Seconds, Elp_S_Seconds;
	int temp;
	int myDays,myHours,myMins;
	switch (event)
	
		{
		case EVENT_COMMIT:
		    DisplayPanel(H_DspTime);
		    time(&Curr_Time);
		    Elp_Seconds = difftime(Curr_Time,Start_Time);
		    Elp_S_Seconds = difftime(Curr_Time,Stress_Time);
			myDays =(int)Elp_Seconds/(24*3600);
			temp = (int)Elp_Seconds%(24*3600);
			myHours = (int)(temp/3600);
			myMins = (int)((temp%3600)/60);
			
			SetCtrlVal(H_DspTime,DSPTIME_TOTALEDAYS,myDays);
			SetCtrlVal(H_DspTime,DSPTIME_TOTALEHOURS,myHours);
			SetCtrlVal(H_DspTime,DSPTIME_TOTALEMINS,myMins);
			
			GetCtrlVal(H_MainWin,MAINMENU_TOTALDAYS,&Elp_Time.Days);
			GetCtrlVal(H_MainWin,MAINMENU_TOTALHOURS,&Elp_Time.Hours);
			GetCtrlVal(H_MainWin,MAINMENU_TOTALMINS,&Elp_Time.Mins);
			CalculateTotalTime(&Elp_Time, myDays,myHours,myMins,2);
			
			SetCtrlVal(H_DspTime,DSPTIME_TOTALRDAYS,Elp_Time.Days);
			SetCtrlVal(H_DspTime,DSPTIME_TOTALRHOURS,Elp_Time.Hours);
			SetCtrlVal(H_DspTime,DSPTIME_TOTALRMINS,Elp_Time.Mins);
			
			myDays =(int)Elp_S_Seconds/(24*3600);
			temp = (int)Elp_S_Seconds%(24*3600);
			myHours = (int)(temp/3600);
			myMins = (int)((temp%3600)/60);
			
			SetCtrlVal(H_DspTime,DSPTIME_STRESSEDAYS,myDays);
			SetCtrlVal(H_DspTime,DSPTIME_STRESSEHOURS,myHours);
			SetCtrlVal(H_DspTime,DSPTIME_STRESSEMINS,myMins);
			
			Elp_Time.Days = SSetting.Days;
			Elp_Time.Hours = SSetting.Hours;
			Elp_Time.Mins = SSetting.Mins;
			CalculateTotalTime(&Elp_Time, myDays,myHours,myMins,2);
			SetCtrlVal(H_DspTime,DSPTIME_STRESSRDAYS,Elp_Time.Days);
			SetCtrlVal(H_DspTime,DSPTIME_STRESSRHOURS,Elp_Time.Hours);
			SetCtrlVal(H_DspTime,DSPTIME_STRESSRMINS,Elp_Time.Mins);
			
			break;
		}
	return 0;
}

int CVICALLBACK DisplayRCurve (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DisplayPanel(H_RCurve);
		/*	if(control==MAINMENU_RTIME || control==TAATIME_RTIME||control==ASYMTIME_RTIME||control==RHCURVE_RTIME)
				DisplayPanel(H_RCurve);
			else if(control==MAINMENU_TAATIME|| control==RTIME_TAATIME||control==ASYMTIME_TAATIME||control==RHCURVE_TAATIME)
				DisplayPanel(H_TaaCurve);				
			else
				DisplayPanel(H_AsymCurve);        "Sung disabled this part 05/03/02" */
			
			break;
		}
	return 0;
}

int CVICALLBACK DisplayASYMCurve (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:			  
			DisplayPanel(H_AsymCurve);
			break;
		}
	return 0;
}

int CVICALLBACK DisplayTAACurve (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:							
			DisplayPanel(H_TaaCurve);				
			break;
		}
	return 0;
}

int CVICALLBACK DisplayRHCurve (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DisplayPanel(H_RHCurve);
			break;
		}
	return 0;
}

int CVICALLBACK DeleteSetting (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int MeasurementVal;
	int MeasurementIndex;
	char name[10];
	char SQLSTR[200];
	int hstmt;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(panel,SETMENU_MEASUREMENTLIST,&MeasurementVal);
  			GetIndexFromValue(panel,SETMENU_MEASUREMENTLIST,&MeasurementIndex,MeasurementVal);
  			GetLabelFromIndex (panel,SETMENU_MEASUREMENTLIST,MeasurementIndex, name);
  			DeleteListItem (panel, SETMENU_MEASUREMENTLIST, MeasurementIndex, 1);
			if(name[0]=='R' && name[1]!='H')  			
  				strcpy(SQLSTR, "delete from RSETTING where Name = '");
  			else if(name[0]=='R' && name[1]=='H')  			
  				strcpy(SQLSTR, "delete from RHSETTING where Name = '");
			else if(name[0]=='S')  			  			
				strcpy(SQLSTR, "delete from SSETTING where Name = '");
			else if(name[0]=='L')  			
				strcpy(SQLSTR, "delete from LSETTING where Name = '");
			
			strcat (SQLSTR,name);
			strcat(SQLSTR,"'" );
			hstmt = DBActivateSQL(hdbc,SQLSTR);
			DBDeactivateSQL(hstmt);  
			break;
		}
	return 0;
}

///////.
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//Below are the New codes for Version 1.1.1.
//Sung Modified to enable to scale the graphs
//05/02/2002


int CVICALLBACK RReDraw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   
    double xmin,xmax,ymin,ymax;     //Properties of the current graph
    int xAxisScaling,yAxisScaling;  //Properties of the current graph 
    double y_min, y_max;            //New y_axis range
	
	switch (event)
		{
		case EVENT_COMMIT:
		  GetCtrlVal(H_RCurve, RTIME_YMAX, &y_max);
		  GetCtrlVal(H_RCurve, RTIME_YMIN, &y_min);
		  GetAxisRange (H_RCurve, RTIME_GRAPH, &xAxisScaling,&xmin,&xmax,&yAxisScaling,&ymin, &ymax);
		  SetAxisRange (H_RCurve, RTIME_GRAPH, VAL_NO_CHANGE, xmin,xmax,VAL_MANUAL,y_min, y_max);
			break;
		}
	return 0;
}

int CVICALLBACK TAAReDraw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   
    double xmin,xmax,ymin,ymax;     //Properties of the current graph
    int xAxisScaling,yAxisScaling;  //Properties of the current graph 
    double y_min, y_max;            //New y_axis range
	
	switch (event)
		{
		case EVENT_COMMIT:
		  GetCtrlVal(H_TaaCurve, TAATIME_YMAX, &y_max);
		  GetCtrlVal(H_TaaCurve, TAATIME_YMIN, &y_min);
		  GetAxisRange (H_TaaCurve, TAATIME_GRAPH, &xAxisScaling,&xmin,&xmax,&yAxisScaling,&ymin, &ymax);
		  SetAxisRange (H_TaaCurve, TAATIME_GRAPH, VAL_NO_CHANGE,xmin,xmax,VAL_MANUAL,y_min, y_max);
			break;
		}
	return 0;
}

int CVICALLBACK ASYMReDraw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   
    double xmin,xmax,ymin,ymax;     //Properties of the current graph
    int xAxisScaling,yAxisScaling;  //Properties of the current graph 
    double y_min, y_max;            //New y_axis range
	
	switch (event)
		{
		case EVENT_COMMIT:
		  GetCtrlVal(H_AsymCurve, ASYMTIME_YMAX, &y_max);
		  GetCtrlVal(H_AsymCurve, ASYMTIME_YMIN, &y_min);
		  GetAxisRange (H_AsymCurve, ASYMTIME_GRAPH, &xAxisScaling,&xmin,&xmax,&yAxisScaling,&ymin, &ymax);
		  SetAxisRange (H_AsymCurve, ASYMTIME_GRAPH, VAL_NO_CHANGE,xmin,xmax,VAL_MANUAL,y_min, y_max);
			break;
		}
	return 0;
}

//Version 1.1.3
int CVICALLBACK TAADiffReDraw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   
    double xmin,xmax,ymin,ymax;     //Properties of the current graph
    int xAxisScaling,yAxisScaling;  //Properties of the current graph 
    double y_min, y_max;            //New y_axis range
	
	switch (event)
		{
		case EVENT_COMMIT:
		  GetCtrlVal(H_TAADiff, TAADIFF_YMAX, &y_max);
		  GetCtrlVal(H_TAADiff, TAADIFF_YMIN, &y_min);
		  GetAxisRange (H_TAADiff, TAADIFF_GRAPH, &xAxisScaling,&xmin,&xmax,&yAxisScaling,&ymin, &ymax);
		  SetAxisRange (H_TAADiff, TAADIFF_GRAPH, VAL_NO_CHANGE,xmin,xmax,VAL_MANUAL,y_min, y_max);
			break;
		}
	return 0;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Version 1.1.3
//Sung modified to add a new panel for displaying TAA_diff vs time
//05/06/02
int CVICALLBACK DisplayDiffCurve (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		   DisplayPanel(H_TAADiff);
			break;
		}
	return 0;
}

