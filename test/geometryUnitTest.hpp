#ifndef GEOMETRYUNITTEST_H
#define GEOMETRYUNITTEST_H

#include "Output.hpp"

#include "IPolygon.hpp"
#include "IPolyhedron.hpp"

using namespace MainApplication;

namespace GeDiM
{
  namespace UnitTest
  {
    namespace Geometry
    {
      class UnitTest;

      class UnitTest
      {
        public:
          static void RunAllTests(const double& tolerance);
          static void RunPolygonTests(const double& tolerance);
          static void RunPolyhedronTests(const double& tolerance);
      };

      class ConcavePolygonUnitTest
      {
        protected:
          /// Create Polygon for test one
          static void CreatePolygonTestOne(vector<Vertex>& vertices,  vector<ISegment*>& segments, IPolygon& concavePolygon);
          /// Create Polygon for test two
          static void CreatePolygonTestTwo(vector<Vertex>& vertices,  vector<ISegment*>& segments, IPolygon& concavePolygon);
          /// Create Polygon for test three
          static void CreatePolygonTestThree(vector<Vertex>& vertices, vector<ISegment*>& segments, IPolygon& concavePolygon);
          /// Test the Polygon
          static void TestPolygon(const IPolygon& concavePolygon, const double& tolerance, const string& fatherFunctionName);

        public:
          static void TestOne(const double& tolerance);
          static void TestTwo(const double& tolerance);
          static void TestThree(const double& tolerance);
      };

      class ConcavePolyhedronUnitTest
      {
        protected:
          /// Create Polyhedron for my test
          static void CreatePolyhedronTestZero(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron);
          /// Create Polyhedron for test one
          static void CreatePolyhedronTestOne(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron);
          /// Create Polyhedron for my test
          static void CreatePolyhedronTestTwo(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron);
          /// Create Polyhedron for my test
          static void CreatePolyhedronTestThree(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron);
          /// Create Polyhedron for my test
          static void CreatePolyhedronTestFour(vector<Vertex>& vertices, vector<ISegment*>& segments, vector<IPolygon*>& faces, IPolyhedron& concavePolyhedron);
          /// Test the Polygon
          static void TestPolyhedron(const IPolyhedron& concavePolyhedron, const double& tolerance, const string& fatherFunctionName);

        public:
          static void TestZero(const double& tolerance);
          static void TestOne(const double& tolerance);
          static void TestTwo(const double& tolerance);
          static void TestThree(const double& tolerance);
          static void TestFour(const double& tolerance);
      };
    }
  }
}

#endif // GEOMETRYUNITTEST_H
