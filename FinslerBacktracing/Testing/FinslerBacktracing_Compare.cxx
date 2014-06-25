// VTK include to write poly-data:
#include <vtkNew.h>
#include <vtkSmartPointer.h>
#include <vtkTrivialProducer.h>
#include <vtkVersion.h>
#include <vtkAlgorithmOutput.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyData.h>
#include <vtkDataArray.h>
#include <vtkPointData.h>

int main(int argc, char **argv)
{
   if(argc < 3){
      std::cerr << "Usage:" << std::endl;
      std::cerr << "testImage, compareImage" << std::endl;
      return -1;
   }
   vtkSmartPointer<vtkXMLPolyDataReader> reader1 = vtkSmartPointer<vtkXMLPolyDataReader>::New();
   vtkSmartPointer<vtkXMLPolyDataReader> reader2 = vtkSmartPointer<vtkXMLPolyDataReader>::New();

   reader1->SetFileName( argv[1] );
   reader2->SetFileName( argv[2] );

   try
   {
      reader1->Update();
      reader2->Update();
   }
   catch(...)
   {
      std::cerr << "Error updating readers: "<< std::endl;
      return EXIT_FAILURE;
   }

   vtkPolyData * poly1 = vtkPolyData::SafeDownCast(reader1->GetOutputPort()->GetProducer()->GetOutputDataObject(
      reader1->GetOutputPort()->GetIndex()));
   vtkPolyData * poly2 = vtkPolyData::SafeDownCast(reader2->GetOutputPort()->GetProducer()->GetOutputDataObject(
      reader2->GetOutputPort()->GetIndex()));

  if (poly1 == 0 || poly2 == 0)
   {
     std::cerr << "Error: poly is 0"<< std::endl;
     return EXIT_FAILURE;
   }

   vtkDataArray *ar1 = poly1->GetPointData()->GetScalars();
   vtkDataArray *ar2 = poly2->GetPointData()->GetScalars();

  if (ar1 == 0 || ar2 == 0)
   {
     std::cerr << "Error: scalar is 0"<< std::endl;
     return EXIT_FAILURE;
   }

   if (poly1->GetNumberOfVerts() != poly2->GetNumberOfVerts())
   {
      std::cerr << "Error in GetNumberOfVerts"<< std::endl;
      return EXIT_FAILURE;
   }

   int n = ar1->GetNumberOfTuples();
   for (int i=0; i< n; i++)
   {
     double *v1 = ar1->GetTuple(i);
     double *v2 = ar2->GetTuple(i);
     double difference = fabs(*v1 - *v2);

     if( difference>1e-9 )
     {
        std::cerr << "Error (" << difference << ") is above tolerance (1e-9)"<< std::endl;
        return EXIT_FAILURE;
     }
   }

   return EXIT_SUCCESS;
}
