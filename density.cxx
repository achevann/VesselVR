#include <vtkCamera.h>
#include <vtkColorTransferFunction.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkNamedColors.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkStructuredPointsReader.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>

int main (int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " ironProt.vtk" << std::endl;
    return EXIT_FAILURE;
  }

// This is a simple volume rendering tutorial that
// uses a vtkFixedPointVolumeRayCastMapper

// TODO: Create the standard renderer, render window
// and interactor

vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();

// TODO: Create the reader for the data

renWin->AddRenderer(ren);
vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
iren->SetRenderWindow(renWin);
vtkSmartPointer<vtkStructuredPointsReader> reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
reader->SetFileName(argv[1]);
reader->Update();

// TODO: Create transfer mapping scalar value to opacity
// GINA: change the transfer function values to change the opacity values at certain voxel densities
vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
opacityTransferFunction->AddPoint(36152.640625, 0.0);
opacityTransferFunction->AddPoint(37485.01171875, 0.5);
opacityTransferFunction->AddPoint(39340.81640625, 1.0);
opacityTransferFunction->AddPoint(39721.49609375, 0.5);
opacityTransferFunction->AddPoint(40482.8515625, 0.0);


// TODO: Create transfer mapping scalar value to color
// GINA: CHANGE RGB Intensity values to change colors
vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
colorTransferFunction->AddRGBPoint(64.0, 1.0, 0.0, 0.0);
colorTransferFunction->AddRGBPoint(128.0, 0.7, 0.0, 0.3);
colorTransferFunction->AddRGBPoint(192.0, 0.0, 1.0, 0.0);
colorTransferFunction->AddRGBPoint(255.0, 0.3, 0.0, 0.7);



// TODO: Create a volume property to describe how the data will look
vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
volumeProperty->SetColor(colorTransferFunction);
volumeProperty->SetScalarOpacity(opacityTransferFunction);
volumeProperty->ShadeOn();
volumeProperty->SetInterpolationTypeToLinear();    // opacity/color values change linearly between  specified scalar values

// TODO: Create the mapper / ray cast function that will render the data
vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper =  vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
volumeMapper->SetInputConnection(reader->GetOutputPort());

// TODO: Create the volume and set its mapper and propery
// to volumeMapper and volumeProperty
vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
volume->SetMapper(volumeMapper);
volume->SetProperty(volumeProperty);

// TODO: Add volume to renderer, set background colors, and start the render loop
ren->AddVolume(volume);
vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
ren->SetBackground(colors->GetColor3d("Wheat").GetData());
renWin->SetSize(600, 600); // sets the size of the render window


renWin->Render();
iren->Start();

  return EXIT_SUCCESS;
}
