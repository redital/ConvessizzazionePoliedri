#ifndef __EIGEN_EXTENSION_H
#define __EIGEN_EXTENSION_H

#include <string>
#include <iostream>

#include "Eigen"
#include "Output.hpp"

using namespace std;
using namespace Eigen;

namespace MainApplication
{
	class EigenExtension;

	class EigenExtension
	{
		private:

		public:
			/// General print of a Eigen vector
			static ostream& PrintVector(ostream& out, const VectorXd& vec);

			/// General print of a Map Eigen vector
			static ostream& PrintVector(ostream& out, const Map<const VectorXd>& vec);

			static const Output::ExitCodes ReadFromBinaryFile(const string& nameFile, VectorXd& dataToRead, const unsigned int& dataSizeToRead = 0, const unsigned int& startingPosition = 0);
			static const Output::ExitCodes WriteToBinaryFile(const string& nameFile, const VectorXd& vec, const unsigned int& dataSizeToWrite = 0, const unsigned int& dataStartingPositionToWrite = 0, const bool& append = false);
			static const Output::ExitCodes ReadFromBinaryFile(const string& nameFile, Map<VectorXd>& dataToRead, const unsigned int& dataSizeToRead = 0, const unsigned int& startingPosition = 0);
			static const Output::ExitCodes WriteToBinaryFile(const string& nameFile, const Map<const VectorXd>& vec, const unsigned int& dataSizeToWrite = 0, const unsigned int& dataStartingPositionToWrite = 0, const bool& append = false);
			static const Output::ExitCodes ReadFromBinaryFile(const string& nameFile, unsigned int& rows, unsigned int& cols, vector<Triplet<double> >& triplets, const unsigned int& startingPosition = 0);
			static const Output::ExitCodes ReadFromBinaryFile(const string& nameFile, SparseMatrix<double, RowMajor>& matrix, const unsigned int& startingPosition = 0);
			static const Output::ExitCodes ReadFromBinaryFile(const string& nameFile, SparseMatrix<double, ColMajor>& matrix, const unsigned int& startingPosition = 0);
			static const Output::ExitCodes WriteToBinaryFile(const string& nameFile, const SparseMatrix<double, RowMajor>& matrix, const UpLoType& matrixType = (UpLoType)0, const bool& append = false);
			static const Output::ExitCodes WriteToBinaryFile(const string& nameFile, const SparseMatrix<double, ColMajor>& matrix, const UpLoType& matrixType = (UpLoType)0, const bool& append = false);
	};
}
#endif // __EIGEN_EXTENSION_H
