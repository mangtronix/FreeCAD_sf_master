/***************************************************************************
 *   Copyright (c) J�rgen Riegel          (juergen.riegel@web.de) 2002     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#include "PreCompiled.h"
#ifndef _PreComp_
#endif


#include <Base/Console.h>
#include <Base/Exception.h>
#include <Base/Unit.h>
#include "FeatureTest.h"
#include "Material.h"
#include "Material.h"

#ifdef _MSC_VER
#pragma warning( disable : 4700 )
#pragma warning( disable : 4723 )
#endif

#define new DEBUG_CLIENTBLOCK
using namespace App;


PROPERTY_SOURCE(App::FeatureTest, App::DocumentObject)

const char* enums[]= {"Zero","One","Two","Three","Four",NULL};
const PropertyIntegerConstraint::Constraints intPercent = {0,100,1};
const PropertyFloatConstraint::Constraints floatPercent = {0.0,100.0,1.0};


FeatureTest::FeatureTest()
{
  ADD_PROPERTY(Integer,(4711)  );
  ADD_PROPERTY(Float  ,(47.11f) );
  ADD_PROPERTY(Bool   ,(true)  );
  ADD_PROPERTY(BoolList,(false));
  ADD_PROPERTY(String ,("4711"));
  ADD_PROPERTY(Path   ,("c:\\temp"));
  ADD_PROPERTY(StringList ,("4711"));

  ADD_PROPERTY(Enum   ,(4));
  Enum.setEnums(enums);
  ADD_PROPERTY(ConstraintInt ,(5));
  ConstraintInt.setConstraints(&intPercent);
  ADD_PROPERTY(ConstraintFloat ,(5.0));
  ConstraintFloat.setConstraints(&floatPercent);

  App::Color c;
  ADD_PROPERTY(Colour      ,(c) );
  ADD_PROPERTY(ColourList  ,(c) );

  ADD_PROPERTY(Distance,(47.11f) );
  ADD_PROPERTY(Angle   ,(3.0f) );

  ADD_PROPERTY(IntegerList,(4711)  );
  ADD_PROPERTY(FloatList  ,(47.11f) );
  
  ADD_PROPERTY(Link     ,(0));
  ADD_PROPERTY(LinkSub,  (0));
  ADD_PROPERTY(LinkList ,(0));

  ADD_PROPERTY(Vector    ,(1.0,2.0,3.0));
  ADD_PROPERTY(VectorList,(3.0,2.0,1.0));
  ADD_PROPERTY(Matrix    ,(Base::Matrix4D(1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0)));
  ADD_PROPERTY(Placement ,(Base::Placement()));
  
  // properties for recompute testing
  static const char* group = "Feature Test";
  ADD_PROPERTY_TYPE(Source1       ,(0),group,Prop_None,"Source for testing links");
  ADD_PROPERTY_TYPE(Source2       ,(0),group,Prop_None,"Source for testing links");
  ADD_PROPERTY_TYPE(SourceN       ,(0),group,Prop_None,"Source for testing links");
  ADD_PROPERTY_TYPE(ExecResult    ,("empty"),group,Prop_None,"Result of the execution");
  ADD_PROPERTY_TYPE(ExceptionType ,(0),group,Prop_None,"The type of exception the execution method throws");
  ADD_PROPERTY_TYPE(ExecCount     ,(0),group,Prop_None,"Number of executions");
  
  // properties with types
  ADD_PROPERTY_TYPE(TypeHidden  ,(4711),group,Prop_Hidden,"An example property which has the type 'Hidden'"  );
  ADD_PROPERTY_TYPE(TypeReadOnly,(4711),group,Prop_ReadOnly ,"An example property which has the type 'ReadOnly'"  );
  ADD_PROPERTY_TYPE(TypeOutput  ,(4711),group,Prop_Output ,"An example property which has the type 'Output'"  );
  ADD_PROPERTY_TYPE(TypeTransient,(4711),group,Prop_Transient ,"An example property which has the type 'Transient'"  );
  ADD_PROPERTY_TYPE(TypeAll     ,(4711),group,(App::PropertyType) (Prop_Output|Prop_ReadOnly |Prop_Hidden ),
      "An example property which has the types 'Output', 'ReadOnly' and 'Hidden'");
 
  ADD_PROPERTY(QuantityLength,(1.0));
  QuantityLength.setUnit(Base::Unit::Length);
  //ADD_PROPERTY(QuantityMass,(1.0));
  //QuantityMass.setUnit(Base::Unit::Mass);
  //ADD_PROPERTY(QuantityAngle,(1.0));
  //QuantityAngle.setUnit(Base::Unit::Angle);

}

FeatureTest::~FeatureTest()
{

}

DocumentObjectExecReturn *FeatureTest::execute(void)
{

  int *i,j;
  float f;
  void *s;

  // Code analyzers may complain about some errors. This can be ignored
  // because this is done on purpose to test the error handling mechanism
  switch(ExceptionType.getValue()) 
  {
    case 0: break;
    case 1: throw "Test Exeption";
    case 2: throw Base::Exception("FeatureTestException::execute(): Testexception");
    case 3: *i=0;printf("%i",*i);break; // seg-vault
    case 4: j=0; printf("%i",1/j); break; // int devision by zero
    case 5: f=0.0; printf("%f",1/f); break; // float devision by zero
    case 6: s = malloc(3600000000ul); free(s); break; // out-of-memory
  }
  
  ExecCount.setValue(ExecCount.getValue() + 1);

  ExecResult.setValue("Exec");

  return DocumentObject::StdReturn;
}


PROPERTY_SOURCE(App::FeatureTestException, App::FeatureTest)


FeatureTestException::FeatureTestException()
{
  ADD_PROPERTY(ExceptionType,(Base::Exception::getClassTypeId().getKey())  );
}

DocumentObjectExecReturn *FeatureTestException::execute(void)
{
  //ExceptionType;

  throw Base::Exception("FeatureTestException::execute(): Testexception  ;-)");

  return 0;
}
