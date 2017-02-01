//////////////////////////////////////////////////////////////////////////
//
//	GPG v.0.8 by Dymaxion 20060730
//
//  dymaxion@naver.com
//
//////////////////////////////////////////////////////////////////////////
#include <ansi_c.h>
#include <math.h>
#include <utility.h>
#include <formatio.h>
#include <cvirte.h>		
#include <userint.h>
#include "GPG.h"

//////////////////////////////////////////////////////////////////////////
//
//	My define
//
//////////////////////////////////////////////////////////////////////////
#define NUM_PARAMETER	10
#define PI	3.14159
#define MAX_CONTROL_POINT	102
#define CIRCLE_CONTROL_POINT	10005

//////////////////////////////////////////////////////////////////////////
//
//	My Variables
//
//////////////////////////////////////////////////////////////////////////
// parameter[0] = resolution
// parameter[1] = resolution_fillet
// parameter[2] = Module
// parameter[3] = Addendum
// parameter[4] = Dedendum
// parameter[5] = R_c (Fillet Radius)
// parameter[6] = Phi (Pressure Angle in Degree)
// parameter[7] = X (Offset Factor)
// parameter[8] = N (Number of Teeth)
// parameter[9] = Phi (Pressure Angle in Radian)
static double parameter[NUM_PARAMETER];
static char proj_dir[MAX_PATHNAME_LEN];
static char parameter_file_name[MAX_PATHNAME_LEN];
static char output_file_name[MAX_PATHNAME_LEN];
// Calculate
static double V, U;
static double Involute[2][MAX_CONTROL_POINT*2];
static double Fillet[2][MAX_CONTROL_POINT*2];
static double Outter_Circle[2][CIRCLE_CONTROL_POINT];
static double Root_Circle[2][CIRCLE_CONTROL_POINT];
static double Pitch_Circle[2][CIRCLE_CONTROL_POINT];
static double r_o, r_r, r_p;
// Plot
static double x_range[2], y_range[2];


static int PanelHandle;
static int HelpPanelHandle;
static int Plot_Handle[5];
//////////////////////////////////////////////////////////////////////////
//
//	My Functions
//
//////////////////////////////////////////////////////////////////////////
int _init (void);
int _Get_Parameter (void);
int _Dim_Control (void);
int _Set_Commandbutton_Load_i (int);
int _Calculate_V_and_U (void);
int _Calculate_Involute (void);
int _Calculate_Fillet (void);
int _Calculate_Outter_Circle (void);
int _Calculate_Root_Circle (void);
int _Calculate_Pitch_Circle (void);
double cot (double);
int _Plot_Profile (void);

//////////////////////////////////////////////////////////////////////////
//
//	Main
//
//////////////////////////////////////////////////////////////////////////
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((PanelHandle = LoadPanel (0, "GPG.uir", PANEL)) < 0)
		return -1;
	_init(); // Initialize
	DisplayPanel (PanelHandle);
	RunUserInterface ();
	DiscardPanel (PanelHandle);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	Initialize
//
//////////////////////////////////////////////////////////////////////////
int _init (void)
{
    GetProjectDir (proj_dir);
	_Dim_Control ();
	_Set_Commandbutton_Load_i (0);
	_Get_Parameter ();
    return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	Choice Input Method
//
//////////////////////////////////////////////////////////////////////////
int CVICALLBACK Callback_Input_Method (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Dim_Control ();
			break;
		}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	Dim Control
//
//////////////////////////////////////////////////////////////////////////
int _Dim_Control (void)
{
	int dim_status;
	GetCtrlVal (PanelHandle, PANEL_INPUT_METHOD, &dim_status);
	if (dim_status == 0)
	{
		SetCtrlAttribute (PanelHandle, PANEL_COMMANDBUTTON_LOAD_I, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_RESOLUTION, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_RESOLUTION_F, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_M, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_ADDENDUM, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_DEDENDUM, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_R_C, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_PHI, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_X, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_N, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_COMMANDBUTTON_SAVE_I, ATTR_DIMMED, 0);
	}
	else if (dim_status == 1)
	{
		SetCtrlAttribute (PanelHandle, PANEL_COMMANDBUTTON_LOAD_I, ATTR_DIMMED, 0);
		SetCtrlAttribute (PanelHandle, PANEL_RESOLUTION, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_RESOLUTION_F, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_M, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_ADDENDUM, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_DEDENDUM, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_R_C, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_PHI, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_X, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_N, ATTR_DIMMED, 1);
		SetCtrlAttribute (PanelHandle, PANEL_COMMANDBUTTON_SAVE_I, ATTR_DIMMED, 1);
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//	Get Parameters
//
//////////////////////////////////////////////////////////////////////////
int _Get_Parameter (void)
{
	// Get Values
	GetCtrlVal (PanelHandle, PANEL_RESOLUTION, &parameter[0]);
	GetCtrlVal (PanelHandle, PANEL_RESOLUTION_F, &parameter[1]);
	GetCtrlVal (PanelHandle, PANEL_M, &parameter[2]);
	GetCtrlVal (PanelHandle, PANEL_ADDENDUM, &parameter[3]);
	GetCtrlVal (PanelHandle, PANEL_DEDENDUM, &parameter[4]);
	GetCtrlVal (PanelHandle, PANEL_R_C, &parameter[5]);
	GetCtrlVal (PanelHandle, PANEL_PHI, &parameter[6]);
	GetCtrlVal (PanelHandle, PANEL_X, &parameter[7]);
	GetCtrlVal (PanelHandle, PANEL_N, &parameter[8]);
	// Degree to Radian
	parameter[9] = parameter[6] *(2.0*PI/360.0);
	return 0;
}

int CVICALLBACK Callback_Resolution (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Get_Parameter();
			break;
		}
	return 0;
}

int CVICALLBACK Callback_Resolution_F (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Get_Parameter();
			break;
		}
	return 0;
}

int CVICALLBACK Callback_M (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Get_Parameter();
			break;
		}
	return 0;
}

int CVICALLBACK Callback_Addendum (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Get_Parameter();
			break;
		}
	return 0;
}

int CVICALLBACK Callback_Dedendum (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Get_Parameter();
			break;
		}
	return 0;
}

int CVICALLBACK Callback_R_c (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Get_Parameter();
			break;
		}
	return 0;
}

int CVICALLBACK Callback_Phi (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Get_Parameter();
			break;
		}
	return 0;
}

int CVICALLBACK Callback_X (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Get_Parameter();
			break;
		}
	return 0;
}

int CVICALLBACK Callback_N (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			_Get_Parameter();
			break;
		}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	Save Parameters into file
//
//////////////////////////////////////////////////////////////////////////
int CVICALLBACK Callback_Save_i (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			if (FileSelectPopup (proj_dir, "*.dat", "*.dat",
					"Parameter File Name to Save", VAL_OK_BUTTON, 0, 1, 1,
					0, parameter_file_name) > 0)
			{
				_Get_Parameter();
				ArrayToFile (parameter_file_name, parameter, VAL_DOUBLE, 
						NUM_PARAMETER, 1, VAL_GROUPS_TOGETHER, 
						VAL_GROUPS_AS_COLUMNS, VAL_CONST_WIDTH, 10, 
						VAL_ASCII, VAL_TRUNCATE);
			}
			break;
		}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	Load Input file including Parameters
//
//////////////////////////////////////////////////////////////////////////
int CVICALLBACK Callback_Load_i (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			if (FileSelectPopup (proj_dir, "*.dat", "*.dat", 
					"Parameter File Name to Load", VAL_OK_BUTTON, 0, 1, 1, 
					0, parameter_file_name) > 0)
			{
				if (FileToArray (parameter_file_name, parameter, VAL_DOUBLE, 
							NUM_PARAMETER, 1, VAL_GROUPS_TOGETHER, 
							VAL_GROUPS_AS_COLUMNS, VAL_ASCII) == 0)
				{
					_Set_Commandbutton_Load_i (1);
					
					// Value Indicate
					SetCtrlVal (PanelHandle, PANEL_RESOLUTION, parameter[0]);
					SetCtrlVal (PanelHandle, PANEL_RESOLUTION_F, parameter[1]);
					SetCtrlVal (PanelHandle, PANEL_M, parameter[2]);
					SetCtrlVal (PanelHandle, PANEL_ADDENDUM, parameter[3]);
					SetCtrlVal (PanelHandle, PANEL_DEDENDUM, parameter[4]);
					SetCtrlVal (PanelHandle, PANEL_R_C, parameter[5]);
					SetCtrlVal (PanelHandle, PANEL_PHI, parameter[6]);
					SetCtrlVal (PanelHandle, PANEL_X, parameter[7]);
					SetCtrlVal (PanelHandle, PANEL_N, parameter[8]);
				}
					
				else return -1;
            }
			break;
		}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	Set Condition of PANEL_COMMANDBUTTON_LOAD_I Button
//
//////////////////////////////////////////////////////////////////////////
int _Set_Commandbutton_Load_i (int Commandbutton_Load_i_status)
{
	// Dim Control
	if (Commandbutton_Load_i_status == 1)  
		SetCtrlAttribute (PanelHandle, PANEL_COMMANDBUTTON_LOAD_I, ATTR_LABEL_COLOR, VAL_BLUE);
	else if (Commandbutton_Load_i_status == 0)
		SetCtrlAttribute (PanelHandle, PANEL_COMMANDBUTTON_LOAD_I, ATTR_LABEL_COLOR, VAL_BLACK);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	Save Output Profile Data into file
//
//////////////////////////////////////////////////////////////////////////
int CVICALLBACK Callback_Save_o (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i,j,temp=0;
	double n_theta = 0.0;
	 FILE *FileHandle;
	
	switch (event)
		{
		case EVENT_COMMIT:
		
		
			if (FileSelectPopup (proj_dir, "*.scr", "*.scr",
					"Output AutoCAD Script File to Save", VAL_OK_BUTTON, 0, 1, 1,
					1, output_file_name) > 0)
			{
				FileHandle = fopen (output_file_name, "w+");
				
				// Instruction of Zoom
				fprintf (FileHandle, "zoom w %f,%f %f,%f\n", 
										(Fillet[0][0]-5),(r_r-5), -(Fillet[0][0]-5),(r_o+5));
				
				// Drawing Circles
				fprintf(FileHandle, "circle %f,%f %f\n", 0.0,0.0, r_o);
				fprintf(FileHandle, "circle %f,%f %f\n", 0.0,0.0, r_r);
				fprintf(FileHandle, "circle %f,%f %f\n", 0.0,0.0, r_p);
				fprintf(FileHandle, "line %f,%f %f,%f\n\n", 0.0,0.0, 0.0,r_o);

				// Drawing Involute Curve
				fprintf(FileHandle, "line ");
				for (i=0;i<(int)parameter[0];i++)
				{
					fprintf(FileHandle, "%f,%f %f,%f\n", 
									(float)Involute[0][i],(float)Involute[1][i], 
									(float)Involute[0][i+1],(float)Involute[1][i+1]);
				}
				fprintf(FileHandle, "\n");
				
				// Drawing Involute Curve Mirror
				fprintf(FileHandle, "line ");
				for (i=0;i<(int)parameter[0];i++)
				{
					fprintf(FileHandle, "%f,%f %f,%f\n", 
									-(float)Involute[0][i],(float)Involute[1][i], 
									-(float)Involute[0][i+1],(float)Involute[1][i+1]);
				}
				fprintf(FileHandle, "\n");

				// Drawing Fillet Curve
				fprintf(FileHandle, "line ");
				for (i=0;i<(int)parameter[1];i++)
				{
					fprintf(FileHandle, "%f,%f %f,%f\n", 
									(float)Fillet[0][i],(float)Fillet[1][i], 
									(float)Fillet[0][i+1],(float)Fillet[1][i+1]);
				}
				fprintf(FileHandle, "\n");

				// Drawing Fillet Curve Mirror
				fprintf(FileHandle, "line ");
				for (i=0;i<(int)parameter[1];i++)
				{
					fprintf(FileHandle, "%f,%f %f,%f\n", 
									-(float)Fillet[0][i],(float)Fillet[1][i], 
									-(float)Fillet[0][i+1],(float)Fillet[1][i+1]);
				}
				fprintf(FileHandle, "\n");

				// Write Spec.
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 --Gear Spec--\n",
						r_o+2.0, 25.0-5.0*0.0, 2.5*1.5);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 Resolution of Involute Curve = %3.0f lines\n",
						r_o+2.0, 25.0-5.0*1.0, 2.5, parameter[0]);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 Resolution of Fillet Curve = %3.0f lines\n",
						r_o+2.0, 25.0-5.0*2.0, 2.5, parameter[1]);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 Gear Module = %3.8f\n",
						r_o+2.0, 25.0-5.0*3.0, 2.5, parameter[2]);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 Addendum = %3.8f mm\n",
						r_o+2.0, 25.0-5.0*4.0, 2.5, parameter[3]);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 Dedendum = %3.8f mm\n",
						r_o+2.0, 25.0-5.0*5.0, 2.5, parameter[4]);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 Tip C-cut Radius = %3.8f mm\n",
						r_o+2.0, 25.0-5.0*6.0, 2.5, parameter[5]);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 Pressure Angle = %3.8f degree\n",
						r_o+2.0, 25.0-5.0*7.0, 2.5, parameter[6]);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 Shift Factor = %3.8f\n",
						r_o+2.0, 25.0-5.0*8.0, 2.5, parameter[7]);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 Number of Teeth = %3.8f ea\n",
						r_o+2.0, 25.0-5.0*9.0, 2.5, parameter[8]);
				fprintf(FileHandle,"text s standard %f,%f,0 %f 0 -- Generated by GPG v0.8 --\n",
						r_o+2.0, 25.0-5.0*10.0, 2.5);

				fclose (FileHandle);
				MessagePopup ("File Save", "File Save Success!");

			}
			break;
		}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	Calculate Profile data
//
//////////////////////////////////////////////////////////////////////////
int CVICALLBACK Callback_Gen (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	
	switch (event)
		{
		case EVENT_COMMIT:
			// Calculate Curve
			_Calculate_V_and_U ();
			_Calculate_Involute ();
			_Calculate_Fillet ();
			_Calculate_Pitch_Circle ();
			_Calculate_Outter_Circle ();
			_Calculate_Root_Circle ();
			
			// Plot Graph
			_Plot_Profile ();
					
			// Set color of Commandbutton_Load_i
			_Set_Commandbutton_Load_i (0);
			break;
		}
	return 0;
}

int _Calculate_V_and_U (void)
{
	V = (parameter[5]/parameter[2]) - (parameter[4]/parameter[2]);
	U = - (PI/4.0 
			+ ((parameter[4]/parameter[2])-(parameter[5]/parameter[2])) * tan(parameter[9]) 
			+ (parameter[5]/parameter[2]) / cos(parameter[9]));
	return 0;
}

int _Calculate_Involute (void)
{
	int i;
	double theta_min, theta_max;
	double theta[MAX_CONTROL_POINT];

	theta_min = (2.0/parameter[8]) * (U + (V+parameter[7])*cot(parameter[9]));
	theta_max = (1.0/(parameter[8]*cos(parameter[9]))) 
				* sqrt(
						pow ( (2.0*(parameter[3]/parameter[2])+parameter[8]+2.0*parameter[7]), 2.0 ) - 
						pow ( (parameter[8]*cos(parameter[9])), 2.0 )
					) 
				- (1.0+(2.0*parameter[7])/parameter[8])*tan(parameter[9]) 
				- PI/(2.0*parameter[8]);
	theta[0] = theta_min;
	
	for (i=0;i<parameter[0]+1;i++)
	{
		if (i==0)
		{
			theta[i] = theta[0];
		}
		else if (i>0)
		{
			theta[i] = theta[i-1] + ((theta_max-theta_min)/parameter[0]);
		}
		Involute[0][i] = (parameter[8]*parameter[2]/2.0) 
						* (sin(theta[i]) 
						- ((theta[i] + PI/(2.0*parameter[8]))*cos(parameter[9]) 
						+ (2.0*parameter[7]/parameter[8])*sin(parameter[9])) 
						* cos(theta[i]+parameter[9]));
		Involute[1][i] = (parameter[8]*parameter[2]/2.0) 
						* (cos(theta[i]) 
						+ ((theta[i] + PI/(2.0*parameter[8]))*cos(parameter[9]) 
						+ (2.0*parameter[7]/parameter[8])*sin(parameter[9])) 
						* sin(theta[i]+parameter[9]));
	}
	return 0;
}

int _Calculate_Fillet (void)
{
	int i;
	double rho_min, rho_max; 
	double rho[MAX_CONTROL_POINT];
	double L=0.0, P=0.0, Q=0.0;
	
	rho_min = (2.0/parameter[8]) * (U + (V+parameter[7]) * cot(parameter[9]));
	rho_max = 2.0 * U / parameter[8];
	rho[0] = rho_min;
	
	for (i=0;i<parameter[1]+1;i++)
	{
		if (i==0)
		{
			rho[i] = rho[0];
		}
		else if (i>0)
		{
			rho[i] = rho[i-1] + ((rho_max-rho_min)/parameter[1]);
		}
		
		L = sqrt ( pow((2.0*U-parameter[8]*rho[i]), 2.0) 
				+ 4.0 * pow((V+parameter[7]), 2.0) );
		P = ((parameter[5]/parameter[2]) / L) * (2.0*U - parameter[8]*rho[i]) 
			+ (U - parameter[8]*rho[i]/2.0);
		Q = (2.0 * (parameter[5]/parameter[2]) / L) * (V + parameter[7]) 
			+ V + parameter[8] / 2.0 + parameter[7];
		Fillet[0][i] = parameter[2]*(P*cos(rho[i]) + Q*sin(rho[i]));
		Fillet[1][i] = parameter[2]*(-P*sin(rho[i]) + Q*cos(rho[i]));
	}

	return 0;
}

int _Calculate_Pitch_Circle (void)
{
	int i;
	double temp[CIRCLE_CONTROL_POINT+1];
	
	//r_p = (1.0/2.0) * parameter[2]*parameter[8];
	r_p = (1.0/2.0) * parameter[2]*parameter[8]  + 0.5*parameter[7]*(parameter[3]+parameter[3]);

	temp[0] = 0.0;
	for (i=0;i<(2.0*parameter[0]*parameter[8]);i++)
	{
		if (i==0)
			{
				temp[i] = temp[0];
			}
			else if (i>0)
			{
				temp[i] = temp[i-1] + 2.0*PI / (2.0*parameter[0]*parameter[8]);
			}
		
		Pitch_Circle[0][i] = r_p * cos(temp[i]);
		Pitch_Circle[1][i] = r_p * sin(temp[i]);
	}
	return 0;
}

int _Calculate_Outter_Circle (void)
{
	int i;
	double temp[CIRCLE_CONTROL_POINT+1];
	
	// r_o = r_p + (1.0+parameter[7])*parameter[2];
	r_o = r_p + parameter[3];
	temp[0] = 0.0;
	for (i=0;i<(2.0*parameter[0]*parameter[8]);i++)
	{
		if (i==0)
			{
				temp[i] = temp[0];
			}
			else if (i>0)
			{
				temp[i] = temp[i-1] + 2.0*PI / (2.0*parameter[0]*parameter[8]);
			}
		
		Outter_Circle[0][i] = r_o * cos(temp[i]);
		Outter_Circle[1][i] = r_o * sin(temp[i]);
	}
	return 0;
}

int _Calculate_Root_Circle (void)
{
	int i;
	double temp[CIRCLE_CONTROL_POINT+1];
	
	r_r = r_p - parameter[4];
	// r_r = r_o - (parameter[3]+parameter[4]);
	temp[0] = 0.0;
	for (i=0;i<(2.0*parameter[0]*parameter[8]);i++)
	{
		if (i==0)
			{
				temp[i] = temp[0];
			}
			else if (i>0)
			{
				temp[i] = temp[i-1] + 2.0*PI / (2.0*parameter[0]*parameter[8]);
			}
		
		Root_Circle[0][i] = r_r * cos(temp[i]);
		Root_Circle[1][i] = r_r * sin(temp[i]);
	}
	return 0;
}

double cot (double temp)
{
	temp = cos(temp)/sin(temp);
	return temp;
}

//////////////////////////////////////////////////////////////////////////
//
//	Plot Graph
//
//////////////////////////////////////////////////////////////////////////
int _Plot_Profile (void)
{
	int i=0;
	double Temp_Involute[MAX_CONTROL_POINT*2], Temp_Fillet[MAX_CONTROL_POINT*2];

	// Symetric Graph
	for (i=0;i<(parameter[0]+1);i++)
	{
		Temp_Involute[i] = (-1.0) * Involute[0][i];
	}
	for (i=0;i<(parameter[1]+1);i++)
	{
		Temp_Fillet[i] = (-1.0) * Fillet[0][i];
	}

	DeleteGraphPlot (PanelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
	SetAxisRange (PanelHandle, PANEL_GRAPH, VAL_AUTOSCALE, 1, 2, VAL_AUTOSCALE, 3, 4);
	
	// Outter_Circle
	Plot_Handle[0] = PlotXY (PanelHandle, PANEL_GRAPH, Outter_Circle[0], Outter_Circle[1], 
						(2.0*parameter[0]*parameter[8]), VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, 
						VAL_DOTTED_SOLID_SQUARE, VAL_DASH_DOT, 1, VAL_CYAN);
	PlotText (PanelHandle, PANEL_GRAPH, 0.0, r_o, " Outter Circle ", 
						VAL_APP_META_FONT, VAL_CYAN, VAL_BLACK);

	// Pitch_Circle
	Plot_Handle[2] = PlotXY (PanelHandle, PANEL_GRAPH, Pitch_Circle[0], Pitch_Circle[1], 
						(2.0*parameter[0]*parameter[8]), VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, 
						VAL_DOTTED_SOLID_SQUARE, VAL_DASH_DOT, 1, VAL_RED);	
	PlotText (PanelHandle, PANEL_GRAPH, 0.0, r_p, " Pitch Circle ", 
						VAL_APP_META_FONT, VAL_RED, VAL_BLACK);

	// Root_Circle
	Plot_Handle[1] = PlotXY (PanelHandle, PANEL_GRAPH, Root_Circle[0], Root_Circle[1], 
						(2.0*parameter[0]*parameter[8]), VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, 
						VAL_DOTTED_SOLID_SQUARE, VAL_DASH_DOT, 1, VAL_CYAN);	
	PlotText (PanelHandle, PANEL_GRAPH, 0.0, r_r, " Root Circle ", 
						VAL_APP_META_FONT, VAL_CYAN, VAL_BLACK);

	// Involute
	Plot_Handle[3] = PlotXY (PanelHandle, PANEL_GRAPH, Involute[0], Involute[1], 
						parameter[0]+1, VAL_DOUBLE, VAL_DOUBLE, VAL_CONNECTED_POINTS, 
						VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_YELLOW);
	PlotText (PanelHandle, PANEL_GRAPH, 
						Involute[0][(int)parameter[0]], Involute[1][(int)parameter[0]]-0.3, 
						" Involute Curve ", VAL_APP_META_FONT, VAL_YELLOW, VAL_BLACK);
	Plot_Handle[3] = PlotXY (PanelHandle, PANEL_GRAPH, Temp_Involute, Involute[1], 
						parameter[0]+1, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, 
						VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_YELLOW);

	// Fillet
	Plot_Handle[4] = PlotXY (PanelHandle, PANEL_GRAPH, Fillet[0], Fillet[1], 
						parameter[1]+1, VAL_DOUBLE, VAL_DOUBLE, VAL_CONNECTED_POINTS, 
						VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_GREEN);
	PlotText (PanelHandle, PANEL_GRAPH, 
						Fillet[0][(int)parameter[1]], Fillet[1][(int)parameter[1]]-0.3, 
						" Fillet Curve ", VAL_APP_META_FONT, VAL_GREEN, VAL_BLACK);
	Plot_Handle[4] = PlotXY (PanelHandle, PANEL_GRAPH, Temp_Fillet, Fillet[1], 
						parameter[1]+1, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, 
						VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_GREEN);

	// Show in brief range
	x_range[0] = (-1.0) * 
				(abs(Fillet[0][(int)parameter[1]]) 
				+ abs(Fillet[0][(int)parameter[1]] + Involute[0][(int)parameter[0]])*0.3);
	x_range[1] = (-1.0) * x_range[0];
	y_range[0] = r_r - abs(r_o-r_r)*0.3;
	y_range[1] = r_o + abs(r_o-r_r)*0.3;
	SetAxisRange (PanelHandle, PANEL_GRAPH, VAL_MANUAL, x_range[0], x_range[1], 
											VAL_MANUAL, y_range[0], y_range[1]);
	PlotText (PanelHandle, PANEL_GRAPH, 
						x_range[0], y_range[0], 
						" (Radius of Root Circle) = (Radius of Pitch Circle) - (a+b) ", VAL_APP_META_FONT, VAL_WHITE, VAL_BLACK);
	PlotText (PanelHandle, PANEL_GRAPH, 
						x_range[0], y_range[0]+0.3, 
						" (Radius of Outter Circle) = (Radius of Pitch Circle) + (1+X)*M ", VAL_APP_META_FONT, VAL_WHITE, VAL_BLACK);
	PlotText (PanelHandle, PANEL_GRAPH, 
						x_range[0], y_range[0]+0.6, 
						" (Radius of Pitch Circle) = (1/2) * M * N ", VAL_APP_META_FONT, VAL_WHITE, VAL_BLACK);
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//	Help Doc
//
//////////////////////////////////////////////////////////////////////////
int CVICALLBACK Callback_Help (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			if ((HelpPanelHandle = LoadPanel (0, "GPG.uir", HELP_PANEL)) < 0)
			return -1;
			DisplayPanel (HelpPanelHandle);
			break;
		}
	return 0;
}

int CVICALLBACK Callback_Help_Ok (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DiscardPanel (HelpPanelHandle);
			break;
		}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	About Doc
//
//////////////////////////////////////////////////////////////////////////
int CVICALLBACK Callback_About (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			MessagePopup ("About GPG v0.8", "Gear Profile Generator v0.8\n\n20060730\nby Dymaxion\ndymaxion@naver.com\n\nJust Enjoy & Please Feedback me~!");
			break;
		}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
//	Terminate Program
//
//////////////////////////////////////////////////////////////////////////
int CVICALLBACK Callback_Quit (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		}
	return 0;
}


