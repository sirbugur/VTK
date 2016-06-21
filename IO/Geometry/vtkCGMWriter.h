/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkCGMWriter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkCGMWriter - write polygonal data as a CGM file
// .SECTION Description
// vtkCGMWriter writes CGM (Computer Graphics Metafile) output. CGM is a 2D
// graphics vector format typically used by large plotters. This writer can
// handle vertices, lines, polygons, and triangle strips in any combination.
// Colors are specified either 1) from cell scalars (assumed to be RGB or
// RGBA color specification), 2) from a specified color; or 3) randomly
// assigned colors.
//
// Note: During output of the polygonal data, triangle strips are converted
// to triangles, and polylines to lines. Also, due to limitations in the CGM
// color model, only 256 colors are available to the color palette.

// .SECTION Caveats
// The class vtkImageToPolyDataFilter is convenient for converting a raster
// image into polygons (and color map) suitable for plotting with CGM.

// .SECTION See Also
// vtkPolyDataWriter vtkPointDataToCellData


#ifndef vtkCGMWriter_h
#define vtkCGMWriter_h

#include "vtkIOGeometryModule.h" // For export macro
#include "vtkPolyDataWriter.h"

class vtkViewport;

#define VTK_COLOR_MODE_DEFAULT 0
#define VTK_COLOR_MODE_SPECIFIED_COLOR 1
#define VTK_COLOR_MODE_RANDOM_COLORS 2

class VTKIOGEOMETRY_EXPORT vtkCGMWriter : public vtkPolyDataWriter
{
public:
  // Description:
  // Instantiate with no viewport defined and sorting on. The default
  // resolution is 10,000, and the color mode is set to default.
  static vtkCGMWriter *New();

  vtkTypeMacro(vtkCGMWriter,vtkPolyDataWriter);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Specify a vtkViewport object to be used to transform the vtkPolyData
  // points into 2D coordinates. By default (no vtkViewport specified), the
  // point coordinates are generated by ignoring the z values. If a viewport
  // is defined, then the points are transformed into viewport coordinates.
  virtual void SetViewport(vtkViewport*);
  vtkGetObjectMacro(Viewport, vtkViewport);

  // Description:
  // Turn on/off the sorting of the cells via depth. If enabled, polygonal
  // cells will be sorted from back to front, i.e., a Painter's algorithm
  // sort.
  vtkSetMacro(Sort,int);
  vtkGetMacro(Sort,int);

  // Description:
  // Specify the resolution of the CGM file. This number is used to integerize
  // the maximum coordinate range of the plot file.
  vtkSetClampMacro(Resolution, int, 100, VTK_INT_MAX);
  vtkGetMacro(Resolution, int);

  // Description:
  // Control how output polydata is colored. By default (ColorModeToDefault),
  // if per cell colors are defined (unsigned chars of 1-4 components), then
  // the cells are colored with these values. (If point colors are defined
  // and cell colors are not, you can use vtkPointDataToCellData to convert
  // the point colors to cell colors.) Otherwise, by default, the cells are
  // set to the specified color. If ColorModeToSpecifiedColor is set, then
  // the primitives will all be set to this color. If ColorModeToRandomColors
  // is set, each cell will be randomly assigned a color.
  vtkSetMacro(ColorMode,int);
  vtkGetMacro(ColorMode,int);
  void SetColorModeToDefault() {
    this->SetColorMode(VTK_COLOR_MODE_DEFAULT);};
  void SetColorModeToSpecifiedColor() {
    this->SetColorMode(VTK_COLOR_MODE_SPECIFIED_COLOR);};
  void SetColorModeToRandomColors() {
    this->SetColorMode(VTK_COLOR_MODE_RANDOM_COLORS);};

  // Description:
  // Set/Get the specified color to color the polydata cells. This
  // color is only used when the color mode is set to
  // ColorModeToSpecifiedColor, or ColorModeToDefault is set and no
  // cell colors are specified. The specified color is specified as RGB
  // values ranging from (0,1). (Note: CGM will map this color to the
  // closest color it supports.)
  vtkSetVector3Macro(SpecifiedColor,float);
  vtkGetVectorMacro(SpecifiedColor,float,3);

protected:
  vtkCGMWriter();
  ~vtkCGMWriter();
  void WriteData();

  vtkViewport *Viewport;
  int         ColorMode;
  float       SpecifiedColor[3];
  int         Resolution;
  int         Sort;

private:
  vtkCGMWriter(const vtkCGMWriter&);  // Not implemented.
  void operator=(const vtkCGMWriter&) VTK_DELETE_FUNCTION;
};

#endif

