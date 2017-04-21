//Ver 1.2 
 
 //Sung Chung 05/02/02	  Ver. 1.1   //Modification for applying constant H field for R test 
 //Sung Chung 07/22/03    Ver. 1.2    //Const Current Density Stres
 //Sung Chung 09/16/03    Ver. 1.5    //Individual Pseudo -Const voltage Stres 
  //ver2.0    //+v -V stress with voltage QST
 int 	H_MainWin;	
 int	H_SetMenu;
 int	H_RSetting;
 int	H_SSetting;
 int	H_RHSetting;
 int	H_LSetting;
 int	H_RHCurve;
 int	H_TaaCurve;
 int	H_RCurve;
 int	H_AsymCurve;
 int    H_DspTime;
 int    H_TAADiff;
 int    H_ViewColdR;                 //Ver. 1.3 08/20/03
 int	hdbc;
 int 	s_test;
 time_t Start_Time;
 time_t Stress_Time;
 int R_Index;
 int RH_Index;
 double Acc_STime;
 int T;					   //Ver 1.2
 double LeadR;			   //Ver 1.2
 double A,B;			   //Ver 1.2
 double Vheat;			   //Ver 1.2
 double VDevice[20];                 //Ver. 1.2
 double CurrentForConstJ[20];        //Ver. 1.2 07/22/03
 double ColdR[20];                   //Ver. 1.3 08/20/03 
 double IndVoltCurr[20];			 //ver. 1.5 09/16/03
	
 
 struct RSetting{
 	char Name[10];
 	double Current;
 	double Rate;
 	int	Times;
 	short ReadGain;
 	double H_Field;     //Sung modified 02/05/02  
 	double CoilGain;	//Sung modified 02/05/02  
 }RSetting;
 
 struct SSetting{
 	char Name[10];
 	double Current;
 	int Days;
 	int	Hours;
 	int	Mins;
 	int Secs;
 	double	Temperature;
 	int Stressmode;
 	double Voltage;
 	
 }SSetting;
 
 struct RHSetting{
 	char Name[10];
 	double Voltage;		 //ver2.0
 	double CmplCurr;			  //ver2.0 
 	double	H_Field;
 	int StepNum;
 	double CoilGain;
 	double Rate;
 	int CycleNum;
 	int InitDir;
 	short ReadGain;
 	double RefCurr;						   //ver2.0 
 	
 }RHSetting;
 
 struct TotalTimes{
 	int	Days;
 	int Hours;
 	int Mins;
 }TotalTimes ;
 
 
 struct LSetting{
 	char Name[10];
 	int Loops;
 	char MeasurementName[300];
	struct TotalTimes L_Times;
 }LSetting;
 
struct Devices{
	char Name[16][10];
	int  IsBlocked[16];
}Devices ;
 
int OddRow;

