#include "Eigen"
#include "Input.hpp"
#include "EigenExtension.hpp"

#include "geometryUnitTest.hpp"
#include "UnitTestSummary.hpp"

using namespace std;
using namespace Eigen;
using namespace GeDiM;
using namespace UnitTest;

int main(int argc, char **argv)
{
  /// Set Variables
  double tolerance = 1e-14;

  Input::AddProperty("tolerance", tolerance);
  Input::Initialize(argc, argv);
  Input::GetPropertyValue("tolerance", tolerance);

  /// Run Unit Tests
  Geometry::UnitTest::RunPolyhedronTests(tolerance);
  Output::PrintLine('*');

  /// Print Summary
  UnitTestSummary::PrintSummary();
  Output::PrintLine('*');
}
