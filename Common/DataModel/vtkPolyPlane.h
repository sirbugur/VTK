/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPolyPlane.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPolyPlane - Implicit function that is generated by extrusion of a polyline along the Z axis
// .SECTION Description
// vtkPolyPlane is, as the name suggests, an extrusion of a vtkPolyLine.
// The extrusion direction is assumed to be the Z vector. It can be used in
// combination with a vtkCutter to cut a dataset with a polyplane.
// vtkPolyPlane is a concrete implementation of the abstract class
// vtkImplicitFunction.
//
// .SECTION ToDo
// Generalize to extrusions along arbitrary directions.

#ifndef vtkPolyPlane_h
#define vtkPolyPlane_h

#include "vtkCommonDataModelModule.h" // For export macro
#include "vtkImplicitFunction.h"

class vtkPolyLine;
class vtkDoubleArray;

class VTKCOMMONDATAMODEL_EXPORT vtkPolyPlane : public vtkImplicitFunction
{
public:
  // Description
  // Construct plane passing through origin and normal to z-axis.
  static vtkPolyPlane *New();

  vtkTypeMacro(vtkPolyPlane,vtkImplicitFunction);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description
  // Evaluate plane equation for point x[3].
  double EvaluateFunction(double x[3]);
  double EvaluateFunction(double x, double y, double z)
    {return this->vtkImplicitFunction::EvaluateFunction(x, y, z); } ;

  // Description
  // Evaluate function gradient at point x[3].
  void EvaluateGradient(double x[3], double g[3]);

  // Description:
  // Set/get point through which plane passes. Plane is defined by point
  // and normal.
  virtual void SetPolyLine( vtkPolyLine * );
  vtkGetObjectMacro( PolyLine, vtkPolyLine );

  // Description:
  // Override GetMTime to include the polyline
  virtual unsigned long GetMTime();

protected:
  vtkPolyPlane();
  ~vtkPolyPlane();

  void ComputeNormals();

  double           ExtrusionDirection[3];
  vtkPolyLine    * PolyLine;
  vtkTimeStamp     NormalComputeTime;
  vtkDoubleArray * Normals;
  vtkIdType        ClosestPlaneIdx;

private:
  vtkPolyPlane(const vtkPolyPlane&);  // Not implemented.
  void operator=(const vtkPolyPlane&) VTK_DELETE_FUNCTION;
};

#endif
