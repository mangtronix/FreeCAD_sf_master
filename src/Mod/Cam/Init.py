# FreeCAD init script of the Cam module  
# (c) 2007 Juergen Riegel

#***************************************************************************
#*   (c) Juergen Riegel (juergen.riegel@web.de) 2002                       *   
#*                                                                         *
#*   This file is Cam of the FreeCAD CAx development system.              *
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU Lesser General Public License (LGPL)    *
#*   as published by the Free Software Foundation; either version 2 of     *
#*   the License, or (at your option) any later version.                   *
#*   for detail see the LICENCE text file.                                 *
#*                                                                         *
#*   FreeCAD is distributed in the hope that it will be useful,            *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        * 
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU Lesser General Public License for more details.                   *
#*                                                                         *
#*   You should have received a copy of the GNU Library General Public     *
#*   License along with FreeCAD; if not, write to the Free Software        * 
#*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
#*   USA                                                                   *
#*                                                                         *
#*   Juergen Riegel 2007                                                   *
#***************************************************************************/


class CamDocument:
	"Cam document"
	def Info(self):
		return "Cam document"
		
            
# Get the Parameter Group of this module
ParGrp = App.ParamGet("System parameter:Modules").GetGroup("Cam")

# Set the needed information
ParGrp.SetString("HelpIndex",        "Cam/Help/index.html")
ParGrp.SetString("DocTemplateName",  "Cam")
ParGrp.SetString("DocTemplateScript","TemplCam.py")
ParGrp.SetString("WorkBenchName",    "Cam Design")
ParGrp.SetString("WorkBenchModule",  "CamWorkbench.py")


